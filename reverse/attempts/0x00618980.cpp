// ?d_00618980@@YAXXZ
// partial score=0.98 date=2026-09-09
// Retail RVA 0x00618980 updates the Living World object's active state and
// reports the resolved value when the object becomes inactive.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeThingGN;

class BfmeInnerGN
{
public:
	BfmeThingGN *bfmeResolveGN(void);
};

class BfmeThingGN
{
public:
	int m_bfmeSpareGN;
	BfmeInnerGN *m_bfmeInnerGN;
	unsigned char m_bfmeGapGN[8];
	int m_bfmeValueGN;
};

class BfmeSourceGN
{
public:
	unsigned char m_bfmeHeadGN[8];
	int m_bfmeTagGN;
};

void __cdecl bfmeReportGN(int tag, int first, int second, int third);

class Rva00618980Object
{
public:
	void rva00618980(int value);

	int m_bfmeSpareGN;
	BfmeThingGN *m_bfmeThingGN;
	int m_bfmePadGN;
	BfmeSourceGN *m_bfmeSourceGN;
	char m_bfmeActiveGN;
	unsigned char m_bfmeGapGN[3];
	int m_bfmeStampGN;
};

void Rva00618980Object::rva00618980(int value)
{
	unsigned char active = static_cast<unsigned char>(value);

	if (m_bfmeActiveGN != 0 && active == 0)
	{
		volatile Rva00618980Object *view = this;
		view->m_bfmeActiveGN = 0;
		view->m_bfmeStampGN = 0;

		BfmeThingGN *thing = view->m_bfmeThingGN;
		BfmeThingGN *resolved;

		if (thing == 0)
			resolved = 0;
		else if (thing->m_bfmeInnerGN == 0)
			resolved = thing;
		else
			resolved = thing->m_bfmeInnerGN->bfmeResolveGN();

		int resolvedValue = resolved->m_bfmeValueGN;
		int tag = view->m_bfmeSourceGN->m_bfmeTagGN;
		volatile int home = resolvedValue;

		bfmeReportGN(tag, resolvedValue, resolvedValue, resolvedValue);
		return;
	}

	if (m_bfmeActiveGN == 0 && active != 0)
	{
		m_bfmeActiveGN = 1;
		m_bfmeStampGN = 0;
	}
}
