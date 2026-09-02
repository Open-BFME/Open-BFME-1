// cl: /DNDEBUG /MD
//
// Retail 0x0050D9B0: CampaignReview playerSideType value provider.  The
// constructor at 0x0050E320 binds this through ILT 0x00042663 as the
// showAptScreenWithArg callback for "playerSideType".  On get (!setting)
// it copies "evil" or "good" into the APT output buffer from the local
// player's +0x1c side flag.

extern "C" char * __cdecl strcpy( char *destination, const char *source );

struct PlayerSideFlag
{
	char m_unmodelled[ 0x1C ];
	unsigned char m_isEvil;
};

extern PlayerSideFlag *g_campaignReviewPlayer;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisconnectMenu.h
// CampaignReview.apt, object 0x258 bytes.
class BfmeAptScreenCampaignReview
{
public:
	void _bfme_playerSideType( const char *selector, void *value, bool setting );
};

// ?_bfme_playerSideType@BfmeAptScreenCampaignReview@@QAEXPBDPAX_N@Z
void BfmeAptScreenCampaignReview::_bfme_playerSideType(
	const char *, void *value, bool setting )
{
	if( setting )
		return;

	if( g_campaignReviewPlayer && g_campaignReviewPlayer->m_isEvil )
		strcpy( (char *)value, "evil" );
	else
		strcpy( (char *)value, "good" );
}
