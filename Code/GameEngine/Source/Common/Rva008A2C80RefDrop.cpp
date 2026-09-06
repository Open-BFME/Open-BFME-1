// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??1Rva00171DB0 (0x00171DB0, Q4OwnedPtrDtors.cpp); same
// single-vtable shape, chaining to the base destructor already landed as
// ??1Gen_008AC620@@QAE@XZ, but the owned member here is a plain refcounted
// pointer decremented via Rva00894D90Accessor::decrement and dropped via
// bfmeDropA when the count reaches zero (instead of a two-vcall release).

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(int *p);
};

void bfmeDropA(void *p);

class Gen_008AC620
{
public:
	virtual ~Gen_008AC620();
};

class Rva008A2C80 : public Gen_008AC620
{
public:
	virtual ~Rva008A2C80();

private:
	unsigned char m_pad[0x34 - 4];
	int *m_ptr;
};

// ?d_008a2c80@@YAXXZ
Rva008A2C80::~Rva008A2C80()
{
	if (m_ptr)
	{
		if (Rva00894D90Accessor::decrement(m_ptr) == 0)
			bfmeDropA(m_ptr);
	}
}
