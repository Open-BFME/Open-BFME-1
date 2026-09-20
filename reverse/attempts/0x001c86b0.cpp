// ?rva001C86B0@Object@@QAEPAUCoord3D@@PAU2@0@Z
// partial score=0.63 date=2026-09-21
// cl: /DNDEBUG /MD /EHs-c-
// ?rva001C86B0@Object@@QAEPAVCoord3D@@PAU1@0@Z

typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef int PathfindLayerEnum;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class BfmeCalc919G
{
public:
	int bfmeCalc919G();
};

class HordeContainInterface
{
public:
#define HC_SLOT(n) virtual void slot##n();
	HC_SLOT(0) HC_SLOT(1) HC_SLOT(2) HC_SLOT(3) HC_SLOT(4) HC_SLOT(5)
	HC_SLOT(6) HC_SLOT(7) HC_SLOT(8) HC_SLOT(9) HC_SLOT(10) HC_SLOT(11)
	HC_SLOT(12) HC_SLOT(13) HC_SLOT(14) HC_SLOT(15) HC_SLOT(16) HC_SLOT(17)
	HC_SLOT(18) HC_SLOT(19) HC_SLOT(20) HC_SLOT(21) HC_SLOT(22) HC_SLOT(23)
	HC_SLOT(24) HC_SLOT(25) HC_SLOT(26) HC_SLOT(27) HC_SLOT(28) HC_SLOT(29)
	HC_SLOT(30) HC_SLOT(31) HC_SLOT(32) HC_SLOT(33) HC_SLOT(34) HC_SLOT(35)
	HC_SLOT(36) HC_SLOT(37) HC_SLOT(38) HC_SLOT(39) HC_SLOT(40) HC_SLOT(41)
	HC_SLOT(42) HC_SLOT(43) HC_SLOT(44) HC_SLOT(45) HC_SLOT(46) HC_SLOT(47)
	HC_SLOT(48) HC_SLOT(49) HC_SLOT(50) HC_SLOT(51) HC_SLOT(52) HC_SLOT(53)
	HC_SLOT(54) HC_SLOT(55) HC_SLOT(56) HC_SLOT(57) HC_SLOT(58) HC_SLOT(59)
	HC_SLOT(60) HC_SLOT(61) HC_SLOT(62) HC_SLOT(63) HC_SLOT(64) HC_SLOT(65)
	HC_SLOT(66) HC_SLOT(67) HC_SLOT(68) HC_SLOT(69) HC_SLOT(70) HC_SLOT(71)
	HC_SLOT(72) HC_SLOT(73) HC_SLOT(74) HC_SLOT(75) HC_SLOT(76) HC_SLOT(77)
	HC_SLOT(78) HC_SLOT(79) HC_SLOT(80) HC_SLOT(81) HC_SLOT(82) HC_SLOT(83)
	HC_SLOT(84) HC_SLOT(85) HC_SLOT(86) HC_SLOT(87)
	virtual Coord3D *rva001C86B0(Coord3D *position, Coord3D *normal);
#undef HC_SLOT
};

class ContainModuleInterface
{
public:
#define CM_SLOT(n) virtual void slot##n();
	CM_SLOT(0) CM_SLOT(1) CM_SLOT(2) CM_SLOT(3) CM_SLOT(4) CM_SLOT(5)
	CM_SLOT(6) CM_SLOT(7) CM_SLOT(8) CM_SLOT(9) CM_SLOT(10) CM_SLOT(11)
	CM_SLOT(12) CM_SLOT(13) CM_SLOT(14) CM_SLOT(15) CM_SLOT(16) CM_SLOT(17)
	CM_SLOT(18) CM_SLOT(19) CM_SLOT(20) CM_SLOT(21) CM_SLOT(22) CM_SLOT(23)
	CM_SLOT(24) CM_SLOT(25)
	virtual HordeContainInterface *getHordeContainInterface();
#undef CM_SLOT
};

class TerrainLogic
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer,
		Coord3D *normal, Bool clip) const;
	PathfindLayerEnum getLayerForDestination(class Object *object,
		const Coord3D *position);
};

extern TerrainLogic *TheTerrainLogic;

class Object
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual BfmeCalc919G *getDrawable();

	UnsignedByte m_pad004[0x8c];
	UnsignedByte m_status;
	UnsignedByte m_pad091[0x16b];
	ContainModuleInterface *m_contain;
	UnsignedByte m_pad200[0x114];
	PathfindLayerEnum m_layer;

	Coord3D *rva001C86B0(Coord3D *position, Coord3D *normal);
};

Coord3D *Object::rva001C86B0(Coord3D *position, Coord3D *normal)
{
	ContainModuleInterface *contain = m_contain;
	if (contain != 0)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde != 0)
		{
			horde->rva001C86B0(position, normal);
			return position;
		}
	}

	BfmeCalc919G *drawable = getDrawable();
	if (drawable != 0)
	{
		int matrix = drawable->bfmeCalc919G();
		Coord3D sample;
		Real sampleX = *(Real *)(matrix + 0x0c);
		Real sampleY = *(Real *)(matrix + 0x1c);
		Real sampleZ = *(Real *)(matrix + 0x2c);
		sample.x = sampleX;
		sample.y = sampleY;
		sample.z = sampleZ;

		if ((m_status & 0x40) != 0)
		{
			PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(
				this, &sample);
			sample.z = TheTerrainLogic->getLayerHeight(
				sampleX, sampleY, layer, normal, true);
		}
		else if (normal != 0)
		{
			TheTerrainLogic->getLayerHeight(
				sampleX, sampleY, m_layer, normal, true);
		}

		*position = sample;
		return position;
	}

	if (normal != 0)
	{
		normal->x = 0.0f;
		normal->y = 0.0f;
		normal->z = 1.0f;
	}
	position->x = 0.0f;
	position->y = 0.0f;
	position->z = 0.0f;
	return position;
}
