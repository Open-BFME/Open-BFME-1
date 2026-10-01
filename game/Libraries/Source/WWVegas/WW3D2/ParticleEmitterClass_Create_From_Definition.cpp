// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Iinputs/reference/shims/sweep
// readable body of ?Create_From_Definition@ParticleEmitterClass@@: game/Libraries/Source/WWVegas/WW3D2/part_emt.cpp
//
// ParticleEmitterClass::Create_From_Definition, retail 0x0097F5D0 (848 bytes).
//
// Identity: the matched caller at 0x00971150 and the official WW3D2
// part_emt.cpp: texture lookup, shader conversion, the six keyframe peeks, the
// 25-argument emitter constructor, the twelve keyframe array deletes, Set_Name
// and the texture release, in that order.
//
// BFME differences, read from the retail body:
//  * the texture comes from BFMEGetWaterTrackTexture (0x0090E910) as an owning
//    handle, the local is that handle (its destructor 0x0005CC00 is the unwind
//    action of states 0 and 3), and the final release is an assignment of
//    NULL to it;
//  * the emitter constructor receives the handle by reference: retail pushes
//    the address of the local handle in the texture slot. The matched
//    constructor row keeps the Zero Hour spelling `TextureClass *tex`, so the
//    handle's address travels through that spelling;
//  * the fog check of Get_Activate_Fog_On_Load is gone.
//
// This body needs /EHsc for the handle's unwind states, so it lives in its own
// TU rather than in the /EHsc- part_emt.cpp.

#include "part_emt.h"
#include "part_ldr.h"
#include "texture.h"


class BFMEWaterTrackTextureHandle
{
public:
	BFMEWaterTrackTextureHandle(TextureClass *texture = 0) : m_texture(texture) {}
	BFMEWaterTrackTextureHandle(const BFMEWaterTrackTextureHandle &other)
		: m_texture(other.m_texture)
	{
		if (m_texture)
			++*(unsigned short *)((char *)m_texture + 4);
	}
	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			((TextureBaseClass *)m_texture)->Release_Ref();
	}
	BFMEWaterTrackTextureHandle &operator=(const BFMEWaterTrackTextureHandle &other)
	{
		if (other.m_texture)
			++*(unsigned short *)((char *)other.m_texture + 4);
		if (m_texture)
			((TextureBaseClass *)m_texture)->Release_Ref();
		m_texture = other.m_texture;
		return *this;
	}
	TextureClass *Peek(void) const { return m_texture; }

	TextureClass *m_texture;
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mipCount, int format);


// ?Create_From_Definition@ParticleEmitterClass@@SAPAV1@ABVParticleEmitterDefClass@@@Z
ParticleEmitterClass *
ParticleEmitterClass::Create_From_Definition (const ParticleEmitterDefClass &definition)
{
	// Attempt to load the texture for this emitter
	const char *ptexture_filename = definition.Get_Texture_Filename ();
	BFMEWaterTrackTextureHandle ptexture;
	if (ptexture_filename && ptexture_filename[0]) {
		ptexture = BFMEGetWaterTrackTexture((char *)ptexture_filename, 0, 0);
	}

	// Assume failure
	ParticleEmitterClass *pemitter;

	ShaderClass shader;
	definition.Get_Shader (shader);
	/*if (ptexture) {
		// If texture has an alpha channel do alpha blending instead of additive
		// (which is the default for point groups):
		srTextureIFace::Dimensions dimensions;
		ptexture->getDimensions(dimensions);
		if (dimensions.pixelFormat.aBits > 0) {
			shader = ShaderClass::_PresetAlphaSpriteShader;
		}
	}*/

	//
	//	Peek at the definition's keyframes
	//
	ParticlePropertyStruct<Vector3> color_keys;
	ParticlePropertyStruct<float> opacity_keys;
	ParticlePropertyStruct<float> size_keys;
	ParticlePropertyStruct<float> rotation_keys;
	ParticlePropertyStruct<float> frame_keys;
	ParticlePropertyStruct<float> blur_time_keys;

	definition.Get_Color_Keyframes (color_keys);
	definition.Get_Opacity_Keyframes (opacity_keys);
	definition.Get_Size_Keyframes (size_keys);
	definition.Get_Rotation_Keyframes (rotation_keys);
	definition.Get_Frame_Keyframes (frame_keys);
	definition.Get_Blur_Time_Keyframes (blur_time_keys);

	//
	//	Create the emitter
	//
	pemitter = NEW_REF( ParticleEmitterClass, (	definition.Get_Emission_Rate (),
																definition.Get_Burst_Size (),
																definition.Get_Creation_Volume (),
																definition.Get_Velocity (), 
																definition.Get_Velocity_Random (),
																definition.Get_Outward_Vel (),
																definition.Get_Vel_Inherit (), 
																color_keys,
																opacity_keys,
																size_keys,
																rotation_keys,
																definition.Get_Initial_Orientation_Random(),
																frame_keys,
																blur_time_keys,
																definition.Get_Acceleration (),
																definition.Get_Lifetime (),
																definition.Get_Future_Start_Time(),
															// BFME passes the handle itself; see the note above.
															reinterpret_cast<TextureClass *>(&ptexture),
																shader, 
																definition.Get_Max_Emissions (),
																0,
																false,
																definition.Get_Render_Mode (),
																definition.Get_Frame_Mode (),
																definition.Get_Line_Properties ()) );

	if (color_keys.KeyTimes != NULL) delete [] color_keys.KeyTimes;
	if (color_keys.Values != NULL) delete [] color_keys.Values;
	if (opacity_keys.KeyTimes != NULL) delete [] opacity_keys.KeyTimes;
	if (opacity_keys.Values != NULL) delete [] opacity_keys.Values;
	if (size_keys.KeyTimes != NULL) delete [] size_keys.KeyTimes;
	if (size_keys.Values != NULL) delete [] size_keys.Values;
	if (rotation_keys.KeyTimes != NULL) delete [] rotation_keys.KeyTimes;
	if (rotation_keys.Values != NULL) delete [] rotation_keys.Values;
	if (frame_keys.KeyTimes != NULL) delete [] frame_keys.KeyTimes;
	if (frame_keys.Values != NULL) delete [] frame_keys.Values;
	if (blur_time_keys.KeyTimes != NULL) delete [] blur_time_keys.KeyTimes;
	if (blur_time_keys.Values != NULL) delete [] blur_time_keys.Values;

	// Pass the name along to the emitter
	pemitter->Set_Name (definition.Get_Name ());

	// release our reference to particle texture.
	ptexture = NULL;

	// Return a pointer to the new emitter
	return pemitter;
}
