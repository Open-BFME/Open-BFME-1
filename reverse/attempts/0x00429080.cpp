// ?doFXPos@DynamicDecalFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
// partial score=0.85 date=2026-09-11
// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ conversion of DynamicDecal's positional dispatch.

extern "C" __declspec(dllimport) char *__cdecl strncpy(
	char *dest, const char *source, unsigned int count);

typedef char Char;
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Char *m_data;

	__forceinline const Char *str(void) const
	{
		if (m_data)
			return m_data + 8;
		return (const Char *)0x0107388b;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	Real red;
	Real green;
	Real blue;

	Int getAsInt(void) const;
};

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D
{
public:
	Real Get_Z_Rotation(void) const;
};

void adjustVector(Coord3D *vec, const Matrix3D *mtx);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0C(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const;
};

extern TerrainLogic *TheTerrainLogic;
extern const Real BfmeZeroRange;

// BFME's dynamic decal path passes the extended ShadowTypeInfo used by the
// renderer's BFME add-decal entry.  The standard ZH header only describes the
// first 64 name bytes, so keep this ABI view local to the conversion TU.
class Shadow
{
public:
	struct ShadowTypeInfo
	{
		Char name[128];
		Int type;
		Bool allowUpdates;
		Bool allowWorldAlign;
		Char pad[2];
		Real sizeX;
		Real sizeY;
		Real offsetX;
		Real offsetY;
		Int unused98;
		Real flags;
		Bool force;
	};

	void setColor(Int value);
	void setOpacity(Int value);

	// The BFME decal object has a vtable/prefix before its position, unlike
	// the small no-vptr view used by the setter-only thunks.
	Char m_pad00[8];
	Real m_x;
	Real m_y;
	Real m_z;
	Char m_pad14[0x0c];
	Real m_localAngle;
};

class Gen00459960
{
public:
	void setBounds(Int a, Int b, Int c, Int d,
		Int e, Int f, Int g, Int h);
};

class ProjectedShadowManager
{
public:
	// This local view retains the two slots before the one-argument add-decal
	// entry: the manager's destructor and object-following overload.
	virtual void managerSlot00(void);
	virtual void managerSlot04(void);
	virtual Shadow *addDecal(Shadow::ShadowTypeInfo *info);
};

extern ProjectedShadowManager *TheProjectedShadowManager;

#define BFME_FRAME_SCALE (*(const Real *)0x010f224c)

class DynamicDecalFXNugget
{
public:
	virtual void v00(void);
	virtual void doFXPos(const Coord3D *, const Matrix3D *, Real,
		const Coord3D *secondary) const;
	virtual void doFXObj(const void *, const void *) const;

private:
	Char m_unmodelled[0xb0];
	AsciiString m_decalName;
	volatile Int m_shader;
	Real m_size;
	RGBColor m_color;
	Coord2D m_offset;
	volatile Bool m_orientToObject;
	Char m_padD5[3];
	volatile UnsignedInt m_opacityStart;
	volatile Real m_opacityFadeTimeOne;
	volatile UnsignedInt m_opacityPeak;
	volatile Real m_opacityPeakTime;
	volatile Real m_opacityFadeTimeTwo;
	volatile UnsignedInt m_opacityEnd;
	volatile Real m_startingDelay;
	volatile Real m_lifetime;
};

// ?doFXPos@DynamicDecalFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
void DynamicDecalFXNugget::doFXPos(const Coord3D *primary,
	const Matrix3D *primaryMtx, Real,
	const Coord3D *secondary) const
{
	if (!primary)
		return;

	Coord3D offset;
	Shadow::ShadowTypeInfo decalInfo;
	decalInfo.flags = 20.0f;
	decalInfo.force = false;
		const Char *decalName = m_decalName.m_data
			? m_decalName.m_data + 8 : (const Char *)0x0107388b;
	strncpy(decalInfo.name, decalName, 0x40);
	decalInfo.type = m_shader == 1 ? 0x800 : 0x400;
	decalInfo.allowUpdates = true;
	decalInfo.allowWorldAlign = true;
	decalInfo.sizeX = m_size;
	decalInfo.sizeY = m_size;
	decalInfo.offsetX = 0.0f;
	decalInfo.offsetY = 0.0f;
	// Retail keeps the offset vector at the low stack address and uses a
	// separate position aggregate for the translated terrain query.
	offset.x = m_offset.x;
	offset.y = m_offset.y;
	offset.z = 0.0f;

	if (primaryMtx && m_orientToObject)
		adjustVector(&offset, primaryMtx);

	Real positionY = offset.y + primary->y;
	Real positionX = offset.x + primary->x;
	Real positionZ = TheTerrainLogic->getGroundHeight(
		positionX, positionY, 0);

	Shadow *shadow = TheProjectedShadowManager->addDecal(&decalInfo);
	if (shadow)
	{
		if (secondary && m_orientToObject)
			shadow->m_localAngle = reinterpret_cast<const Matrix3D *>(secondary)->Get_Z_Rotation();
		else
			shadow->m_localAngle = 0.0f;

		shadow->setColor(m_color.getAsInt());
		shadow->m_x = positionX;
		shadow->m_y = positionY;
		shadow->m_z = positionZ;

		Int initialOpacity = (Int)(m_startingDelay > BfmeZeroRange
			? BfmeZeroRange : (Real)m_opacityStart);
		shadow->setOpacity(initialOpacity);
		reinterpret_cast<Gen00459960 *>(shadow)->setBounds(
			(Int)(m_startingDelay * BFME_FRAME_SCALE),
			(Int)(m_lifetime * BFME_FRAME_SCALE),
			m_opacityStart,
			(Int)(m_opacityFadeTimeOne * BFME_FRAME_SCALE),
			m_opacityPeak,
			(Int)(m_opacityPeakTime * BFME_FRAME_SCALE),
			(Int)(m_opacityFadeTimeTwo * BFME_FRAME_SCALE),
			m_opacityEnd);
	}
}
