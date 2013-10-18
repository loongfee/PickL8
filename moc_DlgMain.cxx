/****************************************************************************
** Meta object code from reading C++ file 'DlgMain.h'
**
** Created: Fri Oct 18 12:56:22 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DlgMain.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgMain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DlgMain[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,    8,   24,    8, 0x0a,
      54,    8,   24,    8, 0x0a,
      80,    8,   24,    8, 0x0a,
     101,    8,   24,    8, 0x0a,
     120,    8,   24,    8, 0x0a,
     147,  136,    8,    8, 0x0a,
     170,    8,    8,    8, 0x0a,
     179,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DlgMain[] = {
    "DlgMain\0\0notifyDEM(int)\0bool\0"
    "OnClickBrowseInputPath()\0"
    "OnClickBrowseOutputPath()\0"
    "OnStartDateChanged()\0OnEndDateChanged()\0"
    "OnClickSearch()\0percentage\0"
    "OnTaskProgress(double)\0lockUI()\0"
    "unlockUI()\0"
};

void DlgMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DlgMain *_t = static_cast<DlgMain *>(_o);
        switch (_id) {
        case 0: _t->notifyDEM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: { bool _r = _t->OnClickBrowseInputPath();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->OnClickBrowseOutputPath();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->OnStartDateChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->OnEndDateChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->OnClickSearch();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: _t->OnTaskProgress((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->lockUI(); break;
        case 8: _t->unlockUI(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DlgMain::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DlgMain::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DlgMain,
      qt_meta_data_DlgMain, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DlgMain::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DlgMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DlgMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DlgMain))
        return static_cast<void*>(const_cast< DlgMain*>(this));
    return QDialog::qt_metacast(_clname);
}

int DlgMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DlgMain::notifyDEM(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
