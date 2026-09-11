// cl: /DNDEBUG /MD /EHs-c-
// BFME's out-of-line five-argument FXList::doFXPos static wrapper.  Its
// null/culling/member-call structure is the positional counterpart of the
// exact FXList::doFXObj static wrapper at 0x00065DE0.  Retail routes the final
// call through ILT 0x0001BB21 to the canonical four-argument member body.

struct Coord3D;
class Matrix3D;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *position,
		const Matrix3D *transform, float speed, const Coord3D *secondary);
	bool bfmeIsBlocked(void) const;
	void doFXPos(const Coord3D *position, const Matrix3D *transform,
		float speed, const Coord3D *secondary) const;
};

// ?doFXPos@FXList@@SAXPBV1@PBUCoord3D@@PBVMatrix3D@@M1@Z
void FXList::doFXPos(const FXList *fx, const Coord3D *position,
	const Matrix3D *transform, float speed, const Coord3D *secondary)
{
	if (fx)
	{
		if (!fx->bfmeIsBlocked())
			fx->doFXPos(position, transform, speed, secondary);
	}
}
