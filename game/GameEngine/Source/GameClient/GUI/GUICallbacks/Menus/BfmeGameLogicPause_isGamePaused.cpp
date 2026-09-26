// Kept out of PopupSaveLoad.cpp because seeing this trivial body lets MSVC
// remove the retail out-of-line calls from that file's matched menu routines.
// Both calls reach ILT 0x00022C96, whose target is the complete seven-byte
// body at 0x00383480; the load itself fixes the pause flag at this+0x11c.

class BfmeGameLogicPause
{
public:
	bool isGamePaused();

private:
	char m_unreconstructed_00[0x11c];
	bool m_gamePaused;
};

bool BfmeGameLogicPause::isGamePaused()
{
	return m_gamePaused;
}
