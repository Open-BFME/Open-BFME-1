// Visual C++ 7.1 ehvecctr.obj, recovered from retail: the compiler's vector
// constructor iterator __ehvec_ctor, ??_L (009F6EE4). A throwing element
// constructor destroys the elements already built through __ArrayUnwind
// (ehvecdtr.cpp). The /d1Binl switch admits the native __thiscall callback
// type; see ehvecdtr.cpp.
// cl: /O1 /G6 /MD /EHsc /d1Binl
void __stdcall __ArrayUnwind(void *ptr, unsigned size, int count, void (__thiscall *pDtor)(void *));

void __stdcall __ehvec_ctor(void *ptr, unsigned size, int count, void (__thiscall *pCtor)(void *), void (__thiscall *pDtor)(void *))
{
    int i;
    int success = 0;
    __try
    {
        for (i = 0; i < count; i++)
        {
            (*pCtor)(ptr);
            ptr = (char *)ptr + size;
        }
        success = 1;
    }
    __finally
    {
        if (!success)
            __ArrayUnwind(ptr, size, i, pDtor);
    }
}
