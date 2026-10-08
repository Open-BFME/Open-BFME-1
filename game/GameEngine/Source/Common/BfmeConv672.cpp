struct Coord3D;

// The callee behind ILT 0x00007E50 is 0x004583A0, the matched
// RadiusDecal::setPosition (RadiusDecal.cpp); the member at +0x1BC is that
// RadiusDecal and the argument is the position.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
public:
	void setPosition(const Coord3D &pos);
};

class BfmeThingDBD
{
public:
	void bfmeGoDBD(void *a);
	unsigned char m_bfmeHead[0x1bc];
	RadiusDecal m_bfmeSub;
};

void BfmeThingDBD::bfmeGoDBD(void *a)
{
	if (a == 0)
		return;
	m_bfmeSub.setPosition(*(const Coord3D *)a);
}
