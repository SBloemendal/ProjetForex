/****************************************************************************
** Meta object code from reading C++ file 'principal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../principal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'principal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Principal_t {
    QByteArrayData data[15];
    char stringdata[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Principal_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Principal_t qt_meta_stringdata_Principal = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Principal"
QT_MOC_LITERAL(1, 10, 15), // "recupereDonnees"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 18), // "setUrlChoixDevises"
QT_MOC_LITERAL(4, 46, 3), // "url"
QT_MOC_LITERAL(5, 50, 19), // "setUrlFiltreDevises"
QT_MOC_LITERAL(6, 70, 13), // "connexionHttp"
QT_MOC_LITERAL(7, 84, 18), // "choixCoupleDevises"
QT_MOC_LITERAL(8, 103, 15), // "intervalleTemps"
QT_MOC_LITERAL(9, 119, 21), // "simulationTransaction"
QT_MOC_LITERAL(10, 141, 12), // "requeteGraph"
QT_MOC_LITERAL(11, 154, 5), // "index"
QT_MOC_LITERAL(12, 160, 15), // "transactionAuto"
QT_MOC_LITERAL(13, 176, 7), // "options"
QT_MOC_LITERAL(14, 184, 16) // "afficheGraphique"

    },
    "Principal\0recupereDonnees\0\0"
    "setUrlChoixDevises\0url\0setUrlFiltreDevises\0"
    "connexionHttp\0choixCoupleDevises\0"
    "intervalleTemps\0simulationTransaction\0"
    "requeteGraph\0index\0transactionAuto\0"
    "options\0afficheGraphique"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Principal[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    1,   70,    2, 0x08 /* Private */,
       5,    1,   73,    2, 0x08 /* Private */,
       6,    0,   76,    2, 0x08 /* Private */,
       7,    0,   77,    2, 0x08 /* Private */,
       8,    0,   78,    2, 0x08 /* Private */,
       9,    0,   79,    2, 0x08 /* Private */,
      10,    1,   80,    2, 0x08 /* Private */,
      12,    0,   83,    2, 0x08 /* Private */,
      13,    0,   84,    2, 0x08 /* Private */,
      14,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Principal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Principal *_t = static_cast<Principal *>(_o);
        switch (_id) {
        case 0: _t->recupereDonnees(); break;
        case 1: _t->setUrlChoixDevises((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->setUrlFiltreDevises((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->connexionHttp(); break;
        case 4: _t->choixCoupleDevises(); break;
        case 5: _t->intervalleTemps(); break;
        case 6: _t->simulationTransaction(); break;
        case 7: _t->requeteGraph((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 8: _t->transactionAuto(); break;
        case 9: _t->options(); break;
        case 10: _t->afficheGraphique(); break;
        default: ;
        }
    }
}

const QMetaObject Principal::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Principal.data,
      qt_meta_data_Principal,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Principal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Principal::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Principal.stringdata))
        return static_cast<void*>(const_cast< Principal*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Principal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE