/****************************************************************************
** Meta object code from reading C++ file 'StageManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../StageManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StageManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StageManager_t {
    QByteArrayData data[28];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StageManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StageManager_t qt_meta_stringdata_StageManager = {
    {
QT_MOC_LITERAL(0, 0, 12), // "StageManager"
QT_MOC_LITERAL(1, 13, 10), // "LOGCONSOLE"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "strText"
QT_MOC_LITERAL(4, 33, 22), // "CONSOLECOLOURS::colour"
QT_MOC_LITERAL(5, 56, 3), // "col"
QT_MOC_LITERAL(6, 60, 14), // "reportCOMPORTS"
QT_MOC_LITERAL(7, 75, 16), // "QVector<QString>"
QT_MOC_LITERAL(8, 92, 4), // "strs"
QT_MOC_LITERAL(9, 97, 22), // "StageMovementCompleted"
QT_MOC_LITERAL(10, 120, 10), // "strMessage"
QT_MOC_LITERAL(11, 131, 8), // "finished"
QT_MOC_LITERAL(12, 140, 17), // "getAvailablePorts"
QT_MOC_LITERAL(13, 158, 11), // "assignPorts"
QT_MOC_LITERAL(14, 170, 14), // "MoveAbsoluteXY"
QT_MOC_LITERAL(15, 185, 1), // "x"
QT_MOC_LITERAL(16, 187, 1), // "y"
QT_MOC_LITERAL(17, 189, 14), // "MoveRelativeXY"
QT_MOC_LITERAL(18, 204, 13), // "SendCommandXY"
QT_MOC_LITERAL(19, 218, 3), // "cmd"
QT_MOC_LITERAL(20, 222, 13), // "SetVelocityXY"
QT_MOC_LITERAL(21, 236, 4), // "velo"
QT_MOC_LITERAL(22, 241, 11), // "CalibrateXY"
QT_MOC_LITERAL(23, 253, 14), // "MeasureRangeXY"
QT_MOC_LITERAL(24, 268, 9), // "ConnectXY"
QT_MOC_LITERAL(25, 278, 8), // "ConnectZ"
QT_MOC_LITERAL(26, 287, 12), // "DisconnectXY"
QT_MOC_LITERAL(27, 300, 7) // "AbortXY"

    },
    "StageManager\0LOGCONSOLE\0\0strText\0"
    "CONSOLECOLOURS::colour\0col\0reportCOMPORTS\0"
    "QVector<QString>\0strs\0StageMovementCompleted\0"
    "strMessage\0finished\0getAvailablePorts\0"
    "assignPorts\0MoveAbsoluteXY\0x\0y\0"
    "MoveRelativeXY\0SendCommandXY\0cmd\0"
    "SetVelocityXY\0velo\0CalibrateXY\0"
    "MeasureRangeXY\0ConnectXY\0ConnectZ\0"
    "DisconnectXY\0AbortXY"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StageManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   99,    2, 0x06 /* Public */,
       1,    1,  104,    2, 0x26 /* Public | MethodCloned */,
       6,    1,  107,    2, 0x06 /* Public */,
       9,    1,  110,    2, 0x06 /* Public */,
      11,    0,  113,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  114,    2, 0x0a /* Public */,
      13,    0,  115,    2, 0x0a /* Public */,
      14,    2,  116,    2, 0x0a /* Public */,
      17,    2,  121,    2, 0x0a /* Public */,
      18,    1,  126,    2, 0x0a /* Public */,
      20,    1,  129,    2, 0x0a /* Public */,
      22,    0,  132,    2, 0x0a /* Public */,
      23,    0,  133,    2, 0x0a /* Public */,
      24,    0,  134,    2, 0x0a /* Public */,
      25,    0,  135,    2, 0x0a /* Public */,
      26,    0,  136,    2, 0x0a /* Public */,
      27,    0,  137,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   15,   16,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   15,   16,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::Double,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void stageControlXY::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        stageControlXY *_t = static_cast<stageControlXY *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[2]))); break;
        case 1: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->reportCOMPORTS((*reinterpret_cast< QVector<QString>(*)>(_a[1]))); break;
        case 3: _t->StageMovementCompleted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->finished(); break;
        case 5: _t->getAvailablePorts(); break;
        case 6: _t->assignPorts(); break;
        case 7: _t->MoveAbsoluteXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 8: _t->MoveRelativeXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 9: _t->SendCommandXY((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->SetVelocityXY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->CalibrateXY(); break;
        case 12: _t->MeasureRangeXY(); break;
        case 13: _t->ConnectXY(); break;
        case 14: _t->ConnectZ(); break;
        case 15: _t->DisconnectXY(); break;
        case 16: _t->AbortXY(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (stageControlXY::*_t)(QString , CONSOLECOLOURS::colour );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stageControlXY::LOGCONSOLE)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (stageControlXY::*_t)(QVector<QString> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stageControlXY::reportCOMPORTS)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (stageControlXY::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stageControlXY::StageMovementCompleted)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (stageControlXY::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stageControlXY::finished)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject stageControlXY::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StageManager.data,
      qt_meta_data_StageManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *stageControlXY::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stageControlXY::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StageManager.stringdata0))
        return static_cast<void*>(const_cast< stageControlXY*>(this));
    return QObject::qt_metacast(_clname);
}

int stageControlXY::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void stageControlXY::LOGCONSOLE(QString _t1, CONSOLECOLOURS::colour _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void stageControlXY::reportCOMPORTS(QVector<QString> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void stageControlXY::StageMovementCompleted(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void stageControlXY::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
