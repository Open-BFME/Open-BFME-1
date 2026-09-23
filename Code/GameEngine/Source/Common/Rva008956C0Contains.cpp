// At 0x008956C0, retail walks a linked list and returns 1 when its call to
// 0x00895510 returns nonzero. No caller or vtable names the owner, so its
// class name retains the retail address.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

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

// The aligned call uses ECX for the receiver, passes one handle on the stack,
// tests an int result, and returns with four argument bytes popped.
void __cdecl d_00895510(void);					// retail 0x00895510

class Rva00895510Receiver;

typedef int (__fastcall *Rva00895510Fn)(Rva00895510Receiver *,
	RefHandle008956C0);

class Rva008956C0Entry
{
public:
	Rva00895510Receiver *getReceiver(void) const
	{
		return m_receiver;
	}

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
			if (((Rva00895510Fn)d_00895510)(node->m_entry->getReceiver(),
				candidate))
				return 1;

			node = node->m_next;
		}
		while (node != 0);
	}

	return 0;
}
