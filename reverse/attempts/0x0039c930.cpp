// ?xfer@Rva0039C930Owner@@QAEXPAVXfer@@@Z
// partial score=0.35 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

// Xfer vtable layout reused verbatim from the already-landed
// Code/GameEngine/Source/Common/BfmeConv599.cpp (isLoading@slot1/off4,
// isSaving@slot2/off8, xferVersion@slot10/off0x28, xferInt@slot30/off0x78);
// slot04/off0x10 here is an extra bool-returning check retail makes before
// isSaving that BfmeConv599's target does not exercise -- its meaning is not
// proven, so it keeps an address-derived name.
class Xfer
{
public:
	virtual ~Xfer();
	virtual bool isLoading();
	virtual bool isSaving();
	virtual void slot03();
	virtual bool slot04off10();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(void *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(void *value);
	virtual void xferReal(float *value);
	virtual void slot29();
	virtual void slot30();
	virtual void xferInt(int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(bool *value);
};

class Rva0039C930Owner
{
public:
	void xfer(Xfer *xfer);

private:
	int m_field4;
	_STL::vector<int> m_vec;			// +8 (begin/end/capacityEnd)
};

void Rva0039C930Owner::xfer(Xfer *xfer)
{
	unsigned char one = 1;
	unsigned char version[2];
	version[0] = one;
	version[1] = one;
	xfer->xferVersion(version);

	int count = (int)m_vec.size();

	if (xfer->slot04off10())
	{
		xfer->xferInt(&m_field4);
		xfer->xferInt(&count);
		return;
	}

	if (xfer->isSaving())
	{
		xfer->xferInt(&count);

		for (_STL::vector<int>::iterator current = m_vec.begin();
			current != m_vec.end(); ++current)
		{
			int value = *current;
			xfer->xferInt(&value);
		}
	}
	else
	{
		xfer->xferInt(&count);

		for (int i = 0; i < count; ++i)
		{
			int value;
			xfer->xferInt(&value);
			m_vec.push_back(value);
		}
	}
}
