// ?d_003f6090@@YAXXZ
// partial score=1.0 date=2026-09-22
// MASKED-EXACT PARTIAL ONLY: 1142/1142 bytes, zero masked differences.
// add_match.py failed on nine unresolved callee aliases and reverted its row.
// /alternatename directives below are NOT consumed by the custom byte linker.
// The aliases differ from existing ledger identities: Coord3D class V versus
// struct U, namespaced radius helper, address-derived ring members and cost.
// Do not add speculative pins: route_verdict requires the exact symbol to
// name the matched target. Needs canonical callee declaration integration.
// Best measured source preserved here; no production claim.
// Pathfinder::adjustDestination -- retail RVA 003F6090, 1142 bytes.
// Identity: named callers through ILT 00027FFC; the analyst hub 002417E0
// passes Pathfinder in ECX and Object, embedded AI+1A8 LocomotorSet,
// mutable Coord3D and nullable group Coord3D on the stack; AL/ret16.
// The complete frame is A4; the query records are 60 bytes (003E6110).
// The ring helpers consume four / three arguments and return AL; the
// observed caller also supplies Pathfinder in ECX, although 003F4F70
// does not read that receiver. The visible ring body is compiler context.
// Reconstruction shaping, not a claim about original source spelling:
// volatile reads keep found.y in EBX and reload the object argument at
// +310/+321; zero-instruction barriers preserve the first success tail
// shared by the +2E7 and +36B branches, separate from the allied tail.
// The included already matched radius body and recursive override walker
// expose genuine callee effects; their call routes remain retail ILTs.
// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath 
#include <math.h>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// The already landed helper is included unchanged to expose its non-retaining
// output-reference contract. It remains a separate, independently checked body.
namespace RadiusContract003DEE30 {
#include "../../Code/GameEngine/Source/GameLogic/AI/PathfindGetRadiusAndCenterE30.cpp"
}
struct RadiusAccess003DEE30 : RadiusContract003DEE30::Pathfinder {
 using RadiusContract003DEE30::Pathfinder::getRadiusAndCenter;
};
typedef int Int;
typedef bool Bool;
typedef float Real;
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &p) {x=p.x; y=p.y; z=p.z;}
inline Coord3D &Coord3D::operator=(const Coord3D &p) {x=p.x; y=p.y; z=p.z;return *this;}
struct ICoord2D { Int x,y; };
enum PathfindLayerEnum { LAYER_INVALID=0 };
class LocomotorSet;
class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern bool Glo012F0239;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(CRCParameterCheck *,const char *,...);
class BfmeOverridable {
public:
 __declspec(noinline) BfmeOverridable *friend_getFinalOverride();
 BfmeOverridable *getFinalOverride() { return m_override ? m_override->friend_getFinalOverride() : this; }
 Int m_unknown00;
 BfmeOverridable *m_override;
 char m_pad08[0xc8-8];
 Int m_flagsC8;
};
// Complete override walker from Overridable.h; compare helper separately.
BfmeOverridable *BfmeOverridable::friend_getFinalOverride() {
 if (m_override) return m_override->friend_getFinalOverride();
 return this;
}
class Object {
public:
 Int m_unknown00;
 BfmeOverridable *m_template;
 char m_pad08[0x74-8];
 Int m_id;
 BfmeOverridable *getTemplate() {
  BfmeOverridable *p=m_template;
  if (p && p->m_override) p=p->m_override->friend_getFinalOverride();
  return p;
 }
};
class TerrainLogic {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6();
 virtual Real getLayerHeight(Real,Real,PathfindLayerEnum,Coord3D *,Bool) const;
 PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;
class Pathfinder {
public:
 Bool adjustDestination(Object *,const LocomotorSet &,Coord3D *,const Coord3D *);
 Bool worldToCell(const Coord3D *,ICoord2D *);
 Bool rva003F4F70(const ICoord2D *,Int,ICoord2D *,void *);
 Bool rva003F5340(const ICoord2D *,Int,void *);
 Int rva003E11E0(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *);
protected:
 void getRadiusAndCenter(const Object *,Int &,Bool &);
 void adjustCoordToCell(Int,Int,Bool,Coord3D &,PathfindLayerEnum);
 void tightenPath(Object *,const LocomotorSet &,Coord3D *,const Coord3D *);
};
class Rva003E6110Info {
public:
 Rva003E6110Info(Pathfinder *,Object *,void *,const Coord3D *,const Coord3D *,Int,Int);
 Pathfinder *volatile m_pathfinder;
 Object *volatile m_obj;
 void *volatile m_arg3;
 unsigned char m_notComputer,m_center;
 Int m_radius;
 const Coord3D *m_groupPos;
 Int m_layer;
 Int volatile m_arg6;
 Int m_pad20,m_pad24,m_zero28;
 Int volatile m_arg7;
 Coord3D m_pos;
};
// The landed 003F4F70 body is unchanged below except its unused receiver.
// Independent byte probe is required before relying on the visible contract.
class BfmeCellTesterRva003F5340 {public: bool test(Int,Int);};
Bool Pathfinder::rva003F4F70(const ICoord2D *center, Int radius, ICoord2D *found, void *userData)
{
	if (Glo012F0239 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(
			TheCRCParameterCheck,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			center->x,
			center->y,
			radius);
	}

	BfmeCellTesterRva003F5340 *tester = (BfmeCellTesterRva003F5340 *)userData;

	if (tester->test(center->x, center->y))
	{
		if (Glo012F0239 && TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tfunc succeeded found=%d,%d", center->x, center->y);
		found->x = center->x;
		found->y = center->y;
		return true;
	}
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tfunc failed");

	Int best = 0;
	Int dx = 0, dy = 0;
	Int delta = 1;
	if (radius > 0)
	{
		do
		{
			radius -= 4 * delta + 2;
			Int count;
			for (count = delta; count > 0; count--)
			{
				dx++;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}
			for (count = delta; count > 0; count--)
			{
				dy++;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}

			for (count = 0; count <= delta; count++)
			{
				dx--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}
			for (count = 0; count <= delta; count++)
			{
				dy--;
				if (best == 0 || dx * dx + dy * dy < best)
				{
					if (tester->test(center->x + dx, center->y + dy))
					{
						best = dx * dx + dy * dy;
						found->x = center->x + dx;
						found->y = center->y + dy;
					}
				}
			}
			if (best != 0) {
				if (Glo012F0239 && TheCRCParameterCheck)
					bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tbest return true. found=%d,%d", found->x, found->y);
				return true;
			}
			delta += 2;
		} while (radius > 0);
	}
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\ttotal failure. found=%d,%d", found->x, found->y);
	return false;
}

Bool Pathfinder::adjustDestination(Object *obj,const LocomotorSet &locomotorSet,Coord3D *dest,const Coord3D *groupDest)
{
 if (Glo012F0239 && TheCRCParameterCheck)
  bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  Pathfinder::AdjustDestination() onEnter dest=%g,%g,%g",dest->x,dest->y,dest->z);
 if (obj->getTemplate()->m_flagsC8 & 0x2000000) {
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  projectile return TRUE");
  _ReadWriteBarrier(); return true;
 }
 Bool center;
 Coord3D adjustDest;
 ICoord2D cell;
 {
 Int iRadius;
 ((RadiusAccess003DEE30*)this)->getRadiusAndCenter((const RadiusContract003DEE30::Object*)obj,iRadius,center);
 if (Glo012F0239 && TheCRCParameterCheck)
  bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  iRadius=%d, center=%s",iRadius,center?"TRUE":"FALSE");
 adjustDest=*dest;
 if (!center) {
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  before adjustDest=%d,%d",adjustDest.x,adjustDest.y);
  adjustDest.x+=5.0f; adjustDest.y+=5.0f;
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  after adjustDest=%d,%d",adjustDest.x,adjustDest.y);
 }
 worldToCell(&adjustDest,&cell);
 if (Glo012F0239 && TheCRCParameterCheck)
  bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  AdjDest obj=%i, dest=%g,%g,%g, radius=%i, center=%i",obj->m_id,dest->x,dest->y,dest->z,iRadius,center?1:0);
 }
 PathfindLayerEnum layer;
 if (obj->getTemplate()->m_flagsC8 & 0x4000)
  layer=TheTerrainLogic->getLayerForDestination(obj,dest);
 else layer=LAYER_INVALID;
 union { Real value; Int bits; } height;
 if (groupDest) height.value=groupDest->z;
 else height.value=TheTerrainLogic->getLayerHeight(dest->x,dest->y,TheTerrainLogic->getLayerForDestination(obj,dest),0,true);
 Rva003E6110Info info(this,obj,(void *)&locomotorSet,dest,groupDest,height.bits,layer);
 ICoord2D found;
 if (rva003F4F70(&cell,400,&found,&info)) {
  Int foundY=*(const volatile Int*)&found.y;
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  got %d,%d",found.x,foundY);
  adjustCoordToCell(found.x,foundY,center,*dest,(PathfindLayerEnum)info.m_layer);
  if (!groupDest) {_ReadWriteBarrier();return true;}
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"        groupDest tighten path case...");
  tightenPath(*(Object *const volatile*)&obj,locomotorSet,dest,groupDest);
  Int cost=rva003E11E0(*(Object *const volatile*)&obj,locomotorSet,groupDest,dest);
  Int distance=(Int)fabs(groupDest->x-adjustDest.x)+(Int)fabs(groupDest->y-adjustDest.y);
  if (!(distance*1.4f<cost)) {_ReadWriteBarrier();return true;}
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"        badGroup = true in tighten case");
 }
 
 if (info.m_zero28) {
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  got with allies %d,%d",info.m_pad20,info.m_pad24);
  adjustCoordToCell(info.m_pad20,info.m_pad24,center,*dest,(PathfindLayerEnum)info.m_layer);
  return true;
 }
 if (groupDest) {
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  IterateCircular with groupDest");
  return rva003F5340(&cell,400,&Rva003E6110Info(this,obj,(void *)&locomotorSet,dest,0,*(const Int*)&dest->z,info.m_arg7));
 }
 if (Glo012F0239 && TheCRCParameterCheck)
  bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  got NOTHING");
 return false;
}

#pragma comment(linker, "/alternatename:?friend_getFinalOverride@BfmeOverridable@RadiusContract003DEE30@@QAEPAV12@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?getRadiusAndCenter@Pathfinder@RadiusContract003DEE30@@IAEXPBVObject@2@AAHAA_N@Z=?j_000461ff@@YAXXZ")
#pragma comment(linker, "/alternatename:?friend_getFinalOverride@BfmeOverridable@@QAEPAV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003F4F70@Pathfinder@@QAE_NPBUICoord2D@@HPAU2@PAX@Z=?j_0000e28c@@YAXXZ")
#pragma comment(linker, "/alternatename:?test@BfmeCellTesterRva003F5340@@QAE_NHH@Z=?j_00046e6b@@YAXXZ")
#pragma comment(linker, "/alternatename:_bfmeRetailCritterDesyncLog=?j_0003a17a@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003F5340@Pathfinder@@QAE_NPBUICoord2D@@HPAX@Z=?j_00011027@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003E11E0@Pathfinder@@QAEHPAVObject@@ABVLocomotorSet@@PBVCoord3D@@2@Z=?j_00038f19@@YAXXZ")
#pragma comment(linker, "/alternatename:?tightenPath@Pathfinder@@IAEXPAVObject@@ABVLocomotorSet@@PAVCoord3D@@PBV4@@Z=?j_0000874c@@YAXXZ")
#pragma comment(linker, "/alternatename:?adjustCoordToCell@Pathfinder@@IAEXHH_NAAVCoord3D@@W4PathfindLayerEnum@@@Z=?j_000411d2@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva003E6110Info@@QAE@PAVPathfinder@@PAVObject@@PAXPBVCoord3D@@3HH@Z=?j_000136bf@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLayerForDestination@TerrainLogic@@QAE?AW4PathfindLayerEnum@@PAVObject@@PBVCoord3D@@@Z=?j_0001c675@@YAXXZ")
#pragma comment(linker, "/alternatename:?worldToCell@Pathfinder@@QAE_NPBVCoord3D@@PAUICoord2D@@@Z=?j_000171e8@@YAXXZ")
