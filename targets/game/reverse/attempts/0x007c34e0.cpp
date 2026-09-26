// ?set@CloudTextureShader@@EAEHH@Z
// partial score=0.55 date=2026-09-26
// Candidate compile in Code\GameEngineDevice\Source\W3DDevice\GameClient\W3DShaderManager.cpp; current body 2028B vs 2117B retail.
// ?set@CloudTextureShader@@EAEHH@Z present-unmatched
Int CloudTextureShader::set(Int stage)
{
	Matrix4x4 curView;
	DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

	D3DXMATRIX inv;
	float det;

	D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

	//Get a texture matrix that applies the current cloud position
	terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv,false);	//update curView with texture matrix

	BFME_SET_TSS(stage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
	BFME_SET_TSS(stage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	{
		DX8Wrapper::matrix_changes++;
		IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
		typedef HRESULT (__stdcall *SetTransformFn)(IDirect3DDevice8 *, DWORD, const Matrix4 *);
		(*(SetTransformFn **)device)[44](device, D3DTS_TEXTURE0 + stage, &curView);
		number_of_DX8_calls++;
	}
	BFME_SET_SAMP(stage, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
	BFME_SET_SAMP(stage, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
	BFME_SET_SAMP(stage, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
	BFME_SET_SAMP(stage, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);

	BFME_SET_TSS(stage, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	BFME_SET_TSS(stage, D3DTSS_COLORARG2, D3DTA_CURRENT);
	BFME_SET_TSS(stage, D3DTSS_COLOROP, D3DTOP_MODULATE);
	BFME_SET_TSS(stage, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	BFME_SET_TSS(stage, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	BFME_SET_TSS(stage, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	{
		BfmeHandleCX texture = bfmeGet(stage);
		IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
		TextureBaseClass *base = texture;
		(*(BFMESetTextureFn **)device)[BFME_SET_TEXTURE_SLOT](device, stage,
			base->Peek_D3D_Base_Texture());
	}

	m_stageOfSet=stage;
	return TRUE;
}

