// ?post_process_fog@MeshModelClass@@IAEXXZ
// partial score=0.93 date=2026-09-12
// Direct port of the Zero Hour reference (meshmdlio.cpp) verbatim; BFME's
// MeshMatDescClass layout matches the reference exactly (ShaderArray is
// ShareBufferClass<ShaderClass>*, same field offsets). First 0x11c (284)
// bytes compile byte-identical to retail including the full emissive_map_effect
// boolean chain. Whole body is only 933B vs retail's 929B (+4B).
//
// Single root cause: retail's REF_PTR_SET(DefMatDesc->Texture[0][0],
// DefMatDesc->Texture[1][0]) compiles to ONE out-of-line call taking
// &Texture[1][0] (lea edx,[eax+0x7c]; push edx) and &Texture[0][0] in ecx
// (lea ecx,[eax+0x74]) at retail +0x122; our compile inlines the macro's
// Add_Ref/Release_Ref test+branch logic directly (test eax,eax; je; inc
// word ptr[eax+4]; ...). REF_PTR_SET's macro text in Code/ and in the Zero
// Hour reference (WWLib/refcount.h) is byte-identical, so this is not a
// macro-version drift. Every later jne/je target in the body is offset by
// the same constant (13 bytes at first divergence, matching the size delta
// of this one call site plus its surrounding code), confirming this single
// site is the only structural defect; nothing else in the function diverges.
//
// Ruled out: macro spelling drift (identical to reference). Not yet tested:
// whether retail's call is MSVC procedural abstraction / linker ICF folding
// this REF_PTR_SET<TextureClass**> expansion with an identical call site
// elsewhere in the program (a TU-local or whole-program shared thunk), which
// would need a matched sibling call site to confirm and could not be forced
// from this function's source alone. t=45min model=claude-sonnet-5

class ShaderClass;
class TexBufferClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmdlio.cpp
void MeshModelClass::post_process_fog(void)
{
	// If two pass...
	if (DefMatDesc->Get_Pass_Count() == 2) {

		// If single shader on both passes...
		if (!DefMatDesc->ShaderArray[0] && !DefMatDesc->ShaderArray[1]) {

			ShaderClass &shader0 = DefMatDesc->Shader [0];
			ShaderClass &shader1 = DefMatDesc->Shader [1];

			// Analyze the mesh to determine if it is the emissive map effect and if it is, fix it up appropriately.
			bool emissive_map_effect = DefMatDesc->PassCount == 2 &&
												shader0.Get_Texturing() == ShaderClass::TEXTURING_DISABLE &&
												shader0.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE &&
												shader0.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ZERO &&
												shader0.Get_Primary_Gradient() == ShaderClass::GRADIENT_MODULATE &&
												shader0.Get_Secondary_Gradient() == ShaderClass::SECONDARY_GRADIENT_DISABLE &&
												shader1.Get_Texturing() == ShaderClass::TEXTURING_ENABLE &&
												shader1.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_SRC_ALPHA &&
												shader1.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_SRC_COLOR;

			if (emissive_map_effect) {

				// Change the shader/texture setting into an equivalent one which will enable setting fog
				// correctly: Note that we are setting up pass 0 to have a texture now.
				shader0.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
				shader1.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE);
				shader0.Set_Fog_Func(ShaderClass::FOG_ENABLE);
				shader1.Set_Fog_Func(ShaderClass::FOG_SCALE_FRAGMENT);

				// Copy pass 1 texture/texture array to pass 0.
				// DIVERGENCE HERE: retail emits one out-of-line call taking
				// &Texture[1][0]/&Texture[0][0]; this inlines Add_Ref/Release_Ref.
				REF_PTR_SET (DefMatDesc->Texture[0][0], DefMatDesc->Texture [1][0]);
				if (DefMatDesc->TextureArray [1][0]) {
					if (!DefMatDesc->TextureArray [0][0]) {
						DefMatDesc->TextureArray [0][0] = NEW_REF (TexBufferClass, (PolyCount, "MeshModelClass::DefMatDesc::TextureArray"));
						for (int i = 0; i < PolyCount; i++) {
							DefMatDesc->TextureArray [0][0]->Set_Element (i, DefMatDesc->TextureArray [1][0]->Peek_Element (i));
						}
					}
				}

				// Make pass 0 point to the same UV array as pass 1. If pass 1 has a vertex material
				// array, we only take the first one for determining UV source. The UV source is
				// used to set the UV source of all the vertex materials in pass 0.
				int uv_source = 0;
				if (DefMatDesc->MaterialArray[1]) {
					uv_source = DefMatDesc->MaterialArray[1]->Peek_Element(0)->Get_UV_Source(0);
				} else {
					DefMatDesc->Material[1]->Get_UV_Source(0);
				}
				if (DefMatDesc->MaterialArray[0]) {
					for (int i = 0; i < VertexCount; i++) {
						DefMatDesc->MaterialArray[0]->Peek_Element(i)->Set_UV_Source(0, uv_source);
					}
				} else {
					DefMatDesc->Material[0]->Set_UV_Source(0, uv_source);
				}

				return;
			}

			// Analyze the mesh to determine if it is the shiny mask effect and if it is, fix it up appropriately.
			bool shiny_mask_effect = shader0.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE &&
											 shader0.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ZERO &&
											 shader1.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE &&
											(shader1.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_SRC_ALPHA ||
											 shader1.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA);

			if (shiny_mask_effect) {
				shader0.Set_Fog_Func(ShaderClass::FOG_SCALE_FRAGMENT);
				shader1.Set_Fog_Func(ShaderClass::FOG_ENABLE);
				return;
			}
		}
	}

	// Mesh is not one of the special two-pass combinations. Apply a per-pass generic fix-up.
	for (int pass = 0; pass < DefMatDesc->PassCount; pass++) {
		DefMatDesc->Shader [pass].Enable_Fog (Get_Name());
		if (DefMatDesc->ShaderArray [pass]) {
			for (int tri = 0; tri < DefMatDesc->ShaderArray [pass]->Get_Count(); tri++) {
				DefMatDesc->ShaderArray [pass]->Get_Element (tri).Enable_Fog (Get_Name());
			}
		}
	}
}
