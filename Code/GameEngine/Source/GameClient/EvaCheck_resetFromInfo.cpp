// cl: /O2

// Called from Eva::setShouldPlay's sibling at 0x00423460 on checks[msg] with
// the matching 28-byte check-info. Stores -1.0 at +4 and the unsigned-to-float
// of either info[0] or info[8], whichever is larger.

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaCheckInfo
{
	unsigned m_a;
	unsigned m_b;
	unsigned m_c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaCheck
{
	void resetFromInfo(const EvaCheckInfo *info);

	Real m_triggeredOnFrame;
	Real m_timeForNextCheck;
};

void EvaCheck::resetFromInfo(const EvaCheckInfo *info)
{
	m_timeForNextCheck = -1.0f;
	const unsigned *p = &info->m_a;
	if (info->m_a < info->m_c)
		p = &info->m_c;
	m_triggeredOnFrame = (Real)(unsigned)*p;
}
