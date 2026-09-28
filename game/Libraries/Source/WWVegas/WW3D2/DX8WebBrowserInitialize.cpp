// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PLAT~MIB/Include
// RVA 0x00958F20: int3 before start, ret at 0x009591EC then three int3.
// BrowserEngine.DLL / DllRegisterServer and the interface / class UUIDs
// identify DX8WebBrowser::Initialize. Native VS2003 COM smart-pointer code
// reproduces the complete 717-byte body. Dependency proofs:
// WW3D::Get_Window at 0x008FD170 reads the witnessed WW3D HWND global;
// _bstr_t::Data_t::Release at 0x00958BF0 independently matches the native
// 70-byte InterlockedDecrement / string-buffer destruction implementation.
#include <objbase.h>
#include <comip.h>
extern void __stdcall _com_issue_errorex(HRESULT,IUnknown *,const IID &);
struct __declspec(uuid("ee883b17-0778-4b18-a12b-e44c0d298412")) IFEBrowserEngine2 : IDispatch {
    virtual HRESULT __stdcall raw_Initialize(long *) = 0;
    virtual void __stdcall slot08() = 0;
    virtual void __stdcall slot09() = 0;
    virtual void __stdcall slot10() = 0;
    virtual void __stdcall slot11() = 0;
    virtual void __stdcall slot12() = 0;
    virtual void __stdcall slot13() = 0;
    virtual void __stdcall slot14() = 0;
    virtual void __stdcall slot15() = 0;
    virtual void __stdcall slot16() = 0;
    virtual void __stdcall slot17() = 0;
    virtual void __stdcall slot18() = 0;
    virtual HRESULT __stdcall put_BadPageURL(BSTR) = 0;
    virtual void __stdcall slot20() = 0;
    virtual HRESULT __stdcall put_LoadingPageURL(BSTR) = 0;
    virtual void __stdcall slot22() = 0;
    virtual HRESULT __stdcall put_MouseFileName(BSTR) = 0;
    virtual void __stdcall slot24() = 0;
    virtual HRESULT __stdcall put_MouseBusyFileName(BSTR) = 0;
    void Initialize(long *device) {
        HRESULT hr=raw_Initialize(device);
        if (hr<0) _com_issue_errorex(hr,this,__uuidof(IFEBrowserEngine2));
    }
};
struct __declspec(uuid("2b2cc8b0-2dc0-48c6-b6fd-c07820a6477e")) FEBrowserEngine2;
typedef _com_ptr_t<_com_IIID<IFEBrowserEngine2,&__uuidof(IFEBrowserEngine2)> > IFEBrowserEngine2Ptr;
extern IFEBrowserEngine2Ptr Rva0134B280Browser;
class WW3D { public: static void *Get_Window(); };
struct IDirect3DDevice8;
class DX8Wrapper { private: static IDirect3DDevice8 *D3DDevice; public: static IDirect3DDevice8 *_Get_D3D_Device8(){return D3DDevice;} };
class DX8WebBrowser {
public:
    static HWND hWnd;
    static bool Initialize(const char *,const char *,const char *,const char *);
};
bool DX8WebBrowser::Initialize(const char *badpageurl,const char *loadingpageurl,const char *mousefilename,const char *mousebusyfilename)
{
    if (Rva0134B280Browser == 0) {
        CoInitialize(0);
        HRESULT hr=Rva0134B280Browser.CreateInstance(__uuidof(FEBrowserEngine2));
        if (hr == REGDB_E_CLASSNOTREG) {
            HMODULE lib=LoadLibraryA("BrowserEngine.DLL");
            if (lib) {
                FARPROC proc=GetProcAddress(lib,"DllRegisterServer");
                if (proc) {
                    proc();
                    hr=Rva0134B280Browser.CreateInstance(__uuidof(FEBrowserEngine2));
                }
                FreeLibrary(lib);
            }
        }
        if (hr == S_OK) {
            hWnd=(HWND)WW3D::Get_Window();
            Rva0134B280Browser->Initialize((long *)DX8Wrapper::_Get_D3D_Device8());
            if (badpageurl) Rva0134B280Browser->put_BadPageURL(_bstr_t(badpageurl));
            if (loadingpageurl) Rva0134B280Browser->put_LoadingPageURL(_bstr_t(loadingpageurl));
            if (mousefilename) Rva0134B280Browser->put_MouseFileName(_bstr_t(mousefilename));
            if (mousebusyfilename) Rva0134B280Browser->put_MouseBusyFileName(_bstr_t(mousebusyfilename));
        } else {
            Rva0134B280Browser=0;
            return false;
        }
    }
    return true;
}
