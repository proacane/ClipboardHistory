#include "configmgr.h"

#include "logmanager.h"

#include <QCoreApplication>
#include"const.h"
ConfigMgr& ConfigMgr::getInstance() {
    static ConfigMgr instance;
    return instance;
}


ConfigMgr::ConfigMgr() : _settings([&]() -> QString {
        QDir dir(ConfigPath);
        if (!dir.exists()) {
            if (!dir.mkpath(ConfigPath)) {
                qCritical() << "Failed to create configuration directory:" << ConfigPath;
            }
        }
        return ConfigPath + "/config.ini";
    }(), QSettings::IniFormat) {

    _settings.beginGroup("Shortcuts");

    _cache["open"] = _settings.value("open", "error").toString();
    // 快捷键
    qDebug() << "Loaded shortcut: open = " << _cache["open"];
    _settings.endGroup();

    _settings.beginGroup("AutoRun");
    _settings.setValue("flag",false);
    _cache["autorun"] = _settings.value("flag", "error").toString();

    _settings.endGroup();

    _settings.beginGroup("FirstTime");
    _settings.setValue("flag",true);
    _cache["FirstTime"] = _settings.value("flag", "error").toString();

    _settings.endGroup();

    _settings.beginGroup("RecordCount");
    _settings.setValue("imageCount",10);
    _cache["imageCount"]= _settings.value("imageCount",10).toString();

    _cache["totalCount"] = _settings.value("totalCount",50).toString();
    _settings.setValue("totalCount",50);

    _settings.endGroup();

    _settings.beginGroup("DataPath");
    _settings.setValue("path",ConfigPath);
    _cache["dataPath"] = _settings.value("path").toString();
    _settings.endGroup();
    qDebug()<<"Data path: " <<_cache["dataPath"];


    for (auto it = _cache.cbegin(); it != _cache.cend(); ++it) {
         qDebug() << "Key:" << it.key() << ", Value:" << it.value();
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
