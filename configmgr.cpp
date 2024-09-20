#include "configmgr.h"

#include "logmanager.h"

#include <QCoreApplication>

ConfigMgr& ConfigMgr::getInstance() {
    static ConfigMgr instance;
    return instance;
}

ConfigMgr::ConfigMgr() : _settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat) {
    _settings.beginGroup("Shortcuts");
    _cache["open"] = _settings.value("open", "error").toString();
    // _cache["theme"] = _settings.value("theme", "light").toString();
    qDebug() << "Loaded shortcut: open = " << _cache["open"];
    _settings.endGroup();

    _settings.beginGroup("AutoRun");
    _cache["autorun"] = _settings.value("flag", "error").toString();
    qDebug()<<"Auto run: "<<_cache["autorun"];
    _settings.endGroup();

    _settings.beginGroup("FirstTime");
    _cache["FirstTime"] = _settings.value("flag", "error").toString();
    qDebug()<<"First time: "<<_cache["FirstTime"];
    _settings.endGroup();

    _settings.beginGroup("RecordCount");
    _cache["imageCount"]= _settings.value("imageCount",10).toString();
    qDebug()<<"Image max count: "<<_cache["imageCount"];
    _cache["totalCount"] = _settings.value("totalCount",50).toString();
    qDebug()<<"Total max count: "<<_cache["totalCount"];
    _settings.endGroup();
    QMap<QString, QString>::const_iterator it;
    for (it = _cache.constBegin(); it != _cache.constEnd(); ++it) {
        LogManager::getInstance().writeLog(LogManager::LogType::Info, "Key: " + it.key() + " Value: " + it.value());
    }
}

ConfigMgr::~ConfigMgr() {
    qInfo() << "ConfigMgr destructor";
}

QString ConfigMgr::value(ConfigGroup group, const QString& key, const QString& defaultValue) {
    // qDebug() << "---Reading value for key: " << key;
    // 先从缓存中查找
    if (_cache.contains(key)) {
        // qDebug()<<"Value is "<<_cache[key];
        return _cache[key];
    }
    QString groupStr = groupMap.value(group);
    _settings.beginGroup(groupStr);
    QVariant value = _settings.value(key, defaultValue);
    _cache[key] = value.toString();
    _settings.endGroup();
    return value.toString();
}

void ConfigMgr::setValue(ConfigGroup group, const QString& key, const QString& value) {
    // qDebug() << "---Setting value for key: " << key << " to " << value;
    _settings.beginGroup(groupMap.value(group));
    _settings.setValue(key, value);
    _settings.endGroup();
    _cache[key] = value;
}
