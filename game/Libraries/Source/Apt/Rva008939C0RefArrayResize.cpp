// cl: /O2 /DNDEBUG /MD /EHsc
#include <new>
extern void *(__cdecl *WideAllocPtr)(unsigned);
extern void (__cdecl *g_bfmeFreeDWF)(void *);
class Rva00894D90Accessor { public: static unsigned decrement(unsigned *); };
class Rva00894D80Accessor { public: static unsigned increment(unsigned *); };
void bfmeDropA(void *value);
class Rva008947A0Elem;
class BfmeElemCU {
protected:
    void *m_value;
public:
    typedef Rva008947A0Elem ArrayElement;
    BfmeElemCU &operator=(const BfmeElemCU &other) {
        if (&other != this) {
            if (m_value && !Rva00894D90Accessor::decrement((unsigned *)m_value))
                bfmeDropA(m_value);
            m_value = other.m_value;
            if (m_value) Rva00894D80Accessor::increment((unsigned *)m_value);
        }
        return *this;
    }
    BfmeElemCU();
    ~BfmeElemCU();
};
class Rva008947A0Elem : public BfmeElemCU {
public:
    Rva008947A0Elem();
    ~Rva008947A0Elem();
    static void *operator new[](unsigned bytes) throw() { return WideAllocPtr(bytes); }
    static void operator delete[](void *value) throw() { g_bfmeFreeDWF(value); }
};
// ?Rva008939C0@@YAPAXPAVBfmeElemCU@@HH@Z
// Open BFME 2: Code/Libraries/Source/Apt/AptRefArrayResize.cpp.
void *Rva008939C0(BfmeElemCU *source, int oldCount, int newCount) {
    if (!source) return new BfmeElemCU::ArrayElement[newCount];
    BfmeElemCU *fresh = 0;
    if (newCount) {
        fresh = new BfmeElemCU::ArrayElement[newCount];
        int count = newCount < oldCount ? newCount : oldCount;
        BfmeElemCU *destination = fresh;
        while (count) { *destination++ = *source++; --count; }
    }
    delete[] (BfmeElemCU::ArrayElement *)source;
    return fresh;
}
