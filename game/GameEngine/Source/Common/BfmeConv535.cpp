class BfmeThingBUF;

// callees.py 0x002E17C0 34: the only call is 0x00887B60, matched in
// functions.csv as the private StringBase<char>::StringBase(const
// StringBase<char> &) (game/Libraries/Source/string/StringBase.cpp).
// Declared TU-locally so this class may be the friend that copies it.
template <typename T>
class StringBase
{
	friend class BfmeThingBUF;

private:
	StringBase(const StringBase &src);

	T *m_data;
};

class BfmeThingBUF
{
public:
	BfmeThingBUF *bfmeInitBUF(void *what);
	StringBase<char> m_bfmeHead;
	volatile bool m_bfmeFlag;
	unsigned char m_bfmePad[3];
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	volatile int m_bfmeC;
};

BfmeThingBUF *BfmeThingBUF::bfmeInitBUF(void *what)
{
	m_bfmeHead.StringBase<char>::StringBase(*(const StringBase<char> *)what);
	m_bfmeFlag = true;
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = 0;
	return this;
}
