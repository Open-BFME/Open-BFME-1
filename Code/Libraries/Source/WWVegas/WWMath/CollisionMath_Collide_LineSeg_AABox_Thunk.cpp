// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#include "colmath.h"
#include "lineseg.h"
#include "aabox.h"

struct BFMEBoxTestStruct
{
	Vector3 Min;
	Vector3 Max;
	Vector3 P0;
	Vector3 DP;
	float Fraction;
	bool Inside;
	int Axis;
	int Side;
};

enum BFMEBoxSideType
{
	BFME_BOX_SIDE_NEGATIVE,
	BFME_BOX_SIDE_POSITIVE,
	BFME_BOX_SIDE_MIDDLE
};

static Vector3 BFMEBoxNormal[3][2] =
{
	{ Vector3(-1.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f) },
	{ Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f) },
	{ Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 0.0f, 1.0f) }
};

bool BFME_Test_Aligned_Box(BFMEBoxTestStruct *test);

bool CollisionMath::Collide(const LineSegClass &line, const AABoxClass &box, CastResultStruct *result)
{
	BFMEBoxTestStruct test;
	test.Min = box.Center - box.Extent;
	test.Max = box.Center + box.Extent;
	test.P0 = line.Get_P0();
	test.DP = line.Get_DP();

	if (!BFME_Test_Aligned_Box(&test)) {
		return false;
	}
	if (test.Inside) {
		result->StartBad = true;
		return true;
	}
	if (test.Fraction < result->Fraction) {
		result->Fraction = test.Fraction;
		result->Normal = BFMEBoxNormal[test.Axis][test.Side];
		if (result->ComputeContactPoint) {
			result->ContactPoint = line.Get_P0() + result->Fraction * line.Get_DP();
		}
		return true;
	}
	return false;
}
