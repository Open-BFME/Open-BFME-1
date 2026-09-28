// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/projectedshadow /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "always.h"
#include "rendobj.h"
#include "Lib/BaseType.h"
#include "GameClient/Color.h"
#include "WW3D2/lightenvironment.h"
#include "W3DDevice/GameClient/W3DProjectedShadow.h"
struct BFMEShadowTypeInfo
{
	Char name[128];
	ShadowType type;
	Bool allowUpdates;
	Bool allowWorldAlign;
	Char pad[2];
	Real sizeX;
	Real sizeY;
	Real offsetX;
	Real offsetY;
	Int unused98;
	Int flags;
	Bool force;
};

class BFMEShadowManagerLayout
{
public:
	W3DShadowTexture *getTexture(const Char *name);
	W3DProjectedShadow *addShadowCore(
		W3DShadowTexture *texture,
		RenderObjClass *robj,
		ShadowType type,
		Bool allowWorldAlign,
		Real sizeX,
		Real sizeY,
		Int flags,
		Real offsetX,
		Real offsetY,
		W3DProjectedShadow **list,
		Bool simple,
		Drawable *draw,
		Bool projected);
};


// RVA 0x007B4180: BFME decal overload; exact public identity is unproven.
class Rva007B4180Manager {
public:
 W3DProjectedShadow *addDecal(RenderObjClass *robj, BFMEShadowTypeInfo *info, bool simple, bool projected);
};
W3DProjectedShadow *Rva007B4180Manager::addDecal(RenderObjClass *robj, BFMEShadowTypeInfo *info, bool simple, bool projected)
{
 if (!robj || !info) return 0;
 float sizeX=info->sizeX;
 float sizeY=info->sizeY;
 volatile int flags=info->flags;
 if (sizeX==0.0f || sizeY==0.0f) {
  AABoxClass box;
  robj->Get_Obj_Space_Bounding_Box(box);
  if (sizeX==0.0f) sizeX=box.Extent.X*2.0f;
  if (sizeY==0.0f) sizeY=box.Extent.Y*2.0f;
 }
 BFMEShadowManagerLayout *manager=(BFMEShadowManagerLayout*)this;
 if (simple) { return manager->addShadowCore(manager->getTexture(info->name),robj,info->type,info->allowWorldAlign,sizeX,sizeY,flags,info->offsetX,info->offsetY,(W3DProjectedShadow**)((char*)this+12),true,0,false); }
 else if (projected) { return manager->addShadowCore(manager->getTexture(info->name),robj,info->type,info->allowWorldAlign,sizeX,sizeY,flags,info->offsetX,info->offsetY,(W3DProjectedShadow**)((char*)this+28),false,(Drawable*)manager->getTexture(info->name+64),true); }
 else { return manager->addShadowCore(manager->getTexture(info->name),robj,info->type,info->allowWorldAlign,sizeX,sizeY,flags,info->offsetX,info->offsetY,(W3DProjectedShadow**)((char*)this+8),false,0,false); }
}




