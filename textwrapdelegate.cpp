#include "textwrapdelegate.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QPainter>
#include <QSize>
#include <QTextDocument>
#include <QTextEdit>
TextWrapDelegate::TextWrapDelegate(QObject* parent) : QStyledItemDelegate(parent) {
}

QSize TextWrapDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
    const QString content = index.data().toString();
    QImage image(content);
    if (!image.isNull()) {
        // 获取图片路径，确保它属于 "images" 文件夹
        QFileInfo fileInfo(content);

        // 检查文件是否属于当前目录下的 "images" 文件夹
        QDir imageDir(QCoreApplication::applicationDirPath() + "/images");
        if (fileInfo.absolutePath() == imageDir.absolutePath()) {
            return QSize(150, 200);  // 增加单元格大小，如 150x150
        }
    }
    QTextDocument doc;
    doc.setDefaultFont(option.font);
    doc.setPlainText(content);
    doc.setTextWidth(option.rect.width());  // 设置最大宽度

    // 获取文本高度
    QSize size = QSize(option.rect.width(), doc.size().height());
    size.setWidth(qMax(size.width(), 580));

    // 日志输出建议的尺寸
    // qDebug() << "Size hint for text:" << text << "is" << size;

    return size;
}

void TextWrapDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());  // 设置选中时的背景颜色
    } else {
        painter->fillRect(option.rect, option.palette.window());  // 设置默认背景颜色
    }
    // 获取内容
    const QString content = index.data().toString();
    // 尝试加载图片
    QImage image(content);
    if (!image.isNull()) {
        // 获取图片路径，确保它属于 "images" 文件夹
        QFileInfo fileInfo(content);

        // 检查文件是否属于当前目录下的 "images" 文件夹
        QDir imageDir(QCoreApplication::applicationDirPath() + "/images");
        if (fileInfo.absolutePath() == imageDir.absolutePath()) {
            // 计算缩放后的图片尺寸，保持宽高比
            QSize imageSize = image.size();
            QSize scaledSize = imageSize.scaled(option.rect.size(), Qt::KeepAspectRatio);

            // 计算图片绘制区域，使图片居中显示
            QRect imageRect = QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, scaledSize, option.rect);

            // 在单元格中绘制缩略图
            painter->drawImage(imageRect, image);
            return;
        }
    }
    // 是否为文件类型
    // 检查内容是否为文件路径
    QFileInfo fileInfo(content);
    if (fileInfo.exists() && fileInfo.isFile()) {
        // 获取文件图标
        QFileIconProvider iconProvider;
        QIcon fileIcon = iconProvider.icon(fileInfo);

        // 计算图标绘制区域
        QRect iconRect(option.rect.x() + 5, option.rect.y() + (option.rect.height() - 16) / 2, 16, 16);

        // 绘制图标
        fileIcon.paint(painter, iconRect);

        // 绘制文件名
        QRect textRect(iconRect.right() + 5, option.rect.y(), option.rect.width() - iconRect.width() - 10,
                       option.rect.height());
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, fileInfo.fileName());
        return;
    }

    // 创建一个文本文档来处理换行
    QTextDocument doc;
    doc.setDefaultFont(option.font);
    doc.setPlainText(content);
    doc.setTextWidth(option.rect.width());  // 设置最大宽度

    // 绘制文本
    painter->save();
    painter->translate(option.rect.topLeft());
    doc.drawContents(painter);
    painter->restore();

    // 日志输出绘制区域的尺寸
    // qDebug() << "Draw area size:" << option.rect.size();
}
