// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/iniexception /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

// FILE: INILivingWorldCampaign.cpp ///////////////////////////////////////////
//
// The LivingWorldCampaign block, retail 0x003AA860. BFME-only.
//
// The function names itself: the INIException it throws for a missing name
// pushes "ParseLivingWorldCampaignBlock::Campaign name expected", so the C++
// name here is the binary's own - the same way INIArmyIcon.cpp got
// ParseArmyIconBlock next door.
//
// TheLivingWorldCampaignManager at 0x012F1024 is the global
// INILivingWorldPlayerArmy.cpp already reaches, under the stand-in class name
// that file gave it so the one global keeps one decorated name.
//
// The campaign record is 0x20 bytes and nothing here reads a member; it is
// built from the name, filled by the field table, given the pass at 0x003A73C0
// that turns its element vector at +0xC/+0x10 into the index it stores at +0x18,
// and only then handed to the manager. That pass is named for what it does at
// this call site, not by the image.
//
// The emptiness test is spelled through the string header rather than through
// AsciiString: every isEmpty/getLength the shim offers is declared-only and
// would emit a call. It has to widen to int on the way out, too - retail is
// `movzx eax,word [eax+4]' then `test eax,eax', which is what a length
// accessor returning int folds to once the null case merges with the zero
// case; a bool test on the member itself compiles to `cmp word ptr, 0'.
//
///////////////////////////////////////////////////////////////////////////////

#include <stddef.h>

#include "Common/AsciiString.h"
#include "Common/INIException.h"

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );
};

// The WWLib StringBase<char> buffer header, as this body reads it.
struct BfmeStringHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[ 1 ];
};

static int stringLength( const AsciiString &string )
{
	const BfmeStringHeader *header = *(const BfmeStringHeader *const *)&string;
	return header ? header->m_length : 0;
}

class LivingWorldCampaign
{
public:
	LivingWorldCampaign( const AsciiString &name );
	~LivingWorldCampaign();

	void indexMissions();

	static const FieldParse m_fieldParseTable[];		// 0x010EC7CC

private:
	char m_unmodelled[ 0x20 ];
};

class BfmeLivingWorldCampaignManager
{
public:
	void addCampaign( LivingWorldCampaign *campaign );
};

extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager;	// 0x012F1024

// ?ParseLivingWorldCampaignBlock@@YAXPAVINI@@@Z
void ParseLivingWorldCampaignBlock( INI *ini )
{
	if( !TheLivingWorldCampaignManager )
		return;

	AsciiString name( ini->getNextToken() );

	if( stringLength( name ) == 0 )
		throw INIException( 3, "ParseLivingWorldCampaignBlock::Campaign name expected" );

	LivingWorldCampaign campaign( name );

	ini->initFromINI( &campaign, LivingWorldCampaign::m_fieldParseTable );

	campaign.indexMissions();

	TheLivingWorldCampaignManager->addCampaign( &campaign );
}
