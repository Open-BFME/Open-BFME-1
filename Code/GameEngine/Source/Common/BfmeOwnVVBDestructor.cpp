// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// Open-BFME5: BfmeOwnVVB's complete destructor at retail RVA 0x00190490.
// The owner releases its array and linked-list members, then destroys the
// inline element array and its two strings in reverse declaration order.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void __cdecl operator delete[](void *block);

template <typename T>
class StringBase
{
public:
	~StringBase()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	char *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	~AsciiString()
	{
	}
};

class BfmeOwnVVBNode
{
public:
	virtual void release(unsigned int flags);

	BfmeOwnVVBNode *m_next;
};

class BfmeElemBX
{
public:
	~BfmeElemBX();

private:
	char m_body[4];
};

class BfmeOwnVVB
{
public:
	virtual ~BfmeOwnVVB();

private:
	BfmeOwnVVBNode *m_nodes;
	AsciiString m_name;
	char m_gap0[4];
	char *m_owned;
	char m_gap1[0x20];
	AsciiString m_description;
	char m_gap2[0x10];
	BfmeElemBX m_elements[6];
};

BfmeOwnVVB::~BfmeOwnVVB()
{
	if (m_owned)
	{
		::operator delete[](m_owned);
		m_owned = 0;
	}

	BfmeOwnVVBNode *node = m_nodes;
	while (node)
	{
		BfmeOwnVVBNode *next = node->m_next;
		node->m_next = 0;
		_ReadWriteBarrier();
		node->release(1);
		node = next;
	}
}
