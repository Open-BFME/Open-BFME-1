// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x006A6F00: STLport deque<PlayingAudioRef>::erase(iterator).
// The verified MilesAudioManager::rva006A8DC0 caller supplies a deque at
// this+0x9d4+k*0x28, a hidden result pointer and a 16-byte iterator.
// Retail copy/copy_backward reach 0x0069F1C0/0x0069CC60, which retain the
// incoming pointee before releasing the old one. The 128-byte block helpers
// at 0x0069E810 and 0x0069E880 use this same four-byte reference element.

#include <deque>

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);

class RefCountedPlayingAudio
{
public:
    virtual ~RefCountedPlayingAudio();

    void Add_Ref() { InterlockedIncrement(&m_refCount); }
    void Release_Ref()
    {
        if (InterlockedDecrement(&m_refCount) <= 0)
            delete this;
    }

private:
    long m_refCount;
};

// Only the counted base is accessed by these element operations.
class PlayingAudio : public RefCountedPlayingAudio {};

class PlayingAudioRef
{
public:
    PlayingAudioRef() : m_ptr(0) {}
    PlayingAudioRef(const PlayingAudioRef &other) : m_ptr(other.m_ptr)
    {
        if (m_ptr)
            m_ptr->Add_Ref();
    }
    ~PlayingAudioRef()
    {
        if (m_ptr)
            m_ptr->Release_Ref();
    }
    PlayingAudioRef &operator=(const PlayingAudioRef &other)
    {
        if (this != &other)
        {
            if (other.m_ptr)
                other.m_ptr->Add_Ref();
            if (m_ptr)
                m_ptr->Release_Ref();
            m_ptr = other.m_ptr;
        }
        return *this;
    }

private:
    PlayingAudio *m_ptr;
};

template _STL::deque<PlayingAudioRef>::iterator
_STL::deque<PlayingAudioRef>::erase(_STL::deque<PlayingAudioRef>::iterator);
