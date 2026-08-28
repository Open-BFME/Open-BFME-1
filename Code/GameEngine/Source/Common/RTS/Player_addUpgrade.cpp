// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?addUpgrade@Player@@QAEPAVUpgrade@@PBVUpgradeTemplate@@W4UpgradeStatusType@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp

typedef unsigned int UnsignedInt;

enum UpgradeStatusType
{
	UPGRADE_STATUS_INVALID,
	UPGRADE_STATUS_IN_PRODUCTION,
	UPGRADE_STATUS_COMPLETE
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UnsignedInt getUpgradeMask() const { return m_upgradeMask; }

private:
	unsigned char m_unreconstructed[0x20];
	UnsignedInt m_upgradeMask;

	friend class Player;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
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

class UpgradeMaskType
{
public:
	void set( UnsignedInt bit )
	{
		UnsignedInt *word = &m_bits[bit >> 5];
		*word |= 1U << (bit & 31);
	}
	void clear( UnsignedInt bit )
	{
		UnsignedInt index = bit >> 5;
		UnsignedInt mask = 1U << (bit & 31);
		UnsignedInt value = m_bits[index] & ~mask;
		m_bits[index] = value;
	}

private:
	UnsignedInt m_bits[6];

	friend class Player;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Upgrade *addUpgrade( const UpgradeTemplate *upgradeTemplate, UpgradeStatusType status );
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
	Upgrade *m_upgradeList;
	unsigned char m_betweenListAndMasks[0x1c];
	UpgradeMaskType m_upgradesInProgress;
	UpgradeMaskType m_upgradesCompleted;
};

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
