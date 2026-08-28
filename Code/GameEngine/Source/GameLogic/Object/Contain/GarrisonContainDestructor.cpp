// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The retail GarrisonContain object has OpenContain's nine polymorphic
// subobjects followed by its 3x40 Coord3D array at offset 0x3fc.  Keep the
// recovered layout in the proper source family so the SEH cleanup and base
// destructor remain tied to the real class.

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
	virtual ~OpenContain();

private:
	unsigned char m_pad[0x3c4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
	~Coord3D() {}

private:
	float m_value[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GarrisonContain.h
class GarrisonContain : public OpenContain
{
public:
	virtual ~GarrisonContain();

private:
	Coord3D m_garrisonPoint[3][40];
};

// ??1GarrisonContain@@UAE@XZ
GarrisonContain::~GarrisonContain()
{
}
