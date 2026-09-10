// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// ??4LightEnvironmentClass@@QAEAAV0@ABV0@@Z
// BFME adds a leading byte before the Zero Hour light-environment layout.

#include "always.h"
#include "vector3.h"

class LightEnvironmentClass
{
public:
	LightEnvironmentClass &operator=(const LightEnvironmentClass &that);

private:
	struct InputLightStruct
	{
		InputLightStruct &operator=(const InputLightStruct &that);

		Vector3 Direction;
		Vector3 Ambient;
		Vector3 Diffuse;
		bool DiffuseRejected;
		bool Point;
		Vector3 Center;
		float InnerRadius;
		float OuterRadius;
		Vector3 PointAmbient;
		Vector3 PointDiffuse;
	};

	struct OutputLightStruct
	{
		Vector3 Direction;
		Vector3 Diffuse;
	};

	unsigned char BfmeLeadingByte;
	int LightCount;
	Vector3 ObjectCenter;
	InputLightStruct InputLights[4];
	Vector3 OutputAmbient;
	OutputLightStruct OutputLights[4];
	InputLightStruct FillLight;
	float FillIntensity;
};

typedef char VerifyLightEnvironmentSize[
	(sizeof(LightEnvironmentClass) == 0x228) ? 1 : -1];

LightEnvironmentClass &LightEnvironmentClass::operator=(
	const LightEnvironmentClass &that)
{
	BfmeLeadingByte = that.BfmeLeadingByte;
	LightCount = that.LightCount;
	ObjectCenter = that.ObjectCenter;
	for (int i = 0; i < 4; ++i) {
		InputLights[i] = that.InputLights[i];
	}
	OutputAmbient = that.OutputAmbient;
	for (int i = 0; i < 4; ++i) {
		OutputLights[i] = that.OutputLights[i];
	}
	FillLight = that.FillLight;
	FillIntensity = that.FillIntensity;
	return *this;
}
