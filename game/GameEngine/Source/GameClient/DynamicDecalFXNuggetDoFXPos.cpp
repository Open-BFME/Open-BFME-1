// ?doFXPos@DynamicDecalFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// Retail RVA 00429080; complete 575-byte positional callback.
// Native StringBase access inlines; math/color accessors stay out of line.
// See identity_evidence/00429080-dynamic-decal.md for slot and ABI evidence.

#define inline __declspec(noinline) inline
#include "Lib/BaseType.h"
#include "matrix3d.h"
#undef inline
#include "ascii_string.h"
#include "GameClient/Color.h"
#include "GameClient/Shadow.h"

void adjustVector(Coord3D *vec, const Matrix3D *mtx);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Rva00429080TerrainView
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

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
extern const Real BfmeZeroRange;

// BFME-only fields are deliberately separate from canonical Shadow.
struct Rva00429080ShadowInfo {
 char name[128]; int type; bool allowUpdates,allowWorldAlign; char pad[2];
 float sizeX,sizeY,offsetX,offsetY,unused98,field9C; bool fieldA0;
};
extern void j_0000dc7e(); // Shadow::setOpacity at4597A0; RET4.
extern void j_00005119(); // Shadow::rva00459960 at459960; RET32.
class Rva00429080ShadowView {
public:
 char field00[8]; Coord3D field08; char field14[12]; float field20;
 __forceinline void setOpacity(int value) {
  typedef void (Rva00429080ShadowView::*Call)(int);
  typedef char WidthCheck[sizeof(Call)==sizeof(void(*)()) ? 1 : -1];
  union { void (*entry)(); Call member; } call;
  call.entry=j_0000dc7e; (this->*call.member)(value);
 }
 __forceinline void rva00459960(int a,int b,int c,int d,int e,int f,int g,int h) {
  typedef void (Rva00429080ShadowView::*Call)(int,int,int,int,int,int,int,int);
  typedef char WidthCheck[sizeof(Call)==sizeof(void(*)()) ? 1 : -1];
  union { void (*entry)(); Call member; } call;
  call.entry=j_00005119; (this->*call.member)(a,b,c,d,e,f,g,h);
 }
};

class BfmeColourABK { public: void bfmeSetABK(int); };

class Rva00429080ShadowManagerView
{
public:
	// This local view retains the two slots before the one-argument add-decal
	// entry: the manager's destructor and object-following overload.
	virtual void managerSlot00(void);
	virtual void managerSlot04(void);
	virtual Shadow *addDecal(Rva00429080ShadowInfo *info);
};

class ProjectedShadowManager;
extern ProjectedShadowManager *TheProjectedShadowManager;

#define BFME_FRAME_SCALE 0.03f

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
	UnsignedInt m_opacityStart;
	Real m_opacityFadeTimeOne;
	UnsignedInt m_opacityPeak;
	Real m_opacityPeakTime;
	Real m_opacityFadeTimeTwo;
	UnsignedInt m_opacityEnd;
	Real m_startingDelay;
	Real m_lifetime;
};

// ?doFXPos@DynamicDecalFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
void DynamicDecalFXNugget::doFXPos(const Coord3D *primary,
	const Matrix3D *primaryMtx, Real,
	const Coord3D *secondary) const
{
	if (!primary)
		return;

	Coord3D offset;
	Rva00429080ShadowInfo decalInfo;
	decalInfo.field9C = 20.0f;
	decalInfo.fieldA0 = false;
	strncpy(decalInfo.name,
		m_decalName.str(), 0x40);
	decalInfo.type = m_shader == 1 ? 0x800 : 0x400;
	decalInfo.allowUpdates = true;
	decalInfo.allowWorldAlign = true;
	decalInfo.sizeX = m_size;
	decalInfo.sizeY = m_size;
	decalInfo.offsetX = 0.0f;
	decalInfo.offsetY = 0.0f;
// Retail builds the translated position from this offset.
	offset.x = m_offset.x;
	offset.y = m_offset.y;
	offset.z = 0.0f;

	if (primaryMtx && m_orientToObject)
		adjustVector(&offset, primaryMtx);

	Coord3D position;
	position.y = primary->y;
	position.x = *(const volatile Real*)&primary->x;
	position.x += offset.x;
	position.y += offset.y;
	position.z = ((Rva00429080TerrainView *)TheTerrainLogic)->getGroundHeight(
		position.x, position.y, 0);

	Shadow *shadow = ((Rva00429080ShadowManagerView *)TheProjectedShadowManager)->addDecal(&decalInfo);
	if (shadow)
	{
		if (primaryMtx && m_orientToObject)
			((Rva00429080ShadowView *)shadow)->field20 = primaryMtx->Get_Z_Rotation();
		else
			((Rva00429080ShadowView *)shadow)->field20 = 0.0f;

		((BfmeColourABK *)shadow)->bfmeSetABK(m_color.getAsInt());
		*(Coord3D*)((char*)shadow+8) = position;

		Int initialOpacity = (Int)(m_startingDelay > BfmeZeroRange
			? BfmeZeroRange : (Real)m_opacityStart);
		((Rva00429080ShadowView *)shadow)->setOpacity(initialOpacity);
		((Rva00429080ShadowView *)shadow)->rva00459960(
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
