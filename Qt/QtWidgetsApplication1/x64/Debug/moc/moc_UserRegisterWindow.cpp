/****************************************************************************
** Meta object code from reading C++ file 'UserRegisterWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../UserRegisterWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UserRegisterWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UserRegisterWindow_t {
    QByteArrayData data[10];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UserRegisterWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UserRegisterWindow_t qt_meta_stringdata_UserRegisterWindow = {
    {
QT_MOC_LITERAL(0, 0, 18), // "UserRegisterWindow"
QT_MOC_LITERAL(1, 19, 23), // "on_returnbotton_clicked"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 15), // "confirm_clicked"
QT_MOC_LITERAL(4, 60, 17), // "username_finished"
QT_MOC_LITERAL(5, 78, 17), // "password_finished"
QT_MOC_LITERAL(6, 96, 15), // "confirmPassword"
QT_MOC_LITERAL(7, 112, 13), // "name_finished"
QT_MOC_LITERAL(8, 126, 15), // "number_finished"
QT_MOC_LITERAL(9, 142, 16) // "address_finished"

    },
    "UserRegisterWindow\0on_returnbotton_clicked\0"
    "\0confirm_clicked\0username_finished\0"
    "password_finished\0confirmPassword\0"
    "name_finished\0number_finished\0"
    "address_finished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UserRegisterWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UserRegisterWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserRegisterWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_returnbotton_clicked(); break;
        case 1: _t->confirm_clicked(); break;
        case 2: _t->username_finished(); break;
        case 3: _t->password_finished(); break;
        case 4: _t->confirmPassword(); break;
        case 5: _t->name_finished(); break;
        case 6: _t->number_finished(); break;
        case 7: _t->address_finished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject UserRegisterWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_UserRegisterWindow.data,
    qt_meta_data_UserRegisterWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UserRegisterWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserRegisterWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UserRegisterWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UserRegisterWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
