// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
//
// The reference ScriptEngine implementation names this body
// doObjectTypeListMaintenance. It gets or creates an ObjectTypes list, adds or
// removes one object type, and removes the list when it becomes empty.

// The reference declaration and implementation are in
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/
// ScriptEngine.h and Source/GameLogic/ScriptEngine/ScriptEngine.cpp. The
// ScriptActions caller forwards the same three arguments from
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp.

// BFME places m_allObjectTypeLists at this+0x17628. The 20 virtual slots before
// getObjectTypes place that lookup at vtable+0x50, which matches retail.
// ObjectTypes is 20 bytes, with its pointer vector at offsets +0x08, +0x0c,
// and +0x10. The explicit ILT call preserves the retail removeObjectType
// thunk, while the matched ObjectTypes constructor and add method resolve to
// their retail ILTs through the normal symbol map.

// stlport
#include "StringInline.h"
#include <vector>

typedef bool Bool;

class ObjectTypes
{
public:
	ObjectTypes(const AsciiString &listName);
	virtual ~ObjectTypes();
	void addObjectType(const AsciiString &objectType);

	unsigned int getListSize() const
	{
		ObjectTypes **begin = *(ObjectTypes ** const *)((const char *)this + 8);
		ObjectTypes **end = *(ObjectTypes ** const *)((const char *)this + 12);
		return (unsigned int)(end - begin);
	}

private:
	void *m_data[4];
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual ObjectTypes *getObjectTypes(const AsciiString &objectTypeList) = 0;
	virtual void doObjectTypeListMaintenance(const AsciiString &objectTypeList,
		const AsciiString &objectType, Bool addObject);

	unsigned char m_padding[0x17624];
	std::vector<ObjectTypes *> m_allObjectTypeLists;
};

extern void j_000014c4();

static __forceinline void bfmeRemoveObjectType(ObjectTypes *types,
	const AsciiString &objectType)
{
	typedef void (ObjectTypes::*Function)(const AsciiString &);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000014c4;
	(types->*fn.member)(objectType);
}

extern void j_000143ad();

static __forceinline void bfmeRemoveObjectTypes(ScriptEngine *engine,
	ObjectTypes *types)
{
	typedef void (ScriptEngine::*Function)(ObjectTypes *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000143ad;
	(engine->*fn.member)(types);
}

// ?doObjectTypeListMaintenance@ScriptEngine@@UAEXABVAsciiString@@0_N@Z
void ScriptEngine::doObjectTypeListMaintenance(
	const AsciiString &objectTypeList, const AsciiString &objectType,
	Bool addObject)
{
	ObjectTypes *currentObjectTypeVec = getObjectTypes(objectTypeList);

	if (!currentObjectTypeVec) {
		ObjectTypes *newVec = new ObjectTypes(objectTypeList);
		m_allObjectTypeLists.push_back(newVec);
		currentObjectTypeVec = newVec;
	}

	if (addObject) {
		currentObjectTypeVec->addObjectType(objectType);
	} else {
		bfmeRemoveObjectType(currentObjectTypeVec, objectType);
	}

	if (currentObjectTypeVec->getListSize() == 0) {
		bfmeRemoveObjectTypes(this, currentObjectTypeVec);
		currentObjectTypeVec = 0;
	}
}
