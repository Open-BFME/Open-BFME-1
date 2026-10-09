// cl: /O2 /Ob0 /G6

struct BfmeShapeE15
{
	char m[0x24];
};

// Full 0x24-byte out-of-range sentinel at retail VA 0x012D4CE8.
// The three IEEE 1.0f words at +4/+8/+12 and byte 1 at +0x20
// are initialized in the shipped image; the remaining bytes are zero.
BfmeShapeE15 g_bfmeBadE15 = {{
	0, 0, 0, 0,
	0, 0, -128, 63,
	0, 0, -128, 63,
	0, 0, -128, 63,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 0, 0, 0
}};

class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(int i);
	char m_00[0x2C];
	BfmeShapeE15 *volatile m_start;
	BfmeShapeE15 *m_finish;
};

BfmeShapeE15 *BfmeObjE15::bfmeAtE15(int i)
{
	if (i >= 0)
	{
		if ((unsigned)i < (unsigned)(m_finish - m_start))
			return m_start + i;
	}
	return &g_bfmeBadE15;
}
