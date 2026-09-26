// cl: /Oy-
// A message laid out into the record's own buffer. When the record still holds
// the first kind it is flushed first, and the kind is written down before the
// laying out. The callee is pinned by address.

extern "C" __declspec(dllimport) int __stdcall wvsprintfA(char *out, const char *how, char *rest);

struct BfmeIOInterfaceQO
{
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void write(int kind, const char *source, const char *buffer) = 0;
};

struct BfmeIOFactoryQO
{
	BfmeIOFactoryQO *m_next;
	const char *m_id;
	const char *m_description;
	void *m_factory;
	BfmeIOInterfaceQO *m_io;
};

struct BfmeIOBufferQO
{
	char *m_buffer;
	unsigned m_used;
	unsigned m_allocated;
	bool m_lastWasCR;
};

struct BfmeThingQO
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual BfmeThingQO &operator<<(const char *text) = 0;

	void bfmeFlushQO(int defaultLog);

	unsigned char m_bfmePrefix[8];
	BfmeIOFactoryQO *m_bfmeFirstIOFactory;
	unsigned char m_bfmeHead[0x9c74];
	BfmeIOBufferQO m_bfmeIOBuffer[7];
	int m_bfmeKind;
	char m_bfmeBuf[0x100];
	unsigned char m_bfmeTail[0x74];
	bool m_bfmeAlwaysFlush;
};

void bfmeLogQO(BfmeThingQO *what, int kind, const char *how, ...)
{
	if (what->m_bfmeKind == 1)
		what->bfmeFlushQO(1);

	what->m_bfmeKind = kind;

	wvsprintfA(what->m_bfmeBuf, how, (char *)(&how + 1));
}

void BfmeThingQO::bfmeFlushQO(int defaultLog)
{
	if (!m_bfmeIOBuffer[m_bfmeKind].m_used)
	{
		m_bfmeKind = 7;
		return;
	}

	if (!m_bfmeIOBuffer[m_bfmeKind].m_lastWasCR)
		*this << "\n";

	for (BfmeIOFactoryQO *current = m_bfmeFirstIOFactory;
		current;
		current = current->m_next)
	{
		if (!current->m_io)
			continue;

		current->m_io->write(
			m_bfmeKind,
			m_bfmeBuf,
			m_bfmeIOBuffer[m_bfmeKind].m_buffer);

		if (m_bfmeAlwaysFlush)
			current->m_io->write(m_bfmeKind, m_bfmeBuf, 0);
	}

	m_bfmeIOBuffer[m_bfmeKind].m_used = 0;
	*m_bfmeIOBuffer[m_bfmeKind].m_buffer = 0;
	m_bfmeBuf[0] = 0;
	m_bfmeKind = 7;
}
