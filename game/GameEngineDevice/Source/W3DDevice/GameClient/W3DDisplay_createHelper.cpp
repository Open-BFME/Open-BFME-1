// cl: /DNDEBUG /MD /EHsc

// Retail 0x006FB780. Factory of the same NEW-with-EH shape as the neighbouring
// W3DGameClient create* methods, but the product constructor takes three
// function pointers (ILT 0x0002FB3F, 0x0003BE9E, 0x0003DFB4) and the block is
// 0x18 bytes.

void rva006fb780_fn_a(void);			// ILT 0x0002FB3F
void rva006fb780_fn_b(void);			// ILT 0x0003BE9E
void rva006fb780_fn_c(void);			// ILT 0x0003DFB4

class Rva006FB780Product
{
public:
	Rva006FB780Product(void (*a)(void), void (*b)(void), void (*c)(void));

private:
	unsigned char m_data[0x18];
};

class Rva006FB780Host
{
public:
	Rva006FB780Product *create(void);
};

// ?create@Rva006FB780Host@@QAEPAVRva006FB780Product@@XZ
Rva006FB780Product *Rva006FB780Host::create(void)
{
	return new Rva006FB780Product(rva006fb780_fn_a, rva006fb780_fn_b, rva006fb780_fn_c);
}
