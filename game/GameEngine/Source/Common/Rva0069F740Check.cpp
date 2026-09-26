// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?check@Rva0069F740Owner@@QAE_NXZ
// Mutex-guarded 3x2 slot occupancy test. Handle at +0x95c matches
// Rva0069AF30Owner / Open269A220. The extra `z` local is the stack slot
// retail zeros before the second handle store.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

struct Rva0069F740Slot
{
	void *m_head;
	char m_pad[0xc];
	void *m_tail;
	char m_rest[0x14];
};

struct Rva0069F740Ref
{
	void *m_value;
};

class Rva0069F740Owner
{
public:
	bool check();
	Rva0069F740Ref getSlot(int group, int inner);

	char m_pad0[0x95c];
	void *m_mutex;
	char m_pad1[0x9d0 - 0x960];
	void *m_sentinel;
	Rva0069F740Slot m_slots[6];
	int m_current[3];
};

class Rva0069F740Lock
{
public:
	Rva0069F740Lock(void *handle)
	{
		unsigned char z = 0;
		m_held = z;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFFu) != 0x102u)
			m_held = 1;
	}

	~Rva0069F740Lock()
	{
		if (m_held)
			ReleaseMutex(m_handle);
	}

	void *m_handle;
	unsigned char m_held;
};

bool Rva0069F740Owner::check()
{
	Rva0069F740Lock lock(m_mutex);
	int group;
	for (group = 0; group < 3; group++)
	{
		int inner;
		for (inner = 0; inner < 2; inner++)
		{
			if (inner == m_current[group])
			{
				if (getSlot(group, inner).m_value != m_sentinel)
					return true;
			}
			else
			{
				Rva0069F740Slot *slot = &m_slots[inner + group * 2];
				if (slot->m_tail != slot->m_head)
					return true;
			}
		}
	}
	return false;
}
