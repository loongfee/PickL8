/****************************************************************************
** Meta object code from reading C++ file 'FileCopyProcessThread.h'
**
** Created: Fri Oct 18 12:56:22 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "FileCopyProcessThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileCopyProcessThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileCopyProcessThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,
      44,   22,   22,   22, 0x05,
      54,   22,   22,   22, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_FileCopyProcessThread[] = {
    "FileCopyProcessThread\0\0taskProgress(double)\0"
    "beginUI()\0endUI()\0"
};

void FileCopyProcessThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FileCopyProcessThread *_t = static_cast<FileCopyProcessThread *>(_o);
        switch (_id) {
        case 0: _t->taskProgress((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->beginUI(); break;
        case 2: _t->endUI(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FileCopyProcessThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FileCopyProcessThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FileCopyProcessThread,
      qt_meta_data_FileCopyProcessThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileCopyProcessThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileCopyProcessThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileCopyProcessThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileCopyProcessThread))
        return static_cast<void*>(const_cast< FileCopyProcessThread*>(this));
    return QThread::qt_metacast(_clname);
}

int FileCopyProcessThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void FileCopyProcessThread::taskProgress(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FileCopyProcessThread::beginUI()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void FileCopyProcessThread::endUI()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
