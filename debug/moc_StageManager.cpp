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
    QByteArrayData data[41];
    char stringdata0[419];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StageManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StageManager_t qt_meta_stringdata_StageManager = {
    {
QT_MOC_LITERAL(0, 0, 12), // "StageManager"
QT_MOC_LITERAL(1, 13, 15), // "ACTIONCOMPLETED"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "msg"
QT_MOC_LITERAL(4, 34, 10), // "LOGCONSOLE"
QT_MOC_LITERAL(5, 45, 7), // "strText"
QT_MOC_LITERAL(6, 53, 22), // "CONSOLECOLOURS::colour"
QT_MOC_LITERAL(7, 76, 3), // "col"
QT_MOC_LITERAL(8, 80, 15), // "UPDATEPOSITIONS"
QT_MOC_LITERAL(9, 96, 4), // "isXY"
QT_MOC_LITERAL(10, 101, 1), // "x"
QT_MOC_LITERAL(11, 103, 1), // "y"
QT_MOC_LITERAL(12, 105, 14), // "STAGECONNECTED"
QT_MOC_LITERAL(13, 120, 14), // "reportCOMPORTS"
QT_MOC_LITERAL(14, 135, 16), // "QVector<QString>"
QT_MOC_LITERAL(15, 152, 3), // "str"
QT_MOC_LITERAL(16, 156, 22), // "StageMovementCompleted"
QT_MOC_LITERAL(17, 179, 10), // "strMessage"
QT_MOC_LITERAL(18, 190, 8), // "finished"
QT_MOC_LITERAL(19, 199, 17), // "getAvailablePorts"
QT_MOC_LITERAL(20, 217, 11), // "assignPorts"
QT_MOC_LITERAL(21, 229, 14), // "MoveAbsoluteXY"
QT_MOC_LITERAL(22, 244, 13), // "MoveAbsoluteZ"
QT_MOC_LITERAL(23, 258, 1), // "z"
QT_MOC_LITERAL(24, 260, 14), // "MoveRelativeXY"
QT_MOC_LITERAL(25, 275, 13), // "SendCommandXY"
QT_MOC_LITERAL(26, 289, 3), // "cmd"
QT_MOC_LITERAL(27, 293, 13), // "SetVelocityXY"
QT_MOC_LITERAL(28, 307, 4), // "velo"
QT_MOC_LITERAL(29, 312, 13), // "SetJoystickXY"
QT_MOC_LITERAL(30, 326, 2), // "on"
QT_MOC_LITERAL(31, 329, 11), // "CalibrateXY"
QT_MOC_LITERAL(32, 341, 14), // "MeasureRangeXY"
QT_MOC_LITERAL(33, 356, 9), // "ConnectXY"
QT_MOC_LITERAL(34, 366, 8), // "ConnectZ"
QT_MOC_LITERAL(35, 375, 12), // "DisconnectXY"
QT_MOC_LITERAL(36, 388, 11), // "DisconnectZ"
QT_MOC_LITERAL(37, 400, 7), // "AbortXY"
QT_MOC_LITERAL(38, 408, 4), // "goXY"
QT_MOC_LITERAL(39, 413, 2), // "fx"
QT_MOC_LITERAL(40, 416, 2) // "fy"

    },
    "StageManager\0ACTIONCOMPLETED\0\0msg\0"
    "LOGCONSOLE\0strText\0CONSOLECOLOURS::colour\0"
    "col\0UPDATEPOSITIONS\0isXY\0x\0y\0"
    "STAGECONNECTED\0reportCOMPORTS\0"
    "QVector<QString>\0str\0StageMovementCompleted\0"
    "strMessage\0finished\0getAvailablePorts\0"
    "assignPorts\0MoveAbsoluteXY\0MoveAbsoluteZ\0"
    "z\0MoveRelativeXY\0SendCommandXY\0cmd\0"
    "SetVelocityXY\0velo\0SetJoystickXY\0on\0"
    "CalibrateXY\0MeasureRangeXY\0ConnectXY\0"
    "ConnectZ\0DisconnectXY\0DisconnectZ\0"
    "AbortXY\0goXY\0fx\0fy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StageManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  129,    2, 0x06 /* Public */,
       4,    2,  132,    2, 0x06 /* Public */,
       8,    3,  137,    2, 0x06 /* Public */,
      12,    2,  144,    2, 0x06 /* Public */,
      13,    1,  149,    2, 0x06 /* Public */,
      16,    1,  152,    2, 0x06 /* Public */,
      18,    0,  155,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    0,  156,    2, 0x0a /* Public */,
      20,    0,  157,    2, 0x0a /* Public */,
      21,    2,  158,    2, 0x0a /* Public */,
      22,    1,  163,    2, 0x0a /* Public */,
      24,    2,  166,    2, 0x0a /* Public */,
      25,    1,  171,    2, 0x0a /* Public */,
      27,    1,  174,    2, 0x0a /* Public */,
      29,    1,  177,    2, 0x0a /* Public */,
      31,    0,  180,    2, 0x0a /* Public */,
      32,    0,  181,    2, 0x0a /* Public */,
      33,    0,  182,    2, 0x0a /* Public */,
      34,    0,  183,    2, 0x0a /* Public */,
      35,    0,  184,    2, 0x0a /* Public */,
      36,    0,  185,    2, 0x0a /* Public */,
      37,    0,  186,    2, 0x0a /* Public */,
      38,    2,  187,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 6,    5,    7,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double, QMetaType::Double,    9,   10,   11,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    9,    2,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   10,   11,
    QMetaType::Void, QMetaType::Double,   23,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   10,   11,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::Double,   28,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   39,   40,

       0        // eod
};

void stageControlXY::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        stageControlXY *_t = static_cast<stageControlXY *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ACTIONCOMPLETED((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[2]))); break;
        case 2: _t->UPDATEPOSITIONS((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 3: _t->STAGECONNECTED((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->reportCOMPORTS((*reinterpret_cast< QVector<QString>(*)>(_a[1]))); break;
        case 5: _t->StageMovementCompleted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->finished(); break;
        case 7: _t->getAvailablePorts(); break;
        case 8: _t->assignPorts(); break;
        case 9: _t->MoveAbsoluteXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 10: _t->MoveAbsoluteZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->MoveRelativeXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 12: _t->SendCommandXY((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->SetVelocityXY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->SetJoystickXY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->CalibrateXY(); break;
        case 16: _t->MeasureRangeXY(); break;
        case 17: _t->ConnectXY(); break;
        case 18: _t->ConnectZ(); break;
        case 19: _t->DisconnectXY(); break;
        case 20: _t->DisconnectZ(); break;
        case 21: _t->AbortXY(); break;
        case 22: _t->goXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
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
            typedef void (stageControlXY::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stageControlXY::ACTIONCOMPLETED)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (stageControlXY::*_t)(QString , CONSOLECOLOURS::colour );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stageControlXY::LOGCONSOLE)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (stageControlXY::*_t)(bool , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stageControlXY::UPDATEPOSITIONS)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (stageControlXY::*_t)(bool , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stageControlXY::STAGECONNECTED)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (stageControlXY::*_t)(QVector<QString> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stageControlXY::reportCOMPORTS)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (stageControlXY::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stageControlXY::StageMovementCompleted)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (stageControlXY::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stageControlXY::finished)) {
                *result = 6;
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
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void stageControlXY::ACTIONCOMPLETED(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void stageControlXY::LOGCONSOLE(QString _t1, CONSOLECOLOURS::colour _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void stageControlXY::UPDATEPOSITIONS(bool _t1, double _t2, double _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void stageControlXY::STAGECONNECTED(bool _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void stageControlXY::reportCOMPORTS(QVector<QString> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void stageControlXY::StageMovementCompleted(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void stageControlXY::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
