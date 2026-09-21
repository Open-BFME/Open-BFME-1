// ?adjustDestination@Pathfinder@@QAE_NPAVObject@@ABVLocomotorSet@@PAUCoord3D@@PBU4@@Z
// partial score=0.2933 date=2026-09-21
// cl: /DNDEBUG /MD
// Experimental reconstruction; no production claim until the complete gate.
#include <math.h>
typedef int Int;
typedef bool Bool;
typedef float Real;
struct Coord3D { Real x,y,z; };
struct ICoord2D { Int x,y; };
enum PathfindLayerEnum { LAYER_INVALID=0 };
class LocomotorSet;
class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern bool Glo012F0239;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(CRCParameterCheck *,const char *,...);
class BfmeOverridable {
public:
 BfmeOverridable *friend_getFinalOverride();
 BfmeOverridable *getFinalOverride() { return m_override ? m_override->friend_getFinalOverride() : this; }
 Int m_unknown00;
 BfmeOverridable *m_override;
 char m_pad08[0xc8-8];
 Int m_flagsC8;
};
class Object {
public:
 Int m_unknown00;
 BfmeOverridable *m_template;
 char m_pad08[0x74-8];
 Int m_id;
 BfmeOverridable *getTemplate() { return m_template ? m_template->getFinalOverride() : m_template; }
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
Bool Pathfinder::adjustDestination(Object *obj,const LocomotorSet &locomotorSet,Coord3D *dest,const Coord3D *groupDest)
{
 if (Glo012F0239 && TheCRCParameterCheck)
  bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  Pathfinder::AdjustDestination() onEnter dest=%g,%g,%g",dest->x,dest->y,dest->z);
 if (obj->getTemplate()->m_flagsC8 & 0x2000000) {
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  projectile return TRUE");
  return true;
 }
 Int iRadius; Bool center;
 getRadiusAndCenter(obj,iRadius,center);
 if (Glo012F0239 && TheCRCParameterCheck)
  bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  iRadius=%d, center=%s",iRadius,center?"TRUE":"FALSE");
 Coord3D adjustDest=*dest;
 if (!center) {
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  before adjustDest=%d,%d",adjustDest.x,adjustDest.y);
  adjustDest.x+=5.0f; adjustDest.y+=5.0f;
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  after adjustDest=%d,%d",adjustDest.x,adjustDest.y);
 }
 ICoord2D cell;
 worldToCell(&adjustDest,&cell);
 if (Glo012F0239 && TheCRCParameterCheck)
  bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  AdjDest obj=%i, dest=%g,%g,%g, radius=%i, center=%i",obj->m_id,dest->x,dest->y,dest->z,iRadius,center?1:0);
 PathfindLayerEnum layer=LAYER_INVALID;
 if (obj->getTemplate()->m_flagsC8 & 0x4000)
  layer=TheTerrainLogic->getLayerForDestination(obj,dest);
 union { Real value; Int bits; } height;
 if (groupDest) height.value=groupDest->z;
 else height.value=TheTerrainLogic->getLayerHeight(dest->x,dest->y,TheTerrainLogic->getLayerForDestination(obj,dest),0,true);
 Rva003E6110Info info(this,obj,(void *)&locomotorSet,dest,groupDest,height.bits,layer);
 ICoord2D found;
 if (rva003F4F70(&cell,400,&found,&info)) {
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  got %d,%d",found.x,found.y);
  adjustCoordToCell(found.x,found.y,center,*dest,(PathfindLayerEnum)info.m_layer);
  if (!groupDest) return true;
  if (Glo012F0239 && TheCRCParameterCheck)
   bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"        groupDest tighten path case...");
  tightenPath(obj,locomotorSet,dest,groupDest);
  Int cost=rva003E11E0(obj,locomotorSet,groupDest,dest);
  Int distance=(Int)fabs(groupDest->y-adjustDest.y)+(Int)fabs(groupDest->x-adjustDest.x);
  if (!(cost>distance*1.4f)) return true;
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
  height.value=dest->z;
  Rva003E6110Info fallback(this,obj,(void *)&locomotorSet,dest,0,height.bits,info.m_arg7);
  return rva003F5340(&cell,400,&fallback);
 }
 if (Glo012F0239 && TheCRCParameterCheck)
  bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  got NOTHING");
 return false;
}
