// Visual C++ 7.1 ehvccctr.obj, recovered from retail: the compiler's vector
// copy-constructor iterator __ehvec_copy_ctor, ??__C (009F7036). A throwing
// element copy destroys the copies already made through __ArrayUnwind
// (ehvecdtr.cpp). The /d1Binl switch admits the native __thiscall callback
// type; see ehvecdtr.cpp.
// cl: /O1 /G6 /MD /EHsc /d1Binl
void __stdcall __ArrayUnwind(void *ptr, unsigned size, int count, void (__thiscall *pDtor)(void *));

void __stdcall __ehvec_copy_ctor(void *dst, void *src, unsigned size, int count, void (__thiscall *pCopyCtor)(void *, void *), void (__thiscall *pDtor)(void *))
{
    int i;
    int success = 0;
    __try
    {
        for (i = 0; i < count; i++)
        {
            (*pCopyCtor)(dst, src);
            dst = (char *)dst + size;
            src = (char *)src + size;
        }
        success = 1;
    }
    __finally
    {
        if (!success)
            __ArrayUnwind(dst, size, i, pDtor);
    }
}
