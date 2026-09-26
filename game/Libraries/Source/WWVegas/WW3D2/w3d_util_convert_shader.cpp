// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// The two W3dUtilityClass::Convert_Shader overloads, lifted from
// W3dUtilityClass_Convert_Shader_Thunk.cpp to the reference source. They live in
// their own translation unit holding nothing else, so the rest of w3d_util.cpp
// stays where the ledger already has it.

#include "w3d_util.h"
#include "vector3.h"
#include "vector4.h"
#include "quat.h"
#include "shader.h"

void W3dUtilityClass::Convert_Shader(const W3dShaderStruct & shader,ShaderClass * set)
{
	set->Set_Depth_Compare		((ShaderClass::DepthCompareType)W3d_Shader_Get_Depth_Compare(&shader));
	set->Set_Depth_Mask			((ShaderClass::DepthMaskType)W3d_Shader_Get_Depth_Mask(&shader));
	set->Set_Color_Mask			(ShaderClass::COLOR_WRITE_ENABLE);
	set->Set_Dst_Blend_Func		((ShaderClass::DstBlendFuncType)W3d_Shader_Get_Dest_Blend_Func(&shader));
	set->Set_Fog_Func				(ShaderClass::FOG_DISABLE);
	set->Set_Primary_Gradient	((ShaderClass::PriGradientType)W3d_Shader_Get_Pri_Gradient(&shader));
	set->Set_Secondary_Gradient((ShaderClass::SecGradientType)W3d_Shader_Get_Sec_Gradient(&shader));
	set->Set_Src_Blend_Func		((ShaderClass::SrcBlendFuncType)W3d_Shader_Get_Src_Blend_Func(&shader));
	set->Set_Texturing			((ShaderClass::TexturingType)W3d_Shader_Get_Texturing(&shader));
	set->Set_Alpha_Test			((ShaderClass::AlphaTestType)W3d_Shader_Get_Alpha_Test(&shader));
// Jani: No cull mode settings for w3d shader - problem?
//	set->Set_Dither_Mask			(ShaderClass::DITHER_ENABLE);
	// The tools do not enable setting post-detail stuff, and in any case we probably wouldn't
	// want to confuse the artists with the distinction between detail and post-detail settings at
	// this point, so we just copy the detail settings into the post-detail settings.
//	set->Set_Post_Detail_Color_Func ((ShaderClass::DetailColorFuncType) W3d_Shader_Get_Post_Detail_Color_Func (&shader));
//	set->Set_Post_Detail_Alpha_Func ((ShaderClass::DetailAlphaFuncType) W3d_Shader_Get_Post_Detail_Alpha_Func (&shader));
	set->Set_Post_Detail_Color_Func ((ShaderClass::DetailColorFuncType) W3d_Shader_Get_Detail_Color_Func (&shader));
	set->Set_Post_Detail_Alpha_Func ((ShaderClass::DetailAlphaFuncType) W3d_Shader_Get_Detail_Alpha_Func (&shader));
}

void W3dUtilityClass::Convert_Shader(const ShaderClass & shader,W3dShaderStruct * set)
{
	W3d_Shader_Reset(set);
	W3d_Shader_Set_Depth_Compare(set,shader.Get_Depth_Compare());
	W3d_Shader_Set_Depth_Mask(set,shader.Get_Depth_Mask());
	W3d_Shader_Set_Dest_Blend_Func(set,shader.Get_Dst_Blend_Func());
	W3d_Shader_Set_Pri_Gradient(set,shader.Get_Primary_Gradient());
	W3d_Shader_Set_Sec_Gradient(set,shader.Get_Secondary_Gradient());
	W3d_Shader_Set_Src_Blend_Func(set,shader.Get_Src_Blend_Func());
	W3d_Shader_Set_Texturing(set,shader.Get_Texturing());
	W3d_Shader_Set_Alpha_Test(set,shader.Get_Alpha_Test());
	W3d_Shader_Set_Post_Detail_Color_Func(set,shader.Get_Post_Detail_Color_Func());
	W3d_Shader_Set_Post_Detail_Alpha_Func(set,shader.Get_Post_Detail_Alpha_Func());
}
