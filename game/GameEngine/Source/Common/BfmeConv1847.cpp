// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include "Common/Thing.h"

class BfmeProbeXM;

struct BfmeStateXM
{
	unsigned char m_bfmeHeadXM[0x18];
	unsigned char m_bfmeTagXM[0x18];
	float m_bfmeXXM;
	float m_bfmeYXM;
	unsigned char m_bfmePadXM[4];
	BfmeProbeXM *m_bfmeBestXM;
	float m_bfmeBestDistXM;
};

class BfmeProbeXM
{
public:
	unsigned char m_bfmeHeadXM[0x38];
	float m_bfmeXXM;
	float m_bfmeYXM;
};

int bfmeVisitXM(BfmeProbeXM *probe, BfmeStateXM *state)
{
	if (reinterpret_cast<Thing *>(probe)->isKindOfMulti(
		*reinterpret_cast<const KindOfMaskType *>(state),
		*reinterpret_cast<const KindOfMaskType *>(state->m_bfmeTagXM)))
	{
		float dx = probe->m_bfmeXXM - state->m_bfmeXXM;
		float dy = probe->m_bfmeYXM - state->m_bfmeYXM;
		float d = dy * dy + dx * dx;

		if (d < state->m_bfmeBestDistXM)
		{
			state->m_bfmeBestXM = probe;
			state->m_bfmeBestDistXM = d;
			return 1;
		}
	}

	return 1;
}
