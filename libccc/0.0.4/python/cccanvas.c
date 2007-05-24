/* -- THIS FILE IS GENERATED - DO NOT EDIT *//* -*- Mode: C; c-basic-offset: 4 -*- */

#include <Python.h>



#line 3 "cccanvas.override"
#include <Python.h>
#include <stdio.h>

#include "pygobject.h"  
#include <gtk/gtk.h>
#include "ccc.h"

#include <pango/pangocairo.h>

#define CC_D_RECT(i) ((CcDRect *)i)
CcDRect *cc_d_rect_new (gdouble x1, gdouble y1, gdouble x2, gdouble y2);

void pycccanvas_add_constants(PyObject *module, const gchar *strip_prefix);
void pycccanvas_register_classes(PyObject *d);

void py_foreach_func(CcItem* item, CcView* view, gpointer data);

#line 26 "cccanvas.c"


/* ---------- types from other modules ---------- */
static PyTypeObject *_PyGObject_Type;
#define PyGObject_Type (*_PyGObject_Type)
static PyTypeObject *_PyGdkPixbuf_Type;
#define PyGdkPixbuf_Type (*_PyGdkPixbuf_Type)
static PyTypeObject *_PyGtkCellRenderer_Type;
#define PyGtkCellRenderer_Type (*_PyGtkCellRenderer_Type)
static PyTypeObject *_PyGtkDrawingArea_Type;
#define PyGtkDrawingArea_Type (*_PyGtkDrawingArea_Type)


/* ---------- forward type declarations ---------- */
PyTypeObject G_GNUC_INTERNAL PyCcDRect_Type;
PyTypeObject G_GNUC_INTERNAL PyCcBrush_Type;
PyTypeObject G_GNUC_INTERNAL PyCcBrushColor_Type;
PyTypeObject G_GNUC_INTERNAL PyCcColor_Type;
PyTypeObject G_GNUC_INTERNAL PyCcItem_Type;
PyTypeObject G_GNUC_INTERNAL PyCcItemView_Type;
PyTypeObject G_GNUC_INTERNAL PyCcPixbuf_Type;
PyTypeObject G_GNUC_INTERNAL PyCcPrinter_Type;
PyTypeObject G_GNUC_INTERNAL PyCcShape_Type;
PyTypeObject G_GNUC_INTERNAL PyCcRectangle_Type;
PyTypeObject G_GNUC_INTERNAL PyCcRoundedRectangle_Type;
PyTypeObject G_GNUC_INTERNAL PyCcLine_Type;
PyTypeObject G_GNUC_INTERNAL PyCcCircle_Type;
PyTypeObject G_GNUC_INTERNAL PyCcText_Type;
PyTypeObject G_GNUC_INTERNAL PyCcView_Type;
PyTypeObject G_GNUC_INTERNAL PyCcViewCellRenderer_Type;
PyTypeObject G_GNUC_INTERNAL PyCcViewPNG_Type;
PyTypeObject G_GNUC_INTERNAL PyCcViewWidget_Type;

#line 60 "cccanvas.c"



/* ----------- CcDRect ----------- */

#line 36 "cccanvas.override"
CcDRect *cc_d_rect_new (gdouble x1, gdouble y1, gdouble x2, gdouble y2) {
   CcDRect *ret = g_new(CcDRect, 1);

   ret->x1 = x1;
   ret->y1 = y1;
   ret->x2 = x2;
   ret->y2 = y2;

   return ret;
}

static int
_wrap_cc_d_rect_new(PyGBoxed *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x1", "x2", "y1", "y2", NULL };
    double x1, x2, y1, y2;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dddd:CcDRect.__init__", kwlist, &x1, &x2, &y1, &y2))
        return -1;
    self->gtype = CC_TYPE_D_RECT;
    self->free_on_dealloc = FALSE;
    self->boxed = cc_d_rect_new(x1, x2, y1, y2);

    if (!self->boxed) {
        PyErr_SetString(PyExc_RuntimeError, "could not create CcDRect object");
        return -1;
    }
    self->free_on_dealloc = TRUE;
    return 0;
}


#line 99 "cccanvas.c"


static PyObject *
_wrap_cc_d_rect_copy(PyObject *self)
{
    CcDRect *ret;

    
    ret = cc_d_rect_copy(pyg_boxed_get(self, CcDRect));
    
    /* pyg_boxed_new handles NULL checking */
    return pyg_boxed_new(CC_TYPE_D_RECT, ret, TRUE, TRUE);
}

#line 70 "cccanvas.override"
static PyObject *
_wrap_cc_d_rect_equal(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "two", NULL };
    PyObject *py_two;
    int ret;
    CcDRect *two = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O:CcDRect.equal", kwlist, &py_two))
        return NULL;
    if (pyg_boxed_check(py_two, CC_TYPE_D_RECT))
        two = pyg_boxed_get(py_two, CcDRect);
    else {
        PyErr_SetString(PyExc_TypeError, "two should be a CcDRect");
        return NULL;
    }
    ret = cc_d_rect_equal(*pyg_boxed_get(self, CcDRect), *two);
    return PyBool_FromLong(ret);

}
#line 135 "cccanvas.c"


#line 92 "cccanvas.override"
static PyObject *
_wrap_cc_d_rect_intersect(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "two", NULL };
    PyObject *py_two;
    int ret;
    CcDRect *two = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O:CcDRect.intersect", kwlist, &py_two))
        return NULL;
    if (pyg_boxed_check(py_two, CC_TYPE_D_RECT))
        two = pyg_boxed_get(py_two, CcDRect);
    else {
        PyErr_SetString(PyExc_TypeError, "two should be a CcDRect");
        return NULL;
    }
    ret = cc_d_rect_intersect(*pyg_boxed_get(self, CcDRect), *two);
    return PyBool_FromLong(ret);

}

#line 160 "cccanvas.c"


#line 115 "cccanvas.override"
static PyObject *
_wrap_cc_d_rect_union(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "two", NULL };
    PyObject *py_two, *py_merged;
    CcDRect *two = NULL, *merged = g_new(CcDRect, 1);

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:CcDRect.union", kwlist, &py_two, &py_merged))
        return NULL;
    if (pyg_boxed_check(py_two, CC_TYPE_D_RECT))
        two = pyg_boxed_get(py_two, CcDRect);
    else {
        PyErr_SetString(PyExc_TypeError, "two should be a CcDRect");
        return NULL;
    }
    if (pyg_boxed_check(py_merged, CC_TYPE_D_RECT))
        merged = pyg_boxed_get(py_merged, CcDRect);
    else {
        PyErr_SetString(PyExc_TypeError, "merged should be a CcDRect");
        return NULL;
    }
    cc_d_rect_union(*pyg_boxed_get(self, CcDRect), *two, merged);

    return pyg_boxed_new(CC_TYPE_D_RECT, merged, FALSE, TRUE);
}
#line 189 "cccanvas.c"


static const PyMethodDef _PyCcDRect_methods[] = {
    { "copy", (PyCFunction)_wrap_cc_d_rect_copy, METH_NOARGS,
      NULL },
    { "equal", (PyCFunction)_wrap_cc_d_rect_equal, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "intersect", (PyCFunction)_wrap_cc_d_rect_intersect, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "union", (PyCFunction)_wrap_cc_d_rect_union, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

static PyObject *
_wrap_cc_d_rect__get_x1(PyObject *self, void *closure)
{
    double ret;

    ret = pyg_boxed_get(self, CcDRect)->x1;
    return PyFloat_FromDouble(ret);
}

static PyObject *
_wrap_cc_d_rect__get_y1(PyObject *self, void *closure)
{
    double ret;

    ret = pyg_boxed_get(self, CcDRect)->y1;
    return PyFloat_FromDouble(ret);
}

static PyObject *
_wrap_cc_d_rect__get_x2(PyObject *self, void *closure)
{
    double ret;

    ret = pyg_boxed_get(self, CcDRect)->x2;
    return PyFloat_FromDouble(ret);
}

static PyObject *
_wrap_cc_d_rect__get_y2(PyObject *self, void *closure)
{
    double ret;

    ret = pyg_boxed_get(self, CcDRect)->y2;
    return PyFloat_FromDouble(ret);
}

static const PyGetSetDef cc_d_rect_getsets[] = {
    { "x1", (getter)_wrap_cc_d_rect__get_x1, (setter)0 },
    { "y1", (getter)_wrap_cc_d_rect__get_y1, (setter)0 },
    { "x2", (getter)_wrap_cc_d_rect__get_x2, (setter)0 },
    { "y2", (getter)_wrap_cc_d_rect__get_y2, (setter)0 },
    { NULL, (getter)0, (setter)0 },
};

PyTypeObject G_GNUC_INTERNAL PyCcDRect_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.DRect",                   /* tp_name */
    sizeof(PyGBoxed),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcDRect_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)cc_d_rect_getsets,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_cc_d_rect_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcBrush ----------- */

PyTypeObject G_GNUC_INTERNAL PyCcBrush_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.Brush",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcBrushColor ----------- */

static int
_wrap_cc_brush_color_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "color", NULL };
    PyGObject *color;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcBrushColor.__init__", kwlist, &PyCcColor_Type, &color))
        return -1;
    self->obj = (GObject *)cc_brush_color_new(CC_COLOR(color->obj));

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create CcBrushColor object");
        return -1;
    }
    g_object_ref(self->obj);
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_cc_brush_color_get_color(PyGObject *self)
{
    CcColor *ret;

    
    ret = cc_brush_color_get_color(CC_BRUSH_COLOR(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_cc_brush_color_set_color(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "color", NULL };
    PyGObject *color;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcBrushColor.set_color", kwlist, &PyCcColor_Type, &color))
        return NULL;
    
    cc_brush_color_set_color(CC_BRUSH_COLOR(self->obj), CC_COLOR(color->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyCcBrushColor_methods[] = {
    { "get_color", (PyCFunction)_wrap_cc_brush_color_get_color, METH_NOARGS,
      NULL },
    { "set_color", (PyCFunction)_wrap_cc_brush_color_set_color, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcBrushColor_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.BrushColor",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcBrushColor_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_cc_brush_color_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcColor ----------- */

PyTypeObject G_GNUC_INTERNAL PyCcColor_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.Color",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcItem ----------- */

static int
_wrap_cc_item_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":ccc.Item.__init__",
                                     kwlist))
        return -1;

    pygobject_constructv(self, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create ccc.Item object");
        return -1;
    }
    g_object_ref(self->obj);

    return 0;
}

static PyObject *
_wrap_CC_ITEM_SET_FLAGS(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "flags", NULL };
    PyObject *py_flags = NULL;
    CcItemFlags flags;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:CcItem.SET_FLAGS", kwlist, &py_flags))
        return NULL;
    if (pyg_flags_get_value(CC_TYPE_ITEM_FLAGS, py_flags, (gpointer)&flags))
        return NULL;
    
    CC_ITEM_SET_FLAGS(CC_ITEM(self->obj), flags);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_item_append(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "child", NULL };
    PyGObject *child;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcItem.append", kwlist, &PyCcItem_Type, &child))
        return NULL;
    
    cc_item_append(CC_ITEM(self->obj), CC_ITEM(child->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_item_bounds_changed(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "view", NULL };
    PyGObject *view;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcItem.bounds_changed", kwlist, &PyCcView_Type, &view))
        return NULL;
    
    cc_item_bounds_changed(CC_ITEM(self->obj), CC_VIEW(view->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

#line 142 "cccanvas.override"
static PyObject *
_wrap_cc_item_dirty(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "view", "dirty_region", NULL };
    PyGObject *view;
    PyObject *py_dirty_region;
    CcDRect *dirty_region = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O:CcItem.dirty", kwlist, &PyCcView_Type, &view, &py_dirty_region))
        return NULL;
    if (pyg_boxed_check(py_dirty_region, CC_TYPE_D_RECT))
        dirty_region = pyg_boxed_get(py_dirty_region, CcDRect);
    else {
        PyErr_SetString(PyExc_TypeError, "dirty_region should be a CcDRect");
        return NULL;
    }
    cc_item_dirty(CC_ITEM(self->obj), CC_VIEW(view->obj), *dirty_region);
    Py_INCREF(Py_None);
    return Py_None;
}
#line 589 "cccanvas.c"


#line 164 "cccanvas.override"
static PyObject *
_wrap_cc_item_distance(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    PyObject *pyfound;
    CcItem *found = NULL;
    double x, y, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd!:CcItem.distance", kwlist, &x, &y))
        return NULL;
    ret = cc_item_distance(CC_ITEM(self->obj), x, y, &found);

    pyfound = pygobject_new(G_OBJECT(found));

    PyObject *pylist = PyList_New(2);

    PyList_SetItem(pylist, 0, PyFloat_FromDouble(ret));
    PyList_SetItem(pylist, 1, (PyObject *)pyfound);

    return pylist;
}
#line 614 "cccanvas.c"


#line 187 "cccanvas.override"

typedef struct {
PyObject *data;
PyObject *func;
int count_views;
} CallBackData;

void py_foreach_func(CcItem* item, CcView* view, gpointer data){
	CallBackData *cb_data = (CallBackData*) data;

	PyObject *pydata = cb_data->data;
	PyObject *pyfunc = cb_data->func;
	PyObject *arg;

	printf(" View %p\n", view);

	int i, n_args = PyTuple_Size(pydata);

	PyObject *args = PyTuple_New(2+n_args);
	
	PyTuple_SetItem( args, 0, pygobject_new(G_OBJECT(item)));
	PyTuple_SetItem( args, 1, pygobject_new(G_OBJECT(view)));

	for (i = 0; i < n_args; i++){
	    arg = PyTuple_GetItem(pydata, i);
	    Py_INCREF(arg);
            PyTuple_SetItem( args, i+2, arg);
	}

	PyObject *ret = PyObject_CallObject( pyfunc, args); 

	/* Check last view */
	//printf("view countdown %d\n", cb_data->count_views);

	if (cb_data->count_views == 1){
           g_free (cb_data);
	   Py_DECREF(pyfunc);
	   Py_DECREF(pydata);
	}
	else 
	   cb_data->count_views--;

	Py_DECREF(args);


	if (ret == NULL)
           return;

	Py_DECREF(ret);

	return;
}

static PyObject *
_wrap_cc_item_foreach_view(PyGObject *self, PyObject *args)
{
    PyObject *pydata, *pyfunc;
    PyObject *arg;
    CcItem *item;
    CallBackData *cb_data = g_malloc0( sizeof(CallBackData));

    int i, n_args = PyTuple_Size(args);

    if (n_args < 1){
        PyErr_SetString(PyExc_SyntaxError, "CcItem.foreach_view take at least a callback function argument");
	return NULL;
	}

    pyfunc = PyTuple_GetItem(	args, 0);

    if (!PyCallable_Check( pyfunc)){
        PyErr_SetString(PyExc_TypeError, "CcItem.foreach_view first argument must be a callable function");
	return NULL;
	}

    pydata = PyTuple_New(n_args-1);

    for (i = 1; i< n_args; i++){
	arg = PyTuple_GetItem(args, i);
	Py_INCREF(arg);
	PyTuple_SetItem(pydata, i-1, PyTuple_GetItem(args, i));
	}

    cb_data->data = pydata;
    cb_data->func = pyfunc;	

    Py_INCREF(cb_data->func);

    /* need to know how views are been called 
       to free correctly the data */
    int n_views = 0;

    for (item = CC_ITEM(self->obj); item; item = item->parent)
	n_views += g_list_length(item->views);

    //printf("Will call %d views\n",n_views);

    cb_data->count_views = n_views;

    cc_item_foreach_view(CC_ITEM(self->obj), py_foreach_func, (gpointer) cb_data);

    Py_INCREF(Py_None);
    return Py_None;
}
#line 722 "cccanvas.c"


static PyObject *
_wrap_cc_item_grab_focus(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "view", NULL };
    PyGObject *view;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcItem.grab_focus", kwlist, &PyCcView_Type, &view))
        return NULL;
    
    cc_item_grab_focus(CC_ITEM(self->obj), CC_VIEW(view->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_item_insert(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "child", "position", NULL };
    PyGObject *child;
    int position;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!i:CcItem.insert", kwlist, &PyCcItem_Type, &child, &position))
        return NULL;
    
    cc_item_insert(CC_ITEM(self->obj), CC_ITEM(child->obj), position);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_item_is_child_of(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "parent", NULL };
    PyGObject *parent;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcItem.is_child_of", kwlist, &PyCcItem_Type, &parent))
        return NULL;
    
    ret = cc_item_is_child_of(CC_ITEM(self->obj), CC_ITEM(parent->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_cc_item_remove(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "child", NULL };
    PyGObject *child;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcItem.remove", kwlist, &PyCcItem_Type, &child))
        return NULL;
    
    cc_item_remove(CC_ITEM(self->obj), CC_ITEM(child->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_item_set_grid_aligned(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "grid_aligned", NULL };
    int grid_aligned;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:CcItem.set_grid_aligned", kwlist, &grid_aligned))
        return NULL;
    
    cc_item_set_grid_aligned(CC_ITEM(self->obj), grid_aligned);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_item_add_view(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "view", NULL };
    PyGObject *view;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcItem.add_view", kwlist, &PyCcView_Type, &view))
        return NULL;
    
    cc_item_add_view(CC_ITEM(self->obj), CC_VIEW(view->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_item_remove_view(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "view", NULL };
    PyGObject *view;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcItem.remove_view", kwlist, &PyCcView_Type, &view))
        return NULL;
    
    cc_item_remove_view(CC_ITEM(self->obj), CC_VIEW(view->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyCcItem_methods[] = {
    { "SET_FLAGS", (PyCFunction)_wrap_CC_ITEM_SET_FLAGS, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "append", (PyCFunction)_wrap_cc_item_append, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "bounds_changed", (PyCFunction)_wrap_cc_item_bounds_changed, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "dirty", (PyCFunction)_wrap_cc_item_dirty, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "distance", (PyCFunction)_wrap_cc_item_distance, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "foreach_view", (PyCFunction)_wrap_cc_item_foreach_view, METH_VARARGS,
      NULL },
    { "grab_focus", (PyCFunction)_wrap_cc_item_grab_focus, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "insert", (PyCFunction)_wrap_cc_item_insert, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "is_child_of", (PyCFunction)_wrap_cc_item_is_child_of, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "remove", (PyCFunction)_wrap_cc_item_remove, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_grid_aligned", (PyCFunction)_wrap_cc_item_set_grid_aligned, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "add_view", (PyCFunction)_wrap_cc_item_add_view, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "remove_view", (PyCFunction)_wrap_cc_item_remove_view, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcItem_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.Item",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcItem_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_cc_item_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcItemView ----------- */

static PyObject *
_wrap_cc_item_view_register(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "item", NULL };
    PyGObject *item;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcItemView.register", kwlist, &PyCcItem_Type, &item))
        return NULL;
    
    cc_item_view_register(CC_ITEM_VIEW(self->obj), CC_ITEM(item->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_item_view_unregister(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "item", NULL };
    PyGObject *item;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcItemView.unregister", kwlist, &PyCcItem_Type, &item))
        return NULL;
    
    cc_item_view_unregister(CC_ITEM_VIEW(self->obj), CC_ITEM(item->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyCcItemView_methods[] = {
    { "register", (PyCFunction)_wrap_cc_item_view_register, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "unregister", (PyCFunction)_wrap_cc_item_view_unregister, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcItemView_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.ItemView",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcItemView_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcPixbuf ----------- */

static int
_wrap_cc_pixbuf_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":ccc.Pixbuf.__init__",
                                     kwlist))
        return -1;

    pygobject_constructv(self, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create ccc.Pixbuf object");
        return -1;
    }
    g_object_ref(self->obj);

    return 0;
}

static PyObject *
_wrap_cc_pixbuf_set_pixbuf(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "pixbuf", NULL };
    PyGObject *pixbuf;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcPixbuf.set_pixbuf", kwlist, &PyGdkPixbuf_Type, &pixbuf))
        return NULL;
    
    cc_pixbuf_set_pixbuf(CC_PIXBUF(self->obj), GDK_PIXBUF(pixbuf->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_pixbuf_set_position(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", "w", "h", NULL };
    double x, y, w, h;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"dddd:CcPixbuf.set_position", kwlist, &x, &y, &w, &h))
        return NULL;
    
    cc_pixbuf_set_position(CC_PIXBUF(self->obj), x, y, w, h);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyCcPixbuf_methods[] = {
    { "set_pixbuf", (PyCFunction)_wrap_cc_pixbuf_set_pixbuf, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_position", (PyCFunction)_wrap_cc_pixbuf_set_position, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcPixbuf_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.Pixbuf",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcPixbuf_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_cc_pixbuf_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcPrinter ----------- */

static int
_wrap_cc_printer_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "filename", NULL };
    char *filename;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:CcPrinter.__init__", kwlist, &filename))
        return -1;
    self->obj = (GObject *)cc_printer_new(filename);

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create CcPrinter object");
        return -1;
    }
    g_object_ref(self->obj);
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_cc_printer_print_page(PyGObject *self)
{
    
    cc_printer_print_page(CC_PRINTER(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyCcPrinter_methods[] = {
    { "print_page", (PyCFunction)_wrap_cc_printer_print_page, METH_NOARGS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcPrinter_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.Printer",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcPrinter_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_cc_printer_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcShape ----------- */

static PyObject *
_wrap_cc_shape_get_brush_border(PyGObject *self)
{
    CcBrush *ret;

    
    ret = cc_shape_get_brush_border(CC_SHAPE(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_cc_shape_set_brush_border(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "brush", NULL };
    PyGObject *brush;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcShape.set_brush_border", kwlist, &PyCcBrush_Type, &brush))
        return NULL;
    
    cc_shape_set_brush_border(CC_SHAPE(self->obj), CC_BRUSH(brush->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_shape_get_brush_content(PyGObject *self)
{
    CcBrush *ret;

    
    ret = cc_shape_get_brush_content(CC_SHAPE(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_cc_shape_set_brush_content(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "brush", NULL };
    PyGObject *brush;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcShape.set_brush_content", kwlist, &PyCcBrush_Type, &brush))
        return NULL;
    
    cc_shape_set_brush_content(CC_SHAPE(self->obj), CC_BRUSH(brush->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_shape_get_width(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "view", NULL };
    PyGObject *view;
    double ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcShape.get_width", kwlist, &PyCcView_Type, &view))
        return NULL;
    
    ret = cc_shape_get_width(CC_SHAPE(self->obj), CC_VIEW(view->obj));
    
    return PyFloat_FromDouble(ret);
}

static PyObject *
_wrap_cc_shape_set_width_pixels(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "width", NULL };
    double width;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"d:CcShape.set_width_pixels", kwlist, &width))
        return NULL;
    
    cc_shape_set_width_pixels(CC_SHAPE(self->obj), width);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_shape_set_width_units(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "width", NULL };
    double width;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"d:CcShape.set_width_units", kwlist, &width))
        return NULL;
    
    cc_shape_set_width_units(CC_SHAPE(self->obj), width);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyCcShape_methods[] = {
    { "get_brush_border", (PyCFunction)_wrap_cc_shape_get_brush_border, METH_NOARGS,
      NULL },
    { "set_brush_border", (PyCFunction)_wrap_cc_shape_set_brush_border, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_brush_content", (PyCFunction)_wrap_cc_shape_get_brush_content, METH_NOARGS,
      NULL },
    { "set_brush_content", (PyCFunction)_wrap_cc_shape_set_brush_content, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_width", (PyCFunction)_wrap_cc_shape_get_width, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_width_pixels", (PyCFunction)_wrap_cc_shape_set_width_pixels, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_width_units", (PyCFunction)_wrap_cc_shape_set_width_units, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcShape_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.Shape",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcShape_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcRectangle ----------- */

static int
_wrap_cc_rectangle_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":ccc.Rectangle.__init__",
                                     kwlist))
        return -1;

    pygobject_constructv(self, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create ccc.Rectangle object");
        return -1;
    }
    g_object_ref(self->obj);

    return 0;
}

static PyObject *
_wrap_cc_rectangle_set_position(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", "w", "h", NULL };
    double x, y, w, h;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"dddd:CcRectangle.set_position", kwlist, &x, &y, &w, &h))
        return NULL;
    
    cc_rectangle_set_position(CC_RECTANGLE(self->obj), x, y, w, h);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_rectangle_set_x(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", NULL };
    double x;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"d:CcRectangle.set_x", kwlist, &x))
        return NULL;
    
    cc_rectangle_set_x(CC_RECTANGLE(self->obj), x);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_rectangle_set_y(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "y", NULL };
    double y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"d:CcRectangle.set_y", kwlist, &y))
        return NULL;
    
    cc_rectangle_set_y(CC_RECTANGLE(self->obj), y);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_rectangle_set_width(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "width", NULL };
    double width;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"d:CcRectangle.set_width", kwlist, &width))
        return NULL;
    
    cc_rectangle_set_width(CC_RECTANGLE(self->obj), width);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_rectangle_set_height(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "height", NULL };
    double height;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"d:CcRectangle.set_height", kwlist, &height))
        return NULL;
    
    cc_rectangle_set_height(CC_RECTANGLE(self->obj), height);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyCcRectangle_methods[] = {
    { "set_position", (PyCFunction)_wrap_cc_rectangle_set_position, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_x", (PyCFunction)_wrap_cc_rectangle_set_x, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_y", (PyCFunction)_wrap_cc_rectangle_set_y, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_width", (PyCFunction)_wrap_cc_rectangle_set_width, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_height", (PyCFunction)_wrap_cc_rectangle_set_height, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcRectangle_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.Rectangle",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcRectangle_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_cc_rectangle_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcRoundedRectangle ----------- */

PyTypeObject G_GNUC_INTERNAL PyCcRoundedRectangle_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.RoundedRectangle",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcLine ----------- */

static int
_wrap_cc_line_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":ccc.Line.__init__",
                                     kwlist))
        return -1;

    pygobject_constructv(self, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create ccc.Line object");
        return -1;
    }
    g_object_ref(self->obj);

    return 0;
}

static PyObject *
_wrap_cc_line_line(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"dd:CcLine.line", kwlist, &x, &y))
        return NULL;
    
    cc_line_line(CC_LINE(self->obj), x, y);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_line_move(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"dd:CcLine.move", kwlist, &x, &y))
        return NULL;
    
    cc_line_move(CC_LINE(self->obj), x, y);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyCcLine_methods[] = {
    { "line", (PyCFunction)_wrap_cc_line_line, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "move", (PyCFunction)_wrap_cc_line_move, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcLine_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.Line",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcLine_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_cc_line_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcCircle ----------- */

static int
_wrap_cc_circle_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":ccc.Circle.__init__",
                                     kwlist))
        return -1;

    pygobject_constructv(self, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create ccc.Circle object");
        return -1;
    }
    g_object_ref(self->obj);

    return 0;
}

static PyObject *
_wrap_cc_circle_set_anchor(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"dd:CcCircle.set_anchor", kwlist, &x, &y))
        return NULL;
    
    cc_circle_set_anchor(CC_CIRCLE(self->obj), x, y);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_circle_set_radius(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "radius", NULL };
    double radius;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"d:CcCircle.set_radius", kwlist, &radius))
        return NULL;
    
    cc_circle_set_radius(CC_CIRCLE(self->obj), radius);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyCcCircle_methods[] = {
    { "set_anchor", (PyCFunction)_wrap_cc_circle_set_anchor, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_radius", (PyCFunction)_wrap_cc_circle_set_radius, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcCircle_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.Circle",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcCircle_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_cc_circle_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcText ----------- */

#line 381 "cccanvas.override"
static int
_wrap_cc_text_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "text", NULL };
    char *text = "";

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|z:CcText.__init__", kwlist, &text))
        return -1;

    self->obj = (GObject *)cc_text_new(text);

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create CcText object");
        return -1;
    }
    g_object_ref(self->obj);
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

#line 1805 "cccanvas.c"


static PyObject *
_wrap_cc_text_is_editable(PyGObject *self)
{
    int ret;

    
    ret = cc_text_is_editable(CC_TEXT(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_cc_text_set_anchor(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"dd:CcText.set_anchor", kwlist, &x, &y))
        return NULL;
    
    cc_text_set_anchor(CC_TEXT(self->obj), x, y);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_text_set_anchor_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "anchor", NULL };
    PyObject *py_anchor = NULL;
    GtkAnchorType anchor;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:CcText.set_anchor_type", kwlist, &py_anchor))
        return NULL;
    if (pyg_enum_get_value(GTK_TYPE_ANCHOR_TYPE, py_anchor, (gpointer)&anchor))
        return NULL;
    
    cc_text_set_anchor_type(CC_TEXT(self->obj), anchor);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_text_set_editable(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "editable", NULL };
    int editable;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:CcText.set_editable", kwlist, &editable))
        return NULL;
    
    cc_text_set_editable(CC_TEXT(self->obj), editable);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_text_set_font_description(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "desc", NULL };
    PyObject *py_desc;
    PangoFontDescription *desc = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:CcText.set_font_description", kwlist, &py_desc))
        return NULL;
    if (pyg_boxed_check(py_desc, PANGO_TYPE_FONT_DESCRIPTION))
        desc = pyg_boxed_get(py_desc, PangoFontDescription);
    else {
        PyErr_SetString(PyExc_TypeError, "desc should be a PangoFontDescription");
        return NULL;
    }
    
    cc_text_set_font_description(CC_TEXT(self->obj), desc);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_text_set_markup(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "text", NULL };
    char *text;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:CcText.set_markup", kwlist, &text))
        return NULL;
    
    cc_text_set_markup(CC_TEXT(self->obj), text);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_text_set_size_pixels(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "size_pixels", NULL };
    int size_pixels;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:CcText.set_size_pixels", kwlist, &size_pixels))
        return NULL;
    
    cc_text_set_size_pixels(CC_TEXT(self->obj), size_pixels);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_text_set_text(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "text", NULL };
    char *text;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:CcText.set_text", kwlist, &text))
        return NULL;
    
    cc_text_set_text(CC_TEXT(self->obj), text);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_text_get_text(PyGObject *self)
{
    const gchar *ret;

    
    ret = cc_text_get_text(CC_TEXT(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyCcText_methods[] = {
    { "is_editable", (PyCFunction)_wrap_cc_text_is_editable, METH_NOARGS,
      NULL },
    { "set_anchor", (PyCFunction)_wrap_cc_text_set_anchor, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_anchor_type", (PyCFunction)_wrap_cc_text_set_anchor_type, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_editable", (PyCFunction)_wrap_cc_text_set_editable, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_font_description", (PyCFunction)_wrap_cc_text_set_font_description, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_markup", (PyCFunction)_wrap_cc_text_set_markup, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_size_pixels", (PyCFunction)_wrap_cc_text_set_size_pixels, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_text", (PyCFunction)_wrap_cc_text_set_text, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_text", (PyCFunction)_wrap_cc_text_get_text, METH_NOARGS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcText_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.Text",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcText_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_cc_text_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcView ----------- */

static PyObject *
_wrap_cc_view_get_focus(PyGObject *self)
{
    CcItem *ret;

    
    ret = cc_view_get_focus(CC_VIEW(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_cc_view_get_root(PyGObject *self)
{
    CcItem *ret;

    
    ret = cc_view_get_root(CC_VIEW(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_cc_view_get_scrolled_region(PyGObject *self)
{
    CcDRect *ret;

    
    ret = cc_view_get_scrolled_region(CC_VIEW(self->obj));
    
    /* pyg_boxed_new handles NULL checking */
    return pyg_boxed_new(CC_TYPE_D_RECT, ret, TRUE, TRUE);
}

static PyObject *
_wrap_cc_view_get_zoom(PyGObject *self)
{
    double ret;

    
    ret = cc_view_get_zoom(CC_VIEW(self->obj));
    
    return PyFloat_FromDouble(ret);
}

static PyObject *
_wrap_cc_view_set_focus(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "focus", NULL };
    PyGObject *focus;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcView.set_focus", kwlist, &PyCcItem_Type, &focus))
        return NULL;
    
    cc_view_set_focus(CC_VIEW(self->obj), CC_ITEM(focus->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_view_set_root(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "root", NULL };
    PyGObject *root;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:CcView.set_root", kwlist, &PyCcItem_Type, &root))
        return NULL;
    
    cc_view_set_root(CC_VIEW(self->obj), CC_ITEM(root->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_view_set_scrolled_region(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "scrolled_region", NULL };
    PyObject *py_scrolled_region = Py_None;
    CcDRect *scrolled_region = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:CcView.set_scrolled_region", kwlist, &py_scrolled_region))
        return NULL;
    if (pyg_boxed_check(py_scrolled_region, CC_TYPE_D_RECT))
        scrolled_region = pyg_boxed_get(py_scrolled_region, CcDRect);
    else if (py_scrolled_region != Py_None) {
        PyErr_SetString(PyExc_TypeError, "scrolled_region should be a CcDRect or None");
        return NULL;
    }
    
    cc_view_set_scrolled_region(CC_VIEW(self->obj), scrolled_region);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_view_set_zoom(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "zoom", NULL };
    double zoom;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"d:CcView.set_zoom", kwlist, &zoom))
        return NULL;
    
    cc_view_set_zoom(CC_VIEW(self->obj), zoom);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_view_grab_item(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "item", "mask", "cursor", "time", NULL };
    PyObject *py_mask = NULL, *py_cursor;
    int ret;
    unsigned long time;
    GdkCursor *cursor = NULL;
    PyGObject *item;
    GdkEventMask mask;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!OOk:CcView.grab_item", kwlist, &PyCcItem_Type, &item, &py_mask, &py_cursor, &time))
        return NULL;
    if (pyg_flags_get_value(GDK_TYPE_EVENT_MASK, py_mask, (gpointer)&mask))
        return NULL;
    if (pyg_boxed_check(py_cursor, GDK_TYPE_CURSOR))
        cursor = pyg_boxed_get(py_cursor, GdkCursor);
    else {
        PyErr_SetString(PyExc_TypeError, "cursor should be a GdkCursor");
        return NULL;
    }
    
    ret = cc_view_grab_item(CC_VIEW(self->obj), CC_ITEM(item->obj), mask, cursor, time);
    
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_cc_view_ungrab_item(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "item", "time", NULL };
    PyGObject *item;
    unsigned long time;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!k:CcView.ungrab_item", kwlist, &PyCcItem_Type, &item, &time))
        return NULL;
    
    cc_view_ungrab_item(CC_VIEW(self->obj), CC_ITEM(item->obj), time);
    
    Py_INCREF(Py_None);
    return Py_None;
}

#line 293 "cccanvas.override"
static PyObject *
_wrap_cc_view_window_to_world(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    double x, y;
    gdouble local_x, local_y;
    PyObject *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd:CcView.window_to_world", kwlist, &x, &y))
        return NULL;

    local_x = x;
    local_y = y;

    cc_view_window_to_world(CC_VIEW(self->obj), &local_x,  &local_y);

    ret = PyTuple_New(2);

    PyTuple_SetItem(ret, 0, PyLong_FromDouble(local_x));
    PyTuple_SetItem(ret, 1, PyLong_FromDouble(local_y));

    return ret;
}
#line 2201 "cccanvas.c"


#line 318 "cccanvas.override"
static PyObject *
_wrap_cc_view_world_to_window(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    double x, y;
    gdouble local_x, local_y;
    PyObject *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd:CcView.world_to_window", kwlist, &x, &y))
        return NULL;

    local_x = x;
    local_y = y;

    cc_view_world_to_window(CC_VIEW(self->obj), &local_x, &local_y);

    ret = PyTuple_New(2);

    PyTuple_SetItem(ret, 0, PyLong_FromDouble(local_x));
    PyTuple_SetItem(ret, 1, PyLong_FromDouble(local_y));

    return ret;
}
#line 2228 "cccanvas.c"


#line 343 "cccanvas.override"

static PyObject *
_wrap_cc_view_world_to_window_distance(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    double x, y;
    gdouble local_x, local_y;
    PyObject *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd:CcView.world_to_window_distance", kwlist, &x, &y))
        return NULL;

    local_x = x;
    local_y = y;

    cc_view_world_to_window_distance(CC_VIEW(self->obj), &local_x, &local_y);

    ret = PyTuple_New(2);

    PyTuple_SetItem(ret, 0, PyLong_FromDouble(local_x));
    PyTuple_SetItem(ret, 1, PyLong_FromDouble(local_y));

    return ret;
}
#line 2256 "cccanvas.c"


#line 369 "cccanvas.override"

static PyObject *
_wrap_cc_view_widget_get_center_view(PyGObject *self)
{
    int ret;

    ret = cc_view_widget_get_center_view((CcViewWidget const*) self->obj);
    return PyBool_FromLong(ret);

}
#line 2270 "cccanvas.c"


static const PyMethodDef _PyCcView_methods[] = {
    { "get_focus", (PyCFunction)_wrap_cc_view_get_focus, METH_NOARGS,
      NULL },
    { "get_root", (PyCFunction)_wrap_cc_view_get_root, METH_NOARGS,
      NULL },
    { "get_scrolled_region", (PyCFunction)_wrap_cc_view_get_scrolled_region, METH_NOARGS,
      NULL },
    { "get_zoom", (PyCFunction)_wrap_cc_view_get_zoom, METH_NOARGS,
      NULL },
    { "set_focus", (PyCFunction)_wrap_cc_view_set_focus, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_root", (PyCFunction)_wrap_cc_view_set_root, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_scrolled_region", (PyCFunction)_wrap_cc_view_set_scrolled_region, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_zoom", (PyCFunction)_wrap_cc_view_set_zoom, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "grab_item", (PyCFunction)_wrap_cc_view_grab_item, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "ungrab_item", (PyCFunction)_wrap_cc_view_ungrab_item, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "window_to_world", (PyCFunction)_wrap_cc_view_window_to_world, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "world_to_window", (PyCFunction)_wrap_cc_view_world_to_window, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "world_to_window_distance", (PyCFunction)_wrap_cc_view_world_to_window_distance, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_center_view", (PyCFunction)_wrap_cc_view_widget_get_center_view, METH_NOARGS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcView_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.View",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcView_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcViewCellRenderer ----------- */

static int
_wrap_cc_view_cell_renderer_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":ccc.ViewCellRenderer.__init__",
                                     kwlist))
        return -1;

    pygobject_constructv(self, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create ccc.ViewCellRenderer object");
        return -1;
    }
    g_object_ref(self->obj);

    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyCcViewCellRenderer_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.ViewCellRenderer",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_cc_view_cell_renderer_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcViewPNG ----------- */

PyTypeObject G_GNUC_INTERNAL PyCcViewPNG_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.ViewPNG",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- CcViewWidget ----------- */

static int
_wrap_cc_view_widget_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":ccc.ViewWidget.__init__",
                                     kwlist))
        return -1;

    pygobject_constructv(self, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create ccc.ViewWidget object");
        return -1;
    }
    g_object_ref(self->obj);

    return 0;
}

static PyObject *
_wrap_cc_view_widget_set_center_view(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "center_view", NULL };
    int center_view;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:CcViewWidget.set_center_view", kwlist, &center_view))
        return NULL;
    
    cc_view_widget_set_center_view(CC_VIEW_WIDGET(self->obj), center_view);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_cc_view_widget_get_zoom_mode(PyGObject *self)
{
    gint ret;

    
    ret = cc_view_widget_get_zoom_mode(CC_VIEW_WIDGET(self->obj));
    
    return pyg_enum_from_gtype(CC_TYPE_ZOOM_MODE, ret);
}

static PyObject *
_wrap_cc_view_widget_set_zoom_mode(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "zoom_mode", NULL };
    PyObject *py_zoom_mode = NULL;
    CcZoomMode zoom_mode;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:CcViewWidget.set_zoom_mode", kwlist, &py_zoom_mode))
        return NULL;
    if (pyg_enum_get_value(CC_TYPE_ZOOM_MODE, py_zoom_mode, (gpointer)&zoom_mode))
        return NULL;
    
    cc_view_widget_set_zoom_mode(CC_VIEW_WIDGET(self->obj), zoom_mode);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyCcViewWidget_methods[] = {
    { "set_center_view", (PyCFunction)_wrap_cc_view_widget_set_center_view, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_zoom_mode", (PyCFunction)_wrap_cc_view_widget_get_zoom_mode, METH_NOARGS,
      NULL },
    { "set_zoom_mode", (PyCFunction)_wrap_cc_view_widget_set_zoom_mode, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyCcViewWidget_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "ccc.ViewWidget",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyCcViewWidget_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_cc_view_widget_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- functions ----------- */

static PyObject *
_wrap_cc_color_new_rgb(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "red", "green", "blue", NULL };
    double red, green, blue;
    CcColor *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"ddd:color_new_rgb", kwlist, &red, &green, &blue))
        return NULL;
    
    ret = cc_color_new_rgb(red, green, blue);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_cc_color_new_rgba(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "red", "green", "blue", "alpha", NULL };
    double red, green, blue, alpha;
    CcColor *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"dddd:color_new_rgba", kwlist, &red, &green, &blue, &alpha))
        return NULL;
    
    ret = cc_color_new_rgba(red, green, blue, alpha);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_cc_color_new_hsv(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "hue", "saturation", "value", NULL };
    double hue, saturation, value;
    CcColor *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"ddd:color_new_hsv", kwlist, &hue, &saturation, &value))
        return NULL;
    
    ret = cc_color_new_hsv(hue, saturation, value);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_cc_color_new_hsva(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "hue", "saturation", "value", "alpha", NULL };
    double hue, saturation, value, alpha;
    CcColor *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"dddd:color_new_hsva", kwlist, &hue, &saturation, &value, &alpha))
        return NULL;
    
    ret = cc_color_new_hsva(hue, saturation, value, alpha);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_cc_view_widget_new_root(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "root", NULL };
    PyGObject *root;
    GtkWidget *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:view_widget_new_root", kwlist, &PyCcItem_Type, &root))
        return NULL;
    
    ret = cc_view_widget_new_root(CC_ITEM(root->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

const PyMethodDef pycccanvas_functions[] = {
    { "color_new_rgb", (PyCFunction)_wrap_cc_color_new_rgb, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "color_new_rgba", (PyCFunction)_wrap_cc_color_new_rgba, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "color_new_hsv", (PyCFunction)_wrap_cc_color_new_hsv, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "color_new_hsva", (PyCFunction)_wrap_cc_color_new_hsva, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "view_widget_new_root", (PyCFunction)_wrap_cc_view_widget_new_root, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};


/* ----------- enums and flags ----------- */

void
pycccanvas_add_constants(PyObject *module, const gchar *strip_prefix)
{
  pyg_flags_add(module, "ItemFlags", strip_prefix, CC_TYPE_ITEM_FLAGS);
  pyg_enum_add(module, "ZoomMode", strip_prefix, CC_TYPE_ZOOM_MODE);

  if (PyErr_Occurred())
    PyErr_Print();
}

/* initialise stuff extension classes */
void
pycccanvas_register_classes(PyObject *d)
{
    PyObject *module;

    if ((module = PyImport_ImportModule("gobject")) != NULL) {
        _PyGObject_Type = (PyTypeObject *)PyObject_GetAttrString(module, "GObject");
        if (_PyGObject_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name GObject from gobject");
            return ;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gobject");
        return ;
    }
    if ((module = PyImport_ImportModule("gtk.gdk")) != NULL) {
        _PyGdkPixbuf_Type = (PyTypeObject *)PyObject_GetAttrString(module, "Pixbuf");
        if (_PyGdkPixbuf_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Pixbuf from gtk.gdk");
            return ;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gtk.gdk");
        return ;
    }
    if ((module = PyImport_ImportModule("gtk._gtk")) != NULL) {
        _PyGtkCellRenderer_Type = (PyTypeObject *)PyObject_GetAttrString(module, "CellRenderer");
        if (_PyGtkCellRenderer_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name CellRenderer from gtk._gtk");
            return ;
        }
        _PyGtkDrawingArea_Type = (PyTypeObject *)PyObject_GetAttrString(module, "DrawingArea");
        if (_PyGtkDrawingArea_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name DrawingArea from gtk._gtk");
            return ;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gtk._gtk");
        return ;
    }


#line 2756 "cccanvas.c"
    pyg_register_boxed(d, "DRect", CC_TYPE_D_RECT, &PyCcDRect_Type);
    pygobject_register_class(d, "CcBrush", CC_TYPE_BRUSH, &PyCcBrush_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_BRUSH);
    pygobject_register_class(d, "CcBrushColor", CC_TYPE_BRUSH_COLOR, &PyCcBrushColor_Type, Py_BuildValue("(O)", &PyCcBrush_Type));
    pygobject_register_class(d, "CcColor", CC_TYPE_COLOR, &PyCcColor_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_COLOR);
    pygobject_register_class(d, "CcItem", CC_TYPE_ITEM, &PyCcItem_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_ITEM);
    pygobject_register_class(d, "CcItemView", CC_TYPE_ITEM_VIEW, &PyCcItemView_Type, NULL);
    pygobject_register_class(d, "CcPixbuf", CC_TYPE_PIXBUF, &PyCcPixbuf_Type, Py_BuildValue("(O)", &PyCcItem_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_PIXBUF);
    pygobject_register_class(d, "CcPrinter", CC_TYPE_PRINTER, &PyCcPrinter_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "CcShape", CC_TYPE_SHAPE, &PyCcShape_Type, Py_BuildValue("(O)", &PyCcItem_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_SHAPE);
    pygobject_register_class(d, "CcRectangle", CC_TYPE_RECTANGLE, &PyCcRectangle_Type, Py_BuildValue("(O)", &PyCcShape_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_RECTANGLE);
    pygobject_register_class(d, "CcRoundedRectangle", CC_TYPE_ROUNDED_RECTANGLE, &PyCcRoundedRectangle_Type, Py_BuildValue("(O)", &PyCcRectangle_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_ROUNDED_RECTANGLE);
    pygobject_register_class(d, "CcLine", CC_TYPE_LINE, &PyCcLine_Type, Py_BuildValue("(O)", &PyCcShape_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_LINE);
    pygobject_register_class(d, "CcCircle", CC_TYPE_CIRCLE, &PyCcCircle_Type, Py_BuildValue("(O)", &PyCcShape_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_CIRCLE);
    pygobject_register_class(d, "CcText", CC_TYPE_TEXT, &PyCcText_Type, Py_BuildValue("(O)", &PyCcItem_Type));
    pygobject_register_class(d, "CcView", CC_TYPE_VIEW, &PyCcView_Type, NULL);
    pygobject_register_class(d, "CcViewCellRenderer", CC_TYPE_VIEW_CELL_RENDERER, &PyCcViewCellRenderer_Type, Py_BuildValue("(OO)", &PyGtkCellRenderer_Type, &PyCcView_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_VIEW_CELL_RENDERER);
    pygobject_register_class(d, "CcViewPNG", CC_TYPE_VIEW_PNG, &PyCcViewPNG_Type, Py_BuildValue("(OO)", &PyGObject_Type, &PyCcView_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_VIEW_PNG);
    pygobject_register_class(d, "CcViewWidget", CC_TYPE_VIEW_WIDGET, &PyCcViewWidget_Type, Py_BuildValue("(OO)", &PyGtkDrawingArea_Type, &PyCcView_Type));
    pyg_set_object_has_new_constructor(CC_TYPE_VIEW_WIDGET);
}
