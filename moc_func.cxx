/****************************************************************************
** Meta object code from reading C++ file 'func.h'
**
** Created: Fri Oct 18 12:56:22 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "func.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'func.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Copier[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x06,
      27,    7,    7,    7, 0x06,

 // slots: signature, parameters, type, tag, flags
      38,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Copier[] = {
    "Copier\0\0newStatus(QString)\0finished()\0"
    "stop()\0"
};

void Copier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Copier *_t = static_cast<Copier *>(_o);
        switch (_id) {
        case 0: _t->newStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->finished(); break;
        case 2: _t->stop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Copier::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Copier::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Copier,
      qt_meta_data_Copier, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Copier::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Copier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Copier::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Copier))
        return static_cast<void*>(const_cast< Copier*>(this));
    return QObject::qt_metacast(_clname);
}

int Copier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Copier::newStatus(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Copier::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
