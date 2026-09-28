// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x0036FBE0 (254B). CastleUpgradeImplementation looks up the literal
// CastleBehavior module name before invoking ILT 0x1E35D: owner evidence.
// The primary object guard skips only its own update; ranges always run.
// The two range calls preserve ECX=this in retail even though the landed
// range walker uses the two stack arguments; the member-pointer adapter
// preserves that call-site ABI without asserting a new callee identity.
// Reached through the member-function-pointer
// cast in Code/GameEngine/Source/GameLogic/Object/Behavior/
// CastleUpgradeImplementation.cpp's CastleUpgrade::upgradeImplementation
// (its j_0001e35d thunk targets this RVA). this+0xa0 names an owning
// object's ObjectID; this+0xb8 and this+0xdc are Gen0036FAD0Range pairs fed
// to the already-matched Code/GameEngine/Source/Common/
// Gen0036FAD0UpgradeWalk.cpp helper; this+0xc4/+0xc8 is a third ObjectID
// range the body walks itself, inlining the SAME TheGameLogic->m_objects
// hash_map lookup that helper performs, with hasUpgrade/affectedByUpgrade
// tested before bfmeMarkUpgradeCompleted.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int ObjectID;

class UpgradeTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	bool hasUpgrade(const UpgradeTemplate *upgrade) const;
	bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	void bfmeMarkUpgradeCompleted(const UpgradeTemplate *upgrade);
};

// Matches Code/GameEngine/Source/Common/Gen0036FAD0UpgradeWalk.cpp's own
// struct exactly, so the call below resolves to that matched body.
struct Gen0036FAD0Range
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

extern void j_00032f97();

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

	char m_pad000[0xb0];
	ObjectPtrHash m_objects;
};

extern GameLogic *TheGameLogic;

class CastleBehavior
{
public:
	void rva0036fbe0(const UpgradeTemplate *upgrade);

private:
	void *m_vtable;
	void *m_moduleData;
	unsigned char m_pad08[0xa0 - 0x08];
	ObjectID m_selfObjectID;			// +0xa0
	unsigned char m_pad_a4[0xb8 - 0xa4];
	Gen0036FAD0Range m_rangeB8;			// +0xb8
	unsigned char m_pad_c0[0xc4 - 0xc0];
	ObjectID *m_idListBegin;			// +0xc4
	ObjectID *m_idListEnd;				// +0xc8
	unsigned char m_pad_cc[0xdc - 0xcc];
	Gen0036FAD0Range m_rangeDC;			// +0xdc
};

// ?rva0036fbe0@CastleBehavior@@QAEXPBVUpgradeTemplate@@@Z
void CastleBehavior::rva0036fbe0(const UpgradeTemplate *upgrade)
{
	Object *object = TheGameLogic->findObjectByID(m_selfObjectID);
    if (object && !object->hasUpgrade(upgrade))
        object->bfmeMarkUpgradeCompleted(upgrade);

    typedef void (CastleBehavior::*Walk)(Gen0036FAD0Range *, const UpgradeTemplate *);
    union { void *address; Walk method; } walk;
    walk.address = (void *)j_00032f97;
    (this->*walk.method)(&m_rangeB8, upgrade);
    (this->*walk.method)(&m_rangeDC, upgrade);

	ObjectID *it = m_idListBegin;
	if (it == m_idListEnd)
		return;

	do
	{
		ObjectID id = *it;
		if (id != 0)
		{
			ObjectPtrHash::iterator found = TheGameLogic->m_objects.find(id);
			if (found != TheGameLogic->m_objects.end())
			{
				Object *object2 = (*found).second;
				if (object2 != 0)
				{
					if (!object2->hasUpgrade(upgrade))
					{
						if (object2->affectedByUpgrade(upgrade))
							object2->bfmeMarkUpgradeCompleted(upgrade);
					}
				}
			}
		}
		++it;
	} while (it != m_idListEnd);
}
