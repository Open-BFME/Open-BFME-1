// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ExperienceTracker.h
// Declaration only: the spelling of the reference this call site makes. The
// definition is ExperienceTrackerBFMEScalar.cpp's body at 0x001B27E0, which
// this TU does not include; retail encodes the call through its ILT thunk
// 0x0000F15F.
class ExperienceTracker
{
public:
	void bfmeResetScalarBaseCount();
};

struct BfmeOwnerBHE
{
	unsigned char m_bfmeHead[0x210];
	ExperienceTracker *m_bfmeSub;
};

int bfmeGoBHE(BfmeOwnerBHE *owner)
{
	owner->m_bfmeSub->bfmeResetScalarBaseCount();
	return 1;
}
