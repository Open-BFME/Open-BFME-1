// cl: /DNDEBUG /MD /EHsc

typedef float Real;

class BfmeBoxF0
{
public:
	bool rva00880AF0(const BfmeBoxF0 *other) const;

	Real m_centerX;
	Real m_centerY;
	Real m_axisX;
	Real m_axisY;
	Real m_perpX;
	Real m_perpY;
	Real m_extentX;
	Real m_extentY;
};

struct Rva00880D10Info
{
	unsigned char m_pad0[8];
	Real m_extentX;
	Real m_extentY;
	unsigned char m_pad1[0x14];
	Real m_centerX;
	Real m_centerY;
	unsigned char m_pad2[4];
	Real m_angle;
};

// ?rva00880C30@@YA_NPAURva00880D10Info@@0@Z
// Open BFME 2: Code/GameEngine/Source/Common/Rva006C0630Cluster.cpp.
bool rva00880C30(Rva00880D10Info *info, Rva00880D10Info *other)
{
	Real extentY = info->m_extentY;
	Real extentX = info->m_extentX;
	Real angle = info->m_angle;

	BfmeBoxF0 box;
	box.m_centerX = info->m_centerX;
	box.m_centerY = info->m_centerY;

	Real cosA, sinA;
	__asm {
		fld     angle
		fsincos
		fstp    cosA
		fstp    sinA
	}

	box.m_perpX = -sinA;
	box.m_extentX = extentX;
	box.m_extentY = extentY;
	box.m_axisX = cosA;
	box.m_axisY = sinA;
	box.m_perpY = cosA;

	Real extentY2 = other->m_extentY;
	Real extentX2 = other->m_extentX;
	Real angle2 = other->m_angle;

	BfmeBoxF0 box2;
	box2.m_centerX = other->m_centerX;
	box2.m_centerY = other->m_centerY;

	Real cosB, sinB;
	__asm {
		fld     angle2
		fsincos
		fstp    cosB
		fstp    sinB
	}

	box2.m_perpX = -sinB;
	box2.m_extentX = extentX2;
	box2.m_extentY = extentY2;
	box2.m_axisX = cosB;
	box2.m_axisY = sinB;
	box2.m_perpY = cosB;

	return box.rva00880AF0(&box2);
}
