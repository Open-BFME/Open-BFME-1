// cl: /O2 /MD
struct IDispatch;
long __cdecl _com_dispatch_method(IDispatch *, long, unsigned short,
    unsigned short, void *, const unsigned short *, ...);
long __cdecl _com_dispatch_raw_method(IDispatch *, long, unsigned short,
    unsigned short, void *, const unsigned short *, ...);

long __stdcall bfmeRva00AFD610DispatchMethod(IDispatch *dispatch, long id,
    unsigned short flags, void *result)
{
    return _com_dispatch_method(dispatch, id, 2, flags, result, 0);
}

long __stdcall bfmeRva00AFE1C0DispatchRawMethod(IDispatch *dispatch, long id,
    unsigned short flags, void *result)
{
    return _com_dispatch_raw_method(dispatch, id, 2, flags, result, 0);
}
