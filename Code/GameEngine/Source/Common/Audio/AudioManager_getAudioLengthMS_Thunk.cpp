// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline
#include "StringInline.h"
class AudioEventInfo;
class AudioEventRTS { public: AudioEventRTS(const AudioEventRTS &); ~AudioEventRTS(); void bfmeGenerateFilename(); void generatePlayInfo(); AsciiString getFilename(); AsciiString getAttackFilename() const; AsciiString getDecayFilename() const; const AudioEventInfo *getAudioEventInfo() const { return m_eventInfo; } private: void *m_vtable; unsigned char m_filename[4]; mutable AudioEventInfo *m_eventInfo; unsigned char m_rest[0x70-0x0c]; };
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *);
class AudioManagerMutex { public: __forceinline AudioManagerMutex(void *mutex) { m_held=0; m_mutex=mutex; if (WaitForSingleObject(m_mutex,0xffffffffu)!=0x102u) m_held=1; } __forceinline ~AudioManagerMutex() { if(m_held) { ReleaseMutex(m_mutex); m_held=0; } } private: void *m_mutex; unsigned char m_held; };
class AudioManager { public:
#define SLOT(n) virtual void slot##n();
SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42)
#undef SLOT
virtual void getInfoForAudioEvent(const AudioEventRTS *) const; virtual float getAudioLengthMS(const AudioEventRTS *); float getFileLengthMS(AsciiString) const; private: unsigned char m_pad[0x95c-4]; void *m_mutex; };
float AudioManager::getAudioLengthMS(const AudioEventRTS *event) { AudioManagerMutex guard(m_mutex); if(!event->getAudioEventInfo()) { getInfoForAudioEvent(event); if(!event->getAudioEventInfo()) return 0.0f; } AudioEventRTS tmpEvent=*event; tmpEvent.bfmeGenerateFilename(); tmpEvent.generatePlayInfo(); return getFileLengthMS(tmpEvent.getAttackFilename()) + getFileLengthMS(tmpEvent.getFilename()) + getFileLengthMS(tmpEvent.getDecayFilename()); }
