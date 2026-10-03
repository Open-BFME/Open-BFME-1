// cl: /DNDEBUG /MD
#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

struct BfmeEffectRecord8030 { int m_values[3]; };

// Retail's 0x00288030 reaches this callee through ILT 0x00002243, whose target
// is 0x00132530: the ledger owns that body as
// ?convertBonePosToWorldPos@Thing@@QBEXPBUCoord3D@@PBVMatrix3D@@PAU2@PAV3@Z
// (game/GameEngine/Source/Common/Thing/Thing.cpp). The body ends `ret 0x10`, so
// it really takes this plus four stack arguments, which is exactly the upstream
// declaration -- restate it with the same class/struct keywords, or the
// argument-type back-references in the mangled name come out different.
// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h:139
struct Coord3D;
class Matrix3D;

class Thing
{
public:
	void convertBonePosToWorldPos( const Coord3D *bonePos,
		const Matrix3D *boneTransform, Coord3D *worldPos,
		Matrix3D *worldTransform ) const;
};

// Retail's second call out of this body goes through ILT 0x00002A59, whose
// target is 0x001D67C0. The ledger owns that 57-byte body as
// ?bfmeTellFB@BfmeThingFB@@QAEXPAX000@Z
// (game/GameEngine/Source/Common/BfmeOneHundredNinetyFour.cpp), which walks the
// listener array at +0x00/+0x04 and hands all four arguments to each entry's
// vslot. It is `ret 0x10`, so it really takes this plus four stack arguments --
// four pointers, which is what the call site pushes (the state, the record and
// two nulls).
class BfmeThingFB
{
public:
	void bfmeTellFB(void *first, void *second, void *third, void *fourth);
};

struct BfmeSelection8030
{
	char m_fields[0x10];
	unsigned int m_index;
};

class BfmeSelector8030
{
public:
	BFME_TEN_VIRTUALS(v00);
	virtual void v10(void); virtual void v11(void); virtual void v12(void);
	virtual void v13(void); virtual void v14(void);
	virtual BfmeSelection8030 *bfmeGet(void);
};

class BfmeEffectState8030
{
public:
	char m_fields[0x200];
	BfmeSelector8030 *m_selector;
};

struct BfmeMaskSource8030
{
	char m_fields[0x48C];
	unsigned int m_mask;
};

// The receiver this file's ledger row names; only its address is ever used.
class BfmeThing8030
{
public:
	char m_fields[4];
};

class Gen_00288030
{
public:
	BFME_TEN_VIRTUALS(v00);
	virtual void v10(void);
	virtual void bfmeRefresh(void);
	void bfmeDispatch(BfmeThing8030 *effect, void *source);

private:
	BfmeMaskSource8030 *m_maskSource;
	BfmeEffectState8030 *m_state;
	char m_fields[0x620];
	unsigned int m_flagIndex;
	unsigned char m_flags[1];
};

// ?bfmeDispatch@Gen_00288030@@QAEXPAVBfmeThing8030@@PAX@Z
void Gen_00288030::bfmeDispatch(BfmeThing8030 *effect, void *source)
{
	BfmeEffectRecord8030 record;
	if (!m_flags[m_flagIndex])
		bfmeRefresh();

	BfmeMaskSource8030 *maskSource = m_maskSource;
	BfmeSelection8030 *selection = m_state->m_selector->bfmeGet();
	if (selection == 0 ||
		(maskSource->m_mask & (1U << (selection->m_index - 1))) != 0) {
		BfmeEffectState8030 *state = m_state;
		((Thing *)state)->convertBonePosToWorldPos( (const Coord3D *)source, 0,
			(Coord3D *)&record, 0 );
		if (effect != 0)
			((BfmeThingFB *)effect)->bfmeTellFB(state, &record, 0, 0);
	}
}

#undef BFME_TEN_VIRTUALS
