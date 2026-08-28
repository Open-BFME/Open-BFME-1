// cl: /DNDEBUG /MD /EHsc
// readable body of ?allow@PartitionFilterRepulsor@@MAE_NPAVObject@@@Z: Code/GameEngine/Source/GameLogic/Object/PartitionManager.cpp
// Isolated thunk for PartitionFilterRepulsor::allow. The Zero Hour source
// (PartitionManager.cpp) compiles to bytes that are 94.8% aligned with
// retail but disagree on three points, all layout/enum drift documented by
// sibling PartitionFilter thunks in PartitionFilters_allow_Thunk.cpp:
//
//   - PartitionFilter's first data member lands at this+0x08 here, not
//     ZH's this+0x04 (base is one word wider), matching every other
//     single-pointer-member filter's ICF-folded constructor.
//   - Object's isEffectivelyDead() bit test reads this+0x344 in retail,
//     not wherever ZH's m_privateStatus would land -- BFME's Object has
//     grown substantially relative to ZH's. Read the confirmed byte/bit
//     directly instead of reconstructing the struct.
//   - The second isKindOf() call passes 0x58 (88), not ZH's KINDOF_INERT
//     (0x54/84); BFME's KindOfType enum has extra entries ahead of it.
//     KINDOF_STRUCTURE (7) is unchanged.

enum Relationship { ENEMIES = 0 };
enum KindOfType { KINDOF_STRUCTURE_ = 7 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isKindOf(KindOfType kindOf) const;			// pinned ILT @0x0003251F
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Relationship getRelationship(const Object *other) const;	// pinned ILT @0x0004A719
	bool isAbleToAttack() const;						// pinned ILT @0x00001FD7

	// retail this+0x90, dword load then test bit 0x100 (OBJECT_STATUS_REPULSOR)
	unsigned char m_unreconstructed_00[0x90];
	unsigned int m_status;								///< retail this+0x90
	unsigned char m_unreconstructed_94[0x344 - 0x94];
	unsigned char m_privateStatus;						///< retail this+0x344, bit 0 = EFFECTIVELY_DEAD
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilterRepulsor
{
protected:
	virtual bool allow(Object *other);

private:
	unsigned char m_unreconstructed_04[0x08 - 4];		///< vtable slot then unpinned base bytes
	const Object *m_self;								///< retail this+0x08
};

// ?allow@PartitionFilterRepulsor@@MAE_NPAVObject@@@Z
bool PartitionFilterRepulsor::allow(Object *other)
{
	if (other == m_self)
	{
		// don't repulse yourself. :)
		return false;
	}

	// If it's flagged, it's a repulsor.
	if (other->m_status & 0x100u)
	{
		return true;
	}

	if (other->m_privateStatus & 0x1u)
		return false; // no dead enemies.

	Relationship r = m_self->getRelationship(other);
	if (r != ENEMIES)
	{
		return false; // only enemies auto repulse.
	}

	if (other->isKindOf((KindOfType)7)) // KINDOF_STRUCTURE
	{
		// always pay attention to buildings that can attack
		if (other->isAbleToAttack())
			return true;
		return false;
	}

	if (other->isKindOf((KindOfType)0x58))
		return false;

	if (!other->isAbleToAttack())
	{
		return false;
	}

	return true;
}
