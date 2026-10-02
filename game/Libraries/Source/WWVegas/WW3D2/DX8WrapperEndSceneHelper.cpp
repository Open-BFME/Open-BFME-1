// cl: /DNDEBUG /MD /EHsc

// Retail 0x00958910 is the COM dispatch helper called by
// DX8Wrapper::End_Scene after EndScene.  Its caller pushes one value and
// removes it after the call, so the helper is cdecl with one argument.

struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;

extern void __stdcall _com_issue_errorex(long error, IUnknown *object,
	const GUID &iid);

// Retail 0x0113DF00: the uuid attribute on IFEBrowserEngine2 (see
// DX8WebBrowserInitialize.cpp) makes the compiler reference this C-linkage
// GUID constant by its __GUID_<uuid> spelling, so that is the name used here.
extern "C" const GUID __GUID_ee883b17_0778_4b18_a12b_e44c0d298412;

struct Rva00958910Object;

struct Rva00958910Vtable
{
	void *slot00;
	void *slot04;
	void *slot08;
	void *slot0c;
	void *slot10;
	void *slot14;
	void *slot18;
	void *slot1c;
	void *slot20;
	void *slot24;
	void *slot28;
	void *slot2c;
	void *slot30;
	void *slot34;
	long (__stdcall *slot38)(Rva00958910Object *self, void *argument);
};

struct Rva00958910Object
{
	Rva00958910Vtable *vtable;

	long invoke(void *argument)
	{
		long result = vtable->slot38(this, argument);
		if (result < 0)
			_com_issue_errorex(result, (IUnknown *)this,
				__GUID_ee883b17_0778_4b18_a12b_e44c0d298412);
		return result;
	}
};

struct Rva00959410Ptr
{
	Rva00958910Object *m_p;

	operator bool() const
	{
		return m_p != 0;
	}

	Rva00958910Object *operator->() const
	{
		return m_p;
	}
};

extern Rva00959410Ptr Rva00959410Dispatch;

// ?bfmeEndSceneTouch00958910@@YAXPAX@Z
void bfmeEndSceneTouch00958910(void *argument)
{
	if (Rva00959410Dispatch)
		Rva00959410Dispatch->invoke(argument);
}
