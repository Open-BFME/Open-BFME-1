// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00362DC0 is the default BfmeOwnVUM constructor.  The class is
// mirrored here because the existing save/destructor TUs deliberately keep
// their own ABI views.

template <typename T> class StringBase
{
friend class AsciiString;

private:
	StringBase(const StringBase<T> &other);

	struct Header
	{
		int refCount;
		int length;
		T text[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	static const AsciiString TheEmptyString;
};

extern "C" void * __cdecl memset(void *destination, int value, unsigned int count);

class Rva00362DC0Block6
{
public:
	void init(int value) { memset(this, value, 0x18); }
	void zero(int value) { memset(this, value, 0x18); }
	int m_00, m_04, m_08, m_0c, m_10, m_14;
};

class Rva00362DC0Block3
{
public:
	void init(int value) { memset(this, value, 0x0c); }
	void zero(int value) { memset(this, value, 0x0c); }
	int m_00, m_04, m_08;
};

class Rva00362DC0Block10
{
public:
	void init(int value) { memset(this, value, 0x28); }
	void zero(int value) { memset(this, value, 0x28); }
	int m_00, m_04, m_08, m_0c, m_10;
	int m_14, m_18, m_1c, m_20, m_24;
};

class BfmeOwnVUM
{
public:
	BfmeOwnVUM();
	~BfmeOwnVUM();
	virtual void bfmeSlot0VUM();
	virtual void bfmeSlot1VUM();
	virtual void bfmeSlot2VUM();
	virtual void bfmeSlot3VUM();
	virtual void bfmeSlot4VUM();

private:
	AsciiString m_04;
	int m_08, m_0c;
	Rva00362DC0Block6 m_10;
	Rva00362DC0Block3 m_28;
	int m_34;
	unsigned char m_38, m_39;
	int m_3c, m_40, m_44, m_48, m_4c;
	Rva00362DC0Block10 m_50;
	int m_78;
	Rva00362DC0Block6 m_7c;
	Rva00362DC0Block6 m_94;
	int m_ac, m_b0;
};

// ??0BfmeOwnVUM@@QAE@XZ
BfmeOwnVUM::BfmeOwnVUM()
	: m_04(AsciiString::TheEmptyString)
{
	m_08 = 0;
	m_0c = 0;
	m_10.init(0);
	m_28.init(0);
	m_34 = 0;
	m_38 = 0;
	m_39 = 0;
	m_3c = 0;
	m_40 = 0;
	m_44 = 0;
	m_48 = 0;
	m_4c = 0;
	m_50.init(0);
	m_78 = 0;
	m_7c.init(0);
	m_94.init(0);
	m_ac = 0;
	m_b0 = 0;
	m_10.zero(0);
	m_7c.zero(0);
	m_94.zero(0);
	m_28.zero(0);
	m_50.zero(0);
}
