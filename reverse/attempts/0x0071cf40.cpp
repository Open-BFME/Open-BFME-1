// ?rva0071CF40@BaseHeightMapResetBuffer@@QAE_NHPAM000@Z
// partial score=0.25 date=2026-09-22
// First-ever compilable candidate for this RVA (both prior verdicts had no
// source attempt, only "high boundary, no owner"). BaseHeightMapResetBuffer
// is an ALREADY-LANDED class -- see
// Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapResetBuffer_removeTreeAtIndex.cpp,
// which independently proves m_numTrees at this+0x1e1cc8 and the 0xA4-byte
// tree-record stride starting at this+0x1548, with treeType at
// this-relative +0x1588 within a record (record+0x40). No caller and no
// source declaration proves THIS method's real name, so it stays
// address-derived under the proven class.
//
// Full disassembly decoded: reads tree record `index` (bounds-checked
// against m_numTrees) and, if both the record and its tree-TYPE record
// (indexed by the record's treeType field, a SEPARATE 0x5C-byte-stride
// table starting at this+0x1E1CD4, right after
// m_numTrees/m_anythingChanged) pass their validity/enabled checks, writes
// the record's position (3 floats) and a direction-weighted scale (1
// float, weighted by the already-named global g_bfmeDirectionWeight1285 at
// VA 0x1075C74) through the caller's first two out-pointers, then copies
// two float pairs from the tree-TYPE record (probably shadow offset/size)
// through the last two out-pointers. Returns true if it wrote through the
// pointers, false (and no writes) otherwise. ret 0x14 confirms 5 stack
// args (index + 4 out-pointers), all of which are read and used.
//
// RESULT: ours=155B retail=178B, 134/178 nonreloc diff, first divergence at
// +1 (only the `push`-less prologue byte matches). Residue is REGISTER
// MATERIALIZATION, not missing logic or wrong offsets -- every field
// offset used here (0x1588, 0x158c, 0x1e1cd4, 0x1e1d00/04/10/14/18, 0x1548/
// 4c/50/54) matches retail's own displacement bytes exactly once the
// diff's target-address noise is discounted. Retail commits the tree
// record's base pointer to a dedicated register (edx = lea [eax+ecx])
// immediately after the `imul`, and reuses it for all six subsequent tree
// field reads; every source shape tried here (a struct pointer local, a
// raw reinterpret_cast<char*>+offset-macro style matching the ALREADY
// LANDED sibling file exactly -- which made it WORSE, 170B/153diff --
// caching tree->m_treeType into a named int before reuse, and a `register`
// hint on the tree pointer) left MSVC folding the first two field accesses
// into combined `[edx+ecx+off]` addressing instead of committing the
// pointer early, which then cascades into different register choices for
// the rest of the function. Also tried swapping the scale multiplication
// operand order (`g_bfmeDirectionWeight1285 * tree->m_scale` vs the
// reverse) to match retail's fld/fmul operand order -- no effect, MSVC's
// x87 codegen picks its own load order independent of source spelling here
// (matches the documented "two squares in Length2" / lea-operand-order
// class of dead end). t=25min model=claude-sonnet-5 score=0.25
// cl: /DNDEBUG /MD /EHsc

extern float g_bfmeDirectionWeight1285;

class BaseHeightMapResetBuffer
{
public:
	bool rva0071CF40( int index, float *outPos, float *outScale,
		float *outShadowA, float *outShadowB );

private:
	char m_pad00[ 0x1e1cc8 ];
	int m_numTrees;
	unsigned char m_anythingChanged;
};

struct Rva0071CF40TreeRecord
{
	char m_pad00[ 0x1548 ];
	float m_posX;
	float m_posY;
	float m_posZ;
	float m_scale;
	char m_pad1558[ 0x30 ];
	int m_treeType;
	unsigned char m_enabled;
};

struct Rva0071CF40TypeRecord
{
	int m_valid;
	char m_pad04[ 0x28 ];
	float m_shadowAX;
	float m_shadowAY;
	char m_pad38[ 8 ];
	float m_shadowBX;
	float m_shadowBY;
	unsigned char m_ready;
};

bool BaseHeightMapResetBuffer::rva0071CF40( int index, float *outPos,
	float *outScale, float *outShadowA, float *outShadowB )
{
	if( index >= m_numTrees )
		return false;
	Rva0071CF40TreeRecord *tree = reinterpret_cast<Rva0071CF40TreeRecord *>(
		reinterpret_cast<char *>( this ) + index * 0xa4 );
	int treeType = tree->m_treeType;
	if( treeType < 0 )
		return false;
	if( !tree->m_enabled )
		return false;

	Rva0071CF40TypeRecord *type = reinterpret_cast<Rva0071CF40TypeRecord *>(
		reinterpret_cast<char *>( this ) + treeType * 0x5c + 0x1e1cd4 );
	if( !type->m_valid )
		return false;
	if( !type->m_ready )
		return false;

	outPos[ 0 ] = tree->m_posX;
	outPos[ 1 ] = tree->m_posY;
	outPos[ 2 ] = tree->m_posZ;
	*outScale = g_bfmeDirectionWeight1285 * tree->m_scale;

	outShadowA[ 0 ] = type->m_shadowAX;
	outShadowA[ 1 ] = type->m_shadowAY;
	outShadowB[ 0 ] = type->m_shadowBX;
	outShadowB[ 1 ] = type->m_shadowBY;
	return true;
}
