// ?getSlot@Rva0069F740Owner@@QAE?AURva0069F740Ref@@HH@Z
// partial score=0.55 date=2026-09-08

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *value);

class Rva0069F740RefObject
{
public:
	virtual void release(int flags);

	long volatile m_refs;
	unsigned char m_pad08[0x0c];
	void *m_nested;
	unsigned char m_pad18[0x1c];
	unsigned char m_flag;
};

class Rva0069F740Handle
{
public:
	Rva0069F740Handle(Rva0069F740RefObject *value) : m_value(value)
	{
		if (m_value != 0)
			InterlockedIncrement(&m_value->m_refs);
	}

	~Rva0069F740Handle()
	{
		if (m_value != 0)
		{
			if (InterlockedDecrement(&m_value->m_refs) <= 0)
				m_value->release(1);
		}
	}

	Rva0069F740RefObject *get() const { return m_value; }

private:
	Rva0069F740RefObject *m_value;
};

class Rva0069F740Nested
{
public:
	unsigned char m_pad00[8];
	void *m_owner;
	unsigned char m_pad0c[0x1c];
	int m_group;
	unsigned char m_pad2c[0x38];
	int m_inner;
};

class Rva0069F740Node
{
public:
	Rva0069F740Node *m_next;
	unsigned char m_pad04[4];
	Rva0069F740RefObject *m_value;
};

struct Rva0069F740Ref
{
	Rva0069F740Node *m_value;

	Rva0069F740Ref(Rva0069F740Node *value) : m_value(value) {}
	~Rva0069F740Ref() {}
};

class Rva0069F740Owner
{
public:
	Rva0069F740Ref getSlot(int group, int inner);

	unsigned char m_pad00[0x9d0];
	Rva0069F740Node *volatile m_sentinel;
};

Rva0069F740Ref Rva0069F740Owner::getSlot(int group, int inner)
{
	Rva0069F740Node *node = m_sentinel->m_next;

	while (node != m_sentinel)
	{
		Rva0069F740Handle valueHandle(node->m_value);
		Rva0069F740RefObject *value = valueHandle.get();

		if (value != 0)
		{
			if (value->m_flag != 0)
			{
			}
			else
			{
				Rva0069F740Nested *nested = (Rva0069F740Nested *)value->m_nested;

				if (*(void **)((char *)nested->m_owner + 0x84) != 0)
				{
				}

				if (nested->m_group == group && nested->m_inner == inner)
				{
					Rva0069F740Ref result(node);
					return result;
				}
			}
		}

		node = node->m_next;
	}

	Rva0069F740Ref result(m_sentinel);
	return result;
}
