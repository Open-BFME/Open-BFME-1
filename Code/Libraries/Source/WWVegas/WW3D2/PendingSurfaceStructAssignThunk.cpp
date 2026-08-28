// cl: /DNDEBUG /MD /EHs-c-

// FILE: PendingSurfaceStructAssignThunk.cpp //////////////////////////////////
//
// Render2DSentenceClass::PendingSurfaceStruct's compiler-generated assignment
// operator, retail 0x0036DAF0.
//
// render2dsentence.cpp compiles it at 40 of 47 bytes.  Three of the seven are
// two member offsets: retail assigns the derived half of the Renderers member
// at +0x4 and +0x8, where the reference WWLib vector.h puts the same two at
// +0x10 and +0x14 because its VectorClass has a virtual destructor, VectorMax
// and two bools.  BFME's base half of that member is four bytes.
//
// The other four say it is not a VectorClass at all.  Retail's out-of-line
// assign for those four bytes is 0x00887B60, a 121-byte body the ledger already
// carries as an identical-code-folding group led by StringBase<char>'s copy
// constructor.  VectorClass<Render2DClass *>::operator= is a different, landed
// 249-byte body at 0x0092F810.  So Renderers is a four-byte handle with a heavy
// assignment plus two ints, and whatever that handle is, it is not the
// reference container.
//
// The base is therefore spelled provisionally, by shape, and its assignment
// operator pinned under a Bfme* name the way the other structurally-named pins
// in reverse/symbols.csv are.  The row's own identity does not rest on it: what
// this body proves is a four-byte first member and two ints after it.
//
///////////////////////////////////////////////////////////////////////////////

class SurfaceClass;

class BfmeRendererListBase
{
public:

	// Declared, never defined: this is the call at the centre of the body, and
	// the whole reason the base cannot be a plain pointer.
	BfmeRendererListBase &operator=(const BfmeRendererListBase &that);

private:

	void *m_bfmeHandle;													// @0x0

};

class BfmeRendererList : public BfmeRendererListBase
{
private:

	int m_bfmeCount;														// @0x4
	int m_bfmeGrowth;														// @0x8

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class Render2DSentenceClass
{
public:

	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
	struct PendingSurfaceStruct
	{
		SurfaceClass *Surface;										// @0x0
		BfmeRendererList Renderers;								// @0x4
	};

};

// The assignment operator is implicit, so it is emitted only where it is used.
void bfmeAssignPendingSurface( Render2DSentenceClass::PendingSurfaceStruct *dst,
															 const Render2DSentenceClass::PendingSurfaceStruct &src )
{
	*dst = src;
}
