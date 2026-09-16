// ?d_00934940@@YAXXZ
// partial score=0.1444 date=2026-09-16
// Function-sized clean-C++ candidate for retail 0x00934940.
// Compiled in Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp context;
// declarations and helper definitions remain in that TU.
void Render2DClass::Render(void)
{
	if ( !Indices.Count() || IsHidden) {
		return;
	}

	Matrix4x4 view,proj;
	Matrix4x4 identity(true);
	DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
	DX8Wrapper::Get_Transform(D3DTS_PROJECTION,proj);

	int width, height, bits;
	bool windowed;
	WW3D::Get_Device_Resolution( width, height, bits, windowed );
	D3DVIEWPORT8 vp = { 0 };
	vp.X = 0;
	vp.Y = 0;
	vp.Width = width;
	vp.Height = height;
	vp.MinZ = 0;
	vp.MaxZ = 1;
	DX8Wrapper::Set_Viewport(&vp);
	DX8Wrapper::Set_Texture(0,Texture);

	VertexMaterialClass *vm=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vm);
	REF_PTR_RELEASE(vm);

	DX8Wrapper::Set_World_Identity();
	DX8Wrapper::Set_View_Identity();
	DX8Wrapper::Set_Transform(D3DTS_PROJECTION,identity);

	DynamicVBAccessClass vb(BUFFER_TYPE_DYNAMIC_DX8,dynamic_fvf_type,Vertices.Count());
	{
		DynamicVBAccessClass::WriteLockClass Lock(&vb);
		const FVFInfoClass &fi=vb.FVF_Info();
		unsigned char *va=(unsigned char*)Lock.Get_Formatted_Vertex_Array();
		int i;
		for (i=0; i<Vertices.Count(); i++)
		{
			Vector3 temp(Vertices[i].X,Vertices[i].Y,ZValue);
			*(Vector3*)(va+fi.Get_Location_Offset())=temp;
			*(unsigned int*)(va+fi.Get_Diffuse_Offset())=Colors[i];
			*(Vector2*)(va+fi.Get_Tex_Offset(0))=UVCoordinates[i];
			va+=fi.Get_FVF_Size();
		}
	}

	DynamicIBAccessClass ib(BUFFER_TYPE_DYNAMIC_DX8,Indices.Count());
	try {
		DynamicIBAccessClass::WriteLockClass Lock(&ib);
		unsigned short *mem=Lock.Get_Index_Array();
		for (int i=0; i<Indices.Count(); i++)
			mem[i]=Indices[i];
		IndexBufferExceptionFunc();
	} catch(...) {
		IndexBufferExceptionFunc();
	}

	DX8Wrapper::Set_Vertex_Buffer(vb);
	DX8Wrapper::Set_Index_Buffer(ib,0);

	if (IsGrayScale)
	{
		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
		DX8Wrapper::Apply_Render_State_Changes();
		if (DX8Wrapper::Get_Current_Caps()->Support_Dot3())
		{
			DX8Wrapper::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR, 0x80A5CA8E);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG0, D3DTA_TFACTOR | D3DTA_ALPHAREPLICATE);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_TFACTOR | D3DTA_ALPHAREPLICATE);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP, D3DTOP_MULTIPLYADD);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG1, D3DTA_CURRENT);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG2, D3DTA_TFACTOR);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP, D3DTOP_DOTPRODUCT3);
		}
		else
		{
			DX8Wrapper::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR, 0x60606060);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		}
	}
	else
		DX8Wrapper::Set_Shader(Shader);
	DX8Wrapper::Draw_Triangles(0,Indices.Count()/3,0,Vertices.Count());

	DX8Wrapper::Set_Transform(D3DTS_VIEW,view);
	DX8Wrapper::Set_Transform(D3DTS_PROJECTION,proj);
	if (IsGrayScale)
		ShaderClass::Invalidate();
}
