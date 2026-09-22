// ?bfmeCheckGK@BfmeMgrGK@@QAE_NPAVBfmeObjGK@@_NPAM@Z
// partial score=0.945 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// BFME 1.03 RVA 0x003A1A30, 566 bytes.
//
// Reached only through the ILT thunk at 0x000481FD, which the matched
// bfmeTryGK (0x00148800, BfmeConv2065.cpp) calls as
// g_bfmeMgrGK->bfmeCheckGK(obj, 0, 0). The body proves the real ABI: arg 2 is
// tested as a byte and arg 3 is an optional float out pointer. `this` is unused.
// Walks obj's 0xB8-byte records by the distance at obj+0x18 and writes the
// interpolated point to obj+0x48 (the field bfmeTryGK copies out on success).
// The record layout (eleven dwords, eleven twelve-byte members at 0x2C, a
// four-byte member at 0xB0, a dword at 0xB4) agrees with the 0xB8-byte copy
// constructor at 0x003A1120 (Rva003A1120CopyCtor.cpp); that the vector holds
// that very type is not proven, so the record keeps this address.
// Identity beyond the caller's placeholder names is not recovered.

#include <math.h>
#include <vector>

class View;
extern View *TheTacticalView;
extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

class BfmeVec3GK
{
public:
	float m_bfmeXGK;
	float m_bfmeYGK;
	float m_bfmeZGK;
};

// One 0xB8-byte record: a float, ten floats consumed as sub-lengths, eleven points.
struct Rva003A1A30Record
{
	float m_float00;
	float m_float04[10];
	BfmeVec3GK m_point2C[11];
	int m_dwordB0;
	int m_dwordB4;
};

class BfmeObjGK
{
public:
	virtual void bfmeVt0GK();

	unsigned char m_bfmeGapGK[0x14];
	float m_bfmeRangeGK;
	float m_float1C;
	int m_int20;
	char m_bfmeFlagGK;
	unsigned char m_gap25[7];
	std::vector<Rva003A1A30Record> m_records2C;
	int m_dword38;
	float m_float3C;
	int m_int40;
	int m_dword44;
	BfmeVec3GK m_bfmeResultGK;
};

class Rva003A1A30ViewVtable
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0; virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0; virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0; virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0; virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0; virtual void slot68() = 0;
	virtual void slot6C(int) = 0;
};

class BfmeMgrGK
{
public:
	bool bfmeCheckGK(BfmeObjGK *obj, bool notify, float *outDelta);
};

bool BfmeMgrGK::bfmeCheckGK(BfmeObjGK *obj, bool notify, float *outDelta)
{
	if (!obj->m_bfmeFlagGK)
		return false;
	if (obj->m_records2C.size() == 0)
		return false;

	while (obj->m_bfmeRangeGK - obj->m_float1C >= obj->m_records2C[obj->m_int20].m_float00)
	{
		if (notify)
			reinterpret_cast<Rva003A1A30ViewVtable *>(TheTacticalView)->slot6C(obj->m_records2C[obj->m_int20 + 2].m_dwordB4);
		obj->m_float1C += obj->m_records2C[obj->m_int20].m_float00;
		obj->m_int20++;
		obj->m_float3C = 0.0f;
		obj->m_int40 = 0;
		if (obj->m_int20 + 3 > obj->m_records2C.size())
			return false;
	}

	float rem = obj->m_bfmeRangeGK - obj->m_float1C - obj->m_float3C;
	float len = obj->m_records2C[obj->m_int20].m_float04[obj->m_int40];
	while (rem >= len)
	{
		obj->m_float3C += len;
		obj->m_int40++;
		rem -= len;
		len = obj->m_records2C[obj->m_int20].m_float04[obj->m_int40];
	}

	float t;
	if (len > BfmeZeroRange)
		t = rem / len;
	else
		t = g_bfmeDefaultBU;

	BfmeVec3GK from;
	if (obj->m_int40 > 0)
		from = obj->m_records2C[obj->m_int20].m_point2C[obj->m_int40 - 1];
	else
		from = obj->m_records2C[obj->m_int20 + 1].m_point2C[10];
	BfmeVec3GK to = obj->m_records2C[obj->m_int20].m_point2C[obj->m_int40];
	BfmeVec3GK r;
	r.m_bfmeXGK = (to.m_bfmeXGK - from.m_bfmeXGK) * t + from.m_bfmeXGK;
	r.m_bfmeYGK = (to.m_bfmeYGK - from.m_bfmeYGK) * t + from.m_bfmeYGK;
	r.m_bfmeZGK = (to.m_bfmeZGK - from.m_bfmeZGK) * t + from.m_bfmeZGK;
	obj->m_bfmeResultGK = r;

	if (outDelta)
	{
		float range = obj->m_bfmeRangeGK;
		*outDelta = fabs(fabs(obj->m_records2C[obj->m_int20].m_float04[0] - range)
			- fabs(obj->m_records2C[obj->m_int20].m_float04[9] - range));
	}
	return true;
}
