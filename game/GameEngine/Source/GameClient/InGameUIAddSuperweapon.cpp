// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BFME 1.03 RVA 0x0044C970 +338. Identity: SpecialPowerModule callers and
// GeneralsMD InGameUI::addSuperweapon; BFME omits evaReadyPlayed.
// The independent landed SuperweaponInfoCtor.cpp proves the ten-word ctor
// and 0x24-byte object. Retail proves map +0x5cc (12-byte stride), font
// +0x758/+0x75c/+0x760, Player color +0x1c4 and required science +0x1c.
// Kept in this BFME-layout TU because InGameUI.cpp includes the incompatible
// ZH SuperweaponInfo declaration (11-word ctor and 0x28-byte object).
// The list node specialization preserves STLport insertion semantics while
// making the scalar pointer construction visible at this call site.
#include "ascii_string.h"
#include <map>
#include <list>
#include <new>
enum ObjectID {};
enum ScienceType { SCIENCE_INVALID = -1 };
class Overridable {
public:
 void *vtable;
 Overridable *m_nextOverride;
 Overridable *friend_getFinalOverride() {
  if (m_nextOverride) return m_nextOverride->friend_getFinalOverride();
  return this;
 }
 const Overridable *friend_getFinalOverride() const {
  if (m_nextOverride) return m_nextOverride->friend_getFinalOverride();
  return this;
 }

};
class SpecialPowerTemplate : public Overridable {
 char pad08[0x14];
 ScienceType m_requiredScience;
public:
 const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate*)friend_getFinalOverride(); }
 ScienceType getRequiredScience() const { return getFO()->m_requiredScience; }
};
class Player {
 char pad000[0x1c4];
 int m_playerColor;
public:
 bool hasScience(ScienceType) const;
 int getPlayerColor() const { return m_playerColor; }
};
class PlayerList { public: Player *getNthPlayer(int); };
extern PlayerList *ThePlayerList;
class SuperweaponInfo {
 virtual ~SuperweaponInfo();
 void *m_nameDisplayString;
 void *m_timeDisplayString;
 int m_color;
 const SpecialPowerTemplate *m_powerTemplate;
 AsciiString m_powerName;
 ObjectID m_id;
 unsigned m_timestamp;
 bool m_hiddenByScript, m_hiddenByScience, m_ready, m_forceUpdateText;
public:
 SuperweaponInfo(ObjectID,unsigned,bool,bool,bool,const AsciiString&,int,bool,int,const SpecialPowerTemplate*);
};
typedef std::list<SuperweaponInfo*> SuperweaponList;
typedef std::map<AsciiString, SuperweaponList> SuperweaponMap;
namespace _STL {
template<> __forceinline SuperweaponList::_Node* SuperweaponList::_M_create_node(SuperweaponInfo* const &v) {
 _Node *p=this->_M_node.allocate(1);
 new ((void*)&p->_M_data) SuperweaponInfo*(v);
 return p;
}
template<> SuperweaponList& SuperweaponMap::operator[](const AsciiString&);
}
class InGameUI {
 char pad000[0x5c8];
 SuperweaponMap m_superweapons[16];
 char pad68c[0xcc];
 AsciiString m_superweaponNormalFont;
 int m_superweaponNormalPointSize;
 bool m_superweaponNormalBold;
protected:
 SuperweaponInfo *findSWInfo(int,const AsciiString&,ObjectID,const SpecialPowerTemplate*);
public:
 virtual void addSuperweapon(int,const AsciiString&,ObjectID,const SpecialPowerTemplate*);
};
void InGameUI::addSuperweapon(int playerIndex,const AsciiString& powerName,ObjectID id,const SpecialPowerTemplate* powerTemplate) {
 if (!powerTemplate) return;
 SuperweaponInfo *swInfo=findSWInfo(playerIndex,powerName,id,powerTemplate);
 if(swInfo) return;
 const Player *player=ThePlayerList->getNthPlayer(playerIndex);
 bool hiddenByScience=(powerTemplate->getRequiredScience()!=SCIENCE_INVALID) && !player->hasScience(powerTemplate->getRequiredScience());
 SuperweaponInfo *info=new SuperweaponInfo(id,-1,false,hiddenByScience,false,m_superweaponNormalFont,m_superweaponNormalPointSize,m_superweaponNormalBold,player->getPlayerColor(),powerTemplate);
 m_superweapons[playerIndex][powerName].push_back(info);
}
