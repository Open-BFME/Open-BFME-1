// cl: /DNDEBUG /MD /EHsc

// Retail AI attack-target filter at 0x0027E170.  `this` is the secondary
// interface at enclosing-object +0x24; the state dispatcher and owning Thing
// therefore sit at -0x24 and -0x1c.  Keep the BFME ABI slice TU-local.

enum KindOfType
{
	KINDOF_BFME_6C = 0x6c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class AIStateTargetDispatch
{
public:
	void attackOptimizedTarget(Thing *target);
	void attackOrdinaryTarget(Thing *target);
};

class GameLogicFrameSlice
{
	unsigned char m_beforeFrame[0x3c];
public:
	unsigned int m_frame;
};

class AIUpdateTargetDispatch
{
	unsigned char m_beforeExpireFrame[0x154];
	unsigned int m_expireFrame;
	unsigned char m_beforeFlags[0x304 - 0x158];
	unsigned char m_flag304;
	unsigned char m_flag305;

public:
	void attackTarget(Thing *target, int maxShotsToFire, int commandSource);
};

extern bool g_aiTargetDispatchSuppressed;
extern GameLogicFrameSlice *TheGameLogic;

void AIUpdateTargetDispatch::attackTarget(Thing *target, int, int)
{
	const unsigned char attackBit = 0x20;
	if ((reinterpret_cast<const unsigned char *>(*reinterpret_cast<Thing **>(reinterpret_cast<unsigned char *>(this) - 0x1c))[0x94] & attackBit) != 0)
		return;
	if ((reinterpret_cast<const unsigned char *>(target)[0x94] & attackBit) != 0)
		return;
	if (g_aiTargetDispatchSuppressed)
		return;
	if (m_expireFrame > TheGameLogic->m_frame)
		return;
	if (m_flag304 || m_flag305)
		return;

	if ((*reinterpret_cast<Thing **>(reinterpret_cast<unsigned char *>(this) - 0x1c))->isKindOf(KINDOF_BFME_6C))
		reinterpret_cast<AIStateTargetDispatch *>(reinterpret_cast<unsigned char *>(this) - 0x24)->attackOptimizedTarget(target);
	else
		reinterpret_cast<AIStateTargetDispatch *>(reinterpret_cast<unsigned char *>(this) - 0x24)->attackOrdinaryTarget(target);
}
