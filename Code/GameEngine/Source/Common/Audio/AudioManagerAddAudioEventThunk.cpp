// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// readable body of ?addAudioEvent@AudioManager@@: Code/GameEngine/Source/Common/Audio/GameAudio.cpp

// Open-BFME5: AudioManager::addAudioEvent
// Retail 19B: push defaults (1,1,0) then event; thiscall impl; ret 4.

class AudioEventRTS;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual unsigned int addAudioEvent(const AudioEventRTS *event);
	unsigned int addAudioEventEx(const AudioEventRTS *event, int a, int b, int c);
};

// ?addAudioEvent@AudioManager@@UAEIPBVAudioEventRTS@@@Z
unsigned int AudioManager::addAudioEvent(const AudioEventRTS *event)
{
	return addAudioEventEx(event, 0, 1, 1);
}
