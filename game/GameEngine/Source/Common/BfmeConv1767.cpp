#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// ILT 0x0000EAB6 reaches this existing body at 0x005CAA10.
class BfmeThing935E
{
public:
	void bfmeGo935E(void *text, void *value);
};

class ParticleSystemManager;
extern ParticleSystemManager *TheParticleSystemManager;

class BfmeOwnCG
{
public:
	void bfmeReportCG(void *first, void *unused);

	unsigned char m_bfmeHeadCG[0xcc];
	char m_bfmeNameCG[1];
};

void BfmeOwnCG::bfmeReportCG(void *first, void *unused)
{
	AsciiString text(m_bfmeNameCG);

	((BfmeThing935E *)TheParticleSystemManager)->bfmeGo935E(&text, first);
}
