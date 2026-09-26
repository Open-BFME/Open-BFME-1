// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
#include "part_ldr.h"
#include "part_emt.h"
#include "texture.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(pointer) \
{ \
	if (pointer) { \
		delete pointer; \
		pointer = 0; \
	} \
}
#endif

// The retail alpha probe is currently an anonymous 3-byte helper at
// 0x0090C640. Reuse its existing generic ABI shim without assigning it a new
// identity; the caller and handle layout establish the call shape here.
class Gen_0090c640
{
public:
	bool m(void);
};

class BFMEWaterTrackTextureHandle : public Gen_0090c640
{
public:
	TextureBaseClass *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mip_count, int format);

void ParticleEmitterDefClass::Convert_To_Ver2(void)
{
	if (m_Version < 0x00020000) {
		m_InfoV2.BurstSize = 1;
		m_InfoV2.OutwardVel = 0;
		m_InfoV2.VelInherit = 0;

		ShaderClass shader = ShaderClass::_PresetAdditiveSpriteShader;
		BFMEWaterTrackTextureHandle texture =
			BFMEGetWaterTrackTexture(m_Info.TextureFilename, 0, 0);
		if (texture.m_texture != NULL) {
			if (texture.m()) {
				shader = ShaderClass::_PresetAlphaSpriteShader;
			}
		}
		W3dUtilityClass::Convert_Shader(shader, &m_InfoV2.Shader);

		m_InfoV2.CreationVolume.ClassID = Vector3Randomizer::CLASSID_SOLIDBOX;
		m_InfoV2.CreationVolume.Value1 = m_Info.PositionRandom / 1000.0f;
		m_InfoV2.CreationVolume.Value2 = m_Info.PositionRandom / 1000.0f;
		m_InfoV2.CreationVolume.Value3 = m_Info.PositionRandom / 1000.0f;

		m_InfoV2.VelRandom.ClassID = Vector3Randomizer::CLASSID_SOLIDBOX;
		m_InfoV2.VelRandom.Value1 = m_Info.VelocityRandom;
		m_InfoV2.VelRandom.Value2 = m_Info.VelocityRandom;
		m_InfoV2.VelRandom.Value3 = m_Info.VelocityRandom;

		SAFE_DELETE(m_pCreationVolume);
		SAFE_DELETE(m_pVelocityRandomizer);
		m_pCreationVolume = Create_Randomizer(m_InfoV2.CreationVolume);
		m_pVelocityRandomizer = Create_Randomizer(m_InfoV2.VelRandom);

		Free_Props();
		m_ColorKeyframes.Start = RGBA_TO_VECTOR3(m_Info.StartColor);
		m_ColorKeyframes.Rand = Vector3(0, 0, 0);
		m_ColorKeyframes.NumKeyFrames = 1;
		m_ColorKeyframes.KeyTimes = W3DNEW float(m_Info.FadeTime);
		m_ColorKeyframes.Values = W3DNEW Vector3(RGBA_TO_VECTOR3(m_Info.EndColor));

		m_OpacityKeyframes.Start = ((float)(m_Info.StartColor.A)) / 255;
		m_OpacityKeyframes.Rand = 0;
		m_OpacityKeyframes.NumKeyFrames = 1;
		m_OpacityKeyframes.KeyTimes = W3DNEW float(m_Info.FadeTime);
		m_OpacityKeyframes.Values = W3DNEW float(((float)(m_Info.EndColor.A)) / 255);

		m_SizeKeyframes.Start = m_Info.StartSize;
		m_SizeKeyframes.Rand = 0;
		m_SizeKeyframes.NumKeyFrames = 0;
	}

	return;
}
