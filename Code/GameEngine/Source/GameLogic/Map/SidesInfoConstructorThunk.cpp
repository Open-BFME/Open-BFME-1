// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// readable body of ??0SidesInfo@@: Code/GameEngine/Source/GameLogic/Map/SidesList.cpp

// Open-BFME5: SidesInfo ctor
// Retail: zero +0, construct sub at +4 with arg 0, zero +8..+14.

class SidesInfoSub
{
public:
	SidesInfoSub(int arg);

private:
	char opaque[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h
class SidesInfo
{
public:
	SidesInfo();

private:
	unsigned int m_0;
	SidesInfoSub m_sub;
	unsigned int m_8;
	unsigned int m_c;
	unsigned int m_10;
	unsigned int m_14;
};

// ??0SidesInfo@@QAE@XZ
SidesInfo::SidesInfo()
	: m_0(0)
	, m_sub(0)
	, m_8(0)
	, m_c(0)
	, m_10(0)
	, m_14(0)
{
}
