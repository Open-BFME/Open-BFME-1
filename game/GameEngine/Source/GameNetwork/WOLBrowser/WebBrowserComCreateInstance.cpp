// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PLAT~MIB/Include

// BrowserEngine.DLL is absent from the source distribution, so reproduce the
// type-library declaration needed by the compiler-generated smart pointer.
// The IID is the one embedded in retail at VA 0x0113DF00.  The genuine
// Platform SDK IDispatch declaration supplies its seven-slot COM prefix; the
// retail browser calls begin at the following slot.  No interface method is
// implemented in this translation unit.

#include <objbase.h>
#include <comip.h>

struct __declspec(uuid("ee883b17-0778-4b18-a12b-e44c0d298412"))
	IFEBrowserEngine2 : IDispatch
{
};

typedef _com_ptr_t<
	_com_IIID<IFEBrowserEngine2, &__uuidof(IFEBrowserEngine2)> >
	IFEBrowserEngine2Ptr;

// Emit the genuine VS2003 comip.h specialization used by
// DX8WebBrowser::Initialize.  Its first call is inlined in retail; the call at
// RVA 0x00958FF8 reaches this out-of-line COMDAT body at RVA 0x00958AB0.
template HRESULT IFEBrowserEngine2Ptr::CreateInstance(
	const CLSID &class_id, IUnknown *outer, DWORD context) throw();
