// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <string>

extern "C" void __cdecl peerStopGame(void *peer);

class BfmeOwnerFP
{
public:
	void bfmeStopFP(void *peer);

	unsigned char m_bfmeHeadFP[0xc0];
	// Retail calls the matched _STL::string::assign(first, last) at
	// 0x000A5810 through its ILT 0x0002B297.
	_STL::string m_bfmeSubFP;
	unsigned char m_bfmeMidFP[0x30c];
	char m_bfmeFlagFP;
};

void BfmeOwnerFP::bfmeStopFP(void *peer)
{
	peerStopGame(peer);
	m_bfmeSubFP.assign("openstaging", "");
	m_bfmeFlagFP = 0;
}
