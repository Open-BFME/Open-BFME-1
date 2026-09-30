// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// ?bfmeDoESM@BfmeHostESM@@QAEDPAVBfmeThingESM@@UBfmePairESM@@PAPAXHH@Z
// Retail 0x00609BA0 (400 B): vertical ray cast at (x, y) against a render object; the ILT 0x00021CEC pin names it.
// Callers 0x00609DA0 and 0x003C8160 pass a float height output as out; retail reads the last argument as one byte.

#include "lineseg.h"
#include "coltest.h"
#include "rendobj.h"

class BfmeThingESM;

struct BfmePairESM
{
	float x;
	float y;
};

class BfmeHostESM
{
public:
	char bfmeDoESM(BfmeThingESM *thing, BfmePairESM pair, void **out, int one,
		int zero);
};

char BfmeHostESM::bfmeDoESM(BfmeThingESM *thing, BfmePairESM pair, void **out, int one,
	int zero)
{
	RenderObjClass *robj = (RenderObjClass *)thing;
	AABoxClass box = robj->Get_Bounding_Box();

	if (pair.x < box.Center.X - box.Extent.X)
		return 0;
	if (pair.x > box.Center.X + box.Extent.X)
		return 0;
	if (pair.y < box.Center.Y - box.Extent.Y)
		return 0;
	if (pair.y > box.Center.Y + box.Extent.Y)
		return 0;

	CastResultStruct result;
	result.ComputeContactPoint = true;
	LineSegClass line(Vector3(pair.x, pair.y, 500.0f), Vector3(pair.x, pair.y, -500.0f));
	RayCollisionTestClass ray(line, &result, one, false, false);
	// The pinned decoration types the last argument as int; retail reads its low byte as a bool.
	ray.CheckHidden = *(bool *)&zero;

	char hit = robj->Cast_Ray(ray);
	if (out)
	{
		if (hit)
			*(float *)out = ray.Result->ContactPoint.Z;
		else
			*(float *)out = 0.0f;
	}
	return hit;
}
