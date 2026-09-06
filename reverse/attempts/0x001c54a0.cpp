// ??0BfmeUpdateERI@@QAE@PAVBfmeThingERI@@PBVBfmeModuleDataERI@@@Z (identity unknown)
// partial score=0.95 date=2026-09-06
// 113/113; three instructions transposed at +0x44 (push 0x10 / state store vs the
// m_list = 0 store). zh_sweep lead ??0SmartBombTargetHomingUpdate.
// Pins: base ctor 0x00021BE8, allocator 0x0082E540,
//       vtables 0x00C9EBBC / 0x00C9EAF8 / 0x00C9EAEC
class BfmeThingERI;
class BfmeModuleDataERI;

extern "C" void *bfmeVtERIa[];
extern "C" void *bfmeVtERIb[];
extern "C" void *bfmeVtERIc[];

void *__cdecl bfmeAllocERI(unsigned int size);

class BfmeNodeERI
{
public:
	BfmeNodeERI *m_bfmeNextERI;
	BfmeNodeERI *m_bfmePrevERI;
	unsigned char m_bfmeDataERI[8];
};

class BfmeUpdateBaseERI
{
public:
	BfmeUpdateBaseERI(BfmeThingERI *thing, const BfmeModuleDataERI *data);
	~BfmeUpdateBaseERI(void);

	void *volatile m_bfmeVtAERI;
	unsigned char m_bfmeHeadERI[8];
	void *volatile m_bfmeVtBERI;
	void *volatile m_bfmeVtCERI;
	unsigned char m_bfmeMidERI[0xc];
	BfmeNodeERI *volatile m_bfmeListERI;
};

class BfmeUpdateERI : public BfmeUpdateBaseERI
{
public:
	BfmeUpdateERI(BfmeThingERI *thing, const BfmeModuleDataERI *data);
};

BfmeUpdateERI::BfmeUpdateERI(BfmeThingERI *thing, const BfmeModuleDataERI *data)
	: BfmeUpdateBaseERI(thing, data)
{
	m_bfmeVtAERI = bfmeVtERIa;
	m_bfmeVtBERI = bfmeVtERIb;
	m_bfmeVtCERI = bfmeVtERIc;
	BfmeNodeERI *node;
	m_bfmeListERI = 0;
	node = (BfmeNodeERI *)bfmeAllocERI(16);
	node->m_bfmeNextERI = node;
	node->m_bfmePrevERI = node;
	m_bfmeListERI = node;
}
