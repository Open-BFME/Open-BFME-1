// Retail 0x007F8730, 95 bytes. Matched bfmeGoDGF factory calls this body.
// The primary vtable 0x0112B8A4 is shared with matched BfmeThingTWA
// deleting destructor 0x007F8970; slots 1/2 are 0x007F8790/0x007F8820.
// Secondary interface at +4: base table 0x0112B89C, derived 0x0112B8A0.
// The +0x10 value has the observed 16-byte prefix of the existing
// Rva00808CB0LanGameEntry view. Ordinary constructors explain the interleaved
// vtable stores and ECX setup; no volatile fields or hand-written vptrs.
// cl: /O2 /GX-
class Rva007E86B0Base {
public:
 Rva007E86B0Base();
 virtual ~Rva007E86B0Base();
 int field04;
};
class Rva00808CB0LanGameEntry : public Rva007E86B0Base {
public:
 Rva00808CB0LanGameEntry() { field08=0; field0c=0; field04=0; }
 virtual ~Rva00808CB0LanGameEntry();
 int field08, field0c;
};
class Rva00803080 {
public:
 Rva00803080() {}
 virtual void slot0(unsigned int);
};
class Rva007EAServiceList {
public: void add(Rva00803080*);
};
class DemanglerPrimary {
public:
 virtual ~DemanglerPrimary();
 virtual void rva007F8790(const char*,int,const char*,unsigned char);
 virtual void set(int,int);
};
class BfmeThingTWA : public DemanglerPrimary, public Rva00803080 {
public:
 BfmeThingTWA(Rva007EAServiceList*);
 virtual ~BfmeThingTWA();
 virtual void slot0(unsigned int);
 virtual void rva007F8790(const char*,int,const char*,unsigned char);
 virtual void set(int,int);
 int field08, field0c;
 Rva00808CB0LanGameEntry packet;
 int field20;
 unsigned char field24;
 int field28, field2c;
};
BfmeThingTWA::BfmeThingTWA(Rva007EAServiceList* service) {
 field0c=0;
 field08=0;
 packet.field08=0;
 packet.field0c=0;
 field20=0;
 field24=0;
 field28=0;
 field2c=0;
 service->add(this);
}
