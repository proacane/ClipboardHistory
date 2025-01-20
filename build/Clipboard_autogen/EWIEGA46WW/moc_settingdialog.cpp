/****************************************************************************
** Meta object code from reading C++ file 'settingdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../settingdialog.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSSettingDialogENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSettingDialogENDCLASS = QtMocHelpers::stringData(
    "SettingDialog",
    "updateShortCutInfo",
    "",
    "autoRun",
    "flag",
    "limitTotal",
    "on_short_open_editingFinished",
    "on_chk_auto_run_stateChanged",
    "arg1",
    "on_image_count_valueChanged",
    "on_total_count_valueChanged"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSettingDialogENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[14];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[5];
    char stringdata5[11];
    char stringdata6[30];
    char stringdata7[29];
    char stringdata8[5];
    char stringdata9[28];
    char stringdata10[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSettingDialogENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSettingDialogENDCLASS_t qt_meta_stringdata_CLASSSettingDialogENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "SettingDialog"
        QT_MOC_LITERAL(14, 18),  // "updateShortCutInfo"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 7),  // "autoRun"
        QT_MOC_LITERAL(42, 4),  // "flag"
        QT_MOC_LITERAL(47, 10),  // "limitTotal"
        QT_MOC_LITERAL(58, 29),  // "on_short_open_editingFinished"
        QT_MOC_LITERAL(88, 28),  // "on_chk_auto_run_stateChanged"
        QT_MOC_LITERAL(117, 4),  // "arg1"
        QT_MOC_LITERAL(122, 27),  // "on_image_count_valueChanged"
        QT_MOC_LITERAL(150, 27)   // "on_total_count_valueChanged"
    },
    "SettingDialog",
    "updateShortCutInfo",
    "",
    "autoRun",
    "flag",
    "limitTotal",
    "on_short_open_editingFinished",
    "on_chk_auto_run_stateChanged",
    "arg1",
    "on_image_count_valueChanged",
    "on_total_count_valueChanged"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSettingDialogENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    1 /* Public */,
       3,    1,   57,    2, 0x06,    2 /* Public */,
       5,    0,   60,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   61,    2, 0x08,    5 /* Private */,
       7,    1,   62,    2, 0x08,    6 /* Private */,
       9,    1,   65,    2, 0x08,    8 /* Private */,
      10,    1,   68,    2, 0x08,   10 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

Q_CONSTINIT const QMetaObject SettingDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSSettingDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSettingDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSettingDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SettingDialog, std::true_type>,
        // method 'updateShortCutInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'autoRun'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'limitTotal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_short_open_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_chk_auto_run_stateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_image_count_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_total_count_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void SettingDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateShortCutInfo(); break;
        case 1: _t->autoRun((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->limitTotal(); break;
        case 3: _t->on_short_open_editingFinished(); break;
        case 4: _t->on_chk_auto_run_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->on_image_count_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->on_total_count_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingDialog::*)();
            if (_t _q_method = &SettingDialog::updateShortCutInfo; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingDialog::*)(bool );
            if (_t _q_method = &SettingDialog::autoRun; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SettingDialog::*)();
            if (_t _q_method = &SettingDialog::limitTotal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *SettingDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSettingDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SettingDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SettingDialog::updateShortCutInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SettingDialog::autoRun(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SettingDialog::limitTotal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
