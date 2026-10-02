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
// and two bools.  So Renderers is a four-byte handle with a heavy copy plus two
// ints, and whatever that handle is, it is not the reference container.
//
// The other four say the handle is a StringBase<char>.  Retail's call is
//
//   +0013 push edi          ; &src->Renderers
//   +0014 lea  ebx, [esi+4] ; &dst->Renderers
//   +0018 push edi
//   +0019 mov  ecx, ebx     ; this
//   +001B call 0x00887B60
//
// which is a copy CONSTRUCTION (a source address as the only argument, `this`
// the destination) of the four-byte subobject at +0x4; the two ints that follow
// are copied inline by the caller.  0x00887B60 is the ledger's
// ??0?$StringBase@D@@AAE@ABV0@@Z (functions.csv row 1621, 121 bytes, matched in
// game/Libraries/Source/string/StringBase.cpp) - StringBase<char>'s copy
// constructor, shared by identical-code folding with GameSpyGroupRoom's and
// BuddyInfo's.  VectorClass<Render2DClass *>::operator= is a different, landed
// 249-byte body at 0x0092F810, and StringBase<char>::operator= is a third at
// 0x008881B0, so the address identifies the copy constructor and nothing else.
//
// So the handle is spelled as the real type: AsciiString, four bytes, whose
// copy constructor is inline precisely because retail call sites that copy one
// emit `call StringBase<char>::StringBase` directly (see
// game/Libraries/Source/WWVegas/WWLib/ascii_string.h).  Nothing here is a
// provisional name any more and no pin is needed: the callee is defined.
//
// The assignment operator is written as the copy of Surface followed by a
// placement new of `this` from a copy constructor that initialises only
// Renderers, because that is the shape retail emits.  Two other spellings were
// measured and rejected: a member-wise `Renderers = that.Renderers` calls
// StringBase<char>::operator= at 0x008881B0 (wrong callee, wrong rel32), and
// placement-newing the member rather than `this` makes MSVC guard the
// construction with a `test`/`je` pair (85 f6 74 xx) that retail's 47 bytes have
// no room for - it only omits the guard when the placement address is `this`.
//
///////////////////////////////////////////////////////////////////////////////

#include <new>

#include "../WWLib/ascii_string.h"

class SurfaceClass;

// The four-byte handle, and the two ints BFME keeps beside it.
class BfmeRendererListBase
{
public:

	AsciiString m_bfmeHandle;														// @0x0// @0x0

};

class BfmeRendererList : public BfmeRendererListBase
{
private:

	int m_bfmeCount;														// @0x4
	int m_bfmeGrowth;														// @0x8

};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class Render2DSentenceClass
{
public:

	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
	struct PendingSurfaceStruct
	{
		SurfaceClass *Surface;										// @0x0
		BfmeRendererList Renderers;								// @0x4

		// Builds Renderers in place and leaves Surface to the caller, which is
		// what retail's 47 bytes do: one call, then the two int copies.
		PendingSurfaceStruct(const PendingSurfaceStruct &that) : Renderers(that.Renderers) {}

		PendingSurfaceStruct &operator=(const PendingSurfaceStruct &that)
		{
			Surface = that.Surface;
			::new (static_cast<void *>(this)) PendingSurfaceStruct(that);
			return *this;
		}

	};

};

// The assignment operator is used, so it is emitted; this wrapper exists so
// the body above is odr-used.
void bfmeAssignPendingSurface( Render2DSentenceClass::PendingSurfaceStruct *dst,
															 const Render2DSentenceClass::PendingSurfaceStruct &src )
{
	*dst = src;
}
