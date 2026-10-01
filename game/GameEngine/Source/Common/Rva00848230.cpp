// Borrowed address views of two unrelated receivers. No native owner identity,
// complete interface, constructor, destructor or receiver lifetime is claimed.
// Each forwards physical argument words to the receiver's vtable then returns p1.
// Pointer spellings preserve word transport; pointee identities and the native
// parameter/slot return types are unproven. Uncalled pure slots reserve offsets
// only; their prototypes describe no observed native call. No object is created.
class Rva00848230
{
    virtual void slot00() = 0;
    virtual void slot04(void *, void *, void *, void *, void *, void *, void *) = 0;
public:
    void *method(void *, void *, void *, void *, void *, void *, void *);
};
void *Rva00848230::method(void *p1, void *p2, void *p3, void *p4, void *p5, void *p6, void *p7)
{
    slot04(p1, p2, p3, p4, p5, p6, p7);
    return p1;
}
class Rva00848260
{
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08(void *, void *, void *, void *, void *, void *, void *, void *, void *) = 0;
public:
    void *method(void *, void *, void *, void *, void *, void *, void *, void *, void *);
};
void *Rva00848260::method(void *p1, void *p2, void *p3, void *p4, void *p5, void *p6, void *p7, void *p8, void *p9)
{
    slot08(p1, p2, p3, p4, p5, p6, p7, p8, p9);
    return p1;
}
