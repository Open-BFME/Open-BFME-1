// cl: /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug
#include "../../../Libraries/Source/WWVegas/WW3D2/seglinerenderer.h"

class TeamsInfoRec
{
public:
	void clear();
};

class Rva0095C7F0State
{
public:
	void initialize();
};

class BfmeSubDUB
{
};

struct BfmeThingDUB
{
	void bfmeGoDUB();
	unsigned char m_bfmeHeadA[0x630];
	BfmeSubDUB m_bfmeA;
	unsigned char m_bfmeHeadB[0x1b];
	BfmeSubDUB m_bfmeB;
};

void BfmeThingDUB::bfmeGoDUB()
{
	((TeamsInfoRec *)&m_bfmeA)->clear();
	((TeamsInfoRec *)&m_bfmeB)->clear();
}

class BfmeSubDUC
{
};

class BfmeSubDUD
{
};

struct BfmeThingDUC
{
	void bfmeGoDUC();
	unsigned char m_bfmeHeadA[0x104];
	BfmeSubDUC m_bfmeA;
	unsigned char m_bfmeHeadB[0x4f];
	BfmeSubDUD m_bfmeB;
};

void BfmeThingDUC::bfmeGoDUC()
{
	((SegLineRendererClass *)&m_bfmeA)->Reset_Line();
	((Rva0095C7F0State *)&m_bfmeB)->initialize();
}
