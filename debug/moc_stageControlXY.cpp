/****************************************************************************
** Meta object code from reading C++ file 'stageControlXY.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../stageControlXY.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stageControlXY.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StageControlXY_t {
    QByteArrayData data[46];
    char stringdata0[454];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StageControlXY_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StageControlXY_t qt_meta_stringdata_StageControlXY = {
    {
QT_MOC_LITERAL(0, 0, 14), // "StageControlXY"
QT_MOC_LITERAL(1, 15, 15), // "ACTIONCOMPLETED"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 3), // "msg"
QT_MOC_LITERAL(4, 36, 15), // "CONNECTEDTOPORT"
QT_MOC_LITERAL(5, 52, 4), // "port"
QT_MOC_LITERAL(6, 57, 10), // "LOGCONSOLE"
QT_MOC_LITERAL(7, 68, 7), // "strText"
QT_MOC_LITERAL(8, 76, 22), // "CONSOLECOLOURS::colour"
QT_MOC_LITERAL(9, 99, 3), // "col"
QT_MOC_LITERAL(10, 103, 15), // "UPDATEPOSITIONS"
QT_MOC_LITERAL(11, 119, 5), // "isFid"
QT_MOC_LITERAL(12, 125, 1), // "x"
QT_MOC_LITERAL(13, 127, 1), // "y"
QT_MOC_LITERAL(14, 129, 14), // "STAGECONNECTED"
QT_MOC_LITERAL(15, 144, 4), // "isXY"
QT_MOC_LITERAL(16, 149, 14), // "reportCOMPORTS"
QT_MOC_LITERAL(17, 164, 16), // "QVector<QString>"
QT_MOC_LITERAL(18, 181, 3), // "str"
QT_MOC_LITERAL(19, 185, 22), // "StageMovementCompleted"
QT_MOC_LITERAL(20, 208, 10), // "strMessage"
QT_MOC_LITERAL(21, 219, 8), // "finished"
QT_MOC_LITERAL(22, 228, 10), // "STAGEMOVED"
QT_MOC_LITERAL(23, 239, 15), // "ACTIONS::action"
QT_MOC_LITERAL(24, 255, 3), // "act"
QT_MOC_LITERAL(25, 259, 15), // "updatePositions"
QT_MOC_LITERAL(26, 275, 9), // "bFiducial"
QT_MOC_LITERAL(27, 285, 10), // "assignPort"
QT_MOC_LITERAL(28, 296, 14), // "AvailablePorts"
QT_MOC_LITERAL(29, 311, 11), // "excludePort"
QT_MOC_LITERAL(30, 323, 12), // "MoveAbsolute"
QT_MOC_LITERAL(31, 336, 12), // "MoveRelative"
QT_MOC_LITERAL(32, 349, 2), // "go"
QT_MOC_LITERAL(33, 352, 2), // "fx"
QT_MOC_LITERAL(34, 355, 2), // "fy"
QT_MOC_LITERAL(35, 358, 11), // "SendCommand"
QT_MOC_LITERAL(36, 370, 3), // "cmd"
QT_MOC_LITERAL(37, 374, 11), // "SetVelocity"
QT_MOC_LITERAL(38, 386, 4), // "velo"
QT_MOC_LITERAL(39, 391, 11), // "SetJoystick"
QT_MOC_LITERAL(40, 403, 2), // "on"
QT_MOC_LITERAL(41, 406, 7), // "Connect"
QT_MOC_LITERAL(42, 414, 10), // "Disconnect"
QT_MOC_LITERAL(43, 425, 5), // "Abort"
QT_MOC_LITERAL(44, 431, 9), // "Calibrate"
QT_MOC_LITERAL(45, 441, 12) // "MeasureRange"

    },
    "StageControlXY\0ACTIONCOMPLETED\0\0msg\0"
    "CONNECTEDTOPORT\0port\0LOGCONSOLE\0strText\0"
    "CONSOLECOLOURS::colour\0col\0UPDATEPOSITIONS\0"
    "isFid\0x\0y\0STAGECONNECTED\0isXY\0"
    "reportCOMPORTS\0QVector<QString>\0str\0"
    "StageMovementCompleted\0strMessage\0"
    "finished\0STAGEMOVED\0ACTIONS::action\0"
    "act\0updatePositions\0bFiducial\0assignPort\0"
    "AvailablePorts\0excludePort\0MoveAbsolute\0"
    "MoveRelative\0go\0fx\0fy\0SendCommand\0cmd\0"
    "SetVelocity\0velo\0SetJoystick\0on\0Connect\0"
    "Disconnect\0Abort\0Calibrate\0MeasureRange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StageControlXY[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  129,    2, 0x06 /* Public */,
       4,    1,  132,    2, 0x06 /* Public */,
       6,    2,  135,    2, 0x06 /* Public */,
      10,    3,  140,    2, 0x06 /* Public */,
      14,    2,  147,    2, 0x06 /* Public */,
      16,    1,  152,    2, 0x06 /* Public */,
      19,    1,  155,    2, 0x06 /* Public */,
      21,    0,  158,    2, 0x06 /* Public */,
      22,    3,  159,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      25,    2,  166,    2, 0x0a /* Public */,
      25,    1,  171,    2, 0x0a /* Public */,
      27,    2,  174,    2, 0x0a /* Public */,
      30,    3,  179,    2, 0x0a /* Public */,
      31,    3,  186,    2, 0x0a /* Public */,
      32,    2,  193,    2, 0x0a /* Public */,
      35,    1,  198,    2, 0x0a /* Public */,
      37,    1,  201,    2, 0x0a /* Public */,
      39,    1,  204,    2, 0x0a /* Public */,
      41,    0,  207,    2, 0x0a /* Public */,
      42,    0,  208,    2, 0x0a /* Public */,
      43,    0,  209,    2, 0x0a /* Public */,
      44,    0,  210,    2, 0x0a /* Public */,
      45,    0,  211,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    7,    9,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double, QMetaType::Double,   11,   12,   13,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   15,    2,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 23,   12,   13,   24,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   12,   13,
    QMetaType::Void, QMetaType::Bool,   26,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QString,   28,   29,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 23,   12,   13,   24,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 23,   12,   13,   24,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   33,   34,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::Double,   38,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StageControlXY::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StageControlXY *_t = static_cast<StageControlXY *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ACTIONCOMPLETED((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->CONNECTEDTOPORT((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[2]))); break;
        case 3: _t->UPDATEPOSITIONS((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 4: _t->STAGECONNECTED((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->reportCOMPORTS((*reinterpret_cast< QVector<QString>(*)>(_a[1]))); break;
        case 6: _t->StageMovementCompleted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->finished(); break;
        case 8: _t->STAGEMOVED((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 9: _t->updatePositions((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 10: _t->updatePositions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->assignPort((*reinterpret_cast< QVector<QString>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 12: _t->MoveAbsolute((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 13: _t->MoveRelative((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 14: _t->go((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 15: _t->SendCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->SetVelocity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->SetJoystick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: { bool _r = _t->Connect();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: _t->Disconnect(); break;
        case 20: _t->Abort(); break;
        case 21: _t->Calibrate(); break;
        case 22: _t->MeasureRange(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        case 11:
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
            typedef void (StageControlXY::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StageControlXY::ACTIONCOMPLETED)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (StageControlXY::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StageControlXY::CONNECTEDTOPORT)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (StageControlXY::*_t)(QString , CONSOLECOLOURS::colour );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StageControlXY::LOGCONSOLE)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (StageControlXY::*_t)(bool , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StageControlXY::UPDATEPOSITIONS)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (StageControlXY::*_t)(bool , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StageControlXY::STAGECONNECTED)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (StageControlXY::*_t)(QVector<QString> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StageControlXY::reportCOMPORTS)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (StageControlXY::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StageControlXY::StageMovementCompleted)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (StageControlXY::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StageControlXY::finished)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (StageControlXY::*_t)(double , double , ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StageControlXY::STAGEMOVED)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject StageControlXY::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StageControlXY.data,
      qt_meta_data_StageControlXY,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StageControlXY::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StageControlXY::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StageControlXY.stringdata0))
        return static_cast<void*>(const_cast< StageControlXY*>(this));
    return QObject::qt_metacast(_clname);
}

int StageControlXY::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void StageControlXY::ACTIONCOMPLETED(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StageControlXY::CONNECTEDTOPORT(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StageControlXY::LOGCONSOLE(QString _t1, CONSOLECOLOURS::colour _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void StageControlXY::UPDATEPOSITIONS(bool _t1, double _t2, double _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void StageControlXY::STAGECONNECTED(bool _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void StageControlXY::reportCOMPORTS(QVector<QString> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void StageControlXY::StageMovementCompleted(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void StageControlXY::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void StageControlXY::STAGEMOVED(double _t1, double _t2, ACTIONS::action _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
