// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// RVA 00329400, dispatcher case104 via ILT00023F29. This is the BFME
// multi-player variant of the upstream object-loss count comparison.
// The two vectors precede ObjectTypesTemp so every exit destroys in retail
// order. The per-player total is reset on each mask iteration.
// getPlayerIndex stays an inline accessor: spelling direct field loads changes
// the two retail call-argument registers under VC7.1.
#include <vector>
#include "ascii_string.h"
class Parameter { public: char unknown00[16]; AsciiString text; };
class ThingTemplate;
class ObjectTypes { public: ObjectTypes(); virtual ~ObjectTypes(); int prepForPlayerCounting(_STL::vector<const ThingTemplate*>&,_STL::vector<int>&); void*words[4]; };
class ObjectTypesTemp { public: ObjectTypes*m_types; ObjectTypesTemp():m_types(0){m_types=new ObjectTypes;} ~ObjectTypesTemp(){if(m_types)delete m_types;} };
class Player { public: char unknown00[0x24]; int m_playerIndex; int getPlayerIndex() const { return m_playerIndex; } void countObjectsByThingTemplate(int,const ThingTemplate*const*,bool,int*,bool)const; };
class PlayerList { public: Player*getEachPlayerFromMask(unsigned short&); };
class ScriptEngine { public: unsigned short unidentified_0034DB40(Parameter*); int getObjectCount(int,const AsciiString&)const; void setObjectCount(int,const AsciiString&,int); };
extern PlayerList *ThePlayerList;
extern ScriptEngine *TheScriptEngine;
class ScriptConditions { friend class Rva00329400Condition; protected: static void objectTypesFromParam(Parameter*,ObjectTypes*); };
class Rva00329400Condition { public: bool evaluate(Parameter*,Parameter*); };
bool Rva00329400Condition::evaluate(Parameter*players,Parameter*type)
{
 _STL::vector<int> counts;
 _STL::vector<const ThingTemplate*> templates;
 ObjectTypesTemp types;
 ScriptConditions::objectTypesFromParam(type,types.m_types);
 int n=types.m_types->prepForPlayerCounting(templates,counts);
 if(n==0)return false;
 unsigned short mask=TheScriptEngine->unidentified_0034DB40(players);
 while(mask) {
  Player*player=ThePlayerList->getEachPlayerFromMask(mask);
  if(player) {
   player->countObjectsByThingTemplate(n,&templates[0],true,&counts[0],true);
   int total=0;
   for(_STL::vector<int>::const_iterator i=counts.begin();i!=counts.end();++i)total+=*i;
   int previous=TheScriptEngine->getObjectCount(player->getPlayerIndex(),type->text);
   if(total!=previous){TheScriptEngine->setObjectCount(player->getPlayerIndex(),type->text,total);if(total<previous)return true;}
  }
 }
 return false;
}
