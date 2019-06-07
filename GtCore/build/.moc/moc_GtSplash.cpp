/****************************************************************************
** Meta object code from reading C++ file 'GtSplash.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GtSplash.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GtSplash.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Splash_t {
    QByteArrayData data[22];
    char stringdata[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Splash_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Splash_t qt_meta_stringdata_Splash = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 14),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 9),
QT_MOC_LITERAL(4, 33, 13),
QT_MOC_LITERAL(5, 47, 14),
QT_MOC_LITERAL(6, 62, 5),
QT_MOC_LITERAL(7, 68, 13),
QT_MOC_LITERAL(8, 82, 8),
QT_MOC_LITERAL(9, 91, 2),
QT_MOC_LITERAL(10, 94, 11),
QT_MOC_LITERAL(11, 106, 9),
QT_MOC_LITERAL(12, 116, 5),
QT_MOC_LITERAL(13, 122, 5),
QT_MOC_LITERAL(14, 128, 12),
QT_MOC_LITERAL(15, 141, 13),
QT_MOC_LITERAL(16, 155, 12),
QT_MOC_LITERAL(17, 168, 11),
QT_MOC_LITERAL(18, 180, 11),
QT_MOC_LITERAL(19, 192, 8),
QT_MOC_LITERAL(20, 201, 4),
QT_MOC_LITERAL(21, 206, 8)
    },
    "Splash\0acceptedSignal\0\0okClicked\0"
    "cancelClicked\0langSelChanged\0index\0"
    "srvSelChanged\0setTitle\0tx\0setHeadline\0"
    "setBottom\0line1\0line2\0btnOkClicked\0"
    "btnCnlClicked\0hideControls\0sel1Changed\0"
    "sel2Changed\0enableOk\0show\0progress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Splash[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    0,   90,    2, 0x06 /* Public */,
       4,    0,   91,    2, 0x06 /* Public */,
       5,    1,   92,    2, 0x06 /* Public */,
       7,    1,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   98,    2, 0x0a /* Public */,
      10,    1,  101,    2, 0x0a /* Public */,
      11,    2,  104,    2, 0x0a /* Public */,
      14,    0,  109,    2, 0x0a /* Public */,
      15,    0,  110,    2, 0x0a /* Public */,
      16,    0,  111,    2, 0x0a /* Public */,
      17,    1,  112,    2, 0x0a /* Public */,
      18,    1,  115,    2, 0x0a /* Public */,
      19,    2,  118,    2, 0x0a /* Public */,
      21,    3,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   20,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,

       0        // eod
};

void Splash::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Splash *_t = static_cast<Splash *>(_o);
        switch (_id) {
        case 0: _t->acceptedSignal(); break;
        case 1: _t->okClicked(); break;
        case 2: _t->cancelClicked(); break;
        case 3: _t->langSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->srvSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->setHeadline((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setBottom((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->btnOkClicked(); break;
        case 9: _t->btnCnlClicked(); break;
        case 10: _t->hideControls(); break;
        case 11: _t->sel1Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->sel2Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->enableOk((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 14: _t->progress((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Splash::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Splash::acceptedSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (Splash::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Splash::okClicked)) {
                *result = 1;
            }
        }
        {
            typedef void (Splash::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Splash::cancelClicked)) {
                *result = 2;
            }
        }
        {
            typedef void (Splash::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Splash::langSelChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (Splash::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Splash::srvSelChanged)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject Splash::staticMetaObject = {
    { &QSplashScreen::staticMetaObject, qt_meta_stringdata_Splash.data,
      qt_meta_data_Splash,  qt_static_metacall, 0, 0}
};


const QMetaObject *Splash::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Splash::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Splash.stringdata))
        return static_cast<void*>(const_cast< Splash*>(this));
    return QSplashScreen::qt_metacast(_clname);
}

int Splash::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSplashScreen::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Splash::acceptedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Splash::okClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Splash::cancelClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Splash::langSelChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Splash::srvSelChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
