// ?rva003B4250@BfmeLivingWorldCampaignManager@@QAEXABVAsciiString@@00@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#include "PreRTS.h"
#include "Common/INI.h"
#include <vector>

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

// The constructors, parser and army helpers are owned by
// GameLogic/LivingWorld/INILivingWorldPlayerArmy.cpp. Keep only this TU's
// campaign operation here so it does not emit alternate helper definitions.
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

class GameLogic;
extern GameLogic *TheGameLogic;

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
				reinterpret_cast<Rva003B4250StoreThunk *>( TheGameLogic );
			store->append(
				reinterpret_cast<const Rva00366890Element *>(
					&m_playerArmies[ i ] ),
				first, second );
			return;
		}
	}
}

