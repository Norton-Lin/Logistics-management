/****************************************************************************
** Meta object code from reading C++ file 'CourierWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../CourierWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CourierWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CourierWindow_t {
    QByteArrayData data[10];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CourierWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CourierWindow_t qt_meta_stringdata_CourierWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CourierWindow"
QT_MOC_LITERAL(1, 14, 23), // "on_returnbotton_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 25), // "on_findAllMessage_clicked"
QT_MOC_LITERAL(4, 65, 24), // "on_changeMessage_clicked"
QT_MOC_LITERAL(5, 90, 16), // "on_check_Clicked"
QT_MOC_LITERAL(6, 107, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(7, 124, 4), // "item"
QT_MOC_LITERAL(8, 129, 6), // "column"
QT_MOC_LITERAL(9, 136, 25) // "on_collectExpress_clicked"

    },
    "CourierWindow\0on_returnbotton_clicked\0"
    "\0on_findAllMessage_clicked\0"
    "on_changeMessage_clicked\0on_check_Clicked\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_collectExpress_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CourierWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    2,   42,    2, 0x08 /* Private */,
       9,    0,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void,

       0        // eod
};

void CourierWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CourierWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_returnbotton_clicked(); break;
        case 1: _t->on_findAllMessage_clicked(); break;
        case 2: _t->on_changeMessage_clicked(); break;
        case 3: _t->on_check_Clicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_collectExpress_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CourierWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CourierWindow.data,
    qt_meta_data_CourierWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CourierWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CourierWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CourierWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CourierWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
