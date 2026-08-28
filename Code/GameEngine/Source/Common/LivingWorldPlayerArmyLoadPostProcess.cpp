// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00365830StringHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[ 1 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager;

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
		LivingWorldArmy *army = TheLivingWorldCampaignManager->findArmy( m_replenishArmyName );
		if( army )
			army->replenish( this );
	}
}
