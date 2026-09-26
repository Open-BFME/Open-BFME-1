// ??1Rva00937F60Owner@@UAE@XZ
// partial score=0.82 date=2026-09-06
// ??1Rva00937F60Owner@@UAE@XZ

class NetCommandMsg;

class NetCommandRef
{
public:
	~NetCommandRef();

private:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
};

class Rva00937F60Owner
{
public:
	virtual ~Rva00937F60Owner();

	NetCommandRef *m_array;
	void *m_8;
	char m_padC;
	bool m_hasArray;
};

Rva00937F60Owner::~Rva00937F60Owner()
{
	if (m_array != 0 && m_hasArray)
	{
		delete[] m_array;
	}

	m_array = 0;
	m_hasArray = false;
	m_8 = 0;
}
