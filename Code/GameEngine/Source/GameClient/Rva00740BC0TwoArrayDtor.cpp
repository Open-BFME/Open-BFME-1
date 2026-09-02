// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00740BC0: destructor of a derived class whose two trailing arrays
// of 0x14-byte elements (255 then 4) go through the eh vector destructor
// iterator, after which the inlined empty base destructor restores the base
// vftable. No derived vftable store on entry.

class Rva00740BC0Elem
{
public:
	~Rva00740BC0Elem();

private:
	unsigned char m_body[0x14];
};

extern void *g_Rva00740BC0BaseVft[];

class Rva00740BC0Base
{
public:
	~Rva00740BC0Base() { m_vft = g_Rva00740BC0BaseVft; }

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
