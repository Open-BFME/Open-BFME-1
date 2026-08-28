// cl: /DNDEBUG /MD /EHsc

// FILE: PivotClassVectorDelete.cpp ///////////////////////////////////////////
//
// PivotClass' vector deleting destructor, retail 0x001B1480.
//
// htree.cpp compiles it at 79 of 80 bytes and the single disagreement is the
// element size handed to `eh vector destructor iterator': retail pushes 0x88,
// the reference pivot.h gives 0xb4.  BFME's PivotClass is 44 bytes narrower.
// pivot.h is included by most of WW3D2, so the size is asserted here instead,
// on a stand-in of exactly that width.
//
// 44 bytes is one Matrix3D (48) less one word gained elsewhere, which is what
// the LAZY_CAP_MTX_ALLOC arm of that header does -- it replaces the CapTransform
// matrix with a pointer.  This body proves the size and nothing else about the
// arrangement, so the stand-in is deliberately opaque rather than a guess at
// which arm BFME compiled.
//
///////////////////////////////////////////////////////////////////////////////

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/pivot.h
struct PivotClass
{
	// User-declared, so `delete []' still has to walk the array -- but empty, so
	// the scalar arm has nothing to call.  Retail's scalar arm goes straight to
	// operator delete, which is how the emptiness shows up in the bytes; the
	// array arm still needs an out-of-line copy to hand the iterator, and that
	// is the 0x0043dc2b it pushes.
	~PivotClass() {}

	char m_bfmeOpaque[0x88];
};

void bfmeDeletePivotArray( PivotClass *pivots )
{
	delete [] pivots;
}
