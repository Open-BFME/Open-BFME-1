// Open-BFME: retail RVA 0x00210730, 322 bytes. Address-derived; no named
// caller, vtable, or string-anchored identity has been proven for the owner
// (Rva00210730Owner) or the container it reaches through m_thing
// (BfmeHostCL, offset 8). The container's flag test at +0x98 and the
// embedded BfmeObjE15/BfmeObjF9 vector at +0xAC reuse the layout already
// proven by the landed 0x0087E150 (BfmeObjE15::bfmeAtE15) and 0x0087FA50
// (BfmeObjF9::rva0087FA50) bodies: both are called with the SAME `this`
// (m_thing + 0xAC), so the two address-derived classes describe one real
// object. The loop searches the vector for a shape whose embedded string
// (offset 0x1C, same string-header shape as BfmeStrF9 in
// Rva0087FA50UpdateFlags.cpp) equals the literal "Bookend"; on a match it
// builds a real AsciiString temporary for the rva0087FA50 call, then resets
// the container via BfmeHostCL::bfmeResetCL (0x001BDEE0) while toggling this
// object's own +0x30 state field 0 -> 3.

// cl: /O2 /G6

typedef int Int;
typedef unsigned short UnsignedShort;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);

extern char g_bfmeEmptyF9[];

struct BfmeAsciiDataE15
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

class BfmeStrE15
{
public:
	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : g_bfmeEmptyF9; }

	BfmeAsciiDataE15 *m_data;
};

struct BfmeShapeE15
{
	int m_pad[7];
	BfmeStrE15 m_1C;
	char m_20;
	char m_pad20[3];
};

class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(int i);

	unsigned char m_pad[0x2C];
	BfmeShapeE15 *m_start;
	BfmeShapeE15 *m_finish;
};

class BfmeStrF9
{
public:
	void *m_data;
};

class BfmeObjF9
{
public:
	void rva0087FA50(const BfmeStrF9 &name, char flag);
};

void j_000358d2();

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer(void);

	void *m_data;
};

class BfmeHostCL
{
public:
	void bfmeResetCL(char full);

	unsigned char m_pad0[0x98];
	unsigned int m_flags98;
};

class Rva00210730Owner
{
public:
	void rva00210730(void);

	unsigned char m_pad0[8];
	BfmeHostCL *m_thing;
	unsigned char m_pad1[0x30 - 0xC];
	int m_state30;
};

void Rva00210730Owner::rva00210730(void)
{
	j_000358d2();

	if (m_thing->m_flags98 & 0x40000)
	{
		BfmeObjE15 *vec = (BfmeObjE15 *)((char *)m_thing + 0xAC);
		BfmeObjF9 *objF9 = (BfmeObjF9 *)((char *)m_thing + 0xAC);

		int count = vec->m_finish - vec->m_start;
		for (int i = 0; i < count; ++i)
		{
			BfmeShapeE15 *shape = vec->bfmeAtE15(i);
			BfmeAsciiDataE15 *data = shape->m_1C.m_data;
			Int len = data ? data->m_len : 0;
			const char *chars = (const char *)(data + 1);
			if (data == 0)
				chars = g_bfmeEmptyF9;
			Int shorter = len < 7 ? len : 7;

			Int diff = memcmp(chars, "Bookend", shorter);
			if (diff == 0)
				diff = len - 7;

			if (diff == 0)
			{
				{
					BFMERetailAsciiString bookend("Bookend");
					objF9->rva0087FA50(*(BfmeStrF9 *)&bookend, 0);
				}

				m_state30 = 0;
				m_thing->bfmeResetCL(1);
				m_state30 = 3;
				return;
			}
		}
	}
}
