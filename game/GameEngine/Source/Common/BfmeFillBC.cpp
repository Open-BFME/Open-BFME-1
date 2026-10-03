// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// Retail 0x0040BB60 is the bfmeFillBC helper called by BfmeObjBC::bfmeGoBC
// at 0x0040BC50. The pinned thunk at 0x0002A31A names the helper.

#include "vector3.h"

extern const float g_01075954;
extern const float g_rva01075350;
#define g_bfmeDefaultEG (1.57079637f)
#define g_010AEBB8 (10000.0f)

struct BfmeVecBC
{
	float x;
	float y;
	float z;
};

void bfmeFillBC(BfmeVecBC *out, int a, int b)
{
	Vector3 direction;
	float first = *(volatile const float *)&a * g_01075954 + g_bfmeDefaultEG;
	float firstSine = (float)sin(first);
	float second = *(volatile const float *)&b * g_01075954;
	direction.X = -(float)cos(second) * firstSine;
	direction.Y = -(float)sin(second) * firstSine;
	direction.Z = -(float)cos(first);
	float lengthSquared = direction.Length2();
	if (lengthSquared != g_rva01075350)
	{
		float inverseLength = WWMath::Inv_Sqrt(lengthSquared);
		direction.X *= inverseLength;
		direction.Y *= inverseLength;
		direction.Z *= inverseLength;
	}
	direction.X *= g_010AEBB8;
	direction.Y *= g_010AEBB8;
	direction.Z *= g_010AEBB8;
	out->x = direction.X;
	out->y = direction.Y;
	out->z = direction.Z;
}
