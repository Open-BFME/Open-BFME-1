// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS::resolveOwnerPosition, retail 0x000B4020, 367B.
// thiscall, two stack args, `ret 8`. Proves the layout of the owner fields:
//   this+0x2C m_ownerID   this+0x30 m_ownerType
//   this+0x34 m_positionOfAudio  this+0x40 m_found (one byte)
//
// The dispatch table at 0x4B4190 has six entries; 0, 1, 2 and 5 reach four
// distinct bodies and 3 and 4 share the zero-fill at +0x149. Those are exactly
// the m_ownerType values the matched constructors write, and each case's null
// path branches to THAT case's own tail, not to a shared fallback -- so the
// tail sits outside the null test in every arm. Case 5's outer null test
// (Glo012F1028) converges on its own tail the same way.
//
// Two codegen facts this shape depends on, both measured:
//
//  1. Retail keeps FOUR byte-identical 34-byte case tails. MSVC 7.1 cross-jumps
//     identical tails, which is where the ~80-byte deficit of the earlier
//     attempts went. Distinct barrier intrinsics on the last statement before
//     each `return` keep the copies apart at zero byte cost: neither intrinsic
//     emits an instruction or a relocation. All three non-trivial arms need a
//     DISTINCT barrier set; fewer arms merge again.
//
//  2. The cached-position copy must read through a reference-returning
//     getPosition(). A pointer-returning one folds the +0x38 into each load,
//     giving `mov ecx,[eax+0x38]` instead of retail's `add eax,0x38` followed
//     by `lea ecx,[esi+0x34]` with both pointers live in registers.
//
// Case 5's owner-position build needs a NON-volatile Coord3D temporary filled
// through set(x, y, z) and copied back; a volatile one forces an x87
// fld/fst/fstp triple where retail uses plain dword moves.

extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

typedef int ObjectID;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Matrix/Coord3D.h
struct Coord3D
{
	float x, y, z;

	void set(const Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}

	void set(float xValue, float yValue, float zValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
	}
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;

	const Coord3D &getPosition() const { return m_position; }
};

class Drawable
{
public:
	// pinned retail ILT thunk 0x0004B12D: pointer-returning, so the copy below
	// dereferences. Case 2's Object view is inlined instead, which is what lets
	// it keep the add/lea form.
	const Coord3D *getPosition() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
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
	virtual void slot28();
	virtual Drawable *findDrawableByID(ObjectID id);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class LivingWorldOwner
{
public:
	char m_pad00[0x0c];
	float m_x;
	float m_y;
};

class LivingWorldOwnerLookup
{
public:
	void *findOwnerByID(ObjectID id);
};

extern GameLogic *TheBfmeGameLogic;
extern GameClient *TheGameClient;
extern void *Glo012F1028;

class AudioEventRTS
{
public:
	void resolveOwnerPosition(Coord3D *pos, bool *found);

private:
	char m_pad00[0x2c];
	ObjectID m_ownerID;
	int m_ownerType;
	Coord3D m_positionOfAudio;
	volatile bool m_found;
};

void AudioEventRTS::resolveOwnerPosition(Coord3D *pos, bool *found)
{
	Coord3D ownerPosition;

	switch (m_ownerType)
	{
	case 0:
		*found = true;
		pos->x = m_positionOfAudio.x;
		pos->y = m_positionOfAudio.y;
		pos->z = m_positionOfAudio.z;
		return;

	case 2:
		{
			Object *object = TheBfmeGameLogic->findObjectByID(m_ownerID);
			if (object != 0)
			{
				m_found = 1;
				m_positionOfAudio = object->getPosition();
			}
			*found = m_found;
			pos->x = m_positionOfAudio.x;
			pos->y = m_positionOfAudio.y;
			pos->z = m_positionOfAudio.z;
			_WriteBarrier();
return;
		}

	case 1:
		{
			Drawable *drawable = TheGameClient->findDrawableByID(m_ownerID);
			if (drawable != 0)
			{
				m_found = 1;
				m_positionOfAudio = *drawable->getPosition();
			}
			*found = m_found;
			pos->set(&m_positionOfAudio);
			_ReadWriteBarrier();
return;
		}

	case 5:
		if (Glo012F1028 != 0)
		{
			LivingWorldOwner *owner = (LivingWorldOwner *)
				((LivingWorldOwnerLookup *)Glo012F1028)->findOwnerByID(m_ownerID);
			if (owner != 0)
			{
				m_found = 1;
				ownerPosition.set(owner->m_x, owner->m_y, 0.0f);
				m_positionOfAudio = ownerPosition;
			}
		}
		*found = m_found;
		pos->x = m_positionOfAudio.x;
		pos->y = m_positionOfAudio.y;
		pos->z = m_positionOfAudio.z;
		_WriteBarrier();
_ReadWriteBarrier();
return;
	}

	*found = false;
	pos->x = 0.0f;
	pos->y = 0.0f;
	pos->z = 0.0f;
}
