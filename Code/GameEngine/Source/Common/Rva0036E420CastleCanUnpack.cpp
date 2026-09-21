// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: retail 0x0036E420 (246 B). Debug-log gate plus a readiness
// check. The retail debug format string burns in the method name and every
// member/parameter name used below: "CAMP: Frame %d: Castle %s(%d) %s
// ::canUnpack() -- m_needInstantBuild=%d, m_currentState=%d, checkTimer=%d,
// m_timer=%g" (literal at 0x010E9848), logged through the CRCParameterCheck
// logger already landed at 0x00065C80 (CRCParameterCheckLog.cpp). The
// override-chain resolve (object+4 -> getFinalOverride) matches the shape
// already landed at 0x001B6070 (Rva001B6070.cpp), just with the trailing
// AsciiString-style value at a different offset in this instantiation.

class CRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);

extern CRCParameterCheck *TheCRCParameterCheck;
extern const float BfmeZeroRange;

class GameLogic
{
public:
	char m_pad00[0x3c];
	int m_frame;
};

extern GameLogic *TheGameLogic;

class StringBaseNarrowAA
{
protected:
	char *m_bfmeNarrowAA;
};

class AsciiStringAA : public StringBaseNarrowAA
{
public:
	const char *bfmeTextAA(void) const
	{
		return (m_bfmeNarrowAA != 0) ? m_bfmeNarrowAA + 8 : "";
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	char m_pad00[4];
	const Overridable *m_nextOverride;
	char m_pad08[0x18];
	AsciiStringAA m_bfmeValueAA;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	char m_pad00[0x1c];
	AsciiStringAA m_bfmeNameAA;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;

	char m_pad00[4];
	const Overridable *m_overrideChain;
	char m_pad08[0x6c];
	int m_id;
};

class Rva0036E420Castle
{
public:
	bool canUnpack(bool checkTimer);

private:
	char m_pad00[8];
	Object *m_object;
	char m_pad0c[0x90];
	int m_currentState;
	char m_pad_a0[4];
	unsigned char m_needInstantBuild;
	char m_pad_a5[3];
	float m_timer;
};

bool Rva0036E420Castle::canUnpack(bool checkTimer)
{
	Object *object = m_object;

	if (*(int *)((char *)TheGameLogic + 0x1a0) > 0)
	{
		if (TheCRCParameterCheck != 0)
		{
			Player *player = object->getControllingPlayer();
			const char *textA = player->m_bfmeNameAA.bfmeTextAA();

			int id = object->m_id;

			const Overridable *chain = object->m_overrideChain;
			const Overridable *resolved;
			if (chain == 0)
			{
				resolved = 0;
			}
			else if (chain->m_nextOverride != 0)
			{
				resolved = chain->m_nextOverride->getFinalOverride();
			}
			else
			{
				resolved = chain;
			}
			const char *textB = resolved->m_bfmeValueAA.bfmeTextAA();

			bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
				"CAMP: Frame %d: Castle %s(%d) %s ::canUnpack() -- "
				"m_needInstantBuild=%d, m_currentState=%d, checkTimer=%d, m_timer=%g",
				TheGameLogic->m_frame, textB, id, textA,
				m_needInstantBuild, m_currentState, checkTimer, (double)m_timer);
		}
	}

	if (m_needInstantBuild)
		return false;

	bool stateReady = (m_currentState == 0);
	if (!stateReady)
		goto returnState;
	if (!checkTimer)
		goto returnState;
	if (m_timer > BfmeZeroRange)
		return false;
returnState:
	return stateReady;
}

// @?canUnpack@Rva0036E420Castle@@QAE_N_N@Z 0x0036E420
