// cl: /DNDEBUG /MD /EHsc
// Retail 0x006DABB0 (92 bytes). Virtual destructor: derived vtable 0x0111E134,
// unregister through global 0x012EF4F0, decrement instance count 0x012F801C,
// then base vtable 0x01073744. Scalar deleting dtor at 0x006DB540 calls this.
// Twin constructor is 0x006DB470 (same vtable and counter).

extern int g_012F801C;

class Rva006DABB0;

class Manager012EF4F0
{
public:
	void unregister(Rva006DABB0 *obj);
};

extern Manager012EF4F0 *g_012EF4F0;

class Rva006DABB0Base
{
public:
	virtual ~Rva006DABB0Base() {}
};

class Rva006DABB0 : public Rva006DABB0Base
{
public:
	virtual ~Rva006DABB0();
};

Rva006DABB0::~Rva006DABB0()
{
	if (g_012EF4F0)
		g_012EF4F0->unregister(this);
	--g_012F801C;
}
