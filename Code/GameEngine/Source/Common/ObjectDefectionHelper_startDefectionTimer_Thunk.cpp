// cl: /DNDEBUG /MD /EHsc
// Lift the startDefectionTimer __emit thunk to clean C++.
//
// Retail reads the owner Object from this+0x08 and tests its status byte at
// +0x344. When the bit is clear it hands the helper an effectively-infinite
// frame (0x3FFFFFFF); otherwise it stamps the current logic frame and the
// deadline, then hands over 1. Both arms end in the same two-argument thiscall,
// which MSVC 7.1 tail-jumps because the callee's `ret 8` matches this frame's.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_unreconstructed_00[0x344];
	unsigned char m_statusBits;					///< retail this+0x344; bit 1 gates the timer
};

class GameLogicFrameSource
{
public:
	unsigned char m_unreconstructed_00[0x3C];
	unsigned int m_frame;						///< retail this+0x3C
};

extern GameLogicFrameSource *TheGameLogic;		///< retail [0x012F0898]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectDefectionHelper.h
class ObjectDefectionHelper
{
public:
	void startDefectionTimer(unsigned int, bool);
	void applyDefectionFrame(Object *, int);	///< pinned to the ILT thunk at 0x000157DA

private:
	unsigned char m_unreconstructed_00[0x08];
	Object *m_owner;							///< retail this+0x08
	unsigned char m_unreconstructed_0C[0x20 - 0x0C];
	unsigned int m_startFrame;					///< retail this+0x20
	unsigned int m_endFrame;					///< retail this+0x24
	unsigned int m_defectorFrame;				///< retail this+0x28
	bool m_flag;								///< retail this+0x2C
};

// ?startDefectionTimer@ObjectDefectionHelper@@QAEXI_N@Z
void ObjectDefectionHelper::startDefectionTimer(unsigned int duration, bool flag)
{
	Object *owner = m_owner;
	if ((owner->m_statusBits & 2) == 0)
	{
		applyDefectionFrame(owner, 0x3FFFFFFF);
		return;
	}

	m_startFrame = TheGameLogic->m_frame;
	m_endFrame = m_startFrame + duration;
	m_defectorFrame = 0;
	m_flag = flag;
	applyDefectionFrame(owner, 1);
}
