// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the nine accessors at 0x000CD680-0x000CD750, address-derived name.
//
// IDENTITY IS NOT ASSERTED. Two independent investigations (re_attempts
// 0x000CD750) eliminated every candidate they could reach: no named caller for
// any of the nine (no rel32 reaches them directly or through the one jmp
// thunk), no vtables.tsv slot, no string_xrefs entry, and GameInfo::m_slot,
// LANPlayer/LANGameSlot, LANAPIInterface, LANGameInfo, NAT.h sourcePorts,
// NetCommandList, FrameData and the GameSpy PeerDefs/StagingRoomGameInfo
// classes all ruled out by layout. The surrounding 0xCB000-0xD1000 is a
// heterogeneous mix of unrelated TUs, so neighbour attribution is unreliable
// here. The class name below is the address of the first body, nothing more.
//
// What the bytes do say: one class holds three POINTERS to separately
// allocated arrays of a 16-byte element, at this+0x0C, this+0x63C and
// this+0x658. The element has a signed 16-bit value at +0x00 and a pointer at
// +0x0C. Each pointer gets the same three accessors: read the first element's
// key, read element i's key, and take the address of element i's pointer field.
//
// One codegen note worth keeping. The SIB byte differs between the +0x0C group
// and the other two -- 0x08 (base eax, index ecx) against 0x01 (base ecx,
// index eax) -- purely because the member load that feeds it takes an int8
// displacement in the first case and an int32 in the other two. It is not a
// source-level difference: all nine bodies here are the same three expressions
// written three times, and all nine matched on the first compile.

typedef int Int;
typedef short Short;

struct Gen_000cd680_Element
{
	Short m_key;
	char m_unknown02[10];
	void *m_pointer;
};

class Gen_000cd680
{
public:
	Int firstKeyA( void ) const;
	Int keyAtA( Int index ) const;
	void **pointerAtA( Int index ) const;

	Int firstKeyB( void ) const;
	Int keyAtB( Int index ) const;
	void **pointerAtB( Int index ) const;

	Int firstKeyC( void ) const;
	Int keyAtC( Int index ) const;
	void **pointerAtC( Int index ) const;

private:
	char m_unknown00[0x0C];
	Gen_000cd680_Element *m_arrayA;			// +0x0C
	char m_unknown10[0x63C - 0x10];
	Gen_000cd680_Element *m_arrayB;			// +0x63C
	char m_unknown640[0x658 - 0x640];
	Gen_000cd680_Element *m_arrayC;			// +0x658
};

Int Gen_000cd680::firstKeyA( void ) const { return m_arrayA[0].m_key; }
Int Gen_000cd680::keyAtA( Int index ) const { return m_arrayA[index].m_key; }
void **Gen_000cd680::pointerAtA( Int index ) const { return &m_arrayA[index].m_pointer; }

Int Gen_000cd680::firstKeyB( void ) const { return m_arrayB[0].m_key; }
Int Gen_000cd680::keyAtB( Int index ) const { return m_arrayB[index].m_key; }
void **Gen_000cd680::pointerAtB( Int index ) const { return &m_arrayB[index].m_pointer; }

Int Gen_000cd680::firstKeyC( void ) const { return m_arrayC[0].m_key; }
Int Gen_000cd680::keyAtC( Int index ) const { return m_arrayC[index].m_key; }
void **Gen_000cd680::pointerAtC( Int index ) const { return &m_arrayC[index].m_pointer; }
