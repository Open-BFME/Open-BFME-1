// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: byte-exact clean C++ implementation of the retail
// WindowVideoManager::resumeAllMovies, retail 0x00499530, 184 bytes.
//
// Sibling of WindowVideoManagerStopAllMovies.cpp / WindowVideoManagerPauseAllMovies.cpp
// -- same BFME WindowVideo layout (no video-stream member, m_state at +0x10)
// and the same inlined setWindowState() shape, called here with
// WINDOW_VIDEO_STATE_PLAY. Both trailing flag stores are FALSE (0) here, so
// MSVC hoists a single zero register (ebx) and reuses it for both the null
// tests and both byte stores -- codegen only, no source change needed.

#include <map>
#include <hash_map>

#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"
#include "window_video_manager.h"
#include "game_window.h"
#include "video_player.h"
#include "display.h"

namespace BfmeResumeAllMovies
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

void WindowVideoManager::resumeAllMovies( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();
	//Iterate through the maps
	while(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			((BfmeResumeAllMovies::WindowVideo *)winVid)->setWindowState(WINDOW_VIDEO_STATE_PLAY);
		it++;
	}
	m_stopAllMovies = FALSE;
	m_pauseAllMovies = FALSE;
}
