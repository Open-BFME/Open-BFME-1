// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// DockUpdateInterface slot 9 at vtable VA 0x010CA800 routes through
// ILT 0x0003F9EA to RVA 0x002CC5C0. BFME removes the approach slot
// through its storage helper after setting both objects docking flags.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_NEWALLOC 1
#include <bitset>
#include <vector>

template<int N> class BitFlags {
public:
 enum BogusInitType { kInit };
 BitFlags(BogusInitType, int a) { m_bits.set(a); }
 BitFlags(BogusInitType, int a, int b) { m_bits.set(a); m_bits.set(b); }
 _STL::bitset<N> m_bits;
};
enum ModelConditionFlag {
 MODELCONDITION_DOCKING=80,
 MODELCONDITION_DOCKING_BEGINNING=81,
 MODELCONDITION_DOCKING_ENDING=83
};
class Object {
public:
 void clearAndSetModelConditionFlags(const BitFlags<320>&, const BitFlags<320>&);
 char pad[0x74]; int id;
};
class DockUpdateStorage {
public:
 void removeApproachPosition(int);
};
class DockUpdate {
public:
 virtual void onEnterReached(Object*);
 char pad[0x3c];
 _STL::vector<int> m_approachPositionOwners;
 char pad4c[0x18];
 bool m_dockerInside;
 Object *getObject() const { return *(Object**)((char*)this-0x18); }
};
void DockUpdate::onEnterReached(Object *docker)
{
 getObject()->clearAndSetModelConditionFlags(BitFlags<320>(BitFlags<320>::kInit,MODELCONDITION_DOCKING_ENDING),BitFlags<320>(BitFlags<320>::kInit,MODELCONDITION_DOCKING_BEGINNING,MODELCONDITION_DOCKING));
 docker->clearAndSetModelConditionFlags(BitFlags<320>(BitFlags<320>::kInit,MODELCONDITION_DOCKING_ENDING),BitFlags<320>(BitFlags<320>::kInit,MODELCONDITION_DOCKING_BEGINNING,MODELCONDITION_DOCKING));
 m_dockerInside=true;
 int dockerID=docker->id;
 for(int i=0;i<m_approachPositionOwners.size();++i) {
  if(m_approachPositionOwners[i]==dockerID) {
   ((DockUpdateStorage*)((char*)this-0x20))->removeApproachPosition(i);
   return;
  }
 }
}
