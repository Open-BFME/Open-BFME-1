// ?setShouldPlay@Eva@@QAE_NW4EvaMessage@@PBUCoord3D@@@Z
// cl: /O2
// stlport

#include <vector>

// Eva::setShouldPlay(EvaMessage, const Coord3D *) at retail 0x004233A0.
// BFME's position-aware setter checks the live and parsed per-message vectors
// before forwarding the optional position to EvaCheck::trigger.  The local
// declarations retain the witnessed retail element sizes and member offsets;
// the trigger callee is independently matched at 0x004223F0.

typedef bool Bool;

extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum EvaMessage
{
	EvaMessage_Invalid = -1
};

struct Coord3D;

struct EvaCheckInfo
{
	unsigned char pad[28];
};

struct EvaCheck
{
	unsigned char pad[24];

	Bool trigger(const EvaCheckInfo *info, const Coord3D *pos);
};

class Eva
{
public:
	Bool setShouldPlay(EvaMessage messageToPlay, const Coord3D *pos);

private:
	unsigned char m_head[0xC];
	_STL::vector<EvaCheckInfo> m_checkInfos;
	unsigned char m_mid[0x4C - 0x18];
	_STL::vector<EvaCheck> m_checks;
};

Bool Eva::setShouldPlay(EvaMessage messageToPlay, const Coord3D *pos)
{
	if (messageToPlay == EvaMessage_Invalid)
	{
		_WriteBarrier();
		return false;
	}

	if (messageToPlay >= 0)
	{
		if ((unsigned)messageToPlay < (unsigned)m_checks.size())
		{
			unsigned int infoCount = (unsigned int)m_checkInfos.size();
			unsigned int liveCount = (unsigned int)m_checks.size();
			if (liveCount == infoCount)
				return m_checks[messageToPlay].trigger(&m_checkInfos[messageToPlay], pos);
		}
	}

	_ReadWriteBarrier();
	return false;
}
