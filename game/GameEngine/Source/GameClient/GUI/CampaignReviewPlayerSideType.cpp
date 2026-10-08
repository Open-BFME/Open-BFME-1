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

// Retail's global at 0x012F1024 is EA's LivingWorldCampaignManager singleton,
// defined once in GameEngine/Source/GameLogic/LivingWorld/
// LivingWorldCampaignManager.cpp, so this reference carries that canonical type
// (class, not struct); the local view above is cast in at the uses.
class LivingWorldCampaignManager;

extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;

// CampaignReview.apt, object 0x258 bytes.
class AptCampaignReview
{
public:
	void _bfme_playerSideType( const char *selector, void *value, bool setting );
};

// ?_bfme_playerSideType@AptCampaignReview@@QAEXPBDPAX_N@Z
void AptCampaignReview::_bfme_playerSideType(
	const char *, void *value, bool setting )
{
	if( setting )
		return;

	if( TheLivingWorldCampaignManager &&
		((PlayerSideFlag *)TheLivingWorldCampaignManager)->m_isEvil )
		strcpy( (char *)value, "evil" );
	else
		strcpy( (char *)value, "good" );
}
