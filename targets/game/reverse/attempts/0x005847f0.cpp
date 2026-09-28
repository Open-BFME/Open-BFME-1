// ?handle@Gen005847F0@@QAEXXZ
// partial score=0.3707317073 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc
// stlport
#include <vector>
class GameLogic {
public:
 void collectObjectIds005847F0(_STL::vector<unsigned int>* ids);
};
class CampaignObject {
public:
 char pad[0x2c];
 bool at2c;
 bool at2d;
 bool active() const { bool flag=at2c; if(at2d) return false; return flag; }
};
extern GameLogic* TheBfmeGameLogic;
extern CampaignObject* TheLivingWorldLogic;
class Gen005847F0 {
public:
 char pad[0x40];
 int at40;
 void handle();
 void processObject00584330(unsigned int id);
};
void Gen005847F0::handle() {
 if (TheBfmeGameLogic) {
  if (TheLivingWorldLogic && TheLivingWorldLogic->active()) {
   _STL::vector<unsigned int> ids;
   TheBfmeGameLogic->collectObjectIds005847F0(&ids);
   for (_STL::vector<unsigned int>::iterator it=ids.begin(); it!=ids.end(); ++it)
    processObject00584330(*it);
  }
  at40=-1;
 }
}
