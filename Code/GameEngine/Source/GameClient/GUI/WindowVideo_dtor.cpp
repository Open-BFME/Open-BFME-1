// cl: /DNDEBUG /MD /EHsc
// Open-BFME: WindowVideo::~WindowVideo, retail 0x004981A0, 116 bytes.
//
// The reference's body without its video-stream half, which BFME does not
// have: clear the window's video buffer without touching the window, drop the
// buffer, and let the name string release itself on the way out.
//
// The window's instance data is fetched after the NULL it will be handed is
// already on the stack, which is the reference's single line compiled in the
// order MSVC evaluates it. The buffer is released through a no-argument
// virtual at vtable+0x1C rather than deleted -- there is no deleting-destructor
// flag pushed -- and slot 7 is five past where the reference has `free`.
//
// Layout: the window at this+0x04, the buffer at +0x08, and an AsciiString at
// +0x0C that the destructor releases last.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class VideoBuffer;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	void setVideoBuffer(VideoBuffer *videoBuffer);		// ILT 0x0002E073
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	WinInstanceData *winGetInstanceData(void);		// ILT 0x00034991
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/VideoPlayer.h
class VideoBuffer
{
public:
	virtual ~VideoBuffer();
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void free(void) = 0;				// slot 7, vtable+0x1C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowVideoManager.h
class WindowVideo
{
public:
	~WindowVideo();

private:
	char m_bfme_head[4];					// this+0x00, untouched
	GameWindow *m_win;					// this+0x04
	VideoBuffer *m_videoBuffer;				// this+0x08
	AsciiString m_movieName;				// this+0x0C
};

WindowVideo::~WindowVideo( void )
{
	// Don't Delete the window, only set it's video buffer to NULL
	if(m_win)
		m_win->winGetInstanceData()->setVideoBuffer( 0 );
	m_win = 0;

	if (m_videoBuffer)
		m_videoBuffer->free();
	m_videoBuffer = 0;

}
