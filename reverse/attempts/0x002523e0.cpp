// ?d_002523e0@@YAXXZ
// partial score=0.73 date=2026-09-18
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Retail 0x002523E0 (403 bytes).  The body is a TransitionDamageFX method
// reached from the landed damage-state dispatcher through the 0x0000AD49
// thunk.  Its anonymous record name is kept address-derived because the
// historical method spelling is not present in the surviving symbols.

#include "ascii_string.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D;
class ObjectCreationList;
class TransitionDamageFX;

class S4Sink004135C0
{
public:
	void invoke(const AsciiString &name, Bool visible, Int a, Int b, Int c);
};

class NameKeyGenerator
{
public:
	Int nameToKey(const char *name);
};

typedef Int NameKeyType;

class Module
{
};

class Thing
{
public:
	void convertBonePosToWorldPos(const Coord3D *bonePos,
		const Matrix3D *boneTransform, Coord3D *worldPos,
		Matrix3D *worldTransform) const;
};

class StatusModule
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual Int getStatus();
};

class Object : public Thing
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual S4Sink004135C0 *getDrawable();

	Module *findModule(NameKeyType key);

	unsigned char m_unmodelled[0x1FC];
	StatusModule *m_statusModule;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

class ObjectCreationList
{
public:
	void createInternal(const Object *primary, const Object *secondary,
		UnsignedInt lifetimeFrames) const;
};

// The record is 0x2c bytes.  The range at +4/+8 is a contiguous array of
// AsciiString objects; +0x10 is the OCL and +0x20 is its local position.
struct Rva002523E0Record
{
	Int m_objectID;
	AsciiString *m_nameBegin;
	AsciiString *m_nameEnd;
	void *m_unmodelled0C;
	ObjectCreationList *m_objectCreationList;
	unsigned char m_unmodelled14[0x0C];
	Coord3D m_localPosition;
};

class TransitionDamageFX
{
public:
	void rva002523E0(Bool applyTransition);

private:
	void *m_vtable;
	void *m_enabled;
	Object *m_object;
	unsigned char m_unmodelled0C[0xC8];
	Rva002523E0Record *m_recordBegin;
	Rva002523E0Record *m_recordEnd;
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheNameKeyGenerator (*(NameKeyGenerator **)0x012ED600)
void TransitionDamageFX::rva002523E0(Bool applyTransition)
{
	if (m_enabled == 0)
		return;

	S4Sink004135C0 *sink = m_object->getDrawable();
	if (sink == 0)
		return;

	for (Rva002523E0Record *record = m_recordBegin;
		record != m_recordEnd; ++record)
	{
		Object *object = TheBfmeGameLogic->findObjectByID(record->m_objectID);
		if (object == 0)
			continue;

		Int status = object->m_statusModule->getStatus();
		for (AsciiString *name = record->m_nameBegin;
			 name != record->m_nameEnd; ++name)
		{
			sink->invoke(*name, status != 3, 0, 0, 0);
		}

		if (!applyTransition)
			continue;

		static NameKeyType transitionDamageKey =
			TheNameKeyGenerator->nameToKey("TransitionDamageFX");

		TransitionDamageFX *transition =
			(TransitionDamageFX *)object->findModule(
				transitionDamageKey);
		if (transition != 0)
			transition->rva002523E0(false);

		if (status != 3 || record->m_objectCreationList == 0)
			continue;

		Coord3D worldPosition;
		m_object->convertBonePosToWorldPos(
			&record->m_localPosition, 0, &worldPosition, 0);
		record->m_objectCreationList->createInternal(
			m_object, m_object, 0);
	}
}
