/****************************************************************************
** Meta object code from reading C++ file 'paintqlabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../paintqlabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paintqlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_drawingObject_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_drawingObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_drawingObject_t qt_meta_stringdata_drawingObject = {
    {
QT_MOC_LITERAL(0, 0, 13) // "drawingObject"

    },
    "drawingObject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_drawingObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void drawingObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject drawingObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_drawingObject.data,
      qt_meta_data_drawingObject,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *drawingObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *drawingObject::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_drawingObject.stringdata0))
        return static_cast<void*>(const_cast< drawingObject*>(this));
    return QObject::qt_metacast(_clname);
}

int drawingObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_PaintQLabel_t {
    QByteArrayData data[25];
    char stringdata0[294];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaintQLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaintQLabel_t qt_meta_stringdata_PaintQLabel = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PaintQLabel"
QT_MOC_LITERAL(1, 12, 16), // "disablePanButton"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 13), // "setTargetArea"
QT_MOC_LITERAL(4, 44, 12), // "drawingShape"
QT_MOC_LITERAL(5, 57, 5), // "shape"
QT_MOC_LITERAL(6, 63, 19), // "unsetDrawingButtons"
QT_MOC_LITERAL(7, 83, 16), // "StatusBarMessage"
QT_MOC_LITERAL(8, 100, 3), // "msg"
QT_MOC_LITERAL(9, 104, 15), // "addFiducialMark"
QT_MOC_LITERAL(10, 120, 1), // "p"
QT_MOC_LITERAL(11, 122, 10), // "enterEvent"
QT_MOC_LITERAL(12, 133, 7), // "QEvent*"
QT_MOC_LITERAL(13, 141, 5), // "event"
QT_MOC_LITERAL(14, 147, 10), // "leaveEvent"
QT_MOC_LITERAL(15, 158, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(16, 173, 12), // "QMouseEvent*"
QT_MOC_LITERAL(17, 186, 15), // "mousePressEvent"
QT_MOC_LITERAL(18, 202, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(19, 220, 10), // "wheelEvent"
QT_MOC_LITERAL(20, 231, 12), // "QWheelEvent*"
QT_MOC_LITERAL(21, 244, 10), // "paintEvent"
QT_MOC_LITERAL(22, 255, 12), // "QPaintEvent*"
QT_MOC_LITERAL(23, 268, 11), // "resizeEvent"
QT_MOC_LITERAL(24, 280, 13) // "QResizeEvent*"

    },
    "PaintQLabel\0disablePanButton\0\0"
    "setTargetArea\0drawingShape\0shape\0"
    "unsetDrawingButtons\0StatusBarMessage\0"
    "msg\0addFiducialMark\0p\0enterEvent\0"
    "QEvent*\0event\0leaveEvent\0mouseMoveEvent\0"
    "QMouseEvent*\0mousePressEvent\0"
    "mouseReleaseEvent\0wheelEvent\0QWheelEvent*\0"
    "paintEvent\0QPaintEvent*\0resizeEvent\0"
    "QResizeEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaintQLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    1,   80,    2, 0x06 /* Public */,
       6,    0,   83,    2, 0x06 /* Public */,
       7,    1,   84,    2, 0x06 /* Public */,
       9,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   90,    2, 0x09 /* Protected */,
      14,    1,   93,    2, 0x09 /* Protected */,
      15,    1,   96,    2, 0x09 /* Protected */,
      17,    1,   99,    2, 0x09 /* Protected */,
      18,    1,  102,    2, 0x09 /* Protected */,
      19,    1,  105,    2, 0x09 /* Protected */,
      21,    1,  108,    2, 0x09 /* Protected */,
      23,    1,  111,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QPoint,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 16,   13,
    QMetaType::Void, 0x80000000 | 16,   13,
    QMetaType::Void, 0x80000000 | 16,   13,
    QMetaType::Void, 0x80000000 | 20,   13,
    QMetaType::Void, 0x80000000 | 22,   13,
    QMetaType::Void, 0x80000000 | 24,   13,

       0        // eod
};

void PaintQLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PaintQLabel *_t = static_cast<PaintQLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->disablePanButton(); break;
        case 1: _t->setTargetArea((*reinterpret_cast< drawingShape(*)>(_a[1]))); break;
        case 2: _t->unsetDrawingButtons(); break;
        case 3: _t->StatusBarMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->addFiducialMark((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 5: _t->enterEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 6: _t->leaveEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 7: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 8: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 9: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 10: _t->wheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 11: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 12: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PaintQLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintQLabel::disablePanButton)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PaintQLabel::*_t)(drawingShape );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintQLabel::setTargetArea)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PaintQLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintQLabel::unsetDrawingButtons)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (PaintQLabel::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintQLabel::StatusBarMessage)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (PaintQLabel::*_t)(QPoint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintQLabel::addFiducialMark)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject PaintQLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_PaintQLabel.data,
      qt_meta_data_PaintQLabel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PaintQLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaintQLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PaintQLabel.stringdata0))
        return static_cast<void*>(const_cast< PaintQLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int PaintQLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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
void PaintQLabel::disablePanButton()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void PaintQLabel::setTargetArea(drawingShape _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PaintQLabel::unsetDrawingButtons()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void PaintQLabel::StatusBarMessage(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PaintQLabel::addFiducialMark(QPoint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
