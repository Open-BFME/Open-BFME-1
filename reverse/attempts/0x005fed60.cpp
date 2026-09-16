// ?method@Rva005FED60Owner@@QAEXXZ
// partial score=0.42 date=2026-09-16
// Scratch-only complete reconstruction for retail 0x005FED60 (758 bytes).
// The owner and field names remain address-derived until identity evidence exists.
// Primary slot 1 via ILT 0xB6E0 in 0x01112884 (factory 0x005E82A0)
// and 0x01112CA4 (constructor 0x005FED10). Full boundary ends 0x005FF056.
// Root review restored all nine fresh handle/null resolutions and kept the
// final phase block inside the distance guard. Its sine term really writes
// X again. The getPosition ABI uses the reference struct Coord3D, not the
// different nontrivial class Coord3D header. 712/758 bytes, 441 differences;
// the null-first resolver form was neutral. No codegen barriers or asm.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

#include "Lib/BaseType.h"
#include <math.h>

class BfmeHandleERU;

class BfmeHandleERUOwner
{
public:
	char m_pad[0x98];
	BfmeHandleERU *m_head;
	BfmeHandleERU *m_tail;
};

class BfmeHandleERU
{
public:
	BfmeHandleERU(const BfmeHandleERU &that)
	{
		BfmeHandleERUOwner *owner = that.m_bfmePtrERU;
		m_bfmePtrERU = owner;
		if (m_bfmePtrERU != 0)
		{
			m_previous = m_bfmePtrERU->m_tail;
			m_next = 0;
			m_bfmePtrERU->m_tail = this;
			if (m_previous != 0)
				m_previous->m_next = this;
			else
				m_bfmePtrERU->m_head = this;
		}
		else
		{
			m_next = 0;
			m_previous = 0;
		}
	}

	~BfmeHandleERU() throw();

	BfmeHandleERUOwner *m_bfmePtrERU;
	BfmeHandleERU *m_previous;
	BfmeHandleERU *m_next;
};

class ParticleSystemZA;
ParticleSystemZA *bfmeNullSystemZA(void);

struct ParticleSystem
{
public:
	void getPosition(Coord3D *pos);
};

class Rva005C3530
{
public:
	int get(void);
};

class Rva005C3510Owner
{
public:
	float field30(void) const;
	float field24(void) const;
	float field2C(void) const;
};

class Rva005C30A0Owner
{
public:
	float Rva005C30A0(void) const;
};

class GameLogic;
class Object
{
public:
	char m_pad[0x38];
	Coord3D m_position;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class BFMERopeDrawableGetPositionShim
{
public:
	const Coord3D *get(void) const;
};

class Rva005FED60DrawableStore
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual BFMERopeDrawableGetPositionShim *getDrawable(int id);
};

struct Rva005FED60SystemData
{
	char m_pad[0x5c];
	float m_field5c;
	float m_field60;
};

class Rva005FED60SystemFields
{
public:
	char m_pad00[0xb4];
	int m_attachedDrawableID;
	int m_attachedObjectID;
	char m_padbc[0x1cc - 0xbc];
	Rva005FED60SystemData *m_data1cc;
};

__forceinline BfmeHandleERUOwner *Rva005FED60Resolve(
	BfmeHandleERU &handle)
{
	return !handle.m_bfmePtrERU
		? (BfmeHandleERUOwner *)bfmeNullSystemZA()
		: handle.m_bfmePtrERU;
}

class Rva005FED60Particle
{
public:
	char m_pad00[0x1c];
	Coord3D m_position;
	char m_pad28[0x24];
	BfmeHandleERU m_handle;
	unsigned int m_field58;
	char m_pad5c[0x94 - 0x5c];
	void *m_source94;
};

class Rva005FED60Owner
{
public:
	void method(void);

	char m_pad00[4];
	Rva005FED60Particle *m_particle;
	char m_pad08[8];
	float m_strength;
};

void Rva005FED60Owner::method(void)
{
	BfmeHandleERU handle(m_particle->m_handle);

	if (((Rva005C3530 *)Rva005FED60Resolve(handle))->get() == 1)
		return;

	float windAngle =
		((Rva005C3510Owner *)Rva005FED60Resolve(handle))->field30();
	Coord3D systemPosition;
	((ParticleSystem *)Rva005FED60Resolve(handle))->getPosition(&systemPosition);

	int objectID = ((Rva005FED60SystemFields *)Rva005FED60Resolve(handle))
		->m_attachedObjectID;
	if (objectID != 0)
	{
		GameLogic *logic = *(GameLogic **)0x012F0898;
		Object *object = logic->findObjectByID(objectID);
		if (object != 0)
		{
			systemPosition.x += object->m_position.x;
			systemPosition.y += object->m_position.y;
			systemPosition.z += object->m_position.z;
		}
	}
	else
	{
		int drawableID =
			((Rva005FED60SystemFields *)Rva005FED60Resolve(handle))
				->m_attachedDrawableID;
		if (drawableID != 0)
		{
			Rva005FED60DrawableStore *store =
				*(Rva005FED60DrawableStore **)0x012F1464;
			BFMERopeDrawableGetPositionShim *drawable =
				store->getDrawable(drawableID);
			if (drawable != 0)
			{
				const Coord3D *position = drawable->get();
				systemPosition.x += position->x;
				systemPosition.y += position->y;
				systemPosition.z += position->z;
			}
		}
	}

	float dx = m_particle->m_position.x - systemPosition.x;
	float dy = m_particle->m_position.y - systemPosition.y;
	float dz = m_particle->m_position.z - systemPosition.z;
	float distanceSquared = dx * dx + dy * dy + dz * dz;

	float noForceDistance =
		((Rva005C3510Owner *)Rva005FED60Resolve(handle))->field2C();
	if (distanceSquared < noForceDistance * noForceDistance)
	{
		float strength =
			((Rva005C3510Owner *)Rva005FED60Resolve(handle))->field24() *
			m_strength;
		float fullForceDistance =
			((Rva005C3510Owner *)Rva005FED60Resolve(handle))->field2C();
		if (distanceSquared > fullForceDistance * fullForceDistance)
		{
			strength *= 1.0f -
				((sqrtf(distanceSquared) - fullForceDistance) /
				 (noForceDistance - fullForceDistance));
		}

		m_particle->m_position.x += cosf(windAngle) * strength;
		m_particle->m_position.y += sinf(windAngle) * strength;

		Rva005FED60SystemData *data =
			((Rva005FED60SystemFields *)Rva005FED60Resolve(handle))->m_data1cc;
		if (data != 0 && data->m_field5c > 0.0f)
		{
			float phase = m_particle->m_position.z * data->m_field60 +
				(float)m_particle->m_field58;
			float magnitude =
				((Rva005C30A0Owner *)m_particle)->Rva005C30A0() *
				data->m_field5c;
			m_particle->m_position.x += cosf(phase) * magnitude;
			m_particle->m_position.x += sinf(phase) * magnitude;
		}
	}
}
