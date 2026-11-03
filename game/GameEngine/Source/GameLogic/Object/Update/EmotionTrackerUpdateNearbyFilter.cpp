// cl: /O2 /MD /EHsc /DNDEBUG 
//
// The object filter EmotionTrackerUpdate builds around its owner: it caches the
// owner's controlling player and counts enemy and ally shroud-cell occupants at
// the owner's position. The class is named after its retail vtable 0x010BE170,
// the only table its constructor installs; its deleting destructor 0x0028F3B0 and
// destructor 0x0028EE20 are still generated rows.
class Player;
#include <new>
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const;
#include "../object.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class EmotionTrackerUpdate;
class PlayerList {public: unsigned short getPlayersWithRelationship(int,int,bool);};
extern PlayerList *ThePlayerList;
class PartitionManager;extern PartitionManager *TheShroudManager;
class Rva002EEDA0ShroudManager {public:int lookup(const Coord3D *,int,unsigned int);};
struct Rva0028F2A0PlayerView {char m_pad00[0x24];int m_index; __forceinline int getIndex() const { return m_index; } };
struct Rva0028F2A0TrackerView {char m_pad00[8];Object *m_object;};
class Rva0028F2A0Base {
public:
 Rva0028F2A0Base():m_next(0){}
 virtual ~Rva0028F2A0Base();
 virtual bool allow(Object *)=0;
 virtual int playerMask();
 Rva0028F2A0Base *m_next;
};
class Rva010BE170 :public Rva0028F2A0Base {
public:
 Rva010BE170(EmotionTrackerUpdate *);
 virtual bool allow(Object *);
 virtual int playerMask();
 EmotionTrackerUpdate *m_module;
 Object *m_object;Player *m_player;
 int m_enemyCount,m_allyCount;
 Object *m_cached;bool m_tested;
};
Rva010BE170::Rva010BE170(EmotionTrackerUpdate *m):m_module(m),m_cached(0),m_tested(false){
 m_object=reinterpret_cast<Rva0028F2A0TrackerView *>(m)->m_object;
 m_enemyCount=0;m_allyCount=0;
 m_player=m_object?m_object->getControllingPlayer():0;
 if(m_player){
  unsigned int allies=ThePlayerList->getPlayersWithRelationship(reinterpret_cast<Rva0028F2A0PlayerView*>(m_player)->getIndex(),3,false);
  unsigned int enemies=ThePlayerList->getPlayersWithRelationship(reinterpret_cast<Rva0028F2A0PlayerView*>(m_player)->getIndex(),4,false);
  m_enemyCount=reinterpret_cast<Rva002EEDA0ShroudManager*>(TheShroudManager)->lookup(reinterpret_cast<const Coord3D *>(m_object->m_cachedPos),1,enemies);
  m_allyCount=reinterpret_cast<Rva002EEDA0ShroudManager*>(TheShroudManager)->lookup(reinterpret_cast<const Coord3D *>(m_object->m_cachedPos),1,allies);
 }
}
