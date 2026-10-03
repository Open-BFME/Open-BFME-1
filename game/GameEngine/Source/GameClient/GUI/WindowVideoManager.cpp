// cl: /DNDEBUG /MD /EHsc
// Retail 0x00498240.  BFME's WindowVideo init takes four stack arguments.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../game_window.h"

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
	virtual int useBuffer();
};

enum WindowVideoPlayType
{
	WINDOW_PLAY_MOVIE_ONCE = 0
};

class WindowVideo
{
public:
	void init( GameWindow *win, AsciiString movieName,
		WindowVideoPlayType playType, VideoBuffer *videoBuffer );

private:
	WindowVideoPlayType m_playType;
	GameWindow *m_win;
	VideoBuffer *m_videoBuffer;
	AsciiString m_movieName;
	int m_state;
};

void WindowVideo::init( GameWindow *win, AsciiString movieName,
	WindowVideoPlayType playType, VideoBuffer *videoBuffer )
{
	m_win = win;
	m_movieName = movieName;
	m_playType = playType;
	m_videoBuffer = videoBuffer;
	m_state = 3;
	if ( m_win )
		m_win->winGetInstanceData()->setVideoBuffer( (VideoBuffer *)videoBuffer->useBuffer() );
}
