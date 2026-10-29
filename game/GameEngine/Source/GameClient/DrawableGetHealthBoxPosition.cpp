// ?getHealthBoxPosition@Drawable@@QBEXAAVCoord3D@@@Z (ilt_oracle CONFIRMED exact at ILT 0x000239ED)
// Retail BFME Drawable health-box anchor at 0x0041FCE0 (212 bytes).
// The body is called by the Drawable health/construct indicator family.
// Both template reads are Zero Hour's OVERRIDE<ThingTemplate> operator->
// over the inline recursive Overridable::getFinalOverride (ILT 0x000022BB).
// cl: /DNDEBUG /MD /EHs-c-

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// class-gate: allow Coord3D canonical header is struct-keyed; retail ILT 0x000239ED proves the class-keyed mangling (ilt_oracle CONFIRMED)
class Coord3D
{
public:
	float x;
	float y;
	float z;
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;

	UnsignedByte m_bfmeData[0x34];
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	void *m_vtable;
	Overridable *m_nextOverride;
};
class ThingTemplate : public Overridable
{
public:
	UnsignedByte m_pad008[0xcc];
	UnsignedInt m_flags;
	UnsignedByte m_pad0d8[0x33c];
	float m_healthBoxHeight;
};
template <class T>
class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_obj)
			return 0;
		return (T *)m_obj->getFinalOverride();
	}
	operator const T *() const { return operator->(); }
	T *m_obj;
};
#define BFME_HEALTH_BOX_SLOT(n) virtual void slot##n();

class BfmeHealthBoxAnchor
{
public:
	BFME_HEALTH_BOX_SLOT(000) BFME_HEALTH_BOX_SLOT(001)
	BFME_HEALTH_BOX_SLOT(002) BFME_HEALTH_BOX_SLOT(003)
	BFME_HEALTH_BOX_SLOT(004) BFME_HEALTH_BOX_SLOT(005)
	BFME_HEALTH_BOX_SLOT(006) BFME_HEALTH_BOX_SLOT(007)
	BFME_HEALTH_BOX_SLOT(008) BFME_HEALTH_BOX_SLOT(009)
	BFME_HEALTH_BOX_SLOT(010) BFME_HEALTH_BOX_SLOT(011)
	BFME_HEALTH_BOX_SLOT(012) BFME_HEALTH_BOX_SLOT(013)
	BFME_HEALTH_BOX_SLOT(014) BFME_HEALTH_BOX_SLOT(015)
	BFME_HEALTH_BOX_SLOT(016) BFME_HEALTH_BOX_SLOT(017)
	BFME_HEALTH_BOX_SLOT(018) BFME_HEALTH_BOX_SLOT(019)
	BFME_HEALTH_BOX_SLOT(020) BFME_HEALTH_BOX_SLOT(021)
	BFME_HEALTH_BOX_SLOT(022) BFME_HEALTH_BOX_SLOT(023)
	BFME_HEALTH_BOX_SLOT(024) BFME_HEALTH_BOX_SLOT(025)
	BFME_HEALTH_BOX_SLOT(026) BFME_HEALTH_BOX_SLOT(027)
	BFME_HEALTH_BOX_SLOT(028) BFME_HEALTH_BOX_SLOT(029)
	BFME_HEALTH_BOX_SLOT(030) BFME_HEALTH_BOX_SLOT(031)
	BFME_HEALTH_BOX_SLOT(032) BFME_HEALTH_BOX_SLOT(033)
	BFME_HEALTH_BOX_SLOT(034) BFME_HEALTH_BOX_SLOT(035)
	BFME_HEALTH_BOX_SLOT(036) BFME_HEALTH_BOX_SLOT(037)
	BFME_HEALTH_BOX_SLOT(038) BFME_HEALTH_BOX_SLOT(039)
	BFME_HEALTH_BOX_SLOT(040) BFME_HEALTH_BOX_SLOT(041)
	BFME_HEALTH_BOX_SLOT(042) BFME_HEALTH_BOX_SLOT(043)
	BFME_HEALTH_BOX_SLOT(044) BFME_HEALTH_BOX_SLOT(045)
	BFME_HEALTH_BOX_SLOT(046) BFME_HEALTH_BOX_SLOT(047)
	BFME_HEALTH_BOX_SLOT(048) BFME_HEALTH_BOX_SLOT(049)
	BFME_HEALTH_BOX_SLOT(050) BFME_HEALTH_BOX_SLOT(051)
	BFME_HEALTH_BOX_SLOT(052) BFME_HEALTH_BOX_SLOT(053)
	BFME_HEALTH_BOX_SLOT(054) BFME_HEALTH_BOX_SLOT(055)
	BFME_HEALTH_BOX_SLOT(056) BFME_HEALTH_BOX_SLOT(057)
	BFME_HEALTH_BOX_SLOT(058) BFME_HEALTH_BOX_SLOT(059)
	BFME_HEALTH_BOX_SLOT(060) BFME_HEALTH_BOX_SLOT(061)
	BFME_HEALTH_BOX_SLOT(062) BFME_HEALTH_BOX_SLOT(063)
	BFME_HEALTH_BOX_SLOT(064) BFME_HEALTH_BOX_SLOT(065)
	BFME_HEALTH_BOX_SLOT(066) BFME_HEALTH_BOX_SLOT(067)
	BFME_HEALTH_BOX_SLOT(068) BFME_HEALTH_BOX_SLOT(069)
	BFME_HEALTH_BOX_SLOT(070) BFME_HEALTH_BOX_SLOT(071)
	BFME_HEALTH_BOX_SLOT(072) BFME_HEALTH_BOX_SLOT(073)
	BFME_HEALTH_BOX_SLOT(074) BFME_HEALTH_BOX_SLOT(075)
	BFME_HEALTH_BOX_SLOT(076) BFME_HEALTH_BOX_SLOT(077)
	BFME_HEALTH_BOX_SLOT(078) BFME_HEALTH_BOX_SLOT(079)
	BFME_HEALTH_BOX_SLOT(080) BFME_HEALTH_BOX_SLOT(081)
	BFME_HEALTH_BOX_SLOT(082) BFME_HEALTH_BOX_SLOT(083)
	BFME_HEALTH_BOX_SLOT(084) BFME_HEALTH_BOX_SLOT(085)
	BFME_HEALTH_BOX_SLOT(086) BFME_HEALTH_BOX_SLOT(087)
	BFME_HEALTH_BOX_SLOT(088) BFME_HEALTH_BOX_SLOT(089)
	BFME_HEALTH_BOX_SLOT(090) BFME_HEALTH_BOX_SLOT(091)
	BFME_HEALTH_BOX_SLOT(092) BFME_HEALTH_BOX_SLOT(093)
	BFME_HEALTH_BOX_SLOT(094) BFME_HEALTH_BOX_SLOT(095)
	BFME_HEALTH_BOX_SLOT(096) BFME_HEALTH_BOX_SLOT(097)
	BFME_HEALTH_BOX_SLOT(098) BFME_HEALTH_BOX_SLOT(099)
	BFME_HEALTH_BOX_SLOT(100) BFME_HEALTH_BOX_SLOT(101)
	BFME_HEALTH_BOX_SLOT(102) BFME_HEALTH_BOX_SLOT(103)
	BFME_HEALTH_BOX_SLOT(104) BFME_HEALTH_BOX_SLOT(105)
	BFME_HEALTH_BOX_SLOT(106) BFME_HEALTH_BOX_SLOT(107)
	BFME_HEALTH_BOX_SLOT(108) BFME_HEALTH_BOX_SLOT(109)
	BFME_HEALTH_BOX_SLOT(110) BFME_HEALTH_BOX_SLOT(111)
	BFME_HEALTH_BOX_SLOT(112) BFME_HEALTH_BOX_SLOT(113)
	BFME_HEALTH_BOX_SLOT(114) BFME_HEALTH_BOX_SLOT(115)
	BFME_HEALTH_BOX_SLOT(116) BFME_HEALTH_BOX_SLOT(117)
	BFME_HEALTH_BOX_SLOT(118) BFME_HEALTH_BOX_SLOT(119)
	BFME_HEALTH_BOX_SLOT(120) BFME_HEALTH_BOX_SLOT(121)
	BFME_HEALTH_BOX_SLOT(122) BFME_HEALTH_BOX_SLOT(123)
	BFME_HEALTH_BOX_SLOT(124) BFME_HEALTH_BOX_SLOT(125)
	BFME_HEALTH_BOX_SLOT(126) BFME_HEALTH_BOX_SLOT(127)
	virtual Bool write(Coord3D *position);
};

class BfmeHealthBoxDrawBridge
{
public:
	BFME_HEALTH_BOX_SLOT(000) BFME_HEALTH_BOX_SLOT(001)
	BFME_HEALTH_BOX_SLOT(002) BFME_HEALTH_BOX_SLOT(003)
	BFME_HEALTH_BOX_SLOT(004) BFME_HEALTH_BOX_SLOT(005)
	BFME_HEALTH_BOX_SLOT(006) BFME_HEALTH_BOX_SLOT(007)
	BFME_HEALTH_BOX_SLOT(008) BFME_HEALTH_BOX_SLOT(009)
	BFME_HEALTH_BOX_SLOT(010) BFME_HEALTH_BOX_SLOT(011)
	BFME_HEALTH_BOX_SLOT(012) BFME_HEALTH_BOX_SLOT(013)
	BFME_HEALTH_BOX_SLOT(014) BFME_HEALTH_BOX_SLOT(015)
	BFME_HEALTH_BOX_SLOT(016) BFME_HEALTH_BOX_SLOT(017)
	BFME_HEALTH_BOX_SLOT(018) BFME_HEALTH_BOX_SLOT(019)
	BFME_HEALTH_BOX_SLOT(020) BFME_HEALTH_BOX_SLOT(021)
	BFME_HEALTH_BOX_SLOT(022) BFME_HEALTH_BOX_SLOT(023)
	BFME_HEALTH_BOX_SLOT(024) BFME_HEALTH_BOX_SLOT(025)
	virtual BfmeHealthBoxAnchor *getAnchor();
};

class BfmeHealthBoxObject
{
public:
	UnsignedByte m_pad000[4];
	OVERRIDE<ThingTemplate> m_template;
	UnsignedByte m_pad008[0xa4];
	GeometryInfo m_geometry;
	UnsignedByte m_pad0e0[0x11c];
	BfmeHealthBoxDrawBridge *m_drawBridge;
};

class Thing
{
public:
	virtual void slot00();
	OVERRIDE<ThingTemplate> m_template;
};

// 0x0041D150 via ILT 0x0003EE55, matched in
// BFMERopeDrawableLinearInterpolatedPosition.cpp.
struct BfmeLinearCoord3D;
class BFMERopeDrawableGetPositionShim
{
public:
	const BfmeLinearCoord3D *getPositionLinear() const;
};

class Snapshot
{
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

class Drawable : public Thing, public Snapshot
{
public:
	void getHealthBoxPosition(Coord3D &position) const;

	UnsignedByte m_pad00c[0xf0];
	BfmeHealthBoxObject *m_object;
};

void Drawable::getHealthBoxPosition(Coord3D &position) const
{
	BfmeHealthBoxObject *object = m_object;
	if (object == 0)
		return;
	Bool placed = false;
	if ((m_template->m_flags & 0x1000) != 0)
	{
		BfmeHealthBoxDrawBridge *bridge = object->m_drawBridge;
		if (bridge != 0 && bridge->getAnchor() != 0 && object->m_drawBridge->getAnchor()->write(&position))
			placed = true;
	}
	if (!placed)
		position = *(const Coord3D *)((BFMERopeDrawableGetPositionShim *)this)->getPositionLinear();
	float healthBoxHeight;
	if (object->m_template == 0)
		healthBoxHeight = 10.0f;
	else
		healthBoxHeight = object->m_template->m_healthBoxHeight;
	position.z = object->m_geometry.getMaxHeightAbovePosition() + position.z + healthBoxHeight;
}
