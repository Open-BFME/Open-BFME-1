// ?rva00694130@Rva00694710AudioWorker@@QAE?AVRva006910F0Handle@@ABVAudioEventRef@@H@Z
// Native 203-byte body. The filename temporary binds to the helper by const reference.
// Identity and ABI: targets/game/reverse/identity_evidence/20261003-audio-worker-reference-abi.md
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /I.
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
struct AudioEventInfo { char pad0[0x84]; int m_soundType; };
class RvaAudioEventFilenameForPortion { public: AsciiString getFilenameForPlayPortion(); };
class AudioEventRTS { public: char pad0[8]; AudioEventInfo *m_eventInfo; };
class AudioEventRef { public: AudioEventRTS *ptr; };
class Gen006BA220;
class Rva006910F0Handle
{
public:
 Rva006910F0Handle();
 ~Rva006910F0Handle();
 Gen006BA220 *m_receiver;
};
class Rva00694710AudioWorker
{
public:
 Rva006910F0Handle rva00694130(const AudioEventRef &event,int value);
 Rva006910F0Handle rva00693B90(const AsciiString &filename,int value);
};
Rva006910F0Handle Rva00694710AudioWorker::rva00694130(const AudioEventRef &event,int value)
{
 AudioEventRTS *e=event.ptr;
 if(!e) return Rva006910F0Handle();
 if(!e->m_eventInfo) return Rva006910F0Handle();
 if(e->m_eventInfo->m_soundType!=2) return Rva006910F0Handle();
 return rva00693B90(reinterpret_cast<RvaAudioEventFilenameForPortion *>(e)->getFilenameForPlayPortion(),value);
}
