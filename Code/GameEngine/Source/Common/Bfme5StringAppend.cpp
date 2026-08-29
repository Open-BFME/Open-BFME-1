// Open-BFME5 conversions: wide-string appends on a widget.
//
// BFME's string header is eight bytes with the character data at +8 and a
// 16-bit length at +4, so `str()` and `getLength()` are two separate inline
// null tests. Keeping them as two helpers is what produces retail's two
// `test eax,eax` branches -- folded into one expression MSVC merges them.

template<class T> class StringBase
{
public:
	void concat(const T *p, int n);
};

struct Bfme5WideHeader
{
	int m_bfmeRefCount;
	unsigned short m_bfmeLength;
	unsigned short m_bfmeAllocated;
};

struct Bfme5WideString
{
	Bfme5WideHeader *m_bfmeData;
};

extern const unsigned short g_bfme5EmptyWide;

static int bfme5WideLength(const Bfme5WideString &s)
{
	return s.m_bfmeData ? s.m_bfmeData->m_bfmeLength : 0;
}

static const unsigned short *bfme5WideChars(const Bfme5WideString &s)
{
	return s.m_bfmeData ? (const unsigned short *)((char *)s.m_bfmeData + 8) : &g_bfme5EmptyWide;
}

class Bfme5TextWidget
{
public:
	virtual void bfmeVM0();
	virtual void bfmeVM1();
	virtual void bfmeVM2();
	virtual void bfmeVM3();
	virtual void bfmeOnTextChanged();

	void bfmeAppend(const Bfme5WideString &s);
	void bfmeAppendChar(int ch);

	StringBase<unsigned short> m_bfmeText;
};

void Bfme5TextWidget::bfmeAppend(const Bfme5WideString &s)
{
	m_bfmeText.concat(bfme5WideChars(s), bfme5WideLength(s));
	bfmeOnTextChanged();
}

void Bfme5TextWidget::bfmeAppendChar(int ch)
{
	int c = ch;

	m_bfmeText.concat((const unsigned short *)&c, 1);
	bfmeOnTextChanged();
}
