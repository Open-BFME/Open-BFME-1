// ?doSkirmishCommandButtonOnMostValuable@ScriptActions@@IAEXABVAsciiString@@0M_N@Z
// partial score=0.982 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
// Clean C++ recovery of ScriptActions::doSkirmishCommandButtonOnMostValuable.
// Retail boundary: 0x002FF770, 795 bytes.  The executeAction
// SKIRMISH_PERFORM_COMMANDBUTTON_ON_MOST_VALUABLE_OBJECT arm names this
// four-argument body.  BFME keeps the reference action's group/filter flow,
// with the BFME ScriptEngine by-value string ABI and the retail filter views.

#include "StringInline.h"
#include <vector>
#include "../../../game/GameEngine/Source/GameLogic/command_source_type.h"
enum GUICommandType {};

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Player;
class CommandButton;
class SpecialPowerTemplate;

class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual class Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

class Player
{
};

class Team
{
public:
	void getTeamAsAIGroup(class AIGroup *group);
	Player *getControllingPlayer() const;
};

class AIGroup
{
public:
	Object *getSpecialPowerSourceObject(unsigned id);
	Object *getCommandButtonSourceObject(GUICommandType commandType);
	bool getCenter(Coord3D *center);
	void groupDoCommandButtonAtObject(const CommandButton *button,
		Object *object, CommandSourceType source);
 void groupDoCommandButtonAtPosition(const CommandButton*,const Coord3D*,CommandSourceType);
};

class AI
{
public:
	AIGroup *createGroup();
};

class SpecialPowerTemplate
{
public:
	unsigned getID() const;
};

class CommandButton
{
public:
	SpecialPowerTemplate *getSpecialPowerTemplate() const
	{
		return *(SpecialPowerTemplate **)((char *)this + 0x34);
	}
	GUICommandType getCommandType() const
	{
		return *(const GUICommandType *)((const char *)this + 0x10);
	}
	bool needsPosition() const { return (getOptions() >> 5) & 1; }
 unsigned getOptions() const
	{
		return *(const unsigned *)((const char *)this + 0x18);
	}
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *object) = 0;
 virtual Int getPlayerMask();
	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class PartitionFilterPlayerAffiliation : public PartitionFilter
{
public:
	PartitionFilterPlayerAffiliation(const Player *player,
		unsigned int affiliation, Bool match)
		: m_player(player), m_match(match), m_affiliation(affiliation) {}

protected:
	virtual Bool allow(Object *object);
 virtual Int getPlayerMask();

private:
	const Player *m_player;
	Bool m_match;
	unsigned int m_affiliation;
};

class PartitionFilterValidCommandButtonTarget : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterValidCommandButtonTarget(Object *source,
		const CommandButton *button, Bool match, CommandSourceType sourceType)
		: m_source(source), m_button(button), m_match(match),
		  m_sourceType(sourceType) {}

protected:
	virtual Bool allow(Object *object);

private:
	Object *m_source;
	const CommandButton *m_button;
	Bool m_match;
	CommandSourceType m_sourceType;
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *object) : m_object(object) {}

protected:
	virtual Bool allow(Object *object);

private:
	const Object *m_object;
};

class Overridable { public: const Overridable *getFinalOverride() const; void *vtable; Overridable *m_nextOverride; };
class ThingTemplate : public Overridable { char pad08[0x47a-8]; unsigned short m_buildCost; public: unsigned short getBuildCost() const {return m_buildCost;} };
class Object { void *vtable; ThingTemplate *m_template; char pad08[0x30]; Coord3D m_position; public:
 const ThingTemplate *getTemplate() const { if(!m_template) return 0; if(m_template->m_nextOverride) return (const ThingTemplate*)m_template->m_nextOverride->getFinalOverride(); return m_template; }
 const Coord3D *getPosition() const {return &m_position;}
};
inline bool moreExpensive(const Object *a,const Object *b) { const ThingTemplate *at=a->getTemplate(); const ThingTemplate *bt=b->getTemplate(); return at->getBuildCost()>bt->getBuildCost(); }
struct BfmeIterEntry { Object *m_obj; void *m_extra; };
struct BfmeObjectIterator { std::vector<BfmeIterEntry> m_entries; BfmeIterEntry *m_cur; int m_refCount; };
class BfmeThingCAD { public: void bfmeGoCAD(); };
class BfmeThingEOF { public: void *bfmeGoEOF(); };
struct BfmeWideResult {
 BfmeObjectIterator *m_value;
 BfmeWideResult(); BfmeWideResult(const BfmeWideResult &);
 ~BfmeWideResult() { ((BfmeThingCAD*)this)->bfmeGoCAD(); }
 Object *first() { return (Object*)((BfmeThingEOF*)this)->bfmeGoEOF(); }
 Object *next() { if(m_value->m_cur==m_value->m_entries.end()) return 0; return (m_value->m_cur++)->m_obj; }
};
enum IterOrderType {};
class PartitionManager { public: BfmeWideResult iterate(const Coord3D*,float,IterOrderType,PartitionFilter*,bool); };

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;
extern ControlBar *TheControlBar;
extern PartitionManager *ThePartitionManager;

enum
{
	ALLOW_ENEMIES = 4,

	FROM_CENTER_2D = 0,
	ITER_SORTED_EXPENSIVE_TO_CHEAP = 3
};

class ScriptActions
{
protected:
	void doSkirmishCommandButtonOnMostValuable(const AsciiString &teamName,
		const AsciiString &ability, Real range, Bool allTeamMembers);
};

// ?doSkirmishCommandButtonOnMostValuable@ScriptActions@@IAEXABVAsciiString@@0M_N@Z
void ScriptActions::doSkirmishCommandButtonOnMostValuable(
	const AsciiString &teamName, const AsciiString &ability, Real range,
	Bool allTeamMembers)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	Player *player = team->getControllingPlayer();
	if (!player)
		return;

	const CommandButton *commandButton =
		TheControlBar->findCommandButton(ability);
	if (!commandButton)
		return;

	Object *srcObj = 0;
	if (commandButton->getSpecialPowerTemplate())
	{
		srcObj = theGroup->getSpecialPowerSourceObject(
			commandButton->getSpecialPowerTemplate()->getID());
	}
	else
	{
		srcObj = theGroup->getCommandButtonSourceObject(
			commandButton->getCommandType());
	}

	if (!srcObj)
		return;

	Coord3D pos;
	theGroup->getCenter(&pos);

 
 if (commandButton->needsPosition()) {
  BfmeWideResult result=ThePartitionManager->iterate(&pos,range,(IterOrderType)0,
   PartitionFilterPlayerAffiliation(team->getControllingPlayer(),ALLOW_ENEMIES,true).link(&PartitionFilterSameMapStatus(srcObj)),false);
  Object *target=result.first();
  
  while((srcObj=result.next())!=0) {
   const ThingTemplate *otherTemplate=srcObj->getTemplate();
   const ThingTemplate *targetTemplate=target->getTemplate();
   if(otherTemplate->getBuildCost()>targetTemplate->getBuildCost()) target=srcObj;
  }
  if(target) theGroup->groupDoCommandButtonAtPosition(commandButton,target->getPosition(),CMD_FROM_SCRIPT);
 } else {
  BfmeWideResult result=ThePartitionManager->iterate(&pos,range,(IterOrderType)0,
   PartitionFilterPlayerAffiliation(team->getControllingPlayer(),ALLOW_ENEMIES,true).link(
    PartitionFilterValidCommandButtonTarget(srcObj,commandButton,true,CMD_FROM_SCRIPT).link(&PartitionFilterSameMapStatus(srcObj))),false);
  Object *target=result.first();
  
  while((srcObj=result.next())!=0) {
   const ThingTemplate *otherTemplate=srcObj->getTemplate();
   const ThingTemplate *targetTemplate=target->getTemplate();
   if(otherTemplate->getBuildCost()>targetTemplate->getBuildCost()) target=srcObj;
  }
  if(target) theGroup->groupDoCommandButtonAtObject(commandButton,target,CMD_FROM_SCRIPT);
 }
}


