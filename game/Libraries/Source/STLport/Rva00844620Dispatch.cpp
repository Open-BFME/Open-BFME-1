// cl: /O2 /Ob0
// Each body is complete and independently bounded by int3 padding.
// Opaque virtual tail routes: only slot offsets are known. The tail jump
// preserves the incoming stack and the callee's result without interpretation.
struct Rva00844620 {
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    void forward();
};
void Rva00844620::forward() { slot14(); }
struct Rva00844630 {
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C(); virtual void slot20();
    virtual void slot24(); void forward();
};
void Rva00844630::forward() { slot24(); }
struct Rva00844640 { char pad00[0x44]; unsigned int field44; unsigned int value() const; };
unsigned int Rva00844640::value() const { return field44; }
struct Rva00844650 { void *value(); };
void *Rva00844650::value() { return (char *)this + 0x48; }
struct Rva00844660 { virtual void slot00(); virtual void slot04(); void forward(); };
void Rva00844660::forward() { slot04(); }
struct Rva00844670 { virtual void slot00(); virtual void slot04(); virtual void slot08(); void forward(); };
void Rva00844670::forward() { slot08(); }
struct Rva00844680 { virtual void slot00(); virtual void slot04(); void forward(); };
void Rva00844680::forward() { slot04(); }
struct Rva00844690 { virtual void slot00(); virtual void slot04(); virtual void slot08(); void forward(); };
void Rva00844690::forward() { slot08(); }
