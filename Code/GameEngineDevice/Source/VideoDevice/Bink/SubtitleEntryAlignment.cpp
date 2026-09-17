// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// The SubtitleEntry update body at 0x004341A0 passes its alignment field at
// +0x10 here.  The invalid-state diagnostic at 0x010F392C identifies the
// helper as the BFME subtitle alignment calculation.

#include <math.h>

typedef int Int;
typedef float Real;

class BfmeDebugReport
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeDebugReport *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(Int value);
};

class BfmeDebugManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeDebugReport *slot6C(void *first, void *second);
};

extern BfmeDebugManager *TheGen001336E5C;
extern void _bfme_debugRecordCallsite(Int kind);

static const Int &bfmeMin(const Int &first, const Int &second)
{
	return first < second ? first : second;
}

// ?bfmeAlignVIL@@YAHHHHMM@Z
Int bfmeAlignVIL(Int alignment, Int base, Int unused, Real low, Real high)
{
	Int difference = (Int)fabs(high - low);

	switch (alignment)
	{
	case 1:
		return 0;
	case 0:
	{
		Int highInt = (Int)high;
		Int lowInt = (Int)low;
		const Int &minimum = bfmeMin(highInt, lowInt);
		return minimum + ((difference - base) >> 1);
	}
	case 2:
	{
		Int highInt = (Int)high;
		Int lowInt = (Int)low;
		const Int &minimum = bfmeMin(highInt, lowInt);
		return minimum - base + difference;
	}
	default:
		_bfme_debugRecordCallsite(1);
		TheGen001336E5C->slot60();
		BfmeDebugReport *report = TheGen001336E5C->slot6C(0, 0);
		report = report->slot38("Invalid Subtitle alignment!");
		report->slot4C(1);
		return 0;
	}
}
