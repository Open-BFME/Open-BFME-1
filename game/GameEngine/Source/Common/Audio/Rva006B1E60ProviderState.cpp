// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Address-derived reconstruction of retail 0x006B1E60.
//
// Retail ABI: thiscall, one four-byte Bool argument, Bool in AL, ret 4.
// The provider array begins at this+0x654 and has 12-byte entries; the
// selected-provider index and mutex are at +0x958 and +0x95c.  The
// j_00041899 thunk reaches this body, but no named caller or owner/vtable is
// present in the current retail evidence, so the C++ identity stays neutral.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long timeout);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern void j_00034626();

class Rva006B1E60MutexGuard
{
public:
	__forceinline Rva006B1E60MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(m_handle, 0xffffffffUL) != 0x102)
			m_owned = 1;
	}

	__forceinline ~Rva006B1E60MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class AsciiString
{
public:
	void *m_data;
	int bfmeCompare1294(const char *text) const;
};

struct Rva006B1E60Provider
{
	AsciiString m_name;
	unsigned int m_id;
	int m_valid;
};

class Rva006B1E60Owner
{
public:
	bool evaluate(bool requested);

private:
	char m_pad[0x654];
	Rva006B1E60Provider m_provider[64];
	unsigned int m_providerCount;
	unsigned int m_selectedProvider;
	void *m_mutex;
};

bool Rva006B1E60Owner::evaluate(bool requested)
{
	Rva006B1E60Owner *self = this;
	void *handle = self->m_mutex;
	Rva006B1E60MutexGuard guard(handle);

	unsigned int selected = self->m_selectedProvider;
	bool request = requested;
	if (selected != 0xffffffffu)
	{
		if (self->m_provider[selected].m_name.bfmeCompare1294(
				"Creative Labs EAX 3 (TM)") == 0)
		{
			if (request)
				return true;
		}
		else if (!request)
		{
			return true;
		}
	}

	typedef void (Rva006B1E60Owner::*Adjust)(bool);
	union
	{
		void (__cdecl *freeAdjust)();
		Adjust memberAdjust;
	} adjust;
	adjust.freeAdjust = ::j_00034626;
	(self->*adjust.memberAdjust)(request);

	selected = self->m_selectedProvider;
	if (selected != 0xffffffffu)
	{
		bool isEax = self->m_provider[selected].m_name.bfmeCompare1294(
			"Creative Labs EAX 3 (TM)") == 0;
		return request == isEax;
	}

	return false;
}
