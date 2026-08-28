#pragma once
#include "ascii_string.h"
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/VideoPlayer.h
class VideoBuffer {
public:
	int allocate(unsigned int w, unsigned int h);
	void close(void);
	unsigned int width(void);
	unsigned int height(void);
};
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/VideoPlayer.h
class VideoStreamInterface {
public:
	void close(void);
	void update(void);
	int isFrameReady(void);
	void frameDecompress(void);
	void frameRender(VideoBuffer*);
	void frameNext(void);
	int frameIndex(void);
	unsigned int width(void);
	unsigned int height(void);
};
class VideoPlayerInterface { public: VideoStreamInterface* open(AsciiString); VideoStreamInterface* load(AsciiString); };
extern VideoPlayerInterface* TheVideoPlayer;
