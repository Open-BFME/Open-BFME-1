// cl: /DNDEBUG /MD /EHsc
//
// RenderInfoClass::RenderInfoClass at retail 0x00923690, 114 bytes.
// BFME keeps Zero Hour's member layout up to OverrideFlagLevel at +0x12c and
// adds a second 32-entry pass array at +0x130 plus two words at +0x1b0 and
// +0x1b4, so the class is spelled here with the retail layout rather than
// taken from the Zero Hour header.

class CameraClass;
class MaterialPassClass;
class LightEnvironmentClass;
class TexProjectClass;

class RenderInfoClass
{
public:
	RenderInfoClass(CameraClass &cam);

	enum RINFO_OVERRIDE_FLAGS
	{
		RINFO_OVERRIDE_DEFAULT = 0x0000
	};

	CameraClass &Camera;

	float fog_scale;
	float fog_start;
	float fog_end;
	float alphaOverride;
	float materialPassAlphaOverride;
	float materialPassEmissiveOverride;

	LightEnvironmentClass *light_environment;
	TexProjectClass *Texture_Projector;

protected:
	MaterialPassClass *AdditionalMaterialPassArray[32];
	unsigned AdditionalMaterialPassCount;
	unsigned RejectedMaterialPasses;
	RINFO_OVERRIDE_FLAGS OverrideFlag[32];
	unsigned OverrideFlagLevel;
	MaterialPassClass *Rva00923690PassArray130[32];
	unsigned Rva00923690Field1B0;
	unsigned Rva00923690Field1B4;
};

// ??0RenderInfoClass@@QAE@AAVCameraClass@@@Z
RenderInfoClass::RenderInfoClass(CameraClass &cam) :
	Camera(cam),
	fog_start(0.0f),
	fog_end(0.0f),
	fog_scale(0.0f),
	light_environment(0),
	AdditionalMaterialPassCount(0),
	RejectedMaterialPasses(0),
	OverrideFlagLevel(0),
	Texture_Projector(0),
	alphaOverride(1.0f),
	materialPassAlphaOverride(1.0f),
	materialPassEmissiveOverride(1.0f),
	Rva00923690Field1B0(0),
	Rva00923690Field1B4(0)
{
	OverrideFlag[OverrideFlagLevel] = RINFO_OVERRIDE_DEFAULT;

	for (int i = 0; i < 32; ++i)
	{
		AdditionalMaterialPassArray[i] = 0;
		Rva00923690PassArray130[i] = 0;
	}
}
