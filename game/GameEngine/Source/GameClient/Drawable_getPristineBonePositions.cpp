// cl: /DNDEBUG /MD /EHsc
// readable body of ?getPristineBonePositions@Drawable@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@H@Z: game/GameEngine/Source/GameClient/Drawable.cpp
//
// Both of Drawable's pristine-bone queries: the five-argument one at retail
// 0x00413930 and BFME's seven-argument one at 0x00413850.
//
// They were two files, and each described the object-draw interface from its own
// call outwards. One put getPristineBonePositionsForConditionState at vtable slot
// 4 with five arguments; the other put a same-named method at slot 3 with seven.
// Neither was wrong: BFME's interface carries BOTH, at adjacent slots, and the
// seven-argument form takes the drawable's condition state at +0x250 as its first
// argument. Declared once, the pair is visible and so is the slot each occupies.
//
// The two Drawable shims stay separate classes on purpose. The ledger's identity
// for the five-argument row is ?getPristineBonePositions@Drawable@@... with an
// explicit object-symbol= mapping onto BfmeDrawableForPristine, but the
// seven-argument row IS ?getPristineBonePositions@BFMEDrawableBoneQuery@@... with
// no such mapping -- its class name is the symbol. Folding the two shims into one
// class renames that row's function and the symbol stops existing in the object.

typedef int Int;
struct Coord3D { float x, y, z; };
class Matrix3D { float m[12]; };

// Slot 3 is BFME's seven-argument form and slot 4 the five-argument one.
//
// These two are declared in the OPPOSITE order to the slots they occupy, and
// that is not a mistake: MSVC lays overloads of the same virtual name into the
// vtable in reverse declaration order. Declared the intuitive way round, the
// five-argument call compiles to `ff 52 0c` -- slot 3 -- where retail has
// `ff 52 10`.
class BfmeObjectDrawForPristine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual Int getPristineBonePositionsForConditionState(
		const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones) const = 0;
	virtual Int getPristineBonePositionsForConditionState(
		const void *conditionState, const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const = 0;
};

class BfmeDrawModuleForPristine
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void slot80() = 0; virtual void slot84() = 0;
	virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual void slot90() = 0; virtual void slot94() = 0;
	virtual BfmeObjectDrawForPristine *getObjectDrawInterface() = 0;
};

class BfmeDrawableForPristine
{
public:
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones) const;
};

class BFMEDrawableBoneQuery
{
public:
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const;
};

// Drawable::getPristineBonePositions, retail 0x00413930, 132 bytes.

// ?getPristineBonePositions@Drawable@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@H@Z
Int BfmeDrawableForPristine::getPristineBonePositions(const char *boneNamePrefix,
	Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones) const
{
	Int count = 0;
	BfmeDrawModuleForPristine **modules =
		*reinterpret_cast<BfmeDrawModuleForPristine ***>((unsigned char *)this + 0x150);
	for (BfmeDrawModuleForPristine **dm = modules; *dm; ++dm)
	{
		if (maxBones <= 0)
			break;
		BfmeObjectDrawForPristine *di = (*dm)->getObjectDrawInterface();
		if (di)
		{
			Int subcount = di->getPristineBonePositionsForConditionState(
				boneNamePrefix, startIndex, positions, transforms, maxBones);
			if (subcount > 0)
			{
				count += subcount;
				if (positions) positions += subcount;
				if (transforms) transforms += subcount;
				maxBones -= subcount;
			}
		}
	}
	return count;
}

// BFME's six-argument Drawable::getPristineBonePositions, retail 0x00413850.

// ?getPristineBonePositions@BFMEDrawableBoneQuery@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@HH@Z
Int BFMEDrawableBoneQuery::getPristineBonePositions(const char *boneNamePrefix,
	Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const
{
	Int count = 0;
	BfmeDrawModuleForPristine **modules =
		*reinterpret_cast<BfmeDrawModuleForPristine ***>((unsigned char *)this + 0x150);
	for (BfmeDrawModuleForPristine **dm = modules; *dm; ++dm) {
		if (maxBones <= 0) {
			break;
		}
		BfmeObjectDrawForPristine *di = (*dm)->getObjectDrawInterface();
		if (di) {
			Int subcount = di->getPristineBonePositionsForConditionState(
				(unsigned char *)this + 0x250, boneNamePrefix, startIndex,
				positions, transforms, maxBones, extra);
			if (subcount > 0) {
				count += subcount;
				if (positions) positions += subcount;
				if (transforms) transforms += subcount;
				maxBones -= subcount;
			}
		}
	}
	return count;
}
