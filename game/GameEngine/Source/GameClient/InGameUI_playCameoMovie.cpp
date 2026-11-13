// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// InGameUI::playCameoMovie, retail RVA 0x00441AF0, 273 bytes (ret 4);
// tools/ilt_oracle.py CONFIRMS the decoration at its ILT 0x00006F69. Zero
// Hour's body (GameClient/InGameUI.cpp) with BFME's video interfaces: the
// player opens the stream from a by-value name plus a zero, the stream takes
// the display's new video buffer through its slot +0x38 (failure stops the
// movie), and the right-HUD window's instance data gets the buffer the UI
// already holds at +0x564.

#include "ascii_string.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class VideoBuffer;

class VideoStreamInterface
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	// Slot +0x38 takes the new video buffer; false means it was refused.
	virtual bool rva00441AF0Slot38(VideoBuffer *buffer);
};

class VideoPlayer
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual VideoStreamInterface *open(AsciiString movieTitle, int flags);
};
class VideoPlayerInterface;
extern VideoPlayerInterface *TheVideoPlayer;

class Display
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual VideoBuffer *createVideoBuffer(int type);
};
extern Display *TheDisplay;

class WinInstanceData
{
public:
	void setVideoBuffer(VideoBuffer *buffer);
};

class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
};

class GameWindowManager
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08c();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09c();
	virtual void v0a0();
	virtual void v0a4();
	virtual void v0a8();
	virtual void v0ac();
	virtual void v0b0();
	virtual void v0b4();
	virtual void v0b8();
	virtual void v0bc();
	virtual void v0c0();
	virtual void v0c4();
	virtual void v0c8();
	virtual void v0cc();
	virtual void v0d0();
	virtual void v0d4();
	virtual void v0d8();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, int id);
};
extern GameWindowManager *TheWindowManager;

class InGameUI
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08c();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09c();
	virtual void v0a0();
	virtual void v0a4();
	virtual void v0a8();
	virtual void v0ac();
	virtual void v0b0();
	virtual void v0b4();
	virtual void v0b8();
	virtual void v0bc();
	virtual void v0c0();
	virtual void v0c4();
	virtual void v0c8();
	virtual void v0cc();
	virtual void v0d0();
	virtual void v0d4();
	virtual void v0d8();
	virtual void v0dc();
	virtual void v0e0();
	virtual void v0e4();
	virtual void v0e8();
	virtual void v0ec();
	virtual void v0f0();
	virtual void v0f4();
	virtual void v0f8();
	virtual void v0fc();
	virtual void v100();
	virtual void v104();
	virtual void v108();
	virtual void v10c();
	virtual void v110();
	virtual void v114();
	virtual void v118();
	virtual void v11c();
	virtual void v120();
	virtual void v124();
	virtual void v128();
	virtual void v12c();
	virtual void v130();
	virtual void v134();
	virtual void v138();
	virtual void v13c();
	virtual void v140();
	virtual void stopCameoMovie();
	virtual void v148();
	virtual void playCameoMovie(const AsciiString &movieName);

private:
	unsigned char m_unmodelled_004[0x564 - 4];
	VideoBuffer *m_cameoVideoBuffer;			// +0x564
	VideoStreamInterface *m_cameoVideoStream;	// +0x568
};

// ?playCameoMovie@InGameUI@@UAEXABVAsciiString@@@Z
void InGameUI::playCameoMovie(const AsciiString &movieName)
{
	stopCameoMovie();
	m_cameoVideoStream = reinterpret_cast<VideoPlayer *>(TheVideoPlayer)->open(movieName, 0);
	if (m_cameoVideoStream == 0)
		return;

	if (!m_cameoVideoStream->rva00441AF0Slot38(TheDisplay->createVideoBuffer(0)))
	{
		stopCameoMovie();
		return;
	}

	GameWindow *window = TheWindowManager->winGetWindowFromId(0,
		TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:RightHUD").str()));
	WinInstanceData *winData = window->winGetInstanceData();
	winData->setVideoBuffer(m_cameoVideoBuffer);
}
