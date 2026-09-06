// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include <map>
#include <hash_map>

// Open-BFME7: near-miss twin of WindowVideoManager::getWinState (dump
// target 0x00498960, near copy in the already-landed window_video_manager.cpp:
// same file, only one field offset differs). The in-file present-unmatched
// getWinState calls WindowVideo::getState(), which resolves to this tree's
// WindowVideo::m_state at +0x14; retail keeps it at +0x10 (same offset
// window_video_manager.cpp's own hideMovie() already reads directly, see its
// "Open-BFME5: map lookup + direct state store at +0x10" comment). This is a
// byte-exact twin under an address-tagged name so it does not collide with
// the real mangled symbol already defined (with the wrong offset) in
// window_video_manager.cpp.
#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"	// This must go first in EVERY cpp file int the GameEngine

#include "window_video_manager.h"
#include "game_window.h"
#include "video_player.h"
#include "display.h"

// Same private hash_map layout as the real WindowVideoManager (m_playingVideos
// is private there, so it is redeclared here rather than touched directly).
class Rva00498960WindowVideoManager : public SubsystemInterface
{
public:
	Int getWinState( GameWindow *win );

private:
	typedef const GameWindow* ConstGameWindowPtr;
	struct hashConstGameWindowPtr
	{
		size_t operator()(ConstGameWindowPtr p) const
		{
			std::hash<UnsignedInt> hasher;
			return hasher((UnsignedInt)p);
		}
	};

	typedef std::hash_map< ConstGameWindowPtr, WindowVideo *, hashConstGameWindowPtr, std::equal_to<ConstGameWindowPtr> > WindowVideoMap;

	WindowVideoMap m_playingVideos;
};

Int Rva00498960WindowVideoManager::getWinState( GameWindow *win )
{
	WindowVideoMap::iterator it = m_playingVideos.find(win);
	if(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			// retail: WindowVideo::m_state at +0x10, not this tree's +0x14.
			return *reinterpret_cast<int *>(reinterpret_cast<char *>(winVid) + 0x10);
	}
	return WINDOW_VIDEO_STATE_STOP;
}
