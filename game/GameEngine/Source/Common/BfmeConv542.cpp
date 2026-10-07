class BfmeThingBWA;

// callees.py 0x000947C0 36: the only call is 0x00887B60, matched in
// functions.csv as the private StringBase<char>::StringBase(const
// StringBase<char> &) (game/Libraries/Source/string/StringBase.cpp).
// Declared TU-locally so this class may be the friend that copies it.
template <typename T>
class StringBase
{
	friend class BfmeThingBWA;

private:
	StringBase(const StringBase &src);

	T *m_data;
};

class BfmeThingBWA
{
public:
	BfmeThingBWA *bfmeInitBWA(void *what, bool flag);
	StringBase<char> m_bfmeHead;
	int m_bfmeNum;
	bool m_bfmeA;
	bool m_bfmeB;
};

BfmeThingBWA *BfmeThingBWA::bfmeInitBWA(void *what, bool flag)
{
	m_bfmeHead.StringBase<char>::StringBase(*(const StringBase<char> *)what);
	m_bfmeA = flag;
	m_bfmeB = flag;
	m_bfmeNum = 0;
	return this;
}
