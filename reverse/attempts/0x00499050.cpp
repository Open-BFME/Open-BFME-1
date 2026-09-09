// ?update@WindowVideoManager@@UAEXXZ
// partial score=0.82 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: byte-exact clean C++ implementation of the retail
// WindowVideoManager::update, retail 0x00499050, 301 bytes.
//
// Sibling of WindowVideoManagerStopAllMovies.cpp / PauseAllMovies.cpp /
// ResumeAllMovies.cpp -- same BFME WindowVideo layout (no video-stream
// member, m_state at +0x10). BFME also folded VideoStreamInterface's
// frame-advance API directly into VideoBuffer, so the ZH source's
// isFrameReady/frameDecompress/frameRender/frameNext/frameIndex chain
// collapses to two VideoBuffer virtuals here: slot06 (vtable+0x18, takes
// an int mode and returns a Bool) and slot08 (vtable+0x20, no args,
// returns Int) -- called through the same useBuffer() accessor (slot15,
// vtable+0x3c) already pinned in GUI/WindowVideo_init_bfme.cpp.

#include <map>
#include <hash_map>

#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"
#include "window_video_manager.h"
#include "game_window.h"
#include "video_player.h"
#include "display.h"

namespace BfmeUpdate
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
		virtual Bool slot06( Int mode );		// slot 6, vtable+0x18
		virtual void slot07();
		virtual Int  slot08();					// slot 8, vtable+0x20
		virtual void slot09();
		virtual void slot10();
		virtual void slot11();
		virtual void slot12();
		virtual void slot13();
		virtual void slot14();
		virtual int useBuffer();				// slot 15, vtable+0x3c
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
		Bool winIsHidden( void );				// ILT 0x0003A5B7
	};

	// TU-local view of the real BFME WindowVideo layout -- only the fields
	// update() touches, cast in from the header's (ZH-shaped) WindowVideo*.
	class WindowVideo
	{
	public:
		WindowVideoPlayType getPlayType( void ) { return m_playType; }
		GameWindow *getWin( void ) { return m_win; }
		VideoBuffer *getVideoBuffer( void ) { return m_videoBuffer; }
		WindowVideoStates getState( void ) { return m_state; }

	private:
		WindowVideoPlayType m_playType;
		GameWindow *m_win;
		VideoBuffer *m_videoBuffer;
		void *m_movieName;
		WindowVideoStates m_state;
	};
}

void WindowVideoManager::update( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();

	if ( m_pauseAllMovies || m_stopAllMovies )
		return;

	while ( it != m_playingVideos.end() )
	{
		BfmeUpdate::WindowVideo *winVid = (BfmeUpdate::WindowVideo *)it->second;

		if ( !winVid )
		{
			DEBUG_CRASH(("There's No WindowVideo in the m_playignVideos list"));
			return;
		}
		BfmeUpdate::GameWindow *win = winVid->getWin();

		if ( winVid->getState() == WINDOW_VIDEO_STATE_HIDDEN && ( win->winIsHidden() == FALSE ) )
			resumeMovie( (GameWindow *)win );

		if ( winVid->getState() == WINDOW_VIDEO_STATE_PLAY && win->winIsHidden() )
			hideMovie( (GameWindow *)win );

		if ( winVid->getState() != WINDOW_VIDEO_STATE_PLAY )
		{
			it++;
			continue;
		}

		BfmeUpdate::VideoBuffer *videoBuffer = winVid->getVideoBuffer();
		Int handle = videoBuffer ? videoBuffer->useBuffer() : 0;

		if ( videoBuffer && handle )
		{
			if ( winVid->getPlayType() == WINDOW_PLAY_MOVIE_LOOP )
			{
				videoBuffer->slot06( 4 );
			}
			else if ( videoBuffer->slot06( 0 ) )
			{
				if ( videoBuffer->slot08() == 0 )
				{
					if ( winVid->getPlayType() == WINDOW_PLAY_MOVIE_ONCE )
						stopMovie( (GameWindow *)win );
					else if ( winVid->getPlayType() == WINDOW_PLAY_MOVIE_SHOW_LAST_FRAME )
						pauseMovie( (GameWindow *)win );
				}
			}
		}

		it++;
	}
}
