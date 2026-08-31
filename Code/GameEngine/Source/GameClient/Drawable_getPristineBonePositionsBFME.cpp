// cl: /DNDEBUG /MD /EHsc
// BFME's six-argument Drawable::getPristineBonePositions, retail 0x00413850.

typedef int Int;
struct Coord3D { float x, y, z; };
class Matrix3D { float m[12]; };

class BfmeObjectDrawForPristineBFME
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual Int getPristineBonePositionsForConditionState(
		const void *conditionState, const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const = 0;
};

class BfmeDrawModuleForPristineBFME
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
	virtual BfmeObjectDrawForPristineBFME *getObjectDrawInterface() = 0;
};

class BFMEDrawableBoneQuery
{
public:
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const;
};

Int BFMEDrawableBoneQuery::getPristineBonePositions(const char *boneNamePrefix,
	Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const
{
	Int count = 0;
	BfmeDrawModuleForPristineBFME **modules =
		*reinterpret_cast<BfmeDrawModuleForPristineBFME ***>((unsigned char *)this + 0x150);
	for (BfmeDrawModuleForPristineBFME **dm = modules; *dm; ++dm) {
		if (maxBones <= 0) {
			break;
		}
		BfmeObjectDrawForPristineBFME *di = (*dm)->getObjectDrawInterface();
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
