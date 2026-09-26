// ?computeSuperweaponTarget@AIPlayer@@UAE_NPBVSpecialPowerTemplate@@PAUCoord3D@@HM@Z
// partial score=0.76 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;

	Real width(void) const { return hi.x - lo.x; }
	Real height(void) const { return hi.y - lo.y; }
};

struct FindPositionOptions
{
	Int value[8];
};

class Rva003FD060TerrainLogic
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual Real getGroundHeight(Real x, Real y);
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern Real g_bfmeDefaultBU;
extern Real g_bfmeK1253;
extern Real g_bfmeScaleBK;
extern "C" __declspec(dllimport) double __cdecl bfmeMathVE(double value);

class Rva00166A80
{
public:
	static void getPlayerStructureBounds(Region2D *bounds, Int playerNdx);
	static Int getPlayerSuperweaponValue(Coord3D *center, Int playerNdx,
		Real radius);
	static Bool findPositionAround(const Coord3D *center,
		const FindPositionOptions *options, Coord3D *result);

	Bool compute(const void *power, Coord3D *retPos, Int playerNdx,
		Real weaponRadius);
};

#pragma comment(linker, "/alternatename:?getPlayerStructureBounds@Rva00166A80@@SAXPAURegion2D@@H@Z=?j_000362aa@@YAXXZ")
#pragma comment(linker, "/alternatename:?getPlayerSuperweaponValue@Rva00166A80@@SAHPAUCoord3D@@HM@Z=?j_000255db@@YAXXZ")
#pragma comment(linker, "/alternatename:?findPositionAround@Rva00166A80@@SA_NPBUCoord3D@@PBUFindPositionOptions@@PAU2@@Z=?j_00026c4c@@YAXXZ")

struct Rva00166A80Override
{
	char value[0x18];
};

class Rva00166A80SubBOB
{
public:
	void *bfmeFindBOB(void);
};

#pragma comment(linker, "/alternatename:?bfmeFindBOB@Rva00166A80SubBOB@@QAEPAXXZ=?j_00048c61@@YAXXZ")

Bool Rva00166A80::compute(const void *power, Coord3D *retPos, Int playerNdx,
	Real weaponRadius)
{
	Int xCount;
	Int yCount;
	Int cash;
	Coord3D pos;
	Coord3D bestPos;
	Int x;
	Int y;
	{
		Region2D bounds;
		getPlayerStructureBounds(&bounds, playerNdx);

		if (weaponRadius < g_bfmeDefaultBU)
			weaponRadius = 1.0f;

		bounds.lo.x += weaponRadius;
		if (bounds.hi.x - weaponRadius < bounds.lo.x)
			bounds.lo.x =
				(bounds.hi.x - weaponRadius + bounds.lo.x) * g_bfmeK1253;
		if (bounds.hi.y < bounds.lo.y)
			bounds.hi.y = bounds.lo.y = (bounds.hi.y + bounds.lo.y) * g_bfmeK1253;

		xCount = (Int)bfmeMathVE((double)((g_bfmeDefaultBU / weaponRadius) *
			(bounds.hi.x - weaponRadius - bounds.lo.x))) + 1;
		yCount = (Int)bfmeMathVE((double)((g_bfmeDefaultBU / weaponRadius) * bounds.height())) + 1;
		if (xCount > 10)
			xCount = 10;
		if (yCount > 10)
			yCount = 10;

		cash = -1;
		for (x = 0; x < xCount; ++x)
		{
			for (y = 0; y < yCount; ++y)
			{
				pos.x = bounds.lo.x +
					((bounds.hi.x - weaponRadius - bounds.lo.x) * x) / xCount;
				pos.y = bounds.lo.y + (bounds.height() * y) / yCount;
				pos.z = 0;
				Int curCash = getPlayerSuperweaponValue(&pos, playerNdx,
					2 * weaponRadius);
				if (curCash > cash)
				{
					cash = curCash;
					bestPos = pos;
				}
			}
		}
	}

	Coord3D veryBestPos;
	xCount = 11;
	yCount = 11;
	cash = -1;
	Int count = 0;
	for (x = 0; x < xCount; ++x)
	{
		for (y = 0; y < yCount; ++y)
		{
			pos.x = bestPos.x + (x - 5) * (weaponRadius * g_bfmeScaleBK);
			pos.y = bestPos.y + (y - 5) * (weaponRadius * g_bfmeScaleBK);
			pos.z = 0;
			Int curCash = getPlayerSuperweaponValue(&pos, playerNdx,
				weaponRadius);
			if (curCash > cash)
			{
				cash = curCash;
				veryBestPos = pos;
				count = 1;
			}
			else if (curCash == cash)
			{
				veryBestPos.x += pos.x;
				veryBestPos.y += pos.y;
				++count;
			}
		}
	}

	if (count > 1)
	{
		veryBestPos.x /= count;
		veryBestPos.y /= count;
	}

	Rva00166A80SubBOB *sub = *(Rva00166A80SubBOB **)((char *)power + 4);
	if (sub != 0)
	{
		Rva00166A80SubBOB *finalSub = *(Rva00166A80SubBOB **)((char *)sub + 4);
		if (finalSub != 0)
		{
			void *bob = finalSub->bfmeFindBOB();
			if (bob != 0 && *(Int *)((char *)bob + 0x14) == 0x4e)
			{
				FindPositionOptions options;
				options.value[0] = 0;
				options.value[1] = 0;
				options.value[2] = 0x43960000;
				options.value[3] = 0xc7c34ff3;
				options.value[4] = 0x501502f9;
				options.value[5] = 0;
				options.value[6] = 0;
				options.value[7] = 0;
				findPositionAround(&veryBestPos, &options, &veryBestPos);
			}
		}
	}

	veryBestPos.z = TheTerrainLogic->getGroundHeight(veryBestPos.x,
		veryBestPos.y);
	*retPos = veryBestPos;
	return cash > -1;
}
