// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"
template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }

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
	if( currentCommandPoints() < m_minCommandPoints && !m_replenishArmyName.StringBase<char>::isEmpty() )
	{
		LivingWorldArmy *army = ((BfmeLivingWorldCampaignManager *)TheLivingWorldCampaignManager)->findArmy( m_replenishArmyName );
		if( army )
			army->replenish( this );
	}
}
