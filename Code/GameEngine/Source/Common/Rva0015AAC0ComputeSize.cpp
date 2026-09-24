// cl: /DNDEBUG /MD /EHsc
// Retail 0x0015AAC0 (114 bytes), same owner as the bucket rebuild at
// 0x0015A790 and the max walk at 0x0015A560.  If +0x1B8 is clear it
// rebuilds, then returns a width/height pair by value (hidden return
// pointer, ret 4): height = (float)[+0x1B4] * TheAI->aiData[+0xA0], width =
// (float)(sum of the first bucket's maxOverride over [+0] passes) *
// aiData[+0xA4].  The pair is a named local with an inline field-wise copy
// constructor, so the width goes from the FPU straight into the return slot
// and the height is copied from the local, as retail does.

typedef int Int;
typedef float Real;

// The pair computeSize returns: width then height, built in the caller's
// return slot.  Address-derived; the retail type is not proven.
struct Rva0015AAC0Size
{
	Rva0015AAC0Size() {}
	Rva0015AAC0Size(const Rva0015AAC0Size &that) : x(that.x), y(that.y) {}
	Real x;
	Real y;
};

class Rva0015A560List
{
public:
	Int maxOverrideField43C() const;
};

class TAiData
{
public:
	char m_pad00[0xA0];
	Real m_scaleA0;					// +0xA0
	Real m_scaleA4;					// +0xA4
};

class AI
{
public:
	char m_pad00[0x14];
	TAiData *m_aiData;				// +0x14
};

extern AI *TheAI;					// 0x012EF214

class Rva0015AAC0Owner
{
public:
	void rebuildBuckets();			// ILT 0x0000C0AE / body 0x0015A790
	Rva0015AAC0Size computeSize();

	Int m_count;					// +0x00
	char m_pad04[4];
	char m_bucketAt8[4];			// +0x08, first 0x1C bucket
	char m_pad0C[0x1B4 - 0x0C];
	Int m_max1B4;					// +0x1B4
	unsigned char m_ready;			// +0x1B8
};

// ?computeSize@Rva0015AAC0Owner@@QAE?AURva0015AAC0Size@@XZ
Rva0015AAC0Size Rva0015AAC0Owner::computeSize()
{
	if (!m_ready)
		rebuildBuckets();

	TAiData *data = TheAI->m_aiData;
	Rva0015AAC0Size size;
	size.y = (Real)m_max1B4 * data->m_scaleA0;
	Int total = 0;
	for (Int i = m_count; i > 0; --i)
		total += ((Rva0015A560List *)m_bucketAt8)->maxOverrideField43C();
	size.x = (Real)total * data->m_scaleA4;
	return size;
}
