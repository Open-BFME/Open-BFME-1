struct BfmeElemCJG
{
	unsigned char m_bfmeHead[0xc];
	void *m_bfmeVal;
	unsigned char m_bfmeTail[0x14];
};

class BfmeThingCJG
{
public:
	void bfmeGoCJG(void *what);
	unsigned char m_bfmeHead[0x2c];
	BfmeElemCJG *volatile m_bfmeBegin;
	BfmeElemCJG *m_bfmeEnd;
};

// Retail's tail call at 0x000FD070+0x25 goes to 0x0087EE60, already matched as
// GeometryInfo::calcBoundingStuff in
// game/GameEngine/Source/Common/System/GeometryInfoCalcBoundingStuff.cpp.
// Only that one member is needed here, so this TU carries a local view of the
// class rather than the full upstream geometry.h. It stays private, as
// upstream declares it, so the reference carries the same mangled name the
// landed body defines; the friend declaration lets this TU's other class
// tail-call it.
class GeometryInfo
{
	friend class BfmeThingCJG;

private:
	void calcBoundingStuff();
};

void BfmeThingCJG::bfmeGoCJG(void *what)
{
	if (m_bfmeEnd - m_bfmeBegin != 0)
		m_bfmeBegin->m_bfmeVal = what;
	((GeometryInfo *)this)->calcBoundingStuff();
}
