// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: destructor of a 12-byte record of three 4-byte strings. Retail
// 0x003B8850, 121 bytes.

template <typename T>
class StringBase
{
	friend class Rva003B8850Str;

private:
	~StringBase();
	int *m_data;
};

class Rva003B8850Str : private StringBase<char>
{
public:
	~Rva003B8850Str() {}
};

class Rva003B8850
{
public:
	~Rva003B8850();

private:
	Rva003B8850Str m_a;
	Rva003B8850Str m_b;
	Rva003B8850Str m_c;
};

Rva003B8850::~Rva003B8850()
{
	m_a.~Rva003B8850Str();
	m_b.~Rva003B8850Str();
	m_c.~Rva003B8850Str();
}
