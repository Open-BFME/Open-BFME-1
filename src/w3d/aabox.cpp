// cl: /DNDEBUG /MD


#include "aabox.h"
#include "colmath.h"
#include "colmathinlines.h"
#include <float.h>


void AABoxClass::Init_Random(float min_center,float max_center,float min_extent,float max_extent)
{
	Center.X = min_center + WWMath::Random_Float() * (max_center - min_center);
	Center.Y = min_center + WWMath::Random_Float() * (max_center - min_center);
	Center.Z = min_center + WWMath::Random_Float() * (max_center - min_center);

	Extent.X = min_extent + WWMath::Random_Float() * (max_extent - min_extent);
	Extent.Y = min_extent + WWMath::Random_Float() * (max_extent - min_extent);
	Extent.Z = min_extent + WWMath::Random_Float() * (max_extent - min_extent);
}


void AABoxClass::Transform(const Matrix3D & tm,const AABoxClass & in,AABoxClass * out)
{
	tm.Transform_Center_Extent_AABox(in.Center,in.Extent,&(out->Center),&(out->Extent));
}

void MinMaxAABoxClass::Init_Empty(void)
{
	MinCorner.Set(FLT_MAX,FLT_MAX,FLT_MAX);
	MaxCorner.Set(-FLT_MAX,-FLT_MAX,-FLT_MAX);
}
