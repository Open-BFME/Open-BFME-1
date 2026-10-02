struct BfmeElemCJF
{
	unsigned char m_bfmeHead[8];
	void *m_bfmeVal;
	unsigned char m_bfmeTail[0x18];
};

class BfmeThingCJF
{
public:
	void bfmeGoCJF(void *what);
	unsigned char m_bfmeHead[0x2c];
	BfmeElemCJF *volatile m_bfmeBegin;
	BfmeElemCJF *m_bfmeEnd;
};

// Retail's tail call at 0x000FD030+0x25 goes to 0x0087EE60, already matched as
// GeometryInfo::calcBoundingStuff in
// game/GameEngine/Source/Common/System/GeometryInfoCalcBoundingStuff.cpp.
// Only that one member is needed here, so this TU carries a local view of the
// class rather than the full upstream geometry.h. It stays private, as
// upstream declares it, so the reference carries the same mangled name the
// landed body defines; the friend declaration lets this TU's other class
// tail-call it.
class GeometryInfo
{
	friend class BfmeThingCJF;

private:
	void calcBoundingStuff();
};

void BfmeThingCJF::bfmeGoCJF(void *what)
{
	if (m_bfmeEnd - m_bfmeBegin != 0)
		m_bfmeBegin->m_bfmeVal = what;
	((GeometryInfo *)this)->calcBoundingStuff();
}
