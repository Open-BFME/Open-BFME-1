// ?gen00474090@@YAXPAUElem16@@PBU1@@Z
// partial score=0.88 date=2026-09-02
// cl: /EHsc

__forceinline void *operator new(unsigned int, void *p)
{
	return p;
}

__forceinline void operator delete(void *, void *)
{
}

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	char *m_data;
};

struct Elem16
{
	int m_at00;
	int m_at04;
	int m_at08;
	AsciiString m_at0c;
};

// ?gen00474090@@YAXPAUElem16@@PBU1@@Z
void gen00474090(Elem16 *slot, const Elem16 *source)
{
	if (slot == 0)
		return;
	new (slot) Elem16(*source);
}
