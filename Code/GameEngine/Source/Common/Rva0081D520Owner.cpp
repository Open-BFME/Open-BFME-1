// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

typedef int Int;
typedef float Real;
class Rva0081D520Owner;
class Rva0081D520Listener
{
public:
    virtual void unknown0();
    virtual void receive(Int value, Rva0081D520Owner *owner,
                         Real x0, Real y0, Real x1, Real y1);
};
class Rva0081D520Owner
{
public:
    void broadcast(Int value, Real x0, Real y0, Real x1, Real y1);
private:
    unsigned char unmodelled[0x14];
    Rva0081D520Listener **begin;
    Rva0081D520Listener **end;
};
void Rva0081D520Owner::broadcast(Int value, Real x0, Real y0, Real x1, Real y1)
{
    for (unsigned i = 0; i < (unsigned)(end - begin); ++i)
        begin[i]->receive(value, this, x0, y0, x1, y1);
}
