// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GenGamma::h000131E2, retail 0x007AFC10, 203 bytes.
// The ILT at 0x000131E2 names this member and the S3 guarded-global triple at
// 0x007B75C0 calls it through the global at 0x01306DF0.

class GenGammaNode
{
public:
	virtual ~GenGammaNode();

private:
	char m_pad[0xd0];

public:
	GenGammaNode *m_next;
};

class GenGammaNode64
{
public:
	virtual ~GenGammaNode64();

private:
	char m_pad[0x60];

public:
	GenGammaNode64 *m_next;
};

class GenGamma
{
public:
	void h000131E2();

private:
	char m_pad0[4];
	GenGammaNode *m_list04;
	GenGammaNode *m_list08;
	GenGammaNode *m_list0c;
	GenGammaNode *m_list10;
	char m_pad14[4];
	GenGammaNode64 *m_list18;
	char m_pad1c[0x234];
	int m_count250;
};

// ?h000131E2@GenGamma@@QAEXXZ
void GenGamma::h000131E2()
{
	GenGammaNode *current;
	GenGammaNode *next = m_list0c;
	m_list0c = 0;
	for (current = next; current; current = next)
	{
		next = current->m_next;
		current->m_next = 0;
		delete current;
	}

	next = m_list04;
	m_list04 = 0;
	for (current = next; current; current = next)
	{
		next = current->m_next;
		current->m_next = 0;
		delete current;
	}

	next = m_list08;
	m_list08 = 0;
	for (current = next; current; current = next)
	{
		next = current->m_next;
		current->m_next = 0;
		delete current;
	}

	next = m_list10;
	m_count250 = 0;
	for (current = next; current; current = next)
	{
		next = current->m_next;
		current->m_next = 0;
		delete current;
	}

	GenGammaNode64 *current64;
	GenGammaNode64 *next64 = m_list18;
	m_list10 = 0;
	for (current64 = next64; current64; current64 = next64)
	{
		next64 = current64->m_next;
		current64->m_next = 0;
		delete current64;
	}
	m_list18 = 0;
}
