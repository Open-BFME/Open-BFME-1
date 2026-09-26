// cl: /O2

class AsciiString;

class Rva0019A260Owned
{
public:
	virtual ~Rva0019A260Owned() {}
};

class BfmeMapObjectExtra
{
public:
	void bfmeReset(void);
	void finalize(void *object);

private:
	char m_padding[4];
};

class Rva0076F980Mid
{
public:
	AsciiString *erase(AsciiString *first, AsciiString *last);
	AsciiString *m_first;
	AsciiString *m_last;
};

class Rva0019A260State
{
public:
	void cleanup(void *object);

private:
	Rva0019A260Owned *m_first;
	BfmeMapObjectExtra m_extra;
	Rva0019A260Owned *m_second;
	Rva0076F980Mid m_range;
};

void Rva0019A260State::cleanup(void *object)
{
	if (m_first != 0)
		delete m_first;
	m_first = 0;
	m_extra.bfmeReset();

	if (m_second != 0)
		delete m_second;
	m_second = 0;
	Rva0076F980Mid *range = &m_range;
	range->erase(range->m_first, range->m_last);

	if (object != 0)
		m_extra.finalize(object);
}
