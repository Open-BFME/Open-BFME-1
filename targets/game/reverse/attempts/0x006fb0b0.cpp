// ?d_006fb0b0@@YAXXZ
// partial score=0.333333333 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <list>
#define _OPERATOR_NEW_DEFINED_ 1
#include "camera.h"
#include "rinfo.h"
#include "aabox.h"
#include "texture.h"
class BaseHeightMapRenderObjClass { public: bool getMaximumVisibleBox(const FrustumClass &,AABoxClass *,bool); };
class SortingRendererClass { public: static void Flush(); };
struct GenNode_006fa270;
struct GenOwner_006fa270 {
 char padding00[0x98];
 GenNode_006fa270 *m_head,*m_tail;
};
struct GenNode_006fa270 {
 GenOwner_006fa270 *m_owner;
 GenNode_006fa270 *m_prev,*m_next;
 GenNode_006fa270(GenOwner_006fa270 *owner) {
  m_owner=owner;
  if (m_owner) {
   m_prev=m_owner->m_tail;
   m_next=0;
   m_owner->m_tail=this;
   if (m_prev) m_prev->m_next=this;
   else m_owner->m_head=this;
  } else { m_prev=0; m_next=0; }
 }
 ~GenNode_006fa270() {
  if (m_owner) {
   if (m_prev) m_prev->m_next=m_next; else m_owner->m_head=m_next;
   if (m_next) m_next->m_prev=m_prev; else m_owner->m_tail=m_prev;
   m_prev=0; m_next=0;
  }
 }

};
namespace _STL {
 template <> void vector<GenNode_006fa270>::push_back(const GenNode_006fa270 &);
 template <> GenNode_006fa270 *__copy(GenNode_006fa270 *,GenNode_006fa270 *,GenNode_006fa270 *,const random_access_iterator_tag &,int *);
 template <> void __destroy_aux(GenNode_006fa270 *,GenNode_006fa270 *,const __false_type &);
}
struct ListNode006FB0B0 { ListNode006FB0B0 *next,*prev; GenOwner_006fa270 *owner; };
class RenderBackend006FB0B0 {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual int render(RenderInfoClass &,AABoxClass &,int &);
};
struct TextureHandle006FB0B0 {
 TextureBaseClass *p;
 TextureHandle006FB0B0():p(0) {}
 ~TextureHandle006FB0B0() { if(p) p->Release_Ref(); }
};
class ParticlePass006FB0B0 {
public:
 void render(RenderInfoClass &);
 char padding00[0x88];
 int field88; int field8c; int field90;
 char padding94[0x2c];
 _STL::vector<GenNode_006fa270> queues[2];
};
void ParticlePass006FB0B0::render(RenderInfoClass &rinfo)
{
 field90=0;
 const FrustumClass &frustum=rinfo.Camera.Get_Frustum();
 AABoxClass box;
 (*(BaseHeightMapRenderObjClass **)0x012F7FE0)->getMaximumVisibleBox(frustum,&box,true);
 field88=0;
 TextureHandle006FB0B0 texture;
 _STL::list<GenOwner_006fa270 *> &systems=*(_STL::list<GenOwner_006fa270 *> *)(*(char **)0x012F64BC+0x80);
 for (_STL::list<GenOwner_006fa270 *>::iterator it=systems.begin();it!=systems.end();++it) {
  GenNode_006fa270 sys(*it);
  if (!sys.m_owner) continue;
  if (*(int *)((char *)sys.m_owner+0xc)!=6) continue;
  if (*(bool *)0x0133F42D && *(unsigned *)((char *)sys.m_owner+0x24)>0 && *(unsigned *)((char *)sys.m_owner+0x24)<2) {
   unsigned kind=*(unsigned *)((char *)sys.m_owner+0x24);
   queues[kind].push_back(sys);
  } else {
   RenderBackend006FB0B0 *renderer=*(RenderBackend006FB0B0 **)((char *)sys.m_owner+0x1c8);
   if (renderer) field90+=renderer->render(rinfo,box,field88);
  }
 }
 if (*(bool *)0x0133F42D) {
  bool saved=*(bool *)0x012D6D75;
  if (saved) *(bool *)0x012D6D75=false;
  for (int pass=1;pass>=0;--pass) {
   _STL::vector<GenNode_006fa270> &queue=queues[pass];
   for (int i=(int)queue.size()-1;i>=0;--i) {
    GenNode_006fa270 sys(queue[i].m_owner);
    if (!sys.m_owner) continue;
    RenderBackend006FB0B0 *renderer=*(RenderBackend006FB0B0 **)((char *)sys.m_owner+0x1c8);
    if (renderer) field90+=renderer->render(rinfo,box,field88);
   }
   queue.clear();
  }
  if (saved) *(bool *)0x012D6D75=true;
 }
 SortingRendererClass::Flush();
}

