// cl: /EHs-c-
//
// Open-BFME: retail 0x0060D3D0, 9 bytes.
//
// The sole caller loads TheLivingWorldManager (0x012F706C) into ecx before
// calling this method.  The method does not use that receiver: it loads
// TheCampaignManager (0x012F1028) and returns its byte at +0x2C.  The vendored
// CampaignManager header identifies that byte as m_victorious, but its Zero
// Hour layout differs, so the measured BFME slice remains TU-local here.

typedef bool Bool;

class CampaignManager;
extern CampaignManager *TheBfmeLivingWorldCampaignState;

class BfmeCampaignManagerVictoriousSlice
{
public:
	unsigned char m_unmodelled00[ 0x2C ];
	Bool m_victorious;
};

class BfmeLivingWorldManager
{
public:
	Bool isCampaignVictorious( void );
};

Bool BfmeLivingWorldManager::isCampaignVictorious( void )
{
	return ((BfmeCampaignManagerVictoriousSlice *)TheBfmeLivingWorldCampaignState)->m_victorious;
}
