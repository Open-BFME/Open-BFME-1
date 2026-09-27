// cl: /DNDEBUG /MD /EHsc
// readable body of ??0GarrisonContain@@QAE@PAVThing@@PBVModuleData@@@Z: game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp
// stlport

// Constructor 0x0021D820, the sibling of the complete destructor 0x0021D9C0 in
// GarrisonContainDestructor.cpp; both bodies share this original source owner.
//
// The retail object is OpenContain's nine polymorphic subobjects (vptrs at +0x00,
// +0x0c, +0x10, +0x20 .. +0x34) followed by the recovered GarrisonContain
// members: the per-point placement record at +0xd8, the in-use count at +0x3f8,
// the 3x40 Coord3D condition array at +0x3fc and the tail through +0x9b6.
// The 3x40 array is placement-new'd in place (the 0x78/0xc argument pair and the
// Coord3D ctor/dtor thunks 0x00016C93/0x0001364C in the retail call), which is
// why Coord3D's ctor and dtor are only declared here.

class Thing;
class ModuleData;

enum
{
	MAX_GARRISON_POINTS = 40,
	MAX_GARRISON_POINT_CONDITIONS = 3
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class OpenContainPrimaryBase
{
public:
	virtual ~OpenContainPrimaryBase() {}

private:
	unsigned char m_pad[8];
};

template <int Number>
class OpenContainSecondaryBase
{
public:
	virtual ~OpenContainSecondaryBase() {}
};

class OpenContainWideSecondaryBase
{
public:
	virtual ~OpenContainWideSecondaryBase() {}

private:
	unsigned char m_pad[12];
};

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainSecondaryBase<1>,
	  public OpenContainWideSecondaryBase,
	  public OpenContainSecondaryBase<2>,
	  public OpenContainSecondaryBase<3>,
	  public OpenContainSecondaryBase<4>,
	  public OpenContainSecondaryBase<5>,
	  public OpenContainSecondaryBase<6>,
	  public OpenContainSecondaryBase<7>
{
public:
	OpenContain(Thing *, const ModuleData *);
	virtual ~OpenContain();

protected:
	unsigned char m_pad38[0x9c];
	unsigned int m_unmodelled_d4;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GarrisonContain.h
struct GarrisonPointData
{
	ObjectID objectID;
	ObjectID targetID;
	unsigned int placeFrame;
	unsigned int lastEffectFrame;
	void *effect;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
	Coord3D();
	~Coord3D();
	void zero()
	{
		m_value[0] = 0.0f;
		m_value[1] = 0.0f;
		m_value[2] = 0.0f;
	}

private:
	float m_value[3];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GarrisonContain.h
class GarrisonContain : public OpenContain
{
public:
	GarrisonContain(Thing *, const ModuleData *);
	virtual ~GarrisonContain();

private:
	GarrisonPointData m_garrisonPointData[MAX_GARRISON_POINTS];
	int m_garrisonPointsInUse;
	Coord3D m_garrisonPoint[MAX_GARRISON_POINT_CONDITIONS][MAX_GARRISON_POINTS];
	int m_unmodelled_99c[MAX_GARRISON_POINT_CONDITIONS];
	unsigned int m_unmodelled_9a8[3];
	bool m_unmodelled_9b4;
	bool m_unmodelled_9b5;
	bool m_unmodelled_9b6;
};

// ??0GarrisonContain@@QAE@PAVThing@@PBVModuleData@@@Z
GarrisonContain::GarrisonContain(Thing *thing, const ModuleData *moduleData)
	: OpenContain(thing, moduleData)
{
	m_unmodelled_d4 = 0;
	m_unmodelled_9b5 = false;
	m_garrisonPointsInUse = 0;
	m_unmodelled_9b4 = false;

	for (int i = 0; i != MAX_GARRISON_POINTS; ++i)
	{
		m_garrisonPointData[i].objectID = INVALID_OBJECT_ID;
		m_garrisonPointData[i].targetID = INVALID_OBJECT_ID;
		m_garrisonPointData[i].placeFrame = 0;
		m_garrisonPointData[i].lastEffectFrame = 0;
		m_garrisonPointData[i].effect = 0;

		// The three conditions are spelled out rather than looped: the nested
		// loop costs two more callee-saved pushes in the prologue than retail
		// has, and this body keeps only esi.
		m_garrisonPoint[0][i].zero();
		m_garrisonPoint[1][i].zero();
		m_garrisonPoint[2][i].zero();
	}

	m_unmodelled_99c[0] = 0;
	m_unmodelled_99c[1] = 0;
	m_unmodelled_99c[2] = 0;
	m_unmodelled_9b6 = false;
	m_unmodelled_9a8[0] = 0;
	m_unmodelled_9a8[1] = 0;
	m_unmodelled_9a8[2] = 0;
}
