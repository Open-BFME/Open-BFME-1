// ?query@Rva00149010AerialPathfinder@@QAE_NPAVRva00149010Object@@PAVBfmeObjGK@@MM@Z
// partial score=0.82 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc-
//
// BFME AerialPathfinder helper at retail RVA 0x00149010 (219 bytes).  The
// Giant Bird selector at 0x002BC9C0 supplies this member's four stack
// arguments and fixes the owner as TheAerialPathfinder.  The two preceding
// AerialPathfinder siblings establish the +0x0C list-bearing object layout;
// this body only needs the object's AI pointer at +0x204 and the query flag
// at +0x24.  The boundary is the final `ret 0x10` at 0x001490E8.

typedef bool Bool;
typedef float Real;

struct Rva00149010Result
{
	Real x;
	Real y;
	Real z;
};

class Rva00149010Object
{
private:
	unsigned char m_pad000[0x204];

public:
	void *m_ai;
};

class BfmeVec3GK
{
public:
	Real x;
	Real y;
	Real z;
};

class BfmeObjGK
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void start(int, int, Real, Real, int, int);

	unsigned char m_pad014[0x14];
	Real m_range;
	unsigned char m_pad020[8];
	Bool m_valid;
	unsigned char m_pad025[0x23];
	BfmeVec3GK m_result;
};

extern Bool __stdcall bfmeTryGK(BfmeObjGK *obj, Real range, BfmeVec3GK *out);

class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual Real getGroundHeight(Real x, Real y, void *normal = 0) = 0;
};

class Rva00149010AerialPathfinder
{
public:
	Bool query(Rva00149010Object *object, BfmeObjGK *queryObject,
		Real range, Real mode);
	Bool helper(Rva00149010Object *object, Rva00149010Result *result,
		BfmeObjGK **queryOutput, Rva00149010Result *helperPosition);
};

#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define TheAerialPathfinder (*(Rva00149010AerialPathfinder **)0x012EF1F8)

// The helper body is still the generated 0x00148C70 family member.  Calling
// its already-ledgered incremental-link thunk preserves retail's direct call
// and callee-cleaned four-word ABI while this body is reconstructed.
#pragma comment(linker, "/alternatename:?helper@Rva00149010AerialPathfinder@@QAE_NPAVRva00149010Object@@PAURva00149010Result@@PAPAVBfmeObjGK@@PAURva00149010Result@@Z=?j_0003f6a7@@YAXXZ")

Bool Rva00149010AerialPathfinder::query(Rva00149010Object *object,
	BfmeObjGK *queryObject, Real range, Real mode)
{
	if (object->m_ai == 0)
		goto success;
	if (!queryObject->m_valid)
		goto success;

	Rva00149010Result result;
	if (!bfmeTryGK(queryObject, range, (BfmeVec3GK *)&result))
		goto success;

	result.z -= mode * *(Real *)0x01094A50;
	Bool terrainClear = false;
	if (TheTerrainLogic->getGroundHeight(result.x, result.y, 0) < result.z)
		terrainClear = true;

	Rva00149010Result helperPosition = { 0, 0, 0 };
	queryObject = 0;
	Bool helperResult = TheAerialPathfinder->helper(object, &result,
		&queryObject, &helperPosition);

	if (terrainClear && helperResult)
		goto success;
	return false;

success:
	return true;
}
