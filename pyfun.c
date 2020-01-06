#define PY_SSIZE_T_CLEAN
#include <Python.h>


int
fun(char *file_name, char *fun_name, int in1, int in2)
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

 /*   if (argc < 3) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return 1;
    }*/

    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault(file_name);//File name
		//pName = "multiply";


    pModule = PyImport_Import(pName);
    Py_DECREF(pName);


    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, fun_name);//Function name
        // pFunc is a new reference 


        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);

            pValue = PyLong_FromLong(in1);
						PyTuple_SetItem(pArgs, 0, pValue);
            pValue = PyLong_FromLong(in2);
						PyTuple_SetItem(pArgs, 1, pValue);
            for (i = 0; i < 2; ++i) {
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                // pValue reference stolen here: 
                //PyTuple_SetItem(pArgs, i, pValue);
            }
						

            pValue = PyObject_CallObject(pFunc, pArgs);

            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", 11);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n",12);
        return 1;
    }
    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}

int main()
{
printf("Calling function...\n");
	fun("multiply","multiply",13,4);
}
