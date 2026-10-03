// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Open-BFME5 conversions.
#include "winbase_shim.h"
#include "rendobj.h"
#include "seglinerenderer.h"

// The assignment at 0x0095C860 is owned by TextureRefAssignOperators.cpp.
class Rva0095C860
{
public:
	Rva0095C860 &operator=(const Rva0095C860 &other);
};

class BfmeSubAVIK
{
public:
	char m_bfmePad[0x50];
};

class BfmeSubBVIK
{
public:
	char m_bfmePad[0x10];
};

class BfmeThingVIK
{
public:
	BfmeThingVIK &bfmeAssignVIK(const BfmeThingVIK &o);
	char m_bfmePad[0xc8];
	int m_bfmec8;
	int m_bfmecc;
	int m_bfmed0;
	int m_bfmed4;
	int m_bfmed8;
	int m_bfmedc;
	int m_bfmee0;
	int m_bfmee4;
	int m_bfmee8;
	int m_bfmeec;
	int m_bfmef0;
	int m_bfmef4;
	int m_bfmef8;
	int m_bfmefc;
	int m_bfme100;
	BfmeSubAVIK m_bfme104;
	BfmeSubBVIK m_bfme154;
};

BfmeThingVIK &BfmeThingVIK::bfmeAssignVIK(const BfmeThingVIK &o)
{
	*(RenderObjClass *)this = *(const RenderObjClass *)&o;
	if (this != &o)
	{
		m_bfmec8 = o.m_bfmec8;
		m_bfmed0 = o.m_bfmed0;
		m_bfmed8 = o.m_bfmed8;
		m_bfmedc = o.m_bfmedc;
		m_bfmee0 = o.m_bfmee0;
		m_bfmee8 = o.m_bfmee8;
		m_bfmeec = o.m_bfmeec;
		m_bfmef0 = o.m_bfmef0;
		m_bfmef8 = o.m_bfmef8;
		m_bfmefc = o.m_bfmefc;
		m_bfme100 = o.m_bfme100;
		*(SegLineRendererClass *)&m_bfme104 = *(const SegLineRendererClass *)&o.m_bfme104;
		*(Rva0095C860 *)&m_bfme154 = *(const Rva0095C860 *)&o.m_bfme154;
		m_bfmecc = o.m_bfmecc;
	}
	return *this;
}
