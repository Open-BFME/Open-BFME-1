// ?set@FlatTerrainShaderPixelShader@@UAEHH@Z
// partial score=0.0425 date=2026-09-16
// Function-sized candidate for retail 0x007C7FD0.
// Compiled in the full W3DShaderManager.cpp TU; declarations and BFME/W3D
// helper definitions intentionally remain in that source file.
Int FlatTerrainShaderPixelShader::set(Int pass)
{
	//setup base pass
	Int curStage = 1;
	// setup terrain [3/31/2003]

	DX8Wrapper::Set_DX8_Texture_Stage_State(0,  D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0,  D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
	DX8Wrapper::Set_Texture(0, W3DShaderManager::getShaderTexture(2));
	DX8Wrapper::Set_Texture(1, W3DShaderManager::getShaderTexture(2));
	//force WW3D2 system to set it's states so it won't later overwrite our custom settings.
	DX8Wrapper::Apply_Render_State_Changes();

	DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
	//tell pixel shader which UV set to use for each stage
	DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_TEXCOORDINDEX, 0 );
	DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);

	if (TheGlobalData && TheGlobalData->m_bilinearTerrainTex || TheGlobalData->m_trilinearTerrainTex) {
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
	} else {
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MINFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MAGFILTER, D3DTEXF_POINT);
	}
	if (TheGlobalData && TheGlobalData->m_trilinearTerrainTex) {
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	} else {
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MIPFILTER, D3DTEXF_POINT);
	}

	curStage = 0;

	W3DShroud *shroud = TheTerrainRenderObject->getShroud();
	if (shroud) {
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		{
			D3DXMATRIX inv;
			float det;
			Matrix4x4 curView;
			DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
			D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);
			D3DXMATRIX scale,offset;
			float xoffset = 0;
			float yoffset = 0;
			Real width=shroud->getCellWidth();
			Real height=shroud->getCellHeight();
			if (TheTerrainRenderObject->getMap()) {
				xoffset = -(float)shroud->getDrawOriginX() + width;
				yoffset = -(float)shroud->getDrawOriginY() + height;
			}
			D3DXMatrixTranslation(&offset, xoffset, yoffset,0);
			width = 1.0f/(width*shroud->getTextureWidth());
			height = 1.0f/(height*shroud->getTextureHeight());
			D3DXMatrixScaling(&scale, width, height, 1);
			*((D3DXMATRIX *)&curView) = (inv * offset) * scale;
			DX8Wrapper::_Set_DX8_Transform((D3DTRANSFORMSTATETYPE )(D3DTS_TEXTURE0+curStage), *((Matrix4x4*)&curView));
		}
		DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State( curStage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::_Get_D3D_Device8()->SetTexture(curStage, shroud->getShroudTexture()->Peek_D3D_Texture());
		curStage++;
		if (curStage==1) curStage++;
	}

	Bool doNoise1 = (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE1 ||
						W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE12);
	if (doNoise1) {
		Matrix4x4 curView;
		DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
		D3DXMATRIX inv;
		float det;
		D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		DX8Wrapper::_Get_D3D_Device8()->SetTexture(curStage, W3DShaderManager::getShaderTexture(2)->Peek_D3D_Texture());
		terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv);
		DX8Wrapper::_Set_DX8_Transform((D3DTRANSFORMSTATETYPE )(D3DTS_TEXTURE0+curStage), *((Matrix4x4*)&curView));
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		curStage++;
		if (curStage==1) curStage++;
	}

	Bool doNoise2 = (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE2 ||
						W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE12);
	if (doNoise2) {
		Matrix4x4 curView;
		DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
		D3DXMATRIX inv;
		float det;
		D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage,  D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		DX8Wrapper::_Get_D3D_Device8()->SetTexture(curStage, W3DShaderManager::getShaderTexture(3)->Peek_D3D_Texture());
		terrainShader2Stage.updateNoise2(((D3DXMATRIX*)&curView),&inv);
		DX8Wrapper::_Set_DX8_Transform((D3DTRANSFORMSTATETYPE )(D3DTS_TEXTURE0+curStage), *((Matrix4x4*)&curView));
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(curStage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		curStage++;
		if (curStage==1) curStage++;
	}
	if (curStage<2) {
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_dwBase0PixelShader);
	} else if (curStage==2) {
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_dwBasePixelShader);
	} else if (curStage==3) {
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_dwBaseNoise1PixelShader);
	} else if (curStage==4) {
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_dwBaseNoise2PixelShader);
	}
	DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::_Get_D3D_Device8()->SetTexture(curStage, W3DShaderManager::getShaderTexture(3)->Peek_D3D_Texture());
	return TRUE;
}
