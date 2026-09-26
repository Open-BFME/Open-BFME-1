// ?bfmeCalcHL@BfmeStateHL@@QAE?AVBfmeVec3HL@@H@Z
// partial score=0.8 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// ?bfmeCalcHL@BfmeStateHL@@QAE?AVBfmeVec3HL@@H@Z @ 0x005C3630, 104 bytes.
//
// The sret ABI (three floats returned through a hidden out-pointer) and the
// guarded fields at +0x1c0 / +0x1c4 are address-derived, but the callee at
// 0x005FAC90 is the MATCHED Rva005FAC90Owner::scale(Coord3D*,void*,const
// Coord3D*,float,void*) thiscall method (Rva005FAC90Scale.cpp), not a
// __stdcall free function: the owner pointer at +0x1c0 stays live in ECX
// across the whole body specifically because it is the thiscall receiver,
// and this function's own retval pointer is forwarded directly as scale's
// "out" argument (RVO, no intermediate copy). bfmeSlotHL() keeps its own
// redundant null test on the already-proven-nonnull BfmeBHL pointer because
// retail re-tests it (cmp esi,edx a second time) inside what is otherwise a
// dead branch.

extern const float g_bfmeK1253;
extern float g_bfmeDefaultBU;

struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadHL[0xab4];
	float m_bfmeRateHL;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva005FAC90Owner;

class BfmeVec3HL
{
public:
	BfmeVec3HL(float x, float y, float z)
	{
		m_bfmeXHL = x;
		m_bfmeYHL = y;
		m_bfmeZHL = z;
	}

	BfmeVec3HL(Rva005FAC90Owner *owner, void *context, const Coord3D *factors, float amount,
		void *extra);

	float m_bfmeXHL;
	float m_bfmeYHL;
	float m_bfmeZHL;
};

class BfmeSlotHL
{
public:
	unsigned char m_bfmeGapHL[4];
};

class BfmeBHL
{
public:
	unsigned char m_bfmeHeadHL[0x18];
	BfmeSlotHL m_bfmeSlotHL;
};

static __forceinline BfmeSlotHL *bfmeSlotHL(BfmeBHL *p)
{
	if (p != 0)
		return &p->m_bfmeSlotHL;

	return 0;
}

class Rva005FAC90Owner
{
public:
	void scale(Coord3D *out, void *context, const Coord3D *factors, float amount,
		void *extra);
};

inline BfmeVec3HL::BfmeVec3HL(Rva005FAC90Owner *owner, void *context, const Coord3D *factors,
	float amount, void *extra)
{
	owner->scale(reinterpret_cast<Coord3D *>(this), context, factors, amount, extra);
}

class BfmeStateHL
{
public:
	BfmeVec3HL bfmeCalcHL(int p);

	unsigned char m_bfmeHeadHL[0x134];
	BfmeVec3HL m_bfme134HL;
	unsigned char m_bfmeGap2HL[0x80];
	Rva005FAC90Owner *m_bfme1c0HL;
	BfmeBHL *m_bfme1c4HL;
};

BfmeVec3HL BfmeStateHL::bfmeCalcHL(int p)
{
	if (m_bfme1c0HL != 0)
	{
		BfmeBHL *b = m_bfme1c4HL;

		if (b != 0)
		{
			float f = (TheWritableGlobalData->m_bfmeRateHL + g_bfmeDefaultBU) * g_bfmeK1253;

			return BfmeVec3HL(m_bfme1c0HL, (void *)p,
				reinterpret_cast<const Coord3D *>(&m_bfme134HL), f, bfmeSlotHL(b));
		}
	}

	return BfmeVec3HL(0, 0, 0);
}
