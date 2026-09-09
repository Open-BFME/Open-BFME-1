// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: byte-exact clean C++ implementation of the retail
// WindowVideoManager::resumeMovie, retail 0x00498810, 119 bytes.
//
// Sibling of WindowVideoManagerStopAllMovies.cpp / PauseAllMovies.cpp /
// ResumeAllMovies.cpp -- same BFME WindowVideo layout (no video-stream
// member, m_state at +0x10) and the same inlined setWindowState() shape,
// called here with WINDOW_VIDEO_STATE_PLAY, but reached through a single
// hash_map find(win) (inlined by MSVC into the div/mod bucket lookup) rather
// than iterating m_playingVideos, matching the already-landed hideMovie's
// find()-based shape (window_video_manager.cpp). MSVC duplicates the
// trailing m_pauseAllMovies/m_stopAllMovies clears (and the epilogue) once
// for the "not found" fast path and once for the "found and processed" path.

#include <map>
#include <hash_map>

#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"
#include "window_video_manager.h"
#include "game_window.h"
#include "video_player.h"
#include "display.h"

namespace BfmeResumeMovie
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

void WindowVideoManager::resumeMovie( GameWindow *win )
{
	WindowVideoMap::iterator it = m_playingVideos.find(win);
	if(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			((BfmeResumeMovie::WindowVideo *)winVid)->setWindowState(WINDOW_VIDEO_STATE_PLAY);
	}
	m_pauseAllMovies = FALSE;
	m_stopAllMovies = FALSE;
}
