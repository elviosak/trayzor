/****************************************************************************
** Meta object code from reading C++ file 'maintray.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/maintray.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maintray.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainTray_t {
    QByteArrayData data[31];
    char stringdata0[367];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainTray_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainTray_t qt_meta_stringdata_MainTray = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MainTray"
QT_MOC_LITERAL(1, 9, 11), // "initWindows"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 15), // "initConnections"
QT_MOC_LITERAL(4, 38, 11), // "iconClicked"
QT_MOC_LITERAL(5, 50, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(6, 84, 6), // "reason"
QT_MOC_LITERAL(7, 91, 12), // "closedWidget"
QT_MOC_LITERAL(8, 104, 15), // "showSettingsBox"
QT_MOC_LITERAL(9, 120, 14), // "reloadSettings"
QT_MOC_LITERAL(10, 135, 13), // "reloadWindows"
QT_MOC_LITERAL(11, 149, 11), // "removeGroup"
QT_MOC_LITERAL(12, 161, 2), // "cl"
QT_MOC_LITERAL(13, 164, 11), // "setMainIcon"
QT_MOC_LITERAL(14, 176, 11), // "clickGlobal"
QT_MOC_LITERAL(15, 188, 13), // "onWindowAdded"
QT_MOC_LITERAL(16, 202, 3), // "WId"
QT_MOC_LITERAL(17, 206, 1), // "w"
QT_MOC_LITERAL(18, 208, 15), // "onWindowRemoved"
QT_MOC_LITERAL(19, 224, 21), // "onActiveWindowChanged"
QT_MOC_LITERAL(20, 246, 12), // "acceptWindow"
QT_MOC_LITERAL(21, 259, 6), // "window"
QT_MOC_LITERAL(22, 266, 15), // "onWindowChanged"
QT_MOC_LITERAL(23, 282, 15), // "NET::Properties"
QT_MOC_LITERAL(24, 298, 4), // "prop"
QT_MOC_LITERAL(25, 303, 16), // "NET::Properties2"
QT_MOC_LITERAL(26, 320, 5), // "prop2"
QT_MOC_LITERAL(27, 326, 9), // "togglePin"
QT_MOC_LITERAL(28, 336, 7), // "checked"
QT_MOC_LITERAL(29, 344, 12), // "removeFilter"
QT_MOC_LITERAL(30, 357, 9) // "setFilter"

    },
    "MainTray\0initWindows\0\0initConnections\0"
    "iconClicked\0QSystemTrayIcon::ActivationReason\0"
    "reason\0closedWidget\0showSettingsBox\0"
    "reloadSettings\0reloadWindows\0removeGroup\0"
    "cl\0setMainIcon\0clickGlobal\0onWindowAdded\0"
    "WId\0w\0onWindowRemoved\0onActiveWindowChanged\0"
    "acceptWindow\0window\0onWindowChanged\0"
    "NET::Properties\0prop\0NET::Properties2\0"
    "prop2\0togglePin\0checked\0removeFilter\0"
    "setFilter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainTray[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x0a /* Public */,
       3,    0,  105,    2, 0x0a /* Public */,
       4,    1,  106,    2, 0x0a /* Public */,
       7,    0,  109,    2, 0x0a /* Public */,
       8,    0,  110,    2, 0x0a /* Public */,
       9,    0,  111,    2, 0x0a /* Public */,
      10,    0,  112,    2, 0x0a /* Public */,
      11,    1,  113,    2, 0x0a /* Public */,
      13,    0,  116,    2, 0x0a /* Public */,
      14,    0,  117,    2, 0x0a /* Public */,
      15,    1,  118,    2, 0x0a /* Public */,
      18,    1,  121,    2, 0x0a /* Public */,
      19,    1,  124,    2, 0x0a /* Public */,
      20,    1,  127,    2, 0x0a /* Public */,
      22,    3,  130,    2, 0x0a /* Public */,
      27,    2,  137,    2, 0x0a /* Public */,
      29,    1,  142,    2, 0x0a /* Public */,
      30,    1,  145,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Bool, 0x80000000 | 16,   21,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 23, 0x80000000 | 25,   17,   24,   26,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   28,   12,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void MainTray::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainTray *_t = static_cast<MainTray *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initWindows(); break;
        case 1: _t->initConnections(); break;
        case 2: _t->iconClicked((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 3: _t->closedWidget(); break;
        case 4: _t->showSettingsBox(); break;
        case 5: _t->reloadSettings(); break;
        case 6: _t->reloadWindows(); break;
        case 7: _t->removeGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setMainIcon(); break;
        case 9: _t->clickGlobal(); break;
        case 10: _t->onWindowAdded((*reinterpret_cast< WId(*)>(_a[1]))); break;
        case 11: _t->onWindowRemoved((*reinterpret_cast< WId(*)>(_a[1]))); break;
        case 12: _t->onActiveWindowChanged((*reinterpret_cast< WId(*)>(_a[1]))); break;
        case 13: { bool _r = _t->acceptWindow((*reinterpret_cast< WId(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->onWindowChanged((*reinterpret_cast< WId(*)>(_a[1])),(*reinterpret_cast< NET::Properties(*)>(_a[2])),(*reinterpret_cast< NET::Properties2(*)>(_a[3]))); break;
        case 15: _t->togglePin((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->removeFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->setFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainTray::staticMetaObject = {
    { &QSystemTrayIcon::staticMetaObject, qt_meta_stringdata_MainTray.data,
      qt_meta_data_MainTray,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainTray::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainTray::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainTray.stringdata0))
        return static_cast<void*>(this);
    return QSystemTrayIcon::qt_metacast(_clname);
}

int MainTray::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSystemTrayIcon::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
