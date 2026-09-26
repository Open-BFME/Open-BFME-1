// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib

// Clean C++ recovery of HTreeClass::Init_Default.
//
// The retail BFME ABI allocates one 0xB4-byte PivotClass without an array
// cookie.  The complete pivot header's destructor changes that new[] shape,
// so this TU keeps the ABI overlay local while retaining the real Matrix3D
// identity code and the already-matched PivotClass constructor.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h

#include "matrix3d.h"
#include <string.h>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/pivot.h
struct PivotClass
{
public:
	PivotClass();

	char Name[16];
	PivotClass *Parent;
	Matrix3D BaseTransform;
	Matrix3D Transform;
	Matrix3D CapTransform;
	int Index;
	bool IsVisible;
	float PivotFade;
	bool WorldSpaceTranslation;
	bool IsCaptured;
	bool Unused;
};

class HTreeClass
{
public:
	void Init_Default();

private:
	void Free()
	{
		if (Pivot != 0) {
			delete[] Pivot;
			Pivot = 0;
		}
		NumPivots = 0;
		ScaleFactor = 1.0f;
	}

	char Name[16];
	int NumPivots;
	PivotClass *Pivot;
	float ScaleFactor;
};

void HTreeClass::Init_Default()
{
	Free();

	NumPivots = 1;
	Pivot = new PivotClass[NumPivots];

	Pivot[0].Index = 0;
	Pivot[0].Parent = 0;
	Pivot[0].BaseTransform.Make_Identity();
	Pivot[0].Transform.Make_Identity();
	Pivot[0].IsVisible = true;
	Pivot[0].PivotFade = 1.0f;
	strcpy(Pivot[0].Name, "RootTransform");
	Name[0] = 0;
}
