// ?d_007dd180@@YAXXZ
// partial score=0.5267 date=2026-09-16
// ?set@TerrainShader2Stage@@UAEHH@Z
// Candidate bank for retail 0x007DD180 (6636 B).  This is the BFME terrain
// state-cache/noise reconstruction tested in W3DShaderManager.cpp.
Int TerrainShader2Stage::set(Int pass)
{
	typedef void (TerrainShader2Stage::*TerrainNoiseMatrixFn)(D3DXMATRIX *, D3DXMATRIX *, Bool);
	union TerrainNoiseMatrixCast {
		void (*raw)();
		TerrainNoiseMatrixFn member;
	};
	TerrainNoiseMatrixCast updateNoise1Cast;
	updateNoise1Cast.raw = j_00019bff;
	TerrainNoiseMatrixCast updateNoise2Cast;
	updateNoise2Cast.raw = j_000051ff;

	DX8Wrapper::Apply_Render_State_Changes();
	Rva006D4690Apply((void *)0);
	Rva006D4690Apply((void *)1);

	switch (pass)
	{
	case 0:
		{
			BfmeHandleCX texture = bfmeGet(0);
			IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
			(*(BFMESetTextureFn **)device)[BFME_SET_TEXTURE_SLOT](device, 0,
				((TextureBaseClass &)texture).Peek_D3D_Base_Texture());
		}
		BFME_SET_SAMP(0, BFME_SAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		BFME_SET_SAMP(0, BFME_SAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		BFME_SET_TSS(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		BFME_SET_TSS(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		BFME_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		BFME_SET_TSS(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		BFME_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		BFME_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		BFME_SET_TSS(0, D3DTSS_TEXCOORDINDEX, 0);
		BFME_SET_RS(D3DRS_ALPHABLENDENABLE, false);
		break;
	case 1:
		{
			BfmeHandleCX texture = bfmeGet(1);
			IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
			(*(BFMESetTextureFn **)device)[BFME_SET_TEXTURE_SLOT](device, 0,
				((TextureBaseClass &)texture).Peek_D3D_Base_Texture());
		}
		BFME_SET_SAMP(0, BFME_SAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		BFME_SET_SAMP(0, BFME_SAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		BFME_SET_TSS(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		BFME_SET_TSS(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		BFME_SET_TSS(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		BFME_SET_TSS(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		BFME_SET_TSS(0, D3DTSS_TEXCOORDINDEX, 1);
		BFME_SET_RS(D3DRS_ALPHABLENDENABLE, true);
		BFME_SET_RS(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		BFME_SET_RS(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		BFME_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		BFME_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		break;
	case 2:
		{
			Matrix4x4 curView;
			DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
			BFME_SET_TSS(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			BFME_SET_TSS(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
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
			D3DXMatrixInverse(&inv, &det, (D3DXMATRIX *)&curView);
			if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_TERRAIN_BASE_NOISE12)
			{
				{
					BfmeHandleCX texture = bfmeGet(2);
					IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
					(*(BFMESetTextureFn **)device)[BFME_SET_TEXTURE_SLOT](device, 0,
						((TextureBaseClass &)texture).Peek_D3D_Base_Texture());
				}
				(this->*updateNoise1Cast.member)((D3DXMATRIX *)&curView, &inv, true);
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE0, curView);
				BFME_SET_SAMP(0, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
				BFME_SET_SAMP(0, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				{
					BfmeHandleCX texture = bfmeGet(3);
					IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
					(*(BFMESetTextureFn **)device)[BFME_SET_TEXTURE_SLOT](device, 1,
						((TextureBaseClass &)texture).Peek_D3D_Base_Texture());
				}
				(this->*updateNoise2Cast.member)((D3DXMATRIX *)&curView, &inv, true);
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
			}
			else
			{
				if (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_TERRAIN_BASE_NOISE1)
				{
					BfmeHandleCX texture = bfmeGet(2);
					IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
					(*(BFMESetTextureFn **)device)[BFME_SET_TEXTURE_SLOT](device, 0,
						((TextureBaseClass &)texture).Peek_D3D_Base_Texture());
					(this->*updateNoise1Cast.member)((D3DXMATRIX *)&curView, &inv, true);
					BFME_SET_SAMP(0, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
					BFME_SET_SAMP(0, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				}
				else
				{
					BfmeHandleCX texture = bfmeGet(3);
					IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
					(*(BFMESetTextureFn **)device)[BFME_SET_TEXTURE_SLOT](device, 0,
						((TextureBaseClass &)texture).Peek_D3D_Base_Texture());
					(this->*updateNoise2Cast.member)((D3DXMATRIX *)&curView, &inv, true);
					BFME_SET_SAMP(0, BFME_SAMP_MINFILTER, D3DTEXF_POINT);
					BFME_SET_SAMP(0, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
				}
				BFME_SET_TSS(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
				BFME_SET_TSS(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
				DX8Wrapper::_Set_DX8_Transform(D3DTS_TEXTURE0, *((Matrix4x4 *)&curView));
			}
		}
		break;
	}
	return TRUE;
}
