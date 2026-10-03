// ?Visibility_Check@RTS3DScene@@UAEXPAVCameraClass@@@Z
// partial score=0.3738 date=2026-10-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define Matrix4x4 Matrix4
#define _OPERATOR_NEW_DEFINED_
#include "Lib/BaseType.h"
#include <slist>
#include <vector>
#include "rendobj.h"
#include "camera.h"
#include "shader.h"
#include "Common/GameMemory.h"
#pragma auto_inline(off)
#include "Common/Overridable.h"
#pragma auto_inline(on)
#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
inline const ThingTemplate *Thing::getTemplate() const {
 const ThingTemplate *tmpl=m_template.getNonOverloadedPointer();
 if (tmpl == 0) return 0;
 const Overridable *next=*reinterpret_cast<const Overridable *const *>(reinterpret_cast<const char *>(tmpl)+4);
 if (next) tmpl=static_cast<const ThingTemplate *>(next->getFinalOverride());
 return tmpl;
}
#include "GameLogic/Object.h"

class Gen_00943CF0 { public: void update(void *); };
class Rva00944430 { void rva00944430(void **, CameraClass *, const float *); friend class RTS3DScene; };
class Gen_00410BA0 { public: int bfmeBusy() const; };
class GlobalData;
class GameLogic;
extern GlobalData *TheGlobalData;
extern GameLogic *TheGameLogic;
struct Rva00715DC0GlobalView {
 char pad0[0x1b4]; unsigned m_defaultOcclusionDelay;
 char pad1[0xa44-0x1b8]; int m_maxVisibleTranslucentObjects;
 int m_maxVisibleOccluderObjects, m_maxVisibleOccludeeObjects, m_maxVisibleNonOccluderOrOccludeeObjects;
};
struct Rva00715DC0DrawableView {
 char pad0[0xb0]; float m_explicitOpacity, m_effectiveStealthOpacity;
 char pad1[0xfc-0xb8]; Object *m_object;
 char pad2[0x110-0x100]; unsigned m_status;
 char pad3[0x3b0-0x114]; bool m_field3b0;
};
struct Rva00715DC0Info { unsigned field0; Rva00715DC0DrawableView *m_drawable; unsigned field8, m_flags; };
#define DATA reinterpret_cast<Rva00715DC0GlobalView *>(TheGlobalData)
// Native STLport vector helper is out of line at ILT00007DD8/body00715D40.
namespace _STL { template<> __declspec(noinline) void vector<RenderObjClass *>::push_back(RenderObjClass *const &x) {
 if (this->_M_finish != this->_M_end_of_storage._M_data) {
  _Construct(this->_M_finish, x); ++this->_M_finish;
 } else _M_insert_overflow(this->_M_finish, x, _IsPODType(), 1UL, true);
} }
template<> void RefMultiListClass<RenderObjClass>::Reset_List();

class RTS3DScene {
public:
 virtual void Visibility_Check(CameraClass *camera);
private:
 char pad0[0x34-4]; char grid[0xbc-0x34];
 MultiListClass<RenderObjClass> pending;
 RefMultiListClass<RenderObjClass> fieldD4;
 RefMultiListClass<RenderObjClass> visible;
 unsigned serial;
 char pad1[0x86c-0x108];
 int m_translucentObjectsCount;
 RenderObjClass **m_translucentObjectsBuffer;
 unsigned field874;
 RenderObjClass **m_potentialOccluders, **m_potentialOccludees, **m_nonOccludersOrOccludees;
 int m_numPotentialOccluders, m_numPotentialOccludees, m_numNonOccluderOrOccludee;
 _STL::vector<RenderObjClass *> field890;
};
static __forceinline void clearPending00715DC0(MultiListClass<RenderObjClass> &pending) {
 while (pending.Peek_Head()!=0) pending.Remove_Head();
}
void RTS3DScene::Visibility_Check(CameraClass *camera)
{
 MultiListIterator<RenderObjClass> it(&pending);
 for (it.First(); !it.Is_Done(); it.Next())
  reinterpret_cast<Gen_00943CF0 *>(grid)->update(it.Peek_Obj());
 clearPending00715DC0(pending);
 ++serial;
 m_numPotentialOccluders=0; m_numPotentialOccludees=0;
 m_translucentObjectsCount=0; m_numNonOccluderOrOccludee=0;
 visible.Reset_List();
 field890.clear();
 _STL::slist<RenderObjClass *> objects;
 register CameraClass *viewCamera=camera;
 reinterpret_cast<Rva00944430 *>(grid)->rva00944430(reinterpret_cast<void **>(&objects), viewCamera, 0);
 RenderObjClass *robj;
 Rva00715DC0DrawableView *draw;
 Rva00715DC0Info *info;
 if (ShaderClass::Is_Backface_Culling_Inverted()) {
  for (_STL::slist<RenderObjClass *>::iterator it=objects.begin(); it!=objects.end(); ++it) {
   robj=*it;
   draw=0;
   info=static_cast<Rva00715DC0Info *>(robj->Get_User_Data());
   if (info) draw=info->m_drawable;
   if (robj->Is_Force_Visible() ||
      ((!draw || (draw->m_status & 1) ||
       ((*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(reinterpret_cast<const Thing *>(draw)->getTemplate())+0xc8)&0x20)!=0)) &&
       !viewCamera->Cull_Sphere(robj->Get_Bounding_Sphere()))) {
    visible.Add(robj); robj->Set_Visible((int)this, serial);
   }
  }
 } else {
  unsigned currentFrame=0;
  if (TheGameLogic) currentFrame=*reinterpret_cast<unsigned *>((char *)TheGameLogic+0x3c);
  if (currentFrame<=DATA->m_defaultOcclusionDelay) currentFrame=DATA->m_defaultOcclusionDelay+1;
  for (_STL::slist<RenderObjClass *>::iterator it=objects.begin(); it!=objects.end(); ++it) {
   robj=*it;
   if (robj->Is_Force_Visible()) {
    visible.Add(robj); robj->Set_Visible((int)this, serial);
   } else if (!robj->Is_Hidden()) {
    SphereClass sphere=robj->Get_Bounding_Sphere();
    sphere.Radius+=robj->_bfme_ro_get_8c();
    if (!viewCamera->Cull_Sphere(sphere)) {
     visible.Add(robj); robj->Set_Visible((int)this, serial);
     info=static_cast<Rva00715DC0Info *>(robj->Get_User_Data());

     if (info && (draw=info->m_drawable)!=0) {
      if (static_cast<unsigned char>(reinterpret_cast<const Gen_00410BA0 *>(draw)->bfmeBusy()) || draw->m_field3b0) {
       visible.Remove(robj); robj->Set_Visible((int)this,0);
      } else {
       info->m_flags=0;
       if ((draw->m_effectiveStealthOpacity*draw->m_explicitOpacity<1.0f || robj->_bfme_ro_get_98()>=0.0f) && m_translucentObjectsCount<DATA->m_maxVisibleTranslucentObjects) {
        info->m_flags=8;
        m_translucentObjectsBuffer[m_translucentObjectsCount++]=robj;
       } else {
        if (robj->Get_Render_Hook()) field890.push_back(robj);
        const Thing *thing=reinterpret_cast<const Thing *>(draw);
        if (thing->isKindOf((KindOfType)7) && m_numPotentialOccluders<DATA->m_maxVisibleOccluderObjects && !thing->isKindOf((KindOfType)110)) {
         m_potentialOccluders[m_numPotentialOccluders++]=robj; info->m_flags|=2;
        } else if (draw->m_object && draw->m_object->getControllingPlayer() &&
         (thing->isKindOf((KindOfType)8)||thing->isKindOf((KindOfType)10)||thing->isKindOf((KindOfType)9)||thing->isKindOf((KindOfType)11)) &&
         !thing->isKindOf((KindOfType)47) && !thing->isKindOf((KindOfType)88) &&
         *reinterpret_cast<unsigned *>((char *)draw->m_object+0x330)<=currentFrame && m_numPotentialOccludees<DATA->m_maxVisibleOccludeeObjects) {
          m_potentialOccludees[m_numPotentialOccludees++]=robj; info->m_flags|=4;
        } else if (!info->m_flags && m_numNonOccluderOrOccludee<DATA->m_maxVisibleNonOccluderOrOccludeeObjects) {
          m_nonOccludersOrOccludees[m_numNonOccluderOrOccludee++]=robj; info->m_flags|=16;
        }
       }
      }
     }
    }
   }
  }
 }
 for (RefMultiListIterator<RenderObjClass> it(&fieldD4); !it.Is_Done(); it.Next()) visible.Add(it.Peek_Obj());
}

/* BANK ONLY: full1391B Visibility_Check draft; not a production byte match.
Identity: RTS3DScene constructor installs VA01120BE0; slot27 reaches ILT00010DF7
then00715DC0, aligned with the ZH Visibility_Check slot. Retail RET4 at0071632C,
INT3 at0071632F. Raw disassembly and Ghidra-created1391B function agree.
The pending multilist contains RenderObjClass*, not spatial-cell receivers:
9434E0 receives scene+34 and each pending object. Native slist node cleanup is8B;
FuncInfo00E3C428 state0 dispatches C4C940 -> ILT2E866 ->712E90 (44B destructor).
Layout: Drawable+FC=m_object (oracle); opacity+B0/B4 witnessed in matched
RTS3DSceneRva00715530.cpp. Unknown shroud byte remains address-qualified.
GlobalData+1B4 and+A44 are oracle witnesses; other limits match the ZH twin's
classification arms and the already matched RTS3DScene constructor. KindOf
ordinals remain numeric; BFME mask at template+C8, not reference+68.
Callees were inventoried before writing. Native noinline vector push_back
independently matches50B at715D40 modulo its overflow relocation; it removes
false spills caused by a bodyless declaration. Its binding remains unverified.
Native clear(), pending helper, and out-of-line final override restore the
complete first212B and the1391B extent. Final draft differs at871 non-relocation
bytes, first+D5; normalized instruction shape.974,16 structural differences,
26 displaced relocation sites. Remaining camera/iterator homes and saved list
receiver reloads affect both branches. No strict binding/EH gate passed.
Failed levers: camera pointer/reference/register forms and const_iterator do
not change code; explicit visible-list pointer only moves its initial spill.
Do not promote this bank on normalized shape or matching size alone.
*/
