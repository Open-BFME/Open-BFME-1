// ?rva002523E0@TransitionDamageFX@@QAEX_N@Z
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Include
// Retail 0x002523E0: walks the 0x2c-byte records at +0xD4 and recurses through the owner-side thunk 0x0000AD49.

#include "basetype.h"
#include "ascii_string.h"

class Matrix3D;
class Module;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class S4Sink004135C0
{
public:
	void invoke(const AsciiString &name, Bool visible, Int a, Int b, Int c);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
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

class Thing
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

	void convertBonePosToWorldPos(const Coord3D *bonePos,
		const Matrix3D *boneTransform, Coord3D *worldPos,
		Matrix3D *worldTransform) const;
};

class Object : public Thing
{
public:
	Module *findDamageModule(NameKeyType key) const { return findModule(key); }

protected:
	Module *findModule(NameKeyType key) const;

public:
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

// 0x2c-byte record: +4/+8 bound an AsciiString array, +0x10 is the OCL, +0x20 the local position.
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

	for (Rva002523E0Record *it = m_recordBegin; it != m_recordEnd; )
	{
		Rva002523E0Record *record = it++;

		Int status = 3;
		Object *object = TheBfmeGameLogic->findObjectByID(record->m_objectID);
		if (object != 0)
			status = object->m_statusModule->getStatus();

		for (AsciiString *name = record->m_nameBegin;
			 name != record->m_nameEnd; ++name)
		{
			sink->invoke(*name, status != 3, 0, 0, 0);
		}

		if (applyTransition)
		{
			static NameKeyType transitionDamageKey =
				TheNameKeyGenerator->nameToKey("TransitionDamageFX");

			if (object != 0)
			{
				TransitionDamageFX *transition =
					(TransitionDamageFX *)object->findDamageModule(
						transitionDamageKey);
				if (transition != 0)
					transition->rva002523E0(false);
			}

			if (status == 3 && record->m_objectCreationList != 0)
			{
				Coord3D worldPosition;
				worldPosition.x = record->m_localPosition.x;
				worldPosition.y = record->m_localPosition.y;
				worldPosition.z = record->m_localPosition.z;
				m_object->convertBonePosToWorldPos(
					&worldPosition, 0, &worldPosition, 0);
				ObjectCreationList *ocl = record->m_objectCreationList;
				if (ocl != 0)
					ocl->createInternal(m_object, m_object, 0);
			}
		}
	}
}
