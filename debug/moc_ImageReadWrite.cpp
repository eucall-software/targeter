/****************************************************************************
** Meta object code from reading C++ file 'ImageReadWrite.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ImageReadWrite.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageReadWrite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageReadWrite_t {
    QByteArrayData data[6];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageReadWrite_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageReadWrite_t qt_meta_stringdata_ImageReadWrite = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ImageReadWrite"
QT_MOC_LITERAL(1, 15, 10), // "LOGCONSOLE"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "strText"
QT_MOC_LITERAL(4, 35, 22), // "CONSOLECOLOURS::colour"
QT_MOC_LITERAL(5, 58, 3) // "col"

    },
    "ImageReadWrite\0LOGCONSOLE\0\0strText\0"
    "CONSOLECOLOURS::colour\0col"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageReadWrite[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       1,    1,   29,    2, 0x26 /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void ImageReadWrite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageReadWrite *_t = static_cast<ImageReadWrite *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[2]))); break;
        case 1: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ImageReadWrite::*_t)(QString , CONSOLECOLOURS::colour );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageReadWrite::LOGCONSOLE)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ImageReadWrite::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ImageReadWrite.data,
      qt_meta_data_ImageReadWrite,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageReadWrite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageReadWrite::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageReadWrite.stringdata0))
        return static_cast<void*>(const_cast< ImageReadWrite*>(this));
    return QObject::qt_metacast(_clname);
}

int ImageReadWrite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ImageReadWrite::LOGCONSOLE(QString _t1, CONSOLECOLOURS::colour _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
