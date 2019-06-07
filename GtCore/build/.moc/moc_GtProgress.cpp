/****************************************************************************
** Meta object code from reading C++ file 'GtProgress.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GtProgress.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GtProgress.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GtProgress_t {
    QByteArrayData data[22];
    char stringdata[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GtProgress_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GtProgress_t qt_meta_stringdata_GtProgress = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 8),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 4),
QT_MOC_LITERAL(4, 26, 4),
QT_MOC_LITERAL(5, 31, 7),
QT_MOC_LITERAL(6, 39, 9),
QT_MOC_LITERAL(7, 49, 7),
QT_MOC_LITERAL(8, 57, 5),
QT_MOC_LITERAL(9, 63, 9),
QT_MOC_LITERAL(10, 73, 11),
QT_MOC_LITERAL(11, 85, 1),
QT_MOC_LITERAL(12, 87, 14),
QT_MOC_LITERAL(13, 102, 12),
QT_MOC_LITERAL(14, 115, 4),
QT_MOC_LITERAL(15, 120, 3),
QT_MOC_LITERAL(16, 124, 11),
QT_MOC_LITERAL(17, 136, 1),
QT_MOC_LITERAL(18, 138, 3),
QT_MOC_LITERAL(19, 142, 5),
QT_MOC_LITERAL(20, 148, 5),
QT_MOC_LITERAL(21, 154, 8)
    },
    "GtProgress\0progress\0\0head\0desc\0permill\0"
    "completed\0success\0error\0cancelled\0"
    "setHeadline\0s\0setDescription\0setCompleted\0"
    "succ\0err\0setProgress\0n\0tot\0abort\0reset\0"
    "setError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GtProgress[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   79,    2, 0x06 /* Public */,
       6,    2,   86,    2, 0x06 /* Public */,
       9,    0,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   92,    2, 0x0a /* Public */,
      12,    1,   95,    2, 0x0a /* Public */,
      12,    2,   98,    2, 0x0a /* Public */,
      13,    3,  103,    2, 0x0a /* Public */,
      13,    2,  110,    2, 0x0a /* Public */,
      16,    3,  115,    2, 0x0a /* Public */,
      16,    2,  122,    2, 0x0a /* Public */,
      19,    0,  127,    2, 0x0a /* Public */,
      20,    0,  128,    2, 0x0a /* Public */,
      21,    1,  129,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    7,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString,    2,   14,   15,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong, QMetaType::LongLong,    2,   17,   18,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,

       0        // eod
};

void GtProgress::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GtProgress *_t = static_cast<GtProgress *>(_o);
        switch (_id) {
        case 0: _t->progress((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->completed((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->cancelled(); break;
        case 3: _t->setHeadline((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setDescription((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->setDescription((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->setCompleted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 7: _t->setCompleted((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->setProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3]))); break;
        case 9: _t->setProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 10: _t->abort(); break;
        case 11: _t->reset(); break;
        case 12: _t->setError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GtProgress::*_t)(const QString & , const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GtProgress::progress)) {
                *result = 0;
            }
        }
        {
            typedef void (GtProgress::*_t)(bool , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GtProgress::completed)) {
                *result = 1;
            }
        }
        {
            typedef void (GtProgress::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GtProgress::cancelled)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject GtProgress::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GtProgress.data,
      qt_meta_data_GtProgress,  qt_static_metacall, 0, 0}
};


const QMetaObject *GtProgress::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GtProgress::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GtProgress.stringdata))
        return static_cast<void*>(const_cast< GtProgress*>(this));
    return QObject::qt_metacast(_clname);
}

int GtProgress::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void GtProgress::progress(const QString & _t1, const QString & _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GtProgress::completed(bool _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GtProgress::cancelled()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
struct qt_meta_stringdata_ProgressBar_t {
    QByteArrayData data[4];
    char stringdata[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProgressBar_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProgressBar_t qt_meta_stringdata_ProgressBar = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 10),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 4)
    },
    "ProgressBar\0setPermill\0\0perm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProgressBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void ProgressBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProgressBar *_t = static_cast<ProgressBar *>(_o);
        switch (_id) {
        case 0: _t->setPermill((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ProgressBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ProgressBar.data,
      qt_meta_data_ProgressBar,  qt_static_metacall, 0, 0}
};


const QMetaObject *ProgressBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProgressBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProgressBar.stringdata))
        return static_cast<void*>(const_cast< ProgressBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int ProgressBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
