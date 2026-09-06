// cl: /DNDEBUG /MD /EHsc
//
// Address-derived body: retail 0x00694D10, size 27. Ghidra names this only as
// a dump; the real name is not proven. Bytes decode to a small "init" method
// on a class holding an AudioEventRTS by value: it copy-constructs the
// caller's AudioEventRTS argument in place at this+0 (thiscall into the
// callee at reloc target 0x00047B27, which reverse/functions.csv already
// binds to ??0AudioEventRTS@@QAE@ABV0@@Z, the AudioEventRTS copy ctor at
// 0x000B2FB0), then zeroes an Int at this+0x70 and a Bool at this+0x74, and
// returns this -- the exact shape of the landed sibling
// BfmeThingBQF::bfmeInitBQF (Code/GameEngine/Source/Common/BfmeConv515.cpp),
// whose m_bfmeHead[0x70]/m_bfmeZero/m_bfmeFlag layout this reuses, except
// this variant's head is copy-constructed from an argument instead of being
// built from a fixed text pointer + flag.

struct Rva00694D10Fields
{
	unsigned char m_bfmeHead[0x70];		///< occupies the embedded AudioEventRTS-sized region
	int m_bfmeZero;					///< +0x70
	bool m_bfmeFlag;					///< +0x74

	void bfmeCopyAudioEvent( const void *event );	///< thiscall(this, event); pinned to 0x00047B27 (AudioEventRTS copy ctor ILT)
	Rva00694D10Fields *bfmeInit( const void *event );
};

// ?bfmeInit@Rva00694D10Fields@@QAEPAU1@PBX@Z
Rva00694D10Fields *Rva00694D10Fields::bfmeInit( const void *event )
{
	bfmeCopyAudioEvent( event );
	m_bfmeZero = 0;
	m_bfmeFlag = false;
	return this;
}
