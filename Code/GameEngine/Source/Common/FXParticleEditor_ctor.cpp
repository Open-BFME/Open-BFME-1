// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef void *RvaModuleHandle;
typedef void *RvaProcAddress;

extern "C" __declspec(dllimport) RvaModuleHandle __stdcall LoadLibraryA(
	const char *name);
extern "C" __declspec(dllimport) RvaProcAddress __stdcall GetProcAddress(
	RvaModuleHandle module, const char *name);
extern __declspec(noreturn) void __stdcall _CxxThrowException(
	void *object, void *throwInfo);

class __declspec(dllimport) exception
{
public:
	exception();
	virtual ~exception();
};

class Rva0033AF00Exception : public exception
{
public:
	Rva0033AF00Exception() : exception()
	{
		*reinterpret_cast<void **>(this) = reinterpret_cast<void *>(0x010E75B4);
	}

private:
	char m_pad[8];
};

class Rva0033AF00Base
{
public:
	Rva0033AF00Base()
	{
		*reinterpret_cast<void **>(this) = reinterpret_cast<void *>(0x010E7520);
		m_module = LoadLibraryA("FXParticleEditorI.dll");
		if (m_module == 0)
		{
			throw Rva0033AF00Exception();
		}
	}
	virtual ~Rva0033AF00Base() {}

private:
	RvaModuleHandle m_module;
};

class Rva0033AF00Editor
{
public:
	virtual void initialize();
};

class __declspec(novtable) Rva0033AF00 : public Rva0033AF00Base
{
public:
	Rva0033AF00(int unused);
	virtual ~Rva0033AF00() {}
	virtual void keepVtable();

private:
	Rva0033AF00Editor *m_editor;
};

Rva0033AF00::Rva0033AF00(int unused)
{
	(void)unused;
	*reinterpret_cast<void **>(this) = reinterpret_cast<void *>(0x010E7530);
	typedef Rva0033AF00Editor *(__cdecl *GetEditorProc)(void);
	GetEditorProc getEditor = (GetEditorProc)GetProcAddress(
		*reinterpret_cast<RvaModuleHandle *>(reinterpret_cast<char *>(this) + 4),
		"GetFXParticleEditor");
	if (getEditor == 0 || (m_editor = getEditor()) == 0)
	{
		throw Rva0033AF00Exception();
	}
	m_editor->initialize();
}
