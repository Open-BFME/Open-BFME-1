// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: Rva000B3FA0Owner::bfmeSet(Rva000B3FA0Thing **) -- retail 0x000B3FA0, 94 bytes.
//
// Conditional refcounted pointer set. The incoming thing (loaded through the
// argument slot) must carry the same AsciiString name at +0x08 as the owner
// holds at +0x14 (compare via ILT 0x000220C5); a self-assignment through the
// owner's own +0x08 slot is a no-op. Otherwise: addRef the incoming thing,
// release the old one, store. No named caller reaches the body, so the class
// and member names are address-derived.
//
// Shape lever (docs/shape_levers.md): retail re-tests the old pointee before
// its virtual drop. Releasing through an inlined member that does
// `delete this` keeps that test; explicit `if (this)` / `if (old)` spellings
// fold it and also flip the esi/edi assignment.
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

#include "ascii_string.h"

class Rva000B3FA0Thing
{
public:
	virtual ~Rva000B3FA0Thing();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;				// +0x04
	AsciiString m_name;				// +0x08
};

class Rva000B3FA0Owner
{
public:
	void bfmeSet(Rva000B3FA0Thing **src);

	unsigned char m_head[8];
	Rva000B3FA0Thing *m_ptr;			// +0x08
	unsigned char m_mid[8];
	AsciiString m_name;				// +0x14
};

// ?bfmeSet@Rva000B3FA0Owner@@QAEXPAPAVRva000B3FA0Thing@@@Z
void Rva000B3FA0Owner::bfmeSet(Rva000B3FA0Thing **src)
{
	Rva000B3FA0Thing *p = *src;

	if (p != 0 && p->m_name.compare(m_name) != 0)
		return;
	if (&m_ptr == src)
		return;
	if (p != 0)
		InterlockedIncrement(&p->m_refCount);
	if (m_ptr != 0)
		m_ptr->Release_Ref();
	m_ptr = *src;
}
