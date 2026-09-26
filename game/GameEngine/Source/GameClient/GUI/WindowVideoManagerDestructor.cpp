// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/GameClient /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: byte-exact clean C++ implementation of the retail destructor.

#include <map>
#include <hash_map>

#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"
#include "window_video_manager.h"
#include "game_window.h"
#include "video_player.h"
#include "display.h"

WindowVideoManager::~WindowVideoManager( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();
	while(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			delete winVid;
		it++;
	}
	m_playingVideos.clear();
}
