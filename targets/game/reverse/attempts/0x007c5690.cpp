// ?d_007c5690@@YAXXZ
// partial score=0.34 date=2026-09-16
// Candidate tested in W3DShaderManager.cpp for retail 0x007C5690 (7909 bytes).
// Identity: FlatTerrainShader2Stage::set(Int), supported by init/reset at
// 0x007C55B0/0x007C5600 and the flat-terrain noise/shroud call sequence.
// Best tested recipe: helper filter calls, BFME_SET_TSS/SAMP/RS expansion,
// bfmeGet handle bindings, and the sibling late-state macro pattern.
Int FlatTerrainShader2Stage::set(Int pass)
{
	DX8Wrapper::Apply_Render_State_Changes();

	setTerrainTextureFilters(0);
	setTerrainTextureFilters(1);

	switch (pass)
	{
		case 0:
			BFME_SET_TSS(0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			BFME_SET_TSS(0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			BFME_SET_TSS(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			BFME_SET_TSS(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
			if ((TextureBaseClass *&)bfmeGet(0)) {
				bfmeSetTexture(0, ((TextureBaseClass &)bfmeGet(0)).Peek_D3D_Base_Texture());
				BFME_SET_TSS(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
				BFME_SET_TSS(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
				BFME_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
				BFME_SET_TSS_LATE(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
				BFME_SET_TSS_LATE(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
				BFME_SET_TSS_LATE(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
				W3DShroud *shroud;
				if ((shroud=TheTerrainRenderObject->getShroud()) != 0)
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
					if (TheTerrainRenderObject->getMap())
					{
						xoffset = -(float)shroud->getDrawOriginX() + width;
						yoffset = -(float)shroud->getDrawOriginY() + height;
					}
					D3DXMatrixTranslation(&offset, xoffset, yoffset,0);
					width = 1.0f/(width*shroud->getTextureWidth());
					height = 1.0f/(height*shroud->getTextureHeight());
					D3DXMatrixScaling(&scale, width, height, 1);
					*((D3DXMATRIX *)&curView) = (inv * offset) * scale;
					DX8Wrapper::_Set_DX8_Transform((D3DTRANSFORMSTATETYPE )(D3DTS_TEXTURE0), *((Matrix4x4*)&curView));
				}
			} else {
				BFME_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
				BFME_SET_TSS(0, D3DTSS_TEXCOORDINDEX, 0);
			}
			BFME_SET_TSS_LATE(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
			BFME_SET_SAMP(1, BFME_SAMP_ADDRESSU, D3DTADDRESS_CLAMP);
			BFME_SET_SAMP(1, BFME_SAMP_ADDRESSV, D3DTADDRESS_CLAMP);
			BFME_SET_TSS(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			BFME_SET_TSS(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
			BFME_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
			BFME_SET_TSS_LATE(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
			BFME_SET_TSS_LATE(1, D3DTSS_TEXCOORDINDEX, 0);
			BFME_SET_TSS_LATE(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
			BFME_SET_TSS_LATE(1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU|0);
			BFME_SET_RS(D3DRS_ALPHABLENDENABLE, false);
			break;
		case 1:
			Matrix4x4 curView;
			DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
			BFME_SET_TSS(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			BFME_SET_TSS(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
			BFME_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
			BFME_SET_TSS_LATE(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
			BFME_SET_TSS_LATE(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
			BFME_SET_TSS(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
			BFME_SET_SAMP(0, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
			BFME_SET_SAMP(0, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);
			BFME_SET_RS(D3DRS_ALPHABLENDENABLE, true);
			BFME_SET_RS(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
			BFME_SET_RS(D3DRS_DESTBLEND, D3DBLEND_ZERO);
			D3DXMATRIX inv;
			float det;
			D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);
			if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE12)
			{
				terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv);
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE0, curView);
				BFME_SET_SAMP(0, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
				BFME_SET_SAMP(0, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				bfmeSetTexture(0, ((TextureBaseClass &)bfmeGet(2)).Peek_D3D_Base_Texture());
				terrainShader2Stage.updateNoise2(((D3DXMATRIX*)&curView),&inv);
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE1, curView);
				BFME_SET_SAMP(1, BFME_SAMP_MINFILTER, D3DTEXF_POINT);
				BFME_SET_SAMP(1, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				BFME_SET_TSS(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
				BFME_SET_TSS(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
				BFME_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
				BFME_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
				BFME_SET_TSS(1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
				BFME_SET_TSS(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
				BFME_SET_SAMP(1, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
				BFME_SET_SAMP(1, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);
				bfmeSetTexture(1, ((TextureBaseClass &)bfmeGet(3)).Peek_D3D_Base_Texture());
			}
			else
			{
				if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_FLAT_TERRAIN_BASE_NOISE1)
				{
					bfmeSetTexture(0, ((TextureBaseClass &)bfmeGet(2)).Peek_D3D_Base_Texture());
					terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv);
					BFME_SET_SAMP(0, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
					BFME_SET_SAMP(0, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				}
				else
				{
					bfmeSetTexture(0, ((TextureBaseClass &)bfmeGet(3)).Peek_D3D_Base_Texture());
					terrainShader2Stage.updateNoise2(((D3DXMATRIX*)&curView),&inv);
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
