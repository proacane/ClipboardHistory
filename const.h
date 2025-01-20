#ifndef CONST_H
#define CONST_H
#include<QString>
// 剪切板获取的类型
enum Type{
    _ALL = 0,
    _TEXT = 1,
    _IMAGE = 2,
    _FILE = 3
};

static QString ConfigPath = "D:/ClipboardHistory/config";
// 注册表自启路径
#define AUTO_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#endif // CONST_H
