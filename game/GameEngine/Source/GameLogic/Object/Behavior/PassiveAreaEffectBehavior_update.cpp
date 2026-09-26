// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)

typedef bool Bool;
typedef int ObjectID;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Object;

class StructureCompletionInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Bool slot10();
};

class Object
{
public:
	// Existing Object getter pin at retail ILT RVA 0x000351D9.
	StructureCompletionInterface *getStructureCompletionInterface();
};

class PassiveAreaEffectBehaviorModuleData
{
public:
	unsigned char m_pad000[0x10];
	UnsignedInt m_updateDelay; // retail module-data +0x10
};

class GameLogic
{
public:
	// Existing GameLogic lookup pin at retail ILT RVA 0x0001F253.
	Object *findObjectByID(ObjectID id);

	unsigned char m_pad000[0x3c];
	UnsignedInt m_frame; // retail GameLogic +0x3c
};

extern GameLogic *TheGameLogic; // retail DIR32 global 0x012F0898

// Primary-table calls are deliberately raw typed virtual dispatches.  The
// table at 0x010A5304 is constructor-proven; these neutral slots preserve its
// retail +0x2c/+0x30 call roles without importing the unrelated BfmeConv975
// candidate name for the +0x30 target.
class PassiveAreaEffectBehaviorPrimary
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12(Object *object);
	virtual void slot13(Object *object);
	virtual void slot14(Object *object);
};

// The UpdateModuleInterface subobject starts at complete-object +0x10.
// Consequently this method receives the secondary this pointer: module data
// is at this-0x0c, Object at this-0x08, last-update state at this+0x10, and
// the affected-object list sentinel at this+0x14.  Constructor 0x00202100
// installs the exact two-slot table 0x010A5234 there; slot 0's ILT
// j_0000e50c jumps directly to this body at 0x002023C0.
class PassiveAreaEffectBehavior
{
public:
	virtual UpdateSleepTime update();
	virtual void updateInterfaceSlot1(); // second constructor-proven slot; unused here
};

// ?update@PassiveAreaEffectBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime PassiveAreaEffectBehavior::update()
{
	char *secondaryThis = reinterpret_cast<char *>(this);
	PassiveAreaEffectBehaviorModuleData *moduleData =
		*reinterpret_cast<PassiveAreaEffectBehaviorModuleData **>(secondaryThis - 0x0c);
	Object *object = *reinterpret_cast<Object **>(secondaryThis - 0x08);

	StructureCompletionInterface *completion = object->getStructureCompletionInterface();
	if (completion != 0)
	{
		if (completion->slot10())
		{
			_WriteBarrier();
			return UPDATE_SLEEP_NONE;
		}
	}
	else if ((*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(object) + 0x90) & 4) != 0)
		return UPDATE_SLEEP_NONE;
	if ((*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(object) + 0x344) & 1) != 0)
		return UPDATE_SLEEP_FOREVER;

	UnsignedInt now = TheGameLogic->m_frame;
	UnsignedInt lastUpdate = *reinterpret_cast<UnsignedInt *>(secondaryThis + 0x10);
	if (now - lastUpdate >= moduleData->m_updateDelay)
	{
		reinterpret_cast<PassiveAreaEffectBehaviorPrimary *>(secondaryThis - 0x10)->slot11();
		*reinterpret_cast<UnsignedInt *>(secondaryThis + 0x10) = now;
	}

	_STL::list<ObjectID> *affectedObjects =
		reinterpret_cast<_STL::list<ObjectID> *>(secondaryThis + 0x14);
	for (_STL::list<ObjectID>::iterator it = affectedObjects->begin();
		it != affectedObjects->end(); ++it)
	{
		Object *affected = TheGameLogic->findObjectByID(*it);
		if (affected != 0)
			reinterpret_cast<PassiveAreaEffectBehaviorPrimary *>(secondaryThis - 0x10)->slot12(affected);
	}

	return static_cast<UpdateSleepTime>(true);
}
