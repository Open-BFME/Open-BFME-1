// The head is built by StringBase<char>'s copy constructor (call target
// 0x00887B60, matched as ??0?$StringBase@D@@AAE@ABV0@@Z).
class BfmeThingBWB;
template <class T> class StringBase
{
	friend class BfmeThingBWB;
	StringBase(const StringBase &other);
	T *m_data;
};

class BfmeThingBWB
{
public:
	BfmeThingBWB *bfmeInitBWB(void *what, int value);
	unsigned char m_bfmeHead[4];
	int m_bfmeNum;
	int m_bfmeA;
	int m_bfmeB;
};

BfmeThingBWB *BfmeThingBWB::bfmeInitBWB(void *what, int value)
{
	((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)what);
	m_bfmeA = value;
	m_bfmeB = value;
	m_bfmeNum = 1;
	return this;
}
