// ?contains008956C0@Rva008956C0List@@QAEHVRefHandle008956C0@@@Z
// partial score=0.91 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// 0x008956C0 -- Rva008956C0List::contains008956C0
//
// The handle is a BY-VALUE PARAMETER, not a local: retail never increments the
// candidate refcount on entry, yet decrements it (and runs the sized delete)
// on BOTH exits with the EH state driven to -1 first.  Under the MSVC ABI the
// callee destroys by-value class parameters, so that pair of epilogue
// destructor blocks IS the parameter's destructor.  ret 4 pops the one-pointer
// handle.  The per-iteration `push ecx / mov eax,esp / mov [esp+0xc],esp /
// mov [eax],edi / inc [edi]` is the copy constructor building the argument for
// 0x00895510 in place plus the unwind registration of that temporary.

extern void (*TheBfmeFree)(void *p, unsigned int bytes);	// retail 0x01337830

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);					// retail 0x00895260

	void operator delete(void *p, unsigned int bytes)
	{
		TheBfmeFree(p, bytes);
	}

	int m_refCount;						// +0x00
	char m_rest[0x14];
};

class RefHandle008956C0
{
public:
	RefHandle008956C0(const RefHandle008956C0 &other)
	{
		BfmeDropObjectA *o = other.m_object;

		m_object = o;

		if (o != 0)
			++o->m_refCount;
	}

	~RefHandle008956C0(void)
	{
		BfmeDropObjectA *o = m_object;

		if (o != 0 && --o->m_refCount == 0)
			delete o;
	}

	BfmeDropObjectA *m_object;				// +0x00
};

// Address-derived: the retail row for 0x00895510 is still the dump placeholder
// ?d_00895510@@YAXXZ, so the TU references that exact decorated name and casts
// it to the receiver/argument shape the aligned call site proves (ECX receiver
// read from entry+0x04, one by-value handle on the stack, int result tested).
void __cdecl d_00895510(void);					// retail 0x00895510

class Rva00895510Receiver;

typedef int (__fastcall *Rva00895510Fn)(Rva00895510Receiver *,
	RefHandle008956C0);

class Rva008956C0Entry
{
public:
	void *m_dword0;						// +0x00
	Rva00895510Receiver *m_receiver;			// +0x04
};

class Rva008956C0Node
{
public:
	Rva008956C0Entry *m_entry;				// +0x00
	Rva008956C0Node *m_next;				// +0x04
};

class Rva008956C0List
{
public:
	int contains008956C0(RefHandle008956C0 candidate);

private:
	Rva008956C0Node *m_head;				// +0x00
};

// ?contains008956C0@Rva008956C0List@@QAEHVRefHandle008956C0@@@Z
int Rva008956C0List::contains008956C0(RefHandle008956C0 candidate)
{
	Rva008956C0Node *node = m_head;

	if (node != 0)
	{
		do
		{
			if (((Rva00895510Fn)d_00895510)(node->m_entry->m_receiver,
				candidate))
				return 1;

			node = node->m_next;
		}
		while (node != 0);
	}

	return 0;
}
