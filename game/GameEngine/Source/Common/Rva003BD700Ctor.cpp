// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: thiscall constructor that writes a 6-slot vftable, copy-constructs
// a 4-byte string member at +4, and stores an int argument at +8. Retail
// 0x003BD700, 83 bytes. A novtable base with an out-of-line destructor makes
// the string copy unwind into the base destructor, which is what emits the
// EH3 frame.

template <typename T>
class StringBase
{
	friend class Rva003BD700String;

private:
	StringBase();
	StringBase(const StringBase<T> &);
	~StringBase();

	int *m_data;
};

class Rva003BD700String : private StringBase<unsigned short>
{
public:
	Rva003BD700String(const Rva003BD700String &other)
		: StringBase<unsigned short>(other)
	{
	}
	~Rva003BD700String() {}
};

class __declspec(novtable) Rva003BD700Base
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	~Rva003BD700Base();
};

class Rva003BD700 : public Rva003BD700Base
{
public:
	Rva003BD700(const Rva003BD700String &s, int n);

private:
	Rva003BD700String m_at04;
	int m_at08;
};

Rva003BD700::Rva003BD700(const Rva003BD700String &s, int n)
	: m_at04(s)
	, m_at08(n)
{
}
