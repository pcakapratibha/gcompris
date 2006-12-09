
#include <pygobject.h>

void pygc_sound_register_classes (PyObject *d); 
extern PyMethodDef pygc_sound_functions[];

void pygc_sound_add_constants(PyObject *module, const gchar *strip_prefix);

DL_EXPORT(void) initgc_sound(void);

DL_EXPORT(void)
initgc_sound(void)
{
    PyObject *m, *d;
 
    init_pygobject ();
 
    m = Py_InitModule ("gc_sound", pygc_sound_functions);
    d = PyModule_GetDict (m);
 
    pygc_sound_register_classes (d);
    pygc_sound_add_constants (m, "");
 
    if (PyErr_Occurred ()) {
        Py_FatalError ("can't initialise module gc_sound");
    }
}
