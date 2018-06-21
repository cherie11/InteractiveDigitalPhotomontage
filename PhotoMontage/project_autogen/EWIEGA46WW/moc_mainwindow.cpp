/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "openEditor"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "openImage"
QT_MOC_LITERAL(4, 33, 9), // "showImage"
QT_MOC_LITERAL(5, 43, 18), // "removeCurrentImage"
QT_MOC_LITERAL(6, 62, 15), // "removeAllImages"
QT_MOC_LITERAL(7, 78, 11), // "receiveEdit"
QT_MOC_LITERAL(8, 90, 8), // "QPixmap*"
QT_MOC_LITERAL(9, 99, 8), // "viewEdit"
QT_MOC_LITERAL(10, 108, 22), // "deleteCurrentImageEdit"
QT_MOC_LITERAL(11, 131, 19), // "deleteAllImageEdits"
QT_MOC_LITERAL(12, 151, 13), // "saveImageEdit"
QT_MOC_LITERAL(13, 165, 12), // "showUserHelp"
QT_MOC_LITERAL(14, 178, 11), // "showAboutUs"
QT_MOC_LITERAL(15, 190, 15), // "generatePoisson"
QT_MOC_LITERAL(16, 206, 18), // "checkGenerateImage"
QT_MOC_LITERAL(17, 225, 7) // "setMode"

    },
    "MainWindow\0openEditor\0\0openImage\0"
    "showImage\0removeCurrentImage\0"
    "removeAllImages\0receiveEdit\0QPixmap*\0"
    "viewEdit\0deleteCurrentImageEdit\0"
    "deleteAllImageEdits\0saveImageEdit\0"
    "showUserHelp\0showAboutUs\0generatePoisson\0"
    "checkGenerateImage\0setMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x0a /* Public */,
       3,    0,   90,    2, 0x0a /* Public */,
       4,    0,   91,    2, 0x0a /* Public */,
       5,    0,   92,    2, 0x0a /* Public */,
       6,    0,   93,    2, 0x0a /* Public */,
       7,    1,   94,    2, 0x0a /* Public */,
       9,    0,   97,    2, 0x0a /* Public */,
      10,    0,   98,    2, 0x0a /* Public */,
      11,    0,   99,    2, 0x0a /* Public */,
      12,    0,  100,    2, 0x0a /* Public */,
      13,    0,  101,    2, 0x0a /* Public */,
      14,    0,  102,    2, 0x0a /* Public */,
      15,    0,  103,    2, 0x0a /* Public */,
      16,    0,  104,    2, 0x0a /* Public */,
      17,    0,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openEditor(); break;
        case 1: _t->openImage(); break;
        case 2: _t->showImage(); break;
        case 3: _t->removeCurrentImage(); break;
        case 4: _t->removeAllImages(); break;
        case 5: _t->receiveEdit((*reinterpret_cast< QPixmap*(*)>(_a[1]))); break;
        case 6: _t->viewEdit(); break;
        case 7: _t->deleteCurrentImageEdit(); break;
        case 8: _t->deleteAllImageEdits(); break;
        case 9: _t->saveImageEdit(); break;
        case 10: _t->showUserHelp(); break;
        case 11: _t->showAboutUs(); break;
        case 12: _t->generatePoisson(); break;
        case 13: _t->checkGenerateImage(); break;
        case 14: _t->setMode(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
