// ??1Rva003BBC20@@UAE@XZ
// partial score=0.55 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: retail 0x003BBC20, 145 bytes. BfmeBaseVUQ destructor family:
// own vtable 0x010ED8F8 stored at entry (already pinned generically as
// ?g_bfmeVtbVNG@@3PAXA), base vtable 0x01073744 restored implicitly at the
// tail. A single owned-pointer member at +0xC is torn down TWICE (states 1
// and 0): the same checker+conditional-virtual-release logic appears in two
// inlined copies, matching the unwind map's two states (build/ehmap.py
// 0x0120EAF0), each guarded by its own EH bookkeeping.
//
// The checker is the same stdcall import already declared in
// Rva00889720.cpp (Rva01358E54); here its return value IS used (checked
// signed > 0), so it is redeclared with an int return -- same decorated
// symbol either way (stdcall decoration ignores return type), same address.

extern "C" __declspec(dllimport) int __stdcall Rva01358E54(void *);

class RefThing003BBC20
{
public:
	virtual void bfmeRelease(int flag);

	int m_field4;
};

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ(void) { }
};

class Rva003BBC20 : public BfmeBaseVUQ
{
public:
	virtual ~Rva003BBC20(void);
	virtual void bfmePure003BBC20(void) = 0;	// keeps MSVC from emitting its own vftable

private:
	unsigned char m_pad004[8];					// +0x04, untouched by this body
	RefThing003BBC20 * volatile m_thing;			// +0x0C
};

// @??1Rva003BBC20@@UAE@XZ 0x003BBC20
Rva003BBC20::~Rva003BBC20(void)
{
	RefThing003BBC20 *thing1 = m_thing;

	if (thing1)
	{
		if (Rva01358E54(&thing1->m_field4) <= 0)
		{
			if (thing1)
				thing1->bfmeRelease(1);
		}
	}

	m_thing = 0;

	RefThing003BBC20 *thing2 = m_thing;

	if (thing2)
	{
		if (Rva01358E54(&thing2->m_field4) <= 0)
		{
			if (thing2)
				thing2->bfmeRelease(1);
		}
	}

	m_thing = 0;
}
