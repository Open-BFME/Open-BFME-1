// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: byte-exact clean C++ implementation of the retail
// WindowVideoManager::stopAllMovies, retail 0x00499310, 234 bytes.
//
// BFME's WindowVideo dropped the video-stream member that ZH keeps between
// the buffer and the name (same finding already recorded in
// GUI/WindowVideo_ctor.cpp and GUI/WindowVideo_dtor.cpp), so m_state sits at
// +0x10 rather than the reference's +0x14. setWindowState() is inlined at
// this call site exactly as ZH wrote it -- both if-blocks reload m_state
// from memory instead of reusing the value that was just stored, which is
// why the (dead, for a literal STOP argument) PLAY/PAUSE branch still shows
// up in the compiled bytes.
//
// Call shape recovered from the bytes: winGetInstanceData() takes NO stack
// argument (matches game_window.h's real declaration and WindowVideo_dtor's
// model) while setVideoBuffer() takes ONE argument that BFME changed from a
// VideoBuffer* to an int handle -- 0 to clear it, or the video buffer's own
// vtable+0x3c useBuffer() accessor (same slot GUI/WindowVideo_init_bfme.cpp
// already pinned) to set it. The pushed argument is evaluated before the
// winGetInstanceData() call in both branches, same evaluation-order note
// already recorded in WindowVideo_dtor.cpp.

#include <map>
#include <hash_map>

#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"
#include "window_video_manager.h"
#include "game_window.h"
#include "video_player.h"
#include "display.h"

namespace BfmeStopAllMovies
{
	class VideoBuffer
	{
	public:
		virtual void slot00();
		virtual void slot01();
		virtual void slot02();
		virtual void slot03();
		virtual void slot04();
		virtual void slot05();
		virtual void slot06();
		virtual void slot07();
		virtual void slot08();
		virtual void slot09();
		virtual void slot10();
		virtual void slot11();
		virtual void slot12();
		virtual void slot13();
		virtual void slot14();
		virtual int useBuffer();			// slot 15, vtable+0x3c
	};

	class WinInstanceData
	{
	public:
		void setVideoBuffer( int bufferHandle );		// ILT 0x0002E073
	};

	class GameWindow
	{
	public:
		WinInstanceData *winGetInstanceData( void );		// ILT 0x00034991
	};

	// TU-local view of the real BFME WindowVideo layout -- only the fields
	// setWindowState touches, cast in from the header's (ZH-shaped) WindowVideo*.
	class WindowVideo
	{
	public:
		void setWindowState( WindowVideoStates state )
		{
			m_state = state;

			if ( m_state == WINDOW_VIDEO_STATE_STOP && m_win )
				m_win->winGetInstanceData()->setVideoBuffer( 0 );

			if ( ( m_state == WINDOW_VIDEO_STATE_PLAY || m_state == WINDOW_VIDEO_STATE_PAUSE ) && m_win )
				m_win->winGetInstanceData()->setVideoBuffer( m_videoBuffer->useBuffer() );
		}

	private:
		WindowVideoPlayType m_playType;
		GameWindow *m_win;
		VideoBuffer *m_videoBuffer;
		void *m_movieName;
		WindowVideoStates m_state;
	};
}

void WindowVideoManager::stopAllMovies( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();
	//Iterate through the maps
	while(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			((BfmeStopAllMovies::WindowVideo *)winVid)->setWindowState(WINDOW_VIDEO_STATE_STOP);
		it++;
	}

	m_stopAllMovies = TRUE;
	m_pauseAllMovies = FALSE;
}
