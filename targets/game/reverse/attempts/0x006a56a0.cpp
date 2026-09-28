// ?d_006a56a0@@YAXXZ
// partial score=0.862 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport
#define _STLP_USE_OWN_NAMESPACE 1
#include <deque>
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);
class Rva00087750Counted
{
public:
    virtual ~Rva00087750Counted();
    void Release_Ref() { if (InterlockedDecrement(&m_refCount) <= 0) delete this; }
    long m_refCount;
};
class Rva00087750Ref
{
public:
    Rva00087750Ref &operator=(const Rva00087750Ref &rhs);
    ~Rva00087750Ref() { if (m_ptr) m_ptr->Release_Ref(); }
private:
    Rva00087750Counted *m_ptr;
};
typedef _STL::deque<Rva00087750Ref> PlayingAudioDeque;
struct OwnerValue { unsigned char pad[0x3c]; int value3c; };
struct AudioValue { unsigned char pad[0x28]; float value28; unsigned char pad2c[8]; unsigned char flag34; unsigned char flag35; };
struct DequeIteratorView { Rva00087750Ref * volatile cur; Rva00087750Ref *first; Rva00087750Ref *last; Rva00087750Ref **node; };
struct DequeView { DequeIteratorView start; DequeIteratorView finish; };
struct OwnerValue;
class Rva006A56A0
{
public:
    void rva006A56A0(int a, int b, int c);
private:
    unsigned char pad000[0x0c];
    OwnerValue *owner;
    unsigned char pad010[0x9c4];
    PlayingAudioDeque cells[6];
    int map[3];
    Rva00087750Ref current[3];
};
void Rva006A56A0::rva006A56A0(int a, int b, int c)
{
    PlayingAudioDeque &cell = cells[b + a * 2];
    DequeView *view = (DequeView *)&cell;
    Rva00087750Ref *finish = view->finish.cur;
    Rva00087750Ref *start = view->start.cur;
    if (finish == start) return;
    Rva00087750Ref &currentRef = current[a];
    currentRef = cell.back();
    AudioValue * volatile *audioSlot = (AudioValue * volatile *)&currentRef;
    AudioValue *audio = *audioSlot;
    if (c == 0) {
        if (audio->flag34) { audio->flag34 = 0; (*audioSlot)->flag35 = 1; }
        else { audio->value28 = (float)owner->value3c; (*audioSlot)->flag35 = 1; }
    } else { audio->flag34 = 0; (*audioSlot)->flag35 = 0; (*audioSlot)->value28 = 0; }
    cell.pop_back();
}
