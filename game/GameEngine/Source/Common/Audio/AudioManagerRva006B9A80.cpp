// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Open-BFME: 22-byte thiscall wrapper at 0x006B9A80. Forwards the event and
// a stack int through AudioManager::addAudioEventEx with two literal ones.
// Sits after the virtual addAudioEvent thunk at 0x006B9A40 and passes this
// through to addAudioEventEx, so the receiver is AudioManager. callers_of
// finds no named caller, so the method name stays address-derived.

class AudioEventRTS;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	unsigned int rva006B9A80(const AudioEventRTS *event, int extra);
};

extern "C" void __cdecl __identifier("?j_00020b08@@YAXXZ")();

// ?rva006B9A80@AudioManager@@QAEIPBVAudioEventRTS@@H@Z
unsigned int AudioManager::rva006B9A80(const AudioEventRTS *event, int extra)
{
	union { void (*raw)(); unsigned int (AudioManager::*member)(const AudioEventRTS *, int, int, int); }
		dispatch = { __identifier("?j_00020b08@@YAXXZ") };
	return (this->*dispatch.member)(event, 1, 1, extra);
}
