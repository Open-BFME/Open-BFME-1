// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x008C6730, 202 bytes.  The body reads two numbers off the Apt value
// stack through the matched AptValue::toNumber at 0x008983D0, asks the target
// for its bounding box through the matched
// BfmeN1235::bfmeInitEmpty1235 at 0x008AE2B0, and returns integer 1 from the
// matched AptInteger::Create at 0x008A11E0 when the point falls inside that
// box.  Every other exit returns g_bfmeFallbackDB.  With three or more
// arguments it also calls the matched AptValue::toInteger at 0x00898300 on the
// third stack slot and drops the result, which is what retail does.
//
// No caller, no data reference and no dispatch-table slot names the function,
// so the name keeps the address.
//
// Writing the four bounds tests as one conjunction is what reaches the exact
// bytes.  Four separate early returns invert two of the x87 status tests and
// swap which callee-saved register holds the argument count.

struct Rva8BB1A0Bounds
{
	float left;
	float top;
	float right;
	float bottom;
};

class AptValue
{
public:
	float toNumber();
	int toInteger() const;
};

class AptInteger : public AptValue
{
public:
	static AptInteger *Create(int value);
};

class BfmeN1235
{
public:
	void bfmeInitEmpty1235(Rva8BB1A0Bounds *bounds);
};

extern AptValue **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern AptValue *g_bfmeFallbackDB;

AptValue *rva008C6730(BfmeN1235 *target, int argc)
{
	AptValue *fallback = g_bfmeFallbackDB;

	if (argc == 1)
		return fallback;
	if (argc <= 1)
		return fallback;

	float x = g_bfmeArr1233[g_bfmeCount1233 - 1]->toNumber();
	float y = g_bfmeArr1233[g_bfmeCount1233 - 2]->toNumber();

	if (argc > 2)
		g_bfmeArr1233[g_bfmeCount1233 - 3]->toInteger();

	Rva8BB1A0Bounds bounds;
	target->bfmeInitEmpty1235(&bounds);

	if (x >= bounds.left && x <= bounds.right
		&& y >= bounds.top && y <= bounds.bottom)
		return AptInteger::Create(1);

	return fallback;
}
