// ?d_007ce290@@YAXXZ
// partial score=0.36 date=2026-09-16
// Candidate tested in W3DShaderManager.cpp for retail 0x007CE290.
// Corrected retail identity: TerrainShader2Stage::set(Int), 8147 bytes.
// This is the current BFME-expanded Terrain candidate; the prior
// FlatTerrain-labelled candidate is retained only in attempt history.
Int TerrainShader2Stage::set(Int pass)
{
	DX8Wrapper::Apply_Render_State_Changes();

	if (TheGlobalData && TheGlobalData->m_bilinearTerrainTex || TheGlobalData->m_trilinearTerrainTex) {
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
	} else {
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MINFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MAGFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_POINT);
	}
	if (TheGlobalData && TheGlobalData->m_trilinearTerrainTex) {
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	} else {
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MIPFILTER, D3DTEXF_POINT);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	}

	switch (pass)
	{
		case 0:
			DX8Wrapper::_Get_D3D_Device8()->SetTexture(0, W3DShaderManager::getShaderTexture(0)->Peek_D3D_Texture());
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);

			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, 0 );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE,false);
			break;
		case 1:
			DX8Wrapper::_Get_D3D_Device8()->SetTexture(0, W3DShaderManager::getShaderTexture(1)->Peek_D3D_Texture());
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);

			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_TEXCOORDINDEX, 1 );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE,true);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
			break;
		case 2:
			Matrix4x4 curView;
			DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			BFME_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
			BFME_SET_TSS(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
			BFME_SET_TSS(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
			BFME_SET_TSS(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
			BFME_SET_SAMP(0, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
			BFME_SET_SAMP(0, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);

			BFME_SET_RS(D3DRS_ALPHABLENDENABLE, true);
			BFME_SET_RS(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
			BFME_SET_RS(D3DRS_DESTBLEND, D3DBLEND_ZERO);

			D3DXMATRIX inv;
			float det;
			D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

			if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_TERRAIN_BASE_NOISE12)
			{
				DX8Wrapper::_Get_D3D_Device8()->SetTexture(0, W3DShaderManager::getShaderTexture(2)->Peek_D3D_Texture());
				updateNoise1(((D3DXMATRIX*)&curView),&inv);
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE0, curView);
				DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				DX8Wrapper::_Get_D3D_Device8()->SetTexture(1, W3DShaderManager::getShaderTexture(3)->Peek_D3D_Texture());
				updateNoise2(((D3DXMATRIX*)&curView),&inv);
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE1, curView);
				DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MINFILTER, D3DTEXF_POINT);
				DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_COLOROP,   D3DTOP_MODULATE );
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
				DX8Wrapper::Set_DX8_Texture_Stage_State( 1, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
			}
			else
			{
				if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_TERRAIN_BASE_NOISE1)
				{
					bfmeSetTexture(0, W3DShaderManager::getShaderTexture(2)->Peek_D3D_Texture());
					updateNoise1(((D3DXMATRIX*)&curView),&inv);
					BFME_SET_SAMP(0, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
					BFME_SET_SAMP(0, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				}
				else
				{
					bfmeSetTexture(0, W3DShaderManager::getShaderTexture(3)->Peek_D3D_Texture());
					updateNoise2(((D3DXMATRIX*)&curView),&inv);
					BFME_SET_SAMP(1, BFME_SAMP_MINFILTER, D3DTEXF_POINT);
					BFME_SET_SAMP(1, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				}
				BFME_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
				BFME_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE0, *((Matrix4x4*)&curView));
			}
			break;
	}

	return TRUE;
}
