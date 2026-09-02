// cl: /DNDEBUG /MD /EHsc
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

class AsciiString
{
public:
	AsciiString() : m_text( 0 ) {}
	~AsciiString();
	void clear() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_text;
};

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
