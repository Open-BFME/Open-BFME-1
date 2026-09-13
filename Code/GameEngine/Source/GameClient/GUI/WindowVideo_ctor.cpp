// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// WindowVideo::WindowVideo, retail 0x00498130. BFME dropped the video-stream
// pointer that sits between the buffer and the name in the reference layout.

typedef int Int;

enum WindowVideoPlayType
{
	WINDOW_PLAY_MOVIE_ONCE = 0
};

enum WindowVideoStates
{
	WINDOW_VIDEO_STATE_STOP = 1
};

class GameWindow;
class VideoBuffer;

#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowVideoManager.h
class WindowVideo
{
public:
	WindowVideo( void );

private:
	WindowVideoPlayType m_playType;
	GameWindow *m_win;
	VideoBuffer *m_videoBuffer;
	AsciiString m_movieName;
	WindowVideoStates m_state;
};

WindowVideo::WindowVideo( void )
{
	m_playType = WINDOW_PLAY_MOVIE_ONCE;
	m_win = 0;
	m_videoBuffer = 0;
	m_movieName.clear();
	m_state = WINDOW_VIDEO_STATE_STOP;
}
