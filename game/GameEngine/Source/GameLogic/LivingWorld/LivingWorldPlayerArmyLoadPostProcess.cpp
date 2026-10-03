// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00365830StringHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[ 1 ];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	bool isEmpty() const { return !m_data || m_data->m_length == 0; }

private:
	Rva00365830StringHeader *m_data;
};

class LivingWorldPlayerArmy;

class LivingWorldArmy
{
public:
	void replenish( LivingWorldPlayerArmy *playerArmy );
};

class BfmeLivingWorldCampaignManager
{
public:
	LivingWorldArmy *findArmy( const AsciiString &name );
};

// The global at retail 0x012F1024 is defined by LivingWorldCampaignManager.cpp
// (data row ?TheLivingWorldCampaignManager@@3PAVLivingWorldCampaignManager@@A),
// so it is spelled here with the class that definition proves; the call below
// casts to this TU's own view of the manager, whose findArmy body lives with
// the other LivingWorld campaign-manager TUs.
class LivingWorldCampaignManager;

extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;

class LivingWorldPlayerArmy
{
public:
	virtual void loadPostProcess();
	int currentCommandPoints() const;

private:
	char m_unreconstructed04[ 0x4C ];
	int m_minCommandPoints;
	AsciiString m_replenishArmyName;
};

void LivingWorldPlayerArmy::loadPostProcess()
{
	if( currentCommandPoints() < m_minCommandPoints && !m_replenishArmyName.isEmpty() )
	{
		LivingWorldArmy *army = ((BfmeLivingWorldCampaignManager *)TheLivingWorldCampaignManager)->findArmy( m_replenishArmyName );
		if( army )
			army->replenish( this );
	}
}
