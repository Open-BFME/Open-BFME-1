// cl: /DNDEBUG /DWIN32 /MD /EHsc
// UnitHelpText retail adapter at 0x004B2470. Identity remains address-derived.
// Matched Rva004B2300 copy constructor owns vtable 0x010F5738.
// Its six-slot table has this owning clone operation at slot 1.
// Local donor: ControlBarRva004C1B60.cpp slot04 at 0x004C1AE0.
// The return handle transfers ownership and deletes through virtual slot 0.
class Rva004B2470Handle;
class Rva004B2300Base {
public:
 virtual ~Rva004B2300Base() {}
 virtual Rva004B2470Handle clone() = 0;
 virtual void slot08() = 0;
 virtual void slot0C() = 0;
 virtual void slot10() = 0;
 virtual void slot14() = 0;
};
class Rva004B2470Handle {
public:
 Rva004B2470Handle(Rva004B2300Base *p):m_ptr(p) {}
 Rva004B2470Handle(Rva004B2470Handle &other):m_ptr(other.release()) {}
 ~Rva004B2470Handle() { delete m_ptr; }
 Rva004B2300Base *release() { Rva004B2300Base *p=m_ptr;m_ptr=0;return p; }
private:
 Rva004B2300Base *m_ptr;
};
class Rva004B2300:public Rva004B2300Base {
public:
 virtual ~Rva004B2300() {}
 virtual Rva004B2470Handle clone();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 int m_04;int m_08;
};
Rva004B2470Handle Rva004B2300::clone()
{
 Rva004B2470Handle h(new Rva004B2300(*this));
 return h;
}
