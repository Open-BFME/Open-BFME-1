// ?rva003B4250@BfmeLivingWorldCampaignManager@@QAEXABVAsciiString@@00@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/moduledata /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#include "PreRTS.h"
#include "Common/INI.h"
#include <vector>

inline Snapshot::~Snapshot()
{
}

class LivingWorldPlayerArmy;

class LivingWorldArmy
{
public:
	virtual ~LivingWorldArmy();
	void replenish( LivingWorldPlayerArmy *playerArmy );
	AsciiString getName() const { return *reinterpret_cast<const AsciiString *>( reinterpret_cast<const char *>( this ) + 4 ); }
	Int getCount() const { return *reinterpret_cast<const Int *>( reinterpret_cast<const char *>( this ) + 0x34 ); }

private:
	char m_unmodelled04[ 0x2C ];
	std::vector<LivingWorldArmy> m_armies;
	char m_unmodelled3C[ 0x78 ];
};

class LivingWorldPlayerArmy : public Snapshot
{
public:
	LivingWorldPlayerArmy();
	LivingWorldPlayerArmy( const LivingWorldPlayerArmy &other );
	~LivingWorldPlayerArmy();
	void clearArmies();
	Int currentCommandPoints() const;
	LivingWorldArmy *findArmy( const AsciiString &name, int *outIndex );
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess();
	AsciiString getName() { return m_name; }

	static const FieldParse m_fieldParseTable[];

	Int m_index;
	Bool m_isActive;
	AsciiString m_name;
	AsciiString m_faction;
	AsciiString m_icon;
	UnsignedInt m_color;
	UnsignedInt m_nightColor;
	Int m_startingCommandPoints;
	Int m_unmodelled24;
	Int m_unmodelled28;
	Int m_unmodelled2C;
	std::vector<LivingWorldArmy> m_armies;
	Int m_unmodelled3C;
	Int m_unmodelled40;
	Int m_survivalThreshold;
	AsciiString m_displayNameTag;
	Bool m_unmodelled4C;
	Int m_minCommandPoints;
	AsciiString m_replenishArmyName;
};

class ThingTemplate
{
public:
	Int getCommandPointCost() const { return m_commandPointCost; }

private:
	char m_unmodelled[ 0x4B4 ];
	Int m_commandPointCost;
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate( const AsciiString &name );
};

extern ThingFactory *TheThingFactory;

void LivingWorldArmy::replenish( LivingWorldPlayerArmy *playerArmy )
{
	for( UnsignedInt i = 0; i < m_armies.size(); ++i )
		playerArmy->m_armies.push_back( m_armies[ i ] );
}

Int LivingWorldPlayerArmy::currentCommandPoints() const
{
	Int commandPoints = 0;
	for( UnsignedInt i = 0; i < m_armies.size(); ++i )
	{
		const LivingWorldArmy &army = m_armies[ i ];
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate( army.getName() );
		if( thingTemplate )
			commandPoints += thingTemplate->getCommandPointCost() * army.getCount();
	}

	return commandPoints;
}

LivingWorldPlayerArmy::LivingWorldPlayerArmy() :
	m_index( 0 ),
	m_isActive( false ),
	m_name( AsciiString::TheEmptyString ),
	m_faction( AsciiString::TheEmptyString ),
	m_icon( AsciiString::TheEmptyString ),
	m_startingCommandPoints( 1 ),
	m_unmodelled24( 0 ),
	m_unmodelled28( 0 ),
	m_unmodelled2C( 0 ),
	m_survivalThreshold( 0 ),
	m_unmodelled4C( false ),
	m_minCommandPoints( 0 )
{
	m_armies.clear();
	m_color = 0xFF000000;
	m_nightColor = 0xFF000000;
	m_unmodelled3C = 0;
	m_unmodelled40 = 0;
}

LivingWorldPlayerArmy::LivingWorldPlayerArmy( const LivingWorldPlayerArmy &other ) :
	m_index( other.m_index ),
	m_isActive( other.m_isActive ),
	m_name( other.m_name ),
	m_faction( other.m_faction ),
	m_icon( other.m_icon ),
	m_color( other.m_color ),
	m_nightColor( other.m_nightColor ),
	m_startingCommandPoints( other.m_startingCommandPoints ),
	m_unmodelled24( other.m_unmodelled24 ),
	m_unmodelled28( other.m_unmodelled28 ),
	m_unmodelled2C( other.m_unmodelled2C ),
	m_armies( other.m_armies ),
	m_unmodelled3C( other.m_unmodelled3C ),
	m_unmodelled40( other.m_unmodelled40 ),
	m_survivalThreshold( other.m_survivalThreshold ),
	m_displayNameTag( other.m_displayNameTag ),
	m_unmodelled4C( other.m_unmodelled4C ),
	m_minCommandPoints( other.m_minCommandPoints ),
	m_replenishArmyName( other.m_replenishArmyName )
{
}

LivingWorldPlayerArmy::~LivingWorldPlayerArmy()
{
}

void LivingWorldPlayerArmy::clearArmies()
{
	m_armies.clear();
	m_isActive = false;
}

class BfmeLivingWorldPlayerArmyCollection
{
public:
	void clearModeFourArmies();

private:
	char m_unmodelled[ 0x18 ];
	std::vector<LivingWorldPlayerArmy> m_playerArmies;
};

void BfmeLivingWorldPlayerArmyCollection::clearModeFourArmies()
{
	for( UnsignedInt i = 0; i < m_playerArmies.size(); ++i )
	{
		if( m_playerArmies[ i ].m_startingCommandPoints == 4 )
			m_playerArmies[ i ].clearArmies();
	}
}

struct Rva00366890Element
{
	char m_body[ 0x58 ];
};

class Rva003B4250StoreThunk
{
public:
	void append( const Rva00366890Element *value,
		const AsciiString &first, const AsciiString &second );
};
#pragma comment(linker, "/alternatename:?append@Rva003B4250StoreThunk@@QAEXPBURva00366890Element@@ABVAsciiString@@1@Z=?invoke@Rva00383820@@QAEXXZ")

struct Rva003B4250StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[ 1 ];
};

static int rva003B4250StringLength( const AsciiString &string )
{
	const Rva003B4250StringData *data =
		*reinterpret_cast<const Rva003B4250StringData * const *>( &string );
	return data ? data->m_length : 0;
}

class BfmeLivingWorldCampaignManager
{
public:
	void addPlayerArmy( LivingWorldPlayerArmy *army );
	LivingWorldArmy *findArmy( const AsciiString &name );
	void rva003B4250( const AsciiString &guard,
		const AsciiString &first, const AsciiString &second );

private:
	char m_unmodelled[ 0x20 ];
	std::vector<LivingWorldPlayerArmy> m_playerArmies;
};

extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager;	// 0x012F1024

void BfmeLivingWorldCampaignManager::addPlayerArmy( LivingWorldPlayerArmy *army )
{
	m_playerArmies.push_back( *army );
	m_playerArmies.back().m_index = m_playerArmies.size() - 1;
}

LivingWorldArmy *LivingWorldPlayerArmy::findArmy(const AsciiString &name, int *outIndex)
{
	for (unsigned i = 0; i < m_armies.size(); ++i)
	{
		AsciiString current = m_armies[i].getName();
		if (current.compare(name) == 0)
		{
			if (outIndex)
				*outIndex = (int)i;
			return &m_armies[i];
		}
	}
	return 0;
}

LivingWorldArmy *BfmeLivingWorldCampaignManager::findArmy( const AsciiString &name )
{
	for( UnsignedInt i = 0; i < m_playerArmies.size(); ++i )
	{
		if( m_playerArmies[ i ].getName().compare( name ) == 0 )
			return reinterpret_cast<LivingWorldArmy *>( &m_playerArmies[ i ] );
	}

	return NULL;
}

void BfmeLivingWorldCampaignManager::rva003B4250(
	const AsciiString &guard, const AsciiString &first, const AsciiString &second )
{
	if( rva003B4250StringLength( guard ) == 0 )
		return;

	UnsignedInt i = 0;
	for( ; i < m_playerArmies.size(); ++i )
	{
		if( m_playerArmies[ i ].getName().compare( guard ) == 0 )
		{
			Rva003B4250StoreThunk *store =
				*reinterpret_cast<Rva003B4250StoreThunk **>( 0x012F0898 );
			store->append(
				reinterpret_cast<const Rva00366890Element *>(
					&m_playerArmies[ i ] ),
				first, second );
			return;
		}
	}
}

void parseLivingWorldPlayerArmy( INI *ini )
{
	if( !TheLivingWorldCampaignManager )
		return;

	LivingWorldPlayerArmy army;

	ini->initFromINI( &army, LivingWorldPlayerArmy::m_fieldParseTable );

	TheLivingWorldCampaignManager->addPlayerArmy( &army );
}
