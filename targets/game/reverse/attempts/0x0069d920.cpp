// ?d_0069d920@@YAXXZ
// partial score=0.523466 date=2026-09-26
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

struct Rva0069F740Node
{
	Rva0069F740Node *m_next;
	Rva0069F740Node *m_prev;
	void *m_value;
};
struct Rva0069F740Ref { Rva0069F740Node *m_value; };
struct Rva0069F740Holder
{
	char m_pad00[0x84];
	void *m_busy;
};
struct Rva0069F740Binding
{
	char m_pad00[8];
	Rva0069F740Holder *m_holder;
	char m_pad0c[0x14 - 0x0c];
	AsciiString m_name;
	char m_pad18[0x28 - 0x18];
	int m_group;
};
struct Rva0069F740Entry
{
	int m_state;
	Rva0069F740Binding *m_binding;
};
struct Rva0069F740Selection
{
	char m_pad00[0x14];
	Rva0069F740Binding *m_binding;
};

class Rva0069F740Lock
{
public:
	Rva0069F740Lock(void *handle)
	{
		unsigned char z = 0;
		m_held = z;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xffffffffu) != 0x102u)
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

class Rva0069F740Owner
{
public:
	Rva0069F740Ref getSlot(int group, int inner);
	AsciiString roomName0069D920();
	char m_pad00[0x4c];
	Rva0069F740Node *m_names;
	char m_pad50[0x604 - 0x50];
	int m_group;
	char m_pad608[0x95c - 0x608];
	void *m_mutex;
	char m_pad960[0x9d0 - 0x960];
	Rva0069F740Node *m_sentinel;
	char m_pad9d4[0xac4 - 0x9d4];
	int m_current[3];
};

extern AsciiString Rva01336E50EmptyString;

AsciiString Rva0069F740Owner::roomName0069D920()
{
	Rva0069F740Lock lock(m_mutex);
	Rva0069F740Node *it = m_names->m_next;
	while (it != m_names)
	{
		Rva0069F740Entry *entry = (Rva0069F740Entry *)it->m_value;
		if (entry->m_state == 0)
		{
			Rva0069F740Binding *binding = entry->m_binding;
			if (binding != 0 && binding->m_group == m_group &&
				binding->m_holder->m_busy == 0)
				return binding->m_name;
		}
		it = it->m_next;
	}
	Rva0069F740Node *node = getSlot(m_group, m_current[m_group]).m_value;
	if (node != m_sentinel)
	{
		Rva0069F740Selection *value =
			(Rva0069F740Selection *)node->m_value;
		return value->m_binding->m_name;
	}
	return Rva01336E50EmptyString;
}
