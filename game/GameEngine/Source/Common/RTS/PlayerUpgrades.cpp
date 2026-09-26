// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?addUpgrade@Player@@QAEPAVUpgrade@@PBVUpgradeTemplate@@W4UpgradeStatusType@@@Z: game/GameEngine/Source/Common/RTS/Player.cpp

// The two halves of one list operation:
//
//   0x000D24C0  addUpgrade     link a node in, set the bits
//   0x000D25F0  removeUpgrade  unlink it, clear the bits
//
// Both find the node with the same private walk of the list at Player+0x54,
// and both then touch the same pair of masks at +0x74 and +0x8C. They sat in
// two files that each carried a private copy of Upgrade, UpgradeTemplate,
// UpgradeMaskType and the same Player layout -- four models written twice for
// two functions that cannot be understood apart.
//
// The copies had drifted in the small ways that go unnoticed until the two
// bodies sit together. Upgrade's status field was UpgradeStatusType in one
// file and a bare int in the other, so only one of them said what the field
// means; stated once, it means something.
//
// UpgradeMaskType::clear() took the bit index in one file and the whole
// UpgradeTemplate in the other, and that one is NOT drift -- collapsing it to
// a single overload was tried and rejected by the bytes. The two spellings
// compile differently and retail contains both: addUpgrade already holds the
// mask in a register and indexes the array twice, while removeUpgrade takes
// the address of the word once and works through it, which is the `lea
// eax,[edx+eax*4+0x74]` in its body. Writing removeUpgrade as two
// clear(getUpgradeMask()) calls produces the indexing form and misses. So both
// overloads stay, now next to each other where the difference is visible.

typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
enum UpgradeStatusType
{
	UPGRADE_STATUS_INVALID,
	UPGRADE_STATUS_IN_PRODUCTION,
	UPGRADE_STATUS_COMPLETE
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UnsignedInt getUpgradeMask() const { return m_upgradeMask; }

private:
	unsigned char m_unreconstructed[0x20];
	UnsignedInt m_upgradeMask;

	friend class Player;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class Upgrade
{
public:
	static void *operator new( unsigned int size );
	Upgrade( const UpgradeTemplate *upgradeTemplate );
	void friend_setPrev( Upgrade *upgrade ) { m_prev = upgrade; }
	void friend_setNext( Upgrade *upgrade ) { m_next = upgrade; }
	void setStatus( UpgradeStatusType status ) { m_status = status; }

private:
	void *m_vtable;
	const UpgradeTemplate *m_upgradeTemplate;
	UpgradeStatusType m_status;
	Upgrade *m_next;
	Upgrade *m_prev;

	friend class Player;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeMaskType
{
public:
	void set( UnsignedInt bit )
	{
		UnsignedInt *word = &m_bits[bit >> 5];
		*word |= 1U << (bit & 31);
	}
	// addUpgrade's form: the mask is already in hand, index the array twice.
	void clear( UnsignedInt bit )
	{
		UnsignedInt index = bit >> 5;
		UnsignedInt mask = 1U << (bit & 31);
		UnsignedInt value = m_bits[index] & ~mask;
		m_bits[index] = value;
	}
	// removeUpgrade's form: take the word's address once and work through it.
	void clear( const UpgradeTemplate *upgradeTemplate )
	{
		UnsignedInt bit = upgradeTemplate->getUpgradeMask();
		UnsignedInt *word = &m_bits[bit >> 5];
		UnsignedInt mask = 1U << (bit & 31);
		UnsignedInt value = *word & ~mask;
		*word = value;
	}

private:
	UnsignedInt m_bits[6];

	friend class Player;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Upgrade *addUpgrade( const UpgradeTemplate *upgradeTemplate, UpgradeStatusType status );
	void removeUpgrade( const UpgradeTemplate *upgradeTemplate );
	void onUpgradeCompleted( const UpgradeTemplate *upgradeTemplate );

private:
	Upgrade *findUpgrade( const UpgradeTemplate *upgradeTemplate )
	{
		for (Upgrade *upgrade = m_upgradeList; upgrade != 0; upgrade = upgrade->m_next)
		{
			if (upgrade->m_upgradeTemplate == upgradeTemplate)
				return upgrade;
		}
		return 0;
	}

	unsigned char m_unreconstructed[0x54];
	Upgrade *m_upgradeList;					// this+0x54
	unsigned char m_betweenListAndMasks[0x1c];
	UpgradeMaskType m_upgradesInProgress;			// this+0x74
	UpgradeMaskType m_upgradesCompleted;			// this+0x8C
};

// ?addUpgrade@Player@@QAEPAVUpgrade@@PBVUpgradeTemplate@@W4UpgradeStatusType@@@Z
Upgrade *Player::addUpgrade( const UpgradeTemplate *upgradeTemplate, UpgradeStatusType status )
{
	Upgrade *upgrade = findUpgrade( upgradeTemplate );

	if (upgrade == 0)
	{
		upgrade = new Upgrade( upgradeTemplate );
		upgrade->friend_setPrev( 0 );
		upgrade->friend_setNext( m_upgradeList );
		if (m_upgradeList != 0)
			m_upgradeList->friend_setPrev( upgrade );
		m_upgradeList = upgrade;
	}

	upgrade->setStatus( status );

	UnsignedInt newMask = upgradeTemplate->getUpgradeMask();
	if (status == UPGRADE_STATUS_IN_PRODUCTION)
	{
		m_upgradesInProgress.set( newMask );
	}
	else if (status == UPGRADE_STATUS_COMPLETE)
	{
		m_upgradesInProgress.clear( newMask );
		m_upgradesCompleted.set( newMask );
		onUpgradeCompleted( upgradeTemplate );
	}

	return upgrade;
}

// ?removeUpgrade@Player@@QAEXPBVUpgradeTemplate@@@Z
void Player::removeUpgrade( const UpgradeTemplate *upgradeTemplate )
{
	Upgrade *upgrade = findUpgrade( upgradeTemplate );

	if (upgrade != 0)
	{
		if (upgrade->m_next != 0)
			upgrade->m_next->m_prev = upgrade->m_prev;
		if (upgrade->m_prev != 0)
			upgrade->m_prev->m_next = upgrade->m_next;
		else
			m_upgradeList = upgrade->m_next;

		m_upgradesInProgress.clear( upgradeTemplate );
		m_upgradesCompleted.clear( upgradeTemplate );
	}
}
