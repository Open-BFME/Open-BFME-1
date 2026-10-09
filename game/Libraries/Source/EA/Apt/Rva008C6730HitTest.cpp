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

// 0x01338748: the Apt stack depth global, defined in Rva00C6DCC0StaticInit.cpp.
struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue **m_rva01338750;
};
// The array pointer at VA 0x01338750 is offset 8 of the existing stack
// object at VA 0x01338748, also witnessed by Rva008AE7C0CreateChannels.cpp.
extern Rva008AE770Stack Rva008AE770TheStack;
extern AptValue *g_bfmeFallbackDB;

AptValue *rva008C6730(BfmeN1235 *target, int argc)
{
	AptValue *fallback = g_bfmeFallbackDB;

	if (argc == 1)
		return fallback;
	if (argc <= 1)
		return fallback;

	float x = (*reinterpret_cast<AptValue **>(4 * (Rva008AE770TheStack.m_count - 1) + reinterpret_cast<unsigned int>(Rva008AE770TheStack.m_rva01338750)))->toNumber();
	float y = (*reinterpret_cast<AptValue **>(4 * (Rva008AE770TheStack.m_count - 2) + reinterpret_cast<unsigned int>(Rva008AE770TheStack.m_rva01338750)))->toNumber();

	if (argc > 2)
		(*reinterpret_cast<AptValue **>(4 * (Rva008AE770TheStack.m_count - 3) + reinterpret_cast<unsigned int>(Rva008AE770TheStack.m_rva01338750)))->toInteger();

	Rva8BB1A0Bounds bounds;
	target->bfmeInitEmpty1235(&bounds);

	if (x >= bounds.left && x <= bounds.right
		&& y >= bounds.top && y <= bounds.bottom)
		return AptInteger::Create(1);

	return fallback;
}
