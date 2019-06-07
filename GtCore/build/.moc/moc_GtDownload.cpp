/****************************************************************************
** Meta object code from reading C++ file 'GtDownload.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GtDownload.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GtDownload.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GtDownload_t {
    QByteArrayData data[19];
    char stringdata[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GtDownload_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GtDownload_t qt_meta_stringdata_GtDownload = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 9),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 2),
QT_MOC_LITERAL(4, 25, 7),
QT_MOC_LITERAL(5, 33, 5),
QT_MOC_LITERAL(6, 39, 8),
QT_MOC_LITERAL(7, 48, 8),
QT_MOC_LITERAL(8, 57, 4),
QT_MOC_LITERAL(9, 62, 7),
QT_MOC_LITERAL(10, 70, 3),
QT_MOC_LITERAL(11, 74, 6),
QT_MOC_LITERAL(12, 81, 5),
QT_MOC_LITERAL(13, 87, 20),
QT_MOC_LITERAL(14, 108, 13),
QT_MOC_LITERAL(15, 122, 14),
QT_MOC_LITERAL(16, 137, 3),
QT_MOC_LITERAL(17, 141, 16),
QT_MOC_LITERAL(18, 158, 1)
    },
    "GtDownload\0completed\0\0id\0success\0error\0"
    "progress\0received\0size\0message\0msg\0"
    "cancel\0start\0replyMetaDataChanged\0"
    "replyFinished\0QNetworkReply*\0rep\0"
    "downloadProgress\0n"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GtDownload[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,
       6,    3,   61,    2, 0x06 /* Public */,
       9,    2,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   73,    2, 0x0a /* Public */,
      12,    0,   74,    2, 0x09 /* Protected */,
      13,    0,   75,    2, 0x09 /* Protected */,
      14,    1,   76,    2, 0x09 /* Protected */,
      17,    2,   79,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong, QMetaType::LongLong,    3,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   18,    2,

       0        // eod
};

void GtDownload::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GtDownload *_t = static_cast<GtDownload *>(_o);
        switch (_id) {
        case 0: _t->completed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 1: _t->progress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3]))); break;
        case 2: _t->message((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->cancel(); break;
        case 4: _t->start(); break;
        case 5: _t->replyMetaDataChanged(); break;
        case 6: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 7: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GtDownload::*_t)(int , bool , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GtDownload::completed)) {
                *result = 0;
            }
        }
        {
            typedef void (GtDownload::*_t)(int , qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GtDownload::progress)) {
                *result = 1;
            }
        }
        {
            typedef void (GtDownload::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GtDownload::message)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject GtDownload::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GtDownload.data,
      qt_meta_data_GtDownload,  qt_static_metacall, 0, 0}
};


const QMetaObject *GtDownload::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GtDownload::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GtDownload.stringdata))
        return static_cast<void*>(const_cast< GtDownload*>(this));
    return QObject::qt_metacast(_clname);
}

int GtDownload::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GtDownload::completed(int _t1, bool _t2, const QString & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GtDownload::progress(int _t1, qint64 _t2, qint64 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GtDownload::message(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_GtDownloader_t {
    QByteArrayData data[10];
    char stringdata[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GtDownloader_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GtDownloader_t qt_meta_stringdata_GtDownloader = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 6),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 10),
QT_MOC_LITERAL(4, 32, 2),
QT_MOC_LITERAL(5, 35, 8),
QT_MOC_LITERAL(6, 44, 4),
QT_MOC_LITERAL(7, 49, 11),
QT_MOC_LITERAL(8, 61, 7),
QT_MOC_LITERAL(9, 69, 5)
    },
    "GtDownloader\0cancel\0\0dlProgress\0id\0"
    "received\0size\0dlCompleted\0success\0"
    "error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GtDownloader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    3,   30,    2, 0x09 /* Protected */,
       7,    3,   37,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong, QMetaType::LongLong,    4,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString,    4,    8,    9,

       0        // eod
};

void GtDownloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GtDownloader *_t = static_cast<GtDownloader *>(_o);
        switch (_id) {
        case 0: _t->cancel(); break;
        case 1: _t->dlProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3]))); break;
        case 2: _t->dlCompleted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject GtDownloader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GtDownloader.data,
      qt_meta_data_GtDownloader,  qt_static_metacall, 0, 0}
};


const QMetaObject *GtDownloader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GtDownloader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GtDownloader.stringdata))
        return static_cast<void*>(const_cast< GtDownloader*>(this));
    return QObject::qt_metacast(_clname);
}

int GtDownloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
