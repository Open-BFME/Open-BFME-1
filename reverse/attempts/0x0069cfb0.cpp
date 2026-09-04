// ?accept@Rva0069CFB0Owner@@QAE_NPAVRva0069CFB0Arg@@@Z
// partial score=0.62 date=2026-09-04
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded accept: require arg name word, virtual +0xAC, return field8!=0.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *hHandle, unsigned long dwMilliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *hMutex);

class Rva0069CFB0MutexGuard
{
public:
	Rva0069CFB0MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva0069CFB0MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

struct Rva0069CFB0Name
{
	char m_pad[4];
	unsigned short m_word;
};

class Rva0069CFB0Arg
{
public:
	char m_pad0[8];
	void *m_field8;
	char m_pad1[8];
	Rva0069CFB0Name *m_name; // +0x14
};

class Rva0069CFB0Owner
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void apply(Rva0069CFB0Arg *arg); // slot 43 @ +0xAC

	bool accept(Rva0069CFB0Arg *arg);

	char m_pad[0x958];
	void *m_mutex;
};

bool Rva0069CFB0Owner::accept(Rva0069CFB0Arg *arg)
{
	Rva0069CFB0Owner *self = this;
	void *handle = self->m_mutex;
	Rva0069CFB0MutexGuard guard(handle);
	Rva0069CFB0Arg *event = arg;

	if (event)
	{
		Rva0069CFB0Name *name = event->m_name;
		if (name)
		{
			if (name->m_word != 0)
			{
				self->apply(event);
				return event->m_field8 != 0;
			}
		}
	}
	return false;
}
