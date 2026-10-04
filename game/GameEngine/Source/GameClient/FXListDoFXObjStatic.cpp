// cl: /DNDEBUG /MD /EHs-c-
// BFME's out-of-line FXList::doFXObj(fx, primary, secondary) static wrapper.
// ZH inlines `if (fx) fx->doFXObj(...)`. Retail also consults a bool member
// through ILT 0x00011F77 (body 0x0042DAA0) and skips the play when it is set.

// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include "FXListRetail.h"
class Object;
struct Coord3D;
class Matrix3D;


// ?doFXObj@FXList@@SAXPBV1@PBVObject@@1@Z
void FXList::doFXObj(const FXList *fxList, const Object *primary, const Object *secondary)
{
	if (fxList)
	{
		FXList *self = const_cast<FXList *>(fxList);
		if (!self->bfmeIsBlocked())
			self->doFXObj(primary, secondary);
	}
}

// ?doFXPos@FXList@@SAXPBV1@PBUCoord3D@@PBVMatrix3D@@M1@Z
void FXList::doFXPos(const FXList *fxList, const Coord3D *position,
	const Matrix3D *transform, float speed, const Coord3D *secondary)
{
	if (fxList)
	{
		FXList *self = const_cast<FXList *>(fxList);
		if (!self->bfmeIsBlocked())
			self->doFXPos(position, transform, speed, secondary);
	}
}
