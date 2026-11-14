extern "C" __declspec(dllimport) int __cdecl atoi( void *text );

class AptPalantirRegionPanel
{
public:
	void closePortrait( int region );
};

struct AptPalantirRegionOwner
{
	unsigned char m_unmodelled00[ 0x154 ];
	AptPalantirRegionPanel m_regionPanel;
};

// Retail 0x012F4B98: use the existing data owner; retain the local pointee view.
extern class AptPalantir *TheAptPalantir;

// ?aptPalantirOnRegionPortraitClosed@@YAXPAX@Z
void aptPalantirOnRegionPortraitClosed( void *regionText )
{
	reinterpret_cast<AptPalantirRegionOwner *>(TheAptPalantir)->m_regionPanel.closePortrait( atoi( regionText ) );
}
