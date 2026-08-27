// cl: /EHs-c-
//
// Open-BFME: retail 0x0060D480, 46 bytes.
//
// The predicate is true only in global mode 1, while this object's byte at
// +0x288 is clear, and while the CampaignManager-family global at 0x012F1028
// has its byte at +0x78 clear.  The types are deliberately TU-local measured
// slices; the remaining owner identity has not been recovered.

typedef bool Bool;

class Glo012F7048CampaignGateMode
{
public:
	void *m_vtable;
	int m_mode;
};

extern Glo012F7048CampaignGateMode *Glo012F7048;

class CampaignManager;
extern CampaignManager *TheBfmeLivingWorldCampaignState;

class BfmeCampaignManagerFlag78Slice
{
public:
	unsigned char m_unmodelled00[ 0x78 ];
	Bool m_flag78;
};

class Rva0060D480CampaignGate
{
public:
	Bool isOpen( void ) const;

private:
	unsigned char m_unmodelled00[ 0x288 ];
	Bool m_blocked;
};

Bool Rva0060D480CampaignGate::isOpen( void ) const
{
	if ( Glo012F7048->m_mode == 1
		&& !m_blocked
		&& !((BfmeCampaignManagerFlag78Slice *)TheBfmeLivingWorldCampaignState)->m_flag78 )
		return true;
	return false;
}
