// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?updateRadarAttackGlow@ControlBar@@IAEXXZ: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// Lift the ControlBar::updateRadarAttackGlow __emit thunk to clean C++.
//
// Verbatim Zero Hour ControlBar.cpp: count the glow down, switch the window
// back on when it expires, and otherwise toggle it every Nth frame.
//
// Retail pins what ZH leaves symbolic: the on flag is the byte at this+0x2E0,
// the remaining frame count is at this+0x2E4, the window pointer at this+0x2E8,
// and the toggle period is 15 (the `idiv` by 0x0F).
//
// The toggle argument compiles to shr 3 / not al / and 0xFFFFFF01 rather than a
// setcc, which is BitTest expanding to a plain mask-and-compare on the status
// word: WIN_STATUS_ENABLED is bit 3, so the shift lands it in bit 0 and the
// negation is done in place.

typedef int Int;

#define BitTest(x, i) (((x) & (i)) != 0)

enum { WIN_STATUS_ENABLED = 0x00000008 };
enum { RADAR_ATTACK_GLOW_NUM_TIMES = 15 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winEnable(bool enable);								///< ILT thunk at 0x0004A1FB
	unsigned int winGetStatus(void);						///< ILT thunk at 0x00023DDA
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
protected:
	void updateRadarAttackGlow(void);

private:
	unsigned char m_unreconstructed_00[0x2E0];
	unsigned char m_radarAttackGlowOn;						///< retail this+0x2E0
	unsigned char m_unreconstructed_2E1[3];
	Int m_remainingRadarAttackGlowFrames;					///< retail this+0x2E4
	GameWindow *m_radarAttackGlowWindow;					///< retail this+0x2E8
};

// ?updateRadarAttackGlow@ControlBar@@IAEXXZ
void ControlBar::updateRadarAttackGlow(void)
{
	if (!m_radarAttackGlowOn || !m_radarAttackGlowWindow)
		return;

	m_remainingRadarAttackGlowFrames--;
	if (m_remainingRadarAttackGlowFrames <= 0)
	{
		m_radarAttackGlowOn = 0;
		m_radarAttackGlowWindow->winEnable(true);
		return;
	}

	if (m_remainingRadarAttackGlowFrames % RADAR_ATTACK_GLOW_NUM_TIMES == 0)
	{
		m_radarAttackGlowWindow->winEnable(
			!BitTest(m_radarAttackGlowWindow->winGetStatus(), WIN_STATUS_ENABLED));
	}
}
