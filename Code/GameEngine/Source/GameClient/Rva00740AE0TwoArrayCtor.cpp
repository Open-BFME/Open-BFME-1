// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00740AE0: constructor of the class whose destructor is 0x00740BC0.
// Inlined base constructor stores the base vftable, calls set(0,0,1.0) on the
// subobject at +0x10 and zeroes the scalar fields; then the derived vftable
// is installed and the two 0x14-byte arrays (255 then 4) are vector-constructed.

class Rva00740BC0Elem
{
public:
	Rva00740BC0Elem();
	~Rva00740BC0Elem();

private:
	unsigned char m_body[0x14];
};

class Gen0002A1B2
{
public:
	void set(int a, int b, float c);

private:
	unsigned char m_body[8];
};

class Rva00740AE0Base
{
public:
	virtual void dummy();
	Rva00740AE0Base();
	~Rva00740AE0Base() {}

	int m_04;
	int m_08;
	unsigned char m_0c[4];
	Gen0002A1B2 m_sub;
	int m_18;
	int m_1c;
	int m_20;
	char m_24;
	int m_28;
};

Rva00740AE0Base::Rva00740AE0Base()
{
	Gen0002A1B2 *sub = &m_sub;
	sub->set(0, 0, 1.0f);
	m_04 = 0;
	m_08 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
}

class Rva00740AE0 : public Rva00740AE0Base
{
public:
	Rva00740AE0();

private:
	Rva00740BC0Elem m_arr255[255];
	Rva00740BC0Elem m_arr4[4];
};

Rva00740AE0::Rva00740AE0() {}
