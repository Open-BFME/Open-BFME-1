// ?Render@WW3D@@SA?AW4WW3DErrorType@@PAVSceneClass@@PAVCameraClass@@_N2ABVVector3@@@Z
// partial score=0.76 date=2026-09-10
// Complete research bank for retail RVA 0x008FE3C0.  The production owner is
// ww3d.cpp; this isolated copy exists only so re_log can retain one body.
WW3DErrorType WW3D::Render(SceneClass *scene, CameraClass *cam, bool clear,
                            bool clearz, const Vector3 &color)
{
	if (!IsInitted) {
		return (WW3D_ERROR_OK);
	}

	WWPROFILE("WW3D::Render");
	WWMEMLOG(MEM_GAMEDATA);
	WWASSERT(IsInitted);
	WWASSERT(IsRendering);
	WWASSERT(scene);
	WWASSERT(cam);

	cam->On_Frame_Update();
	RenderInfoClass rinfo(*cam);

	cam->Apply();

	if (clear || clearz) {
		DX8Wrapper::Clear(clear, clearz, color);
	}

	switch (scene->Get_Polygon_Mode()) {
	case SceneClass::POINT:
		DX8Wrapper::Set_DX8_Render_State(D3DRS_FILLMODE, D3DFILL_POINT);
		break;
	case SceneClass::LINE:
		DX8Wrapper::Set_DX8_Render_State(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		break;
	case SceneClass::FILL:
		DX8Wrapper::Set_DX8_Render_State(D3DRS_FILLMODE, D3DFILL_SOLID);
		break;
	}

	DX8Wrapper::Set_Ambient(scene->Get_Ambient_Light());
	TheDX8MeshRenderer.Set_Camera(&rinfo.Camera);
	scene->Render(rinfo);
	Flush(rinfo);

	return WW3D_ERROR_OK;
}
