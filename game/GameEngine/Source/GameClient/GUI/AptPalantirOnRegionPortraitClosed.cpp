extern "C" __declspec(dllimport) int __cdecl atoi( void *text );

// Open-BFME5 conversions.

struct BfmeCellSHA
{
	int m_bfme00;
	int m_bfme04;
};

class BfmeMakerSHA
{
public:
	void bfmeFillSHA(BfmeCellSHA *out, int *key);
};

class BfmeStoreSHA
{
public:
	void bfmeUseSHA(int *key);
};

class BfmeThingSHA
{
public:
	void bfmeGoSHA(int key);
	char m_bfmePad[0x10];
	BfmeStoreSHA m_bfmeStore;
	char m_bfmePad2[0xb];
	BfmeMakerSHA m_bfmeMaker;
};


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
	reinterpret_cast<BfmeThingSHA *>(&reinterpret_cast<AptPalantirRegionOwner *>(TheAptPalantir)->m_regionPanel)->bfmeGoSHA( atoi( regionText ) );
}
