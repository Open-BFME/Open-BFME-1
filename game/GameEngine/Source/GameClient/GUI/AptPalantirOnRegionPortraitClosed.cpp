extern "C" __declspec(dllimport) int __cdecl bfmeCvtDXI( void *text );

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

extern AptPalantirRegionOwner *g_bfmeObjDXJ;

// ?aptPalantirOnRegionPortraitClosed@@YAXPAX@Z
void aptPalantirOnRegionPortraitClosed( void *regionText )
{
	g_bfmeObjDXJ->m_regionPanel.closePortrait( bfmeCvtDXI( regionText ) );
}
