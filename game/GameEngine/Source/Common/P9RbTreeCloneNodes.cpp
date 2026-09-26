// cl: /DNDEBUG /MD /EHs-c-

// Open-BFME5: ten STLport _Rb_tree clone-node bodies.
//
// THE NODE LAYOUT IDENTIFIES THE TEMPLATE.  Every one of the ten allocates a
// block, copies a sub-object at +0x10, zeroes +8 and +0xC, and copies a
// single BYTE at +0.  That is _Rb_tree_node exactly: a colour byte at 0, the
// parent pointer at 4 (never touched here), left at 8, right at 0xC and the
// value at 0x10.  The body is STLport's own _M_clone_node -- create from the
// source's value, take its colour, null both children -- and the value width
// is therefore the node size minus 0x10.
//
// TWO THINGS THE BYTES SETTLE THAT A GUESS WOULD GET WRONG.
//
// The assignment order is colour FIRST, then the two children -- STLport's
// own order.  Written children-first the body is two bytes shorter and the
// colour read no longer hoists above the zeroing.
//
// And these are __stdcall, not __cdecl: the tail is `ret 4`, so the callee
// clears its one argument.  Spelled __cdecl everything else matches and the
// body ends two bytes early on a bare `ret`.
//
// The allocator is chosen at COMPILE time, not at run time: nine call the
// small-block node allocator and the tenth, whose node is 0x84 bytes, calls
// the large one directly with no size test in front of it.  STLport's
// `n > _MAX_BYTES` folds because the node size is a constant.
//
// IDENTITY IS NOT RECOVERED beyond the shape: the value type is named for the
// body's address and modelled by width, and its copy is pinned per body.

void *__cdecl bfmeNodeAllocSmall( unsigned int size );		// 0x0082E540
void *__cdecl bfmeNodeAllocLarge( unsigned int size );		// 0x00881F30

struct BfmeValue00064970
{
	char m_body[ 0x2C - 0x10 ];
};

void __cdecl BfmeCopy00064970( BfmeValue00064970 *destination, const BfmeValue00064970 *source );	// ILT 0x0000EF6B

struct BfmeNode00064970
{
	unsigned char m_bfmeColour;
	BfmeNode00064970 *m_bfmeParent;
	BfmeNode00064970 *m_bfmeLeft;
	BfmeNode00064970 *m_bfmeRight;
	BfmeValue00064970 m_bfmeValue;
};

struct BfmeValue000BF3B0
{
	char m_body[ 0x14 - 0x10 ];
};

void __cdecl BfmeCopy000BF3B0( BfmeValue000BF3B0 *destination, const BfmeValue000BF3B0 *source );	// ILT 0x00007554

struct BfmeNode000BF3B0
{
	unsigned char m_bfmeColour;
	BfmeNode000BF3B0 *m_bfmeParent;
	BfmeNode000BF3B0 *m_bfmeLeft;
	BfmeNode000BF3B0 *m_bfmeRight;
	BfmeValue000BF3B0 m_bfmeValue;
};

struct BfmeValue000BFA00
{
	char m_body[ 0x20 - 0x10 ];
};

void __cdecl BfmeCopy000BFA00( BfmeValue000BFA00 *destination, const BfmeValue000BFA00 *source );	// ILT 0x0000D71F

struct BfmeNode000BFA00
{
	unsigned char m_bfmeColour;
	BfmeNode000BFA00 *m_bfmeParent;
	BfmeNode000BFA00 *m_bfmeLeft;
	BfmeNode000BFA00 *m_bfmeRight;
	BfmeValue000BFA00 m_bfmeValue;
};

struct BfmeValue000EFCB0
{
	char m_body[ 0x1C - 0x10 ];
};

void __cdecl BfmeCopy000EFCB0( BfmeValue000EFCB0 *destination, const BfmeValue000EFCB0 *source );	// ILT 0x0004AA25

struct BfmeNode000EFCB0
{
	unsigned char m_bfmeColour;
	BfmeNode000EFCB0 *m_bfmeParent;
	BfmeNode000EFCB0 *m_bfmeLeft;
	BfmeNode000EFCB0 *m_bfmeRight;
	BfmeValue000EFCB0 m_bfmeValue;
};

struct BfmeValue00136770
{
	char m_body[ 0x84 - 0x10 ];
};

void __cdecl BfmeCopy00136770( BfmeValue00136770 *destination, const BfmeValue00136770 *source );	// ILT 0x00048874

struct BfmeNode00136770
{
	unsigned char m_bfmeColour;
	BfmeNode00136770 *m_bfmeParent;
	BfmeNode00136770 *m_bfmeLeft;
	BfmeNode00136770 *m_bfmeRight;
	BfmeValue00136770 m_bfmeValue;
};

struct BfmeValue00138250
{
	char m_body[ 0x20 - 0x10 ];
};

void __cdecl BfmeCopy00138250( BfmeValue00138250 *destination, const BfmeValue00138250 *source );	// ILT 0x0002289F

struct BfmeNode00138250
{
	unsigned char m_bfmeColour;
	BfmeNode00138250 *m_bfmeParent;
	BfmeNode00138250 *m_bfmeLeft;
	BfmeNode00138250 *m_bfmeRight;
	BfmeValue00138250 m_bfmeValue;
};

struct BfmeValue004D55C0
{
	char m_body[ 0x24 - 0x10 ];
};

void __cdecl BfmeCopy004D55C0( BfmeValue004D55C0 *destination, const BfmeValue004D55C0 *source );	// ILT 0x0002367D

struct BfmeNode004D55C0
{
	unsigned char m_bfmeColour;
	BfmeNode004D55C0 *m_bfmeParent;
	BfmeNode004D55C0 *m_bfmeLeft;
	BfmeNode004D55C0 *m_bfmeRight;
	BfmeValue004D55C0 m_bfmeValue;
};

struct BfmeValue00769060
{
	char m_body[ 0x48 - 0x10 ];
};

void __cdecl BfmeCopy00769060( BfmeValue00769060 *destination, const BfmeValue00769060 *source );	// ILT 0x000366E2

struct BfmeNode00769060
{
	unsigned char m_bfmeColour;
	BfmeNode00769060 *m_bfmeParent;
	BfmeNode00769060 *m_bfmeLeft;
	BfmeNode00769060 *m_bfmeRight;
	BfmeValue00769060 m_bfmeValue;
};

struct BfmeValue009C94C0
{
	char m_body[ 0x30 - 0x10 ];
};

void __cdecl BfmeCopy009C94C0( BfmeValue009C94C0 *destination, const BfmeValue009C94C0 *source );	// ILT 0x009C9120

struct BfmeNode009C94C0
{
	unsigned char m_bfmeColour;
	BfmeNode009C94C0 *m_bfmeParent;
	BfmeNode009C94C0 *m_bfmeLeft;
	BfmeNode009C94C0 *m_bfmeRight;
	BfmeValue009C94C0 m_bfmeValue;
};

struct BfmeValue009D02C0
{
	char m_body[ 0x24 - 0x10 ];
};

void __cdecl BfmeCopy009D02C0( BfmeValue009D02C0 *destination, const BfmeValue009D02C0 *source );	// ILT 0x009CF3C0

struct BfmeNode009D02C0
{
	unsigned char m_bfmeColour;
	BfmeNode009D02C0 *m_bfmeParent;
	BfmeNode009D02C0 *m_bfmeLeft;
	BfmeNode009D02C0 *m_bfmeRight;
	BfmeValue009D02C0 m_bfmeValue;
};

// ?bfmeCloneNode00064970@@YGPAUBfmeNode00064970@@PBU1@@Z		50B
BfmeNode00064970 *__stdcall bfmeCloneNode00064970( const BfmeNode00064970 *source )
{
	BfmeNode00064970 *node = (BfmeNode00064970 *)bfmeNodeAllocSmall( sizeof( BfmeNode00064970 ) );

	BfmeCopy00064970( &node->m_bfmeValue, &source->m_bfmeValue );

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

// ?bfmeCloneNode000BF3B0@@YGPAUBfmeNode000BF3B0@@PBU1@@Z		50B
BfmeNode000BF3B0 *__stdcall bfmeCloneNode000BF3B0( const BfmeNode000BF3B0 *source )
{
	BfmeNode000BF3B0 *node = (BfmeNode000BF3B0 *)bfmeNodeAllocSmall( sizeof( BfmeNode000BF3B0 ) );

	BfmeCopy000BF3B0( &node->m_bfmeValue, &source->m_bfmeValue );

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

// ?bfmeCloneNode000BFA00@@YGPAUBfmeNode000BFA00@@PBU1@@Z		50B
BfmeNode000BFA00 *__stdcall bfmeCloneNode000BFA00( const BfmeNode000BFA00 *source )
{
	BfmeNode000BFA00 *node = (BfmeNode000BFA00 *)bfmeNodeAllocSmall( sizeof( BfmeNode000BFA00 ) );

	BfmeCopy000BFA00( &node->m_bfmeValue, &source->m_bfmeValue );

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

// ?bfmeCloneNode000EFCB0@@YGPAUBfmeNode000EFCB0@@PBU1@@Z		50B
BfmeNode000EFCB0 *__stdcall bfmeCloneNode000EFCB0( const BfmeNode000EFCB0 *source )
{
	BfmeNode000EFCB0 *node = (BfmeNode000EFCB0 *)bfmeNodeAllocSmall( sizeof( BfmeNode000EFCB0 ) );

	BfmeCopy000EFCB0( &node->m_bfmeValue, &source->m_bfmeValue );

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

// ?bfmeCloneNode00136770@@YGPAUBfmeNode00136770@@PBU1@@Z		53B
BfmeNode00136770 *__stdcall bfmeCloneNode00136770( const BfmeNode00136770 *source )
{
	BfmeNode00136770 *node = (BfmeNode00136770 *)bfmeNodeAllocLarge( sizeof( BfmeNode00136770 ) );

	BfmeCopy00136770( &node->m_bfmeValue, &source->m_bfmeValue );

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

// ?bfmeCloneNode00138250@@YGPAUBfmeNode00138250@@PBU1@@Z		50B
BfmeNode00138250 *__stdcall bfmeCloneNode00138250( const BfmeNode00138250 *source )
{
	BfmeNode00138250 *node = (BfmeNode00138250 *)bfmeNodeAllocSmall( sizeof( BfmeNode00138250 ) );

	BfmeCopy00138250( &node->m_bfmeValue, &source->m_bfmeValue );

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

// ?bfmeCloneNode004D55C0@@YGPAUBfmeNode004D55C0@@PBU1@@Z		50B
BfmeNode004D55C0 *__stdcall bfmeCloneNode004D55C0( const BfmeNode004D55C0 *source )
{
	BfmeNode004D55C0 *node = (BfmeNode004D55C0 *)bfmeNodeAllocSmall( sizeof( BfmeNode004D55C0 ) );

	BfmeCopy004D55C0( &node->m_bfmeValue, &source->m_bfmeValue );

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

// ?bfmeCloneNode00769060@@YGPAUBfmeNode00769060@@PBU1@@Z		50B
BfmeNode00769060 *__stdcall bfmeCloneNode00769060( const BfmeNode00769060 *source )
{
	BfmeNode00769060 *node = (BfmeNode00769060 *)bfmeNodeAllocSmall( sizeof( BfmeNode00769060 ) );

	BfmeCopy00769060( &node->m_bfmeValue, &source->m_bfmeValue );

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

// ?bfmeCloneNode009C94C0@@YGPAUBfmeNode009C94C0@@PBU1@@Z		50B
BfmeNode009C94C0 *__stdcall bfmeCloneNode009C94C0( const BfmeNode009C94C0 *source )
{
	BfmeNode009C94C0 *node = (BfmeNode009C94C0 *)bfmeNodeAllocSmall( sizeof( BfmeNode009C94C0 ) );

	BfmeCopy009C94C0( &node->m_bfmeValue, &source->m_bfmeValue );

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

// ?bfmeCloneNode009D02C0@@YGPAUBfmeNode009D02C0@@PBU1@@Z		50B
BfmeNode009D02C0 *__stdcall bfmeCloneNode009D02C0( const BfmeNode009D02C0 *source )
{
	BfmeNode009D02C0 *node = (BfmeNode009D02C0 *)bfmeNodeAllocSmall( sizeof( BfmeNode009D02C0 ) );

	BfmeCopy009D02C0( &node->m_bfmeValue, &source->m_bfmeValue );

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}
