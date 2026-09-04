// ?computeSize@Rva0015AAC0Owner@@QAEXPAM@Z
// partial score=0.97 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: leftover of d_00153d10.asm at 0x0015AAC0, 114 bytes.
// Same owner as the 0x0015A790 bucket rebuild and the 0x0015A560 max walk.
// If +0x1B8 is clear, rebuild. Then write two floats through the out-arg:
//   [out+4] = (float)[+0x1B4] * TheAI->aiData[+0xA0]  (raw dword copy)
//   [out+0] = (float)(count * firstBucket.maxOverride()) * aiData[+0xA4]
// Counted call loop on the first 0x1C bucket at +8; aiData lives in ebp.
//
// Size exact 114/114. Sole wall is the last two instructions: retail
// `pop ebx; fstp [eax]`, ours `fstp [eax]; pop ebx` (3 bytes). /Ot /Os
// and *out vs out[0] all keep that adjacent swap.

typedef int Int;
typedef float Real;

class Rva0015A560List
{
public:
	Int maxOverrideField43C();
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
	void computeSize(Real *out);

	Int m_count;					// +0x00
	char m_pad04[4];
	char m_bucketAt8[4];			// +0x08, first 0x1C bucket
	char m_pad0C[0x1B4 - 0x0C];
	Int m_max1B4;					// +0x1B4
	unsigned char m_ready;			// +0x1B8
};

// ?computeSize@Rva0015AAC0Owner@@QAEXPAM@Z
#pragma optimize("t", on)
void Rva0015AAC0Owner::computeSize(Real *out)
{
	if (!m_ready)
		rebuildBuckets();

	struct Frame
	{
		Int sum;
		Int mid;
		Real scaledMax;
	} frame;
	frame.sum = 0;
	frame.mid = 0;
	TAiData *data = TheAI->m_aiData;
	frame.scaledMax = (Real)m_max1B4 * data->m_scaleA0;
	if (m_count > 0)
	{
		Rva0015A560List *bucket =
			(Rva0015A560List *)(8 + (unsigned int)this);
		Int n = m_count;
		do
		{
			frame.sum += bucket->maxOverrideField43C();
		} while (--n);
	}
	Real result = (Real)frame.sum;
	Int bits = *(Int *)&frame.scaledMax;
	result = result * data->m_scaleA4;
	*(Int *)(out + 1) = bits;
	*out = result;
}
#pragma optimize("", on)
