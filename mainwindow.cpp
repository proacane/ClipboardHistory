#include "mainwindow.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDir>
#include <QFileInfo>
#include <QKeyEvent>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QMimeData>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollBar>
#include <QTimer>

#include "./ui_mainwindow.h"
#include "configmgr.h"
#include "logmanager.h"
#include "quitmessagebox.h"
#include "textwrapdelegate.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), _settings_dialog(new SettingDialog(this)), _is_open(true),
    _cur_type(Type::_ALL) {
    ui->setupUi(this);
    setWindowTitle("Clipboard history");
    // 将窗口移动到屏幕中央
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    // 单机单元格复制
    connect(ui->clipboardHistoryTable, &QTableView::clicked, this, &MainWindow::clipboardHistoryTableClicked);
    // 显示剪切板历史的视图
    model = new QSqlQueryModel(this);
    ui->clipboardHistoryTable->setWordWrap(true);
    ui->clipboardHistoryTable->setSizeAdjustPolicy(QAbstractItemView::AdjustToContents);

    // 创建数据库和剪切板管理器
    dbHandler = new DatabaseHandler();
    clipboardManager = new ClipboardManager(QApplication::clipboard(), dbHandler, this);
    // 启动时加载剪切板记录
    clipboardManager->loadClipboardHistory();

    // 初始化 ui 界面
    TextWrapDelegate* delegate = new TextWrapDelegate(ui->clipboardHistoryTable);
    ui->clipboardHistoryTable->setItemDelegateForColumn(1, delegate);
    model->setQuery(dbHandler->getHistory());
    model->setHeaderData(0, Qt::Horizontal, tr("类型"));
    model->setHeaderData(1, Qt::Horizontal, tr("内容"));
    ui->clipboardHistoryTable->setModel(model);
    ui->clipboardHistoryTable->hideColumn(0);
    // ui->clipboardHistoryTable->hideColumn(1);
    // ui->clipboardHistoryTable->hideColumn(3);

    ui->clipboardHistoryTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->clipboardHistoryTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->clipboardHistoryTable->resizeColumnsToContents();
    ui->clipboardHistoryTable->resizeRowsToContents();
    ui->clipboardHistoryTable->setColumnWidth(1, this->width());
    // 隐藏行头和列头
    ui->clipboardHistoryTable->verticalHeader()->hide();
    ui->clipboardHistoryTable->horizontalHeader()->hide();
    // 滚轮平滑滚动
    ui->clipboardHistoryTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);  // 设置为像素移动
    QScrollBar* a = ui->clipboardHistoryTable->verticalScrollBar();  // 获取到tablewidget的滚动条
    a->setSingleStep(15);                                            // 设置单步，值越小，下滑越慢

    // 连接剪切板更新信号，以刷新界面
    connect(clipboardManager, &ClipboardManager::clipboardHistoryUpdated, this, &MainWindow::updateClipboardHistoryUI);
    // 更新打开软件的快捷键
    connect(_settings_dialog, &SettingDialog::updateShortCutInfo, this, &MainWindow::updateShortCut);
    // 开机自启
    connect(_settings_dialog, &SettingDialog::autoRun, this, &MainWindow::setProcessAutoRun);
    // 限制总条数
    connect(_settings_dialog, &SettingDialog::limitTotal, this, &MainWindow::updateClipboardHistoryUI);
    // QHotkey捕获全局快捷键
    _open_shortcut =
        new QHotkey(QKeySequence(ConfigMgr::getInstance().value(ConfigGroup::Shortcuts, "open")), true, this);
    // 动态读取快捷键来显示软件
    connect(_open_shortcut, &QHotkey::activated, this, [=]() {
        // 打开状态就关闭
        if (_is_open) {
            this->hide();
            _is_open = false;
            return;
        }
        // 取消最小化状态并恢复到正常大小
        this->showNormal();
        // 将窗口移动到屏幕中央
        QRect screenGeometry = QApplication::primaryScreen()->geometry();
        int x = (screenGeometry.width() - this->width()) / 2;
        int y = (screenGeometry.height() - this->height()) / 2;
        this->move(x, y);
        // 焦点置于窗口上
        this->raise();
        this->activateWindow();
        _is_open = true;
    });

    QMenu* menu = new QMenu("Clipboard");
    QAction* actionOpen = new QAction("打开");
    QAction* actionSetting = new QAction("设置");
    QAction* actionClear = new QAction("清除缓存");
    QAction* actionClose = new QAction("关闭");
    menu->addAction(actionOpen);
    menu->addAction(actionSetting);
    menu->addAction(actionClear);
    menu->addAction(actionClose);
    // 托管图标
    systemIcon = new QSystemTrayIcon(QIcon(tr(":/res/logo.png")), this);
    systemIcon->setContextMenu(menu);
    // TODO tooltip 不显示
    systemIcon->setToolTip("ClipBoard software");
    // 点击图标显示软件
    connect(systemIcon, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Context) {
            // 右键点击，不执行任何操作，直接返回
            // qDebug() << "Right click!";
            return;
        }

        // 处理其他类型的激活，比如左键单击、双击等
        if (reason == QSystemTrayIcon::Trigger) {
            // 左键单击
            // qDebug() << "Left click!";
        } else if (reason == QSystemTrayIcon::DoubleClick) {
            // 双击
            // qDebug() << "Double click!";
        } else if (reason == QSystemTrayIcon::MiddleClick) {
            // 中键点击
            // qDebug() << "Middle click!";
        }
        // 取消最小化状态并恢复到正常大小
        this->showNormal();

        // 将窗口移动到屏幕中央
        QRect screenGeometry = QApplication::primaryScreen()->geometry();
        int x = (screenGeometry.width() - this->width()) / 2;
        int y = (screenGeometry.height() - this->height()) / 2;
        this->move(x, y);

        // 焦点置于窗口上
        this->raise();
        this->activateWindow();
        _is_open = true;
    });

    connect(actionClose, &QAction::triggered, this, &MainWindow::close);
    connect(actionOpen, &QAction::triggered, this, [this] {
        _is_open = true;
        show();
    });
    connect(actionSetting, &QAction::triggered, _settings_dialog, [this]() {
        _settings_dialog->setModal(true);
        _settings_dialog->show();
    });
    // 清除缓存
    connect(actionClear, &QAction::triggered, this, &MainWindow::clearHistory);
    systemIcon->show();
    // 配置文件添加验证字段，如果是第一次打开就弹出设置窗口
    QString first_time = ConfigMgr::getInstance().value(ConfigGroup::FirstTime, "FirstTime", "error");
    qDebug() << "First time is: " << first_time;
    if (first_time == "true") {
        LogManager::getInstance().writeLog(LogManager::LogType::Info, "First time open this app");
        _settings_dialog->show();
        ConfigMgr::getInstance().setValue(ConfigGroup::FirstTime, "flag", "false");
    } else if (first_time != "false") {
        LogManager::getInstance().writeLog(LogManager::LogType::Warning,
                                           "failed to open config FirstTime->flag: " + first_time);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateClipboardHistoryUI() {
    qDebug() << "Update ui---";
    // 更新界面展示
    // 更新 ui 界面
    if (_cur_type == Type::_ALL) {
        model->setQuery(dbHandler->getHistory());
    }else{
        model->setQuery(dbHandler->getHistory(_cur_type));
    }
}

void MainWindow::updateShortCut() {
    qDebug() << "Update shortcut, new soft open short cut is "
             << ConfigMgr::getInstance().value(ConfigGroup::Shortcuts, "open");
    LogManager::getInstance().writeLog(LogManager::LogType::Info,
                                       "Update shortcut, new soft open short cut is " +
                                           ConfigMgr::getInstance().value(ConfigGroup::Shortcuts, "open"));
    _open_shortcut->resetShortcut();
    _open_shortcut->setShortcut(QKeySequence(ConfigMgr::getInstance().value(ConfigGroup::Shortcuts, "open")), true);
}

void MainWindow::closeEvent(QCloseEvent* event) {  // 创建自定义弹窗
    QuitMessageBox msg_box;
    connect(&msg_box, &QuitMessageBox::minimized, this, &MainWindow::hide);
    connect(&msg_box, &QuitMessageBox::quit, qApp, &QApplication::quit);
    QRect mainWindowGeometry = this->geometry();  // 获取主窗口的几何信息
    int x = mainWindowGeometry.x() + (mainWindowGeometry.width() - msg_box.width()) / 2;
    int y = mainWindowGeometry.y() + (mainWindowGeometry.height() - msg_box.height()) / 2;
    msg_box.setModal(true);
    msg_box.move(x, y);
    msg_box.exec();
    if (msg_box.result() == QDialog::Accepted) {
        // 用户点击了确定按钮，但具体的动作已经在信号槽中处理了
    } else {
        // 用户点击了关闭按钮或取消按钮，忽略关闭事件
        event->ignore();
    }
}

void MainWindow::clipboardHistoryTableClicked(const QModelIndex& index) {
    // 单击单元格进行复制
    qDebug() << "---Clicked content";
    // 获取选中单元格的数据
    QString content = model->data(index).toString();

    // 获取对应行的 `type` 字段的值
    Type type = static_cast<Type>(model->data(model->index(index.row(), 1)).toInt());

    clipboardManager->setContext(type, content);
    qDebug() << "copied to clipboard:" << content << "Type: " << type;
    LogManager::getInstance().writeLog(LogManager::LogType::Info, "Copy message is " + content);

    // 创建 QLabel 显示提示框
    QLabel* label = new QLabel("已复制到剪切板", this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("background-color: #333; color: white; padding: 10px; border-radius: 5px;");

    // 设置 QLabel 的大小和位置（比如设置到窗口的中央）
    label->resize(150, 50);
    QRect mainWindowGeometry = this->geometry();  // 获取主窗口的几何信息
    int x = mainWindowGeometry.x() + (mainWindowGeometry.width() - label->width()) / 2;
    int y = mainWindowGeometry.y() + (mainWindowGeometry.height() - label->height()) / 2;

    label->move(x, y);

    // 设置窗口属性：不可点击，最上层，且无边框
    label->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);  // 使其不可点击
    label->show();

    QTimer::singleShot(500, this, [=]() {
        // 使用 QPropertyAnimation 实现淡出效果
        QPropertyAnimation* animation = new QPropertyAnimation(label, "windowOpacity");
        animation->setDuration(1000);  // 持续 1 秒
        animation->setStartValue(1.0);
        animation->setEndValue(0.0);
        connect(animation, &QPropertyAnimation::finished, label, &QLabel::deleteLater);  // 动画结束后删除 QLabel
        animation->start();
    });
}

void MainWindow::clearHistory() {
    QRect mainWindowGeometry = this->geometry();  // 获取主窗口的几何信息
    bool is_delete = dbHandler->clearHistory(mainWindowGeometry);
    if (is_delete) {
        LogManager::getInstance().writeLog(LogManager::LogType::Info, "remove all records in database");
        // 显示所有数据
        updateClipboardHistoryUI();
    }
}

void MainWindow::setProcessAutoRun(bool flag) {
    QSettings settings(AUTO_RUN, QSettings::NativeFormat);

    // 以程序名称作为注册表中的键,根据键获取对应的值（程序路径）
    QString appPath = QApplication::applicationFilePath();
    LogManager::getInstance().writeLog(LogManager::LogType::Info, "App path is " + appPath);
    QFileInfo fInfo(appPath);
    QString name = fInfo.baseName();  // 键-名称

    // 如果注册表中的路径和当前程序路径不一样，则表示没有设置自启动或本自启动程序已经更换了路径
    QString oldPath = settings.value(name).toString();    // 获取目前的值-绝对路劲
    QString newPath = QDir::toNativeSeparators(appPath);  // toNativeSeparators函数将"/"替换为"\"
    if (flag) {
        if (oldPath != newPath) {
            settings.setValue(name, newPath);
            LogManager::getInstance().writeLog(LogManager::LogType::Info, "Set app auto run");
        }
    } else {
        settings.remove(name);
        LogManager::getInstance().writeLog(LogManager::LogType::Info, "Remove app auto run");
    }
}

void MainWindow::changeEvent(QEvent* event) {
    // 最小化到托盘
    if (event->type() == QEvent::WindowStateChange) {
        if (isMinimized()) {
            QTimer::singleShot(0, this, &MainWindow::hide);  // 延迟隐藏窗口
            _is_open = false;
        }
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::on_btn_all_toggled(bool checked) {
    if (checked) {
        model->setQuery(dbHandler->getHistory());
        _cur_type = Type::_ALL;
    }
}

void MainWindow::on_btn_text_toggled(bool checked) {
    if (checked) {
        model->setQuery(dbHandler->getHistory(Type::_TEXT));
        _cur_type = Type::_TEXT;
    }
}

void MainWindow::on_btn_image_toggled(bool checked) {
    if (checked) {
        model->setQuery(dbHandler->getHistory(Type::_IMAGE));
        _cur_type = Type::_IMAGE;
    }
}

void MainWindow::on_btn_file_toggled(bool checked) {
    if (checked) {
        model->setQuery(dbHandler->getHistory(Type::_FILE));
        _cur_type = Type::_FILE;
    }
}
