// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// BFME retail 0x001CDAD0.  The matched AIAttackFireWeaponState::update
// caller passes its Object owner in ecx, the goal Object, and the goal
// position.  This is BFME's extended pre-fire path: it remembers the target,
// waits until the selected weapon can fire on the next frame, clears three
// stale model conditions, and passes both target forms to Weapon.

typedef unsigned int UnsignedInt;
typedef int ObjectID;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit
	};

	BitFlags(BogusInitType, int bit1, int bit2, int bit3);

private:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<304> ModelConditionFlags;

class Drawable
{
	friend class Object;

private:
	void applyPendingModelConditionFlags(bool force);
};

class Weapon
{
public:
	void preFireWeapon(const Object *source, const Object *victim,
		const Coord3D *position);
	UnsignedInt getPossibleNextShotFrame() const
	{
		return m_whenWeCanFireAgain;
	}

private:
	unsigned char m_beforeNextShot[0x18];
	UnsignedInt m_whenWeCanFireAgain;
};

struct Rva00367E30Logic
{
	unsigned char m_beforeFrame[0x3c];
	UnsignedInt m_frame;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class Object
{
public:
	void preFireCurrentWeapon(const Object *victim,
		const Coord3D *position);
	void clearModelConditionFlags(const ModelConditionFlags &flags);

private:
	unsigned char m_beforePosition[0x38];
	Coord3D m_position;
	unsigned char m_gap44[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_gap78[0x80 - 0x78];
	Drawable *m_drawable;
	unsigned char m_gap84[0x98 - 0x84];
	UnsignedInt m_statusBits98;
	unsigned char m_gap9c[0x26c - 0x9c];
	Weapon *m_weapons[4];
	UnsignedInt m_currentWeapon;
	unsigned char m_gap280[0x2a8 - 0x280];
	Coord3D m_preAttackPosition;
	ObjectID m_preAttackVictimID;
	unsigned char m_gap2b8[0x344 - 0x2b8];
	unsigned char m_privateStatus;
};

void Object::preFireCurrentWeapon(const Object *victim,
	const Coord3D *position)
{
	Weapon *weapon = m_weapons[m_currentWeapon];

	if (victim != 0)
	{
		m_preAttackPosition = victim->m_position;
		m_preAttackVictimID = victim->m_id;
	}
	else if (position != 0)
	{
		m_preAttackPosition = *position;
		m_preAttackVictimID = 0;
	}

	if (weapon != 0 &&
		TheBfmeGameLogic->m_frame + 1 >= weapon->getPossibleNextShotFrame())
	{
		if (m_drawable != 0 && (m_statusBits98 & 0x400) == 0)
		{
			clearModelConditionFlags(ModelConditionFlags(
				ModelConditionFlags::kInit, 0x29, 0x2f, 0x35));
			m_drawable->applyPendingModelConditionFlags(false);
		}

		weapon->preFireWeapon(this, victim, position);
		m_privateStatus &= (unsigned char)~2;
	}
}
