// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_NEWALLOC 1
#include <vector>
// Called by the byte-matched cancelDock and onEnterReached implementations.
// Retail [0x002CBD60, 0x002CBE86) ends with ret 4 then INT3 padding;
// Ghidra's old 285-byte extent truncates the final bit-vector assignment.
class DockUpdateStorage {
public:
 void removeApproachPosition(int index);
 char pad[0x60];
 _STL::vector<int> m_approachPositionOwners;
 _STL::vector<bool> m_approachPositionReached;
};
void DockUpdateStorage::removeApproachPosition(int index)
{
 int last=m_approachPositionOwners.size()-1;
 for(int i=index;i<last;++i) {
  if(m_approachPositionOwners[i]==0) break;
  m_approachPositionOwners[i]=m_approachPositionOwners[i+1];
  m_approachPositionReached[i]=m_approachPositionReached[i+1];
 }
 m_approachPositionOwners[last]=0;
 m_approachPositionReached[last]=false;
}
