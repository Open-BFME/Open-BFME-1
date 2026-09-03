// cl: /DNDEBUG /MD /EHsc
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

extern void j_00007086(void);

typedef int ObjectID;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	bool hasUpgrade(const UpgradeTemplate *upgrade) const;
	bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
};

typedef void (Object::*MarkUpgradeCompletedCall)(const UpgradeTemplate *);

class BfmeY982
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual bool isComplete();
	virtual void unused4();
	virtual void unused5();
	virtual Object *getObject();

	BfmeY982 *bfmeConv982B();
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	char m_pad000[0xb0];
	ObjectPtrHash m_objects;
};

extern GameLogic *TheGameLogic;

struct Gen0036FAD0Range
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

void __stdcall gen0036FAD0UpgradeWalk(Gen0036FAD0Range *range,
	UpgradeTemplate *upgrade)
{
	ObjectID *current = range->m_begin;
	if (current != range->m_end) {
		for (;;) {
			ObjectID id = *current;
			if (id != 0) {
				ObjectPtrHash::iterator it = TheGameLogic->m_objects.find(id);
				if (it != TheGameLogic->m_objects.end()) {
					Object *object = (*it).second;
					if (object != 0) {
						union { void *asVoid; MarkUpgradeCompletedCall asMember; }
							markUpgradeCompleted;
						markUpgradeCompleted.asVoid = (void *)j_00007086;
						(object->*markUpgradeCompleted.asMember)(upgrade);
						BfmeY982 *completion =
							((BfmeY982 *)object)->bfmeConv982B();
						if (completion != 0 && completion->isComplete()) {
							Object *next = completion->getObject();
							if (next != 0 && !next->hasUpgrade(upgrade) &&
								next->affectedByUpgrade(upgrade))
							{
								union { void *asVoid; MarkUpgradeCompletedCall asMember; }
									markUpgradeCompleted;
								markUpgradeCompleted.asVoid = (void *)j_00007086;
								(next->*markUpgradeCompleted.asMember)(upgrade);
							}
						}
					}
				}
			}
			++current;
			if (current == range->m_end)
				break;
		}
	}
}
