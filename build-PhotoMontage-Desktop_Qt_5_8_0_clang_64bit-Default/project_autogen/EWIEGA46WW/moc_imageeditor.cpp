/****************************************************************************
** Meta object code from reading C++ file 'imageeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../PhotoMontage/imageeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageEditor_t {
    QByteArrayData data[10];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageEditor_t qt_meta_stringdata_ImageEditor = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ImageEditor"
QT_MOC_LITERAL(1, 12, 8), // "sendEdit"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "QPixmap*"
QT_MOC_LITERAL(4, 31, 12), // "editorClosed"
QT_MOC_LITERAL(5, 44, 9), // "ShowColor"
QT_MOC_LITERAL(6, 54, 13), // "increaseWidth"
QT_MOC_LITERAL(7, 68, 13), // "decreaseWidth"
QT_MOC_LITERAL(8, 82, 5), // "clear"
QT_MOC_LITERAL(9, 88, 8) // "saveEdit"

    },
    "ImageEditor\0sendEdit\0\0QPixmap*\0"
    "editorClosed\0ShowColor\0increaseWidth\0"
    "decreaseWidth\0clear\0saveEdit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       4,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   55,    2, 0x0a /* Public */,
       6,    0,   56,    2, 0x0a /* Public */,
       7,    0,   57,    2, 0x0a /* Public */,
       8,    0,   58,    2, 0x0a /* Public */,
       9,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ImageEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageEditor *_t = static_cast<ImageEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendEdit((*reinterpret_cast< QPixmap*(*)>(_a[1])),(*reinterpret_cast< QPixmap*(*)>(_a[2]))); break;
        case 1: _t->editorClosed(); break;
        case 2: _t->ShowColor(); break;
        case 3: _t->increaseWidth(); break;
        case 4: _t->decreaseWidth(); break;
        case 5: _t->clear(); break;
        case 6: _t->saveEdit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ImageEditor::*_t)(QPixmap * , QPixmap * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageEditor::sendEdit)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ImageEditor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageEditor::editorClosed)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ImageEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageEditor.data,
      qt_meta_data_ImageEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageEditor.stringdata0))
        return static_cast<void*>(const_cast< ImageEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ImageEditor::sendEdit(QPixmap * _t1, QPixmap * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImageEditor::editorClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
