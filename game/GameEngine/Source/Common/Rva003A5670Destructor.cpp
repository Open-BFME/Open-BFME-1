// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"
#include <vector>

#include "System/snapshot.h"

extern int g_010EC738;

// Direct destructor ABI through the existing address-derived ILT pin.
class Gen_dtor_003a3d90
{
public:
    virtual ~Gen_dtor_003a3d90();
};

class Rva003A5250Element
{
public:
    ~Rva003A5250Element()
    {
        m_fieldA.clear();
        m_fieldB.clear();
    }
    float m_at00;
    float m_at04;
    AsciiString m_fieldA;
    AsciiString m_fieldB;
    float m_at10;
};

template<> _STL::vector<Rva003A5250Element>::~vector();

// The static helper accesses native vector storage through pointers to members.
class Rva003A5670VectorAccess : public _STL::vector<Rva003A5250Element>
{
public:
    // ?eraseAll@Rva003A5670VectorAccess@@SAXAAV?$vector@VRva003A5250Element@@V?$allocator@VRva003A5250Element@@@_STL@@@_STL@@@Z absent-from-retail
    static __forceinline void eraseAll(_STL::vector<Rva003A5250Element> &values)
    {
        Rva003A5250Element *newFinish = _STL::__copy(values.*&Rva003A5670VectorAccess::_M_finish, values.*&Rva003A5670VectorAccess::_M_finish, values.*&Rva003A5670VectorAccess::_M_start, _STL::random_access_iterator_tag(), (int *)0);
        _STL::_Destroy(newFinish, values.*&Rva003A5670VectorAccess::_M_finish);
        values.*&Rva003A5670VectorAccess::_M_finish = newFinish;
    }
};

class Rva003A5670AudioView
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38();
    virtual void slot3c(); virtual void slot40(); virtual void slot44();
    virtual void slot48(); virtual void slot4c(unsigned int value);
};
class AudioManager;
extern AudioManager *TheAudio;

class Rva003A5670Owner : public Snapshot
{
public:
    virtual ~Rva003A5670Owner();
    AsciiString m_at04;
    AsciiString m_at08;
    unsigned char m_pad0c[0x18];
    unsigned int m_at24;
    _STL::vector<Rva003A5250Element> m_at28;
    AsciiString m_at34;
    unsigned char m_pad38[8];
    AsciiString m_at40;
    unsigned char m_pad44[4];
    _STL::vector<Gen_dtor_003a3d90 *> m_at48;
};

// Evidence: targets/game/reverse/identity_evidence/003a5670-destructor.md
// ??1Rva003A5670Owner@@UAE@XZ
Rva003A5670Owner::~Rva003A5670Owner()
{
    // Install the dispatch table already recorded for the constructor.
    *reinterpret_cast<void **>(this) = &g_010EC738;
    for (unsigned int i = 0; i < m_at48.size(); ++i)
    {
        Gen_dtor_003a3d90 *item = m_at48[i];
        if (item)
        {
            item->Gen_dtor_003a3d90::~Gen_dtor_003a3d90();
            ::operator delete(item);
        }
    }
    Rva003A5670VectorAccess::eraseAll(m_at28);
    if (TheAudio && m_at24 != 1)
        reinterpret_cast<Rva003A5670AudioView *>(TheAudio)->slot4c(m_at24);
}
