#ifndef CONFIGMGR_H
#define CONFIGMGR_H
#include <QMap>
#include <QSettings>
#include <QString>
// 枚举类，表示不同的 group 类型
enum class ConfigGroup { Shortcuts, AutoRun, FirstTime,RecordCount,Preferences, NetworkSettings };

class ConfigMgr {
  public:
    static ConfigMgr& getInstance();
    ConfigMgr(const ConfigMgr&) = delete;
    ConfigMgr& operator=(const ConfigMgr&) = delete;
    ~ConfigMgr();

    // 获取配置值
    QString value(ConfigGroup group, const QString& key, const QString& defaultValue = QString());

    // 设置配置值
    void setValue(ConfigGroup group, const QString& key, const QString& value);

  private:
    ConfigMgr();
    QSettings _settings;
    QMap<QString, QString> _cache;  // 缓存配置值，提高性能

    // 创建一个 QMap，将枚举值和 group 字符串进行映射
    QMap<ConfigGroup, QString> groupMap = {{ConfigGroup::Shortcuts, "Shortcuts"},
                                           {ConfigGroup::AutoRun,"AutoRun"},
                                           {ConfigGroup::FirstTime,"FirstTime"},
                                           {ConfigGroup::RecordCount,"RecordCount"},
                                           {ConfigGroup::Preferences, "Preferences"},
                                           {ConfigGroup::NetworkSettings, "NetworkSettings"}};
};

#endif  // CONFIGMGR_H
