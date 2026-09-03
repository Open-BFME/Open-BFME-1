// ?setText@Rva00415AA0@@QAEXABVRva0036CA00Str@@@Z
// partial score=0.9 date=2026-09-02
// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	void releaseBuffer();
	void set(const Rva0036CA00Str &other);

	struct Data
	{
		short a;
		short b;
		unsigned short first;
	};

	Data *m_item;
};

class Rva00415AA0
{
	char m_pad[0x2D8];
	Rva0036CA00Str m_2D8;

public:
	void setText(const Rva0036CA00Str &src);
};

void Rva00415AA0::setText(const Rva0036CA00Str &src)
{
	if (!src.m_item || !src.m_item->first)
		m_2D8.releaseBuffer();
	else
		m_2D8.set(src);
}
