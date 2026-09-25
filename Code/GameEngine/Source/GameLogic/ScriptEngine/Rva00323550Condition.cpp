// cl: /DNDEBUG /DWIN32 /MD /EHsc
// RVA 00323550, called by dispatcher case92 through ILT 0003CF74.
// The first Parameter resolves a player mask; the second fills an ObjectTypes
// list. Each selected Player is passed to the witnessed 001DB720 predicate
// scan. Its semantic condition name remains unknown, so keep the address.
// ObjectTypesTemp's visible native constructor and virtual-delete lifetime
// match the neighbouring ScriptConditionsCastleObjectTypes implementation.
class Parameter;
class Player;
class ObjectTypes {
public:
 ObjectTypes();
 virtual ~ObjectTypes();
 void *words[4];
};
class ObjectTypesTemp {
public:
 ObjectTypes *m_types;
 ObjectTypesTemp():m_types(0) { m_types=new ObjectTypes; }
 ~ObjectTypesTemp() { if(m_types) delete m_types; }
};
class Rva001DB720Predicate;
class Rva001DB720NameList { public: bool anyTemplateAcceptedBy(Rva001DB720Predicate*); };
class ScriptEngine { public: unsigned short unidentified_0034DB40(Parameter*); };
class PlayerList { public: Player *getEachPlayerFromMask(unsigned short &); };
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
class ScriptConditions { friend class Rva00323550Condition; protected: static void objectTypesFromParam(Parameter*,ObjectTypes*); };
class Rva00323550Condition { public: bool evaluate(Parameter*,Parameter*); };
bool Rva00323550Condition::evaluate(Parameter *players,Parameter *type)
{
 ObjectTypesTemp types;
 ScriptConditions::objectTypesFromParam(type,types.m_types);
 unsigned short mask=TheScriptEngine->unidentified_0034DB40(players);
 while(mask) {
  Player *player=ThePlayerList->getEachPlayerFromMask(mask);
  if(player && ((Rva001DB720NameList*)types.m_types)->anyTemplateAcceptedBy((Rva001DB720Predicate*)player)) return true;
 }
 return false;
}
