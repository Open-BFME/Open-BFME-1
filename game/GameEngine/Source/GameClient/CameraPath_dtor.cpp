// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00740BC0: destructor of a derived class whose two trailing arrays
// of 0x14-byte elements (255 then 4) go through the eh vector destructor
// iterator, after which the inlined empty base destructor restores the base
// vftable. No derived vftable store on entry.

// The per-element destructor the vector-destructor iterator is handed at
// 0x00740BC0 is 0x0001DF2A, the five-byte gen-thunk ?j_0001df2a (routed to
// 0x00740960); no body under this name is matched there, so the out-of-line
// spelling resolved to nothing. Define it inline and route the thiscall through
// the thunk instead, the way HordeContain/Rva002458B0FormationPosition.cpp
// reaches ?j_0001f91f. The address the ctor pushes is still this TU's
// ??1Rva00740BC0Elem@@QAE@XZ, which the ledger pins at 0x0001DF2A.
extern void j_0001df2a();

class Rva00740BC0Elem
{
public:
	~Rva00740BC0Elem()
	{
		typedef void (Rva00740BC0Elem::*Fn)();
		union { void (*raw)(); Fn member; } f;
		f.raw = j_0001df2a;
		(this->*f.member)();
	}

private:
	unsigned char m_body[0x14];
};

// The vftable the base destructor restores sits at VA 0x010C7450, which the
// ledger records as ?_7Rva00740AE0Base@@6B@ and which CameraPath_ctor.cpp emits.
// __identifier is how BfmeConv2075.cpp names the vftables of classes it does not
// itself instantiate.
extern "C" void *__identifier("??_7Rva00740AE0Base@@6B@")[];

class Rva00740BC0Base
{
public:
	~Rva00740BC0Base() { m_vft = __identifier("??_7Rva00740AE0Base@@6B@"); }

	void *m_vft;
	unsigned char m_pad[0x28];
};

class Rva00740BC0 : public Rva00740BC0Base
{
public:
	~Rva00740BC0();

private:
	Rva00740BC0Elem m_arr255[255];
	Rva00740BC0Elem m_arr4[4];
};

Rva00740BC0::~Rva00740BC0() {}
