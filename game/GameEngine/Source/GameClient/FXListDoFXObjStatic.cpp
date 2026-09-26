// cl: /DNDEBUG /MD /EHs-c-
// BFME's out-of-line FXList::doFXObj(fx, primary, secondary) static wrapper.
// ZH inlines `if (fx) fx->doFXObj(...)`. Retail also consults a bool member
// through ILT 0x00011F77 (body 0x0042DAA0) and skips the play when it is set.

class Object;
struct Coord3D;
class Matrix3D;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	static void doFXObj(const FXList *fxList, const Object *primary, const Object *secondary);
	static void doFXPos(const FXList *fxList, const Coord3D *position,
		const Matrix3D *transform, float speed, const Coord3D *secondary);
	bool bfmeIsBlocked(void) const;
	void doFXObj(const Object *primary, const Object *secondary) const;
	void doFXPos(const Coord3D *position, const Matrix3D *transform,
		float speed, const Coord3D *secondary) const;
};

// ?doFXObj@FXList@@SAXPBV1@PBVObject@@1@Z
void FXList::doFXObj(const FXList *fxList, const Object *primary, const Object *secondary)
{
	if (fxList)
	{
		if (!fxList->bfmeIsBlocked())
			fxList->doFXObj(primary, secondary);
	}
}

// ?doFXPos@FXList@@SAXPBV1@PBUCoord3D@@PBVMatrix3D@@M1@Z
void FXList::doFXPos(const FXList *fxList, const Coord3D *position,
	const Matrix3D *transform, float speed, const Coord3D *secondary)
{
	if (fxList)
	{
		if (!fxList->bfmeIsBlocked())
			fxList->doFXPos(position, transform, speed, secondary);
	}
}
