// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006A5F20, 280 bytes. The +0x9D0 stream list and +0x14 event
// handle agree with the verified MilesAudioManager and PlayingAudio bodies.
// AudioEventRTS+8 and AudioEventInfo+0x84 agree with the sound-class mapper
// at 0x000B2950. A retained local keeps the current audio alive while the
// release call and list erasure run. Preserve retail's lack of advancement
// for a null element; changing it would change the original behavior.
// The accessor layers and named InterlockedDecrement result preserve the
// register allocation used by retail, including its exception cleanup.

#include <list>
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);
struct AudioEventInfo {
    char pad00[0x84];
    unsigned int m_soundClass;
};
class AudioEventRTS {
public:
    char pad00[8];
    const AudioEventInfo *m_eventInfo;
    const AudioEventInfo *getEventInfo() const { return m_eventInfo; }
};
class RefCountedPlayingAudio {
public:
    virtual ~RefCountedPlayingAudio();
    void Add_Ref() { InterlockedIncrement(&m_refCount); }
    void Release_Ref()
    {
        long count = InterlockedDecrement(&m_refCount);
        if (count <= 0)
            delete this;
    }
    long volatile m_refCount;
};
class PlayingAudio : public RefCountedPlayingAudio {
public:
    char pad08[0x14 - 8];
    AudioEventRTS *m_audioEventRTS;
    AudioEventRTS *getAudioEvent() const { return m_audioEventRTS; }
};
class PlayingAudioRef {
public:
    PlayingAudioRef() : m_ptr(0) {}
    ~PlayingAudioRef() { if(m_ptr) m_ptr->Release_Ref(); }
    PlayingAudioRef& operator=(const PlayingAudioRef &other) {
        if(this!=&other) {
            if(other.m_ptr) other.m_ptr->Add_Ref();
            if(m_ptr) m_ptr->Release_Ref();
            m_ptr=other.m_ptr;
        }
        return *this;
    }
    operator PlayingAudio *() const { return m_ptr; }
    PlayingAudio *operator->() const { return m_ptr; }
private:
    PlayingAudio *m_ptr;
};
// Retail callers use ILT 0x0002669D -> 0x006A59F0, a thiscall with one
// PlayingAudio pointer. The old member declaration had no linked provider.
extern void j_0002669d();
template <class Function>
__forceinline Function rva006A59F0Thunk()
{
    union { void (*raw)(); Function member; } fn;
    fn.raw = j_0002669d;
    return fn.member;
}

class MilesAudioManager {
    char pad000[0x9d0];
    _STL::list<PlayingAudioRef> m_playingStreams;
public:
    void rva006A5F20();
};
void MilesAudioManager::rva006A5F20() {
    PlayingAudioRef audio;
    _STL::list<PlayingAudioRef>::iterator it;
    for(it=m_playingStreams.begin();it!=m_playingStreams.end();) {
        audio=*it;
        if(audio) {
            if(audio->getAudioEvent()->getEventInfo()->m_soundClass==1) {
                (this->*rva006A59F0Thunk<void (MilesAudioManager::*)(PlayingAudio *)>())(audio);
                it=m_playingStreams.erase(it);
            } else ++it;
        }
    }
}
