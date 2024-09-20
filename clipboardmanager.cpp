#include "clipboardmanager.h"

#include <QBuffer>
#include <QCryptographicHash>
#include <QDebug>
#include <QDir>
#include <QImage>
#include <QMimeData>
#include <QObject>
#include <QUrl>
#include <QUuid>

#include "configmgr.h"
#include "logmanager.h"

ClipboardManager::ClipboardManager(QClipboard* clipboard, DatabaseHandler* dbHandler, QObject* parent) :
    QObject(parent), m_clipboard(clipboard), m_dbHandler(dbHandler), _suppress_dataChangedSignal(false) {
    // 剪切板内容变化就触发
    connect(m_clipboard, &QClipboard::dataChanged, this, &ClipboardManager::onClipboardDataChanged);
}

void ClipboardManager::loadClipboardHistory() {
    qDebug() << "Load all records";
    m_dbHandler->getHistory();
}

void ClipboardManager::setContext(Type t, const QString& content) {
    _suppress_dataChangedSignal = true;

    // 设置剪切板内容
    if (t == Type::_FILE) {
        QList<QUrl> copyFile;
        QUrl url = QUrl::fromLocalFile(content);
        qDebug() << "Url is " << url.toString();
        if (url.isValid()) {
            qDebug() << "URL is valid:" << url.toString();
            copyFile.push_back(url);
        } else {
            qDebug() << "URL is not valid";
        }
        QMimeData* data = new QMimeData;
        data->setUrls(copyFile);
        m_clipboard->setMimeData(data);
    } else if (t == Type::_TEXT) {
        m_clipboard->setText(content);
    } else if (t == Type::_IMAGE) {
        m_clipboard->setImage(QImage(content));
    }
}

void ClipboardManager::onClipboardDataChanged() {
    if (_suppress_dataChangedSignal) {
        _suppress_dataChangedSignal = false;  // 重置标志
        return;                               // 不处理
    }
    // 保存当前剪切板内容到数据库
    saveCurrentClipboardContent();

    // 发射信号通知主窗口刷新界面
    emit clipboardHistoryUpdated();
}

QString ClipboardManager::saveImageToFile(const QImage& image) {
    QDir dir(QCoreApplication::applicationDirPath() + "/images");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    cleanupOldImages();
    // 计算图片的哈希值，用作唯一标识
    QByteArray imageBytes;
    QBuffer buffer(&imageBytes);
    image.save(&buffer, "PNG");  // 将图片保存到字节数组中
    QByteArray hash = QCryptographicHash::hash(imageBytes, QCryptographicHash::Sha256).toHex();

    // 使用哈希值作为文件名来存储图片
    QString path = dir.path() + "/image_" + QString(hash) + ".png";

    // 检查图片文件是否已经存在
    if (QFile::exists(path)) {
        qDebug() << "Image already exists, skipping save:" << path;
        return "";
    } else {
        if (!image.save(path)) {
            qDebug() << "Failed to save image:" << path;
            LogManager::getInstance().writeLog(LogManager::LogType::Warning, "Failed to remove image file: " + path);
            return "";
        } else {
            qDebug() << "Image saved to:" << path;
        }
    }
    return path;
}

void ClipboardManager::saveCurrentClipboardContent() {
    // 获取剪切板内容
    const QMimeData* mimeData = m_clipboard->mimeData();
    qDebug() << "MIME formats:" << mimeData->formats();
    // 先检查图片
    if (mimeData->hasImage()) {
        QImage image = qvariant_cast<QImage>(mimeData->imageData());
        qDebug() << "Image copied, size:" << image.size();
        // 将图片保存到文件
        QString imagePath = saveImageToFile(image);
        if (!imagePath.isEmpty()) {
            m_dbHandler->insertRecord(Type::_IMAGE, imagePath);
        }
    }
    // 然后检查文件
    else if (mimeData->hasUrls()) {
        QList<QUrl> urls = mimeData->urls();
        foreach (const QUrl& url, urls) {
            // 每个文件的路径
            qDebug() << "Url is " << url.toString();
            QString filePath = url.toLocalFile();
            qDebug() << "File copied:" << filePath;
            if (!filePath.isEmpty()) {
                m_dbHandler->insertRecord(Type::_FILE, filePath);
            }
        }
    }
    // 最后检查文本
    else if (mimeData->hasText()) {
        QString text = mimeData->text();
        qDebug() << "Text copied:" << text;
        m_dbHandler->insertRecord(Type::_TEXT, text);
    }
}

void ClipboardManager::cleanupOldImages() {
    //  动态自定义图片记录条数
    int maxImages = ConfigMgr::getInstance().value(ConfigGroup::RecordCount, "imageCount").toInt();

    // 查询数据库中保存的图片记录数量
    int imageCount = m_dbHandler->getImageRecordCount();
    if (imageCount > maxImages) {
        QStringList oldImagePaths = m_dbHandler->getOldestImagePaths(imageCount - maxImages);
        foreach (const QString& imagePath, oldImagePaths) {
            if (QFile::remove(imagePath)) {            // 删除图片文件
                m_dbHandler->deleteRecord(imagePath);  // 从数据库中删除记录
            } else {
                LogManager::getInstance().writeLog(LogManager::LogType::Warning,
                                                   "Failed to remove image file: " + imagePath);
                qDebug() << "Failed to remove image file:" << imagePath;
            }
        }
    }
}
