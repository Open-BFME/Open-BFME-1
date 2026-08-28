#pragma once
class VideoBuffer;
class WinInstanceData { public: void setVideoBuffer(VideoBuffer*); };
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow {
public:
	WinInstanceData* winGetInstanceData(void);
	int winIsHidden(void);
};
