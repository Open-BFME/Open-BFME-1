// cl: /O2 /Ob2 /EHsc

// BFME's object-render overload returns bool and uses the BFME renderer
// pointer at 0x0134B0E8. The body also inlines the static-sort-list helper
// after flushing the mesh renderer.

class CameraClass;
class RenderInfoClass;

class RenderObjClass
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void Render(RenderInfoClass &rinfo);
};

class CameraClass
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void On_Frame_Update(void);
	void Apply(void);
};

class RenderInfoClass
{
public:
	CameraClass *Camera;
	char m_padding04[0x18];
	void *light_environment;
};

class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
};

class DX8MeshRendererClass
{
public:
	void Set_Camera(CameraClass *camera) { m_camera = camera; }
	void Flush(void);
	void Clear_Pending_Delete_Lists(void);

private:
	char m_padding00[4];
	CameraClass *m_camera;
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class SortingRendererClass
{
public:
	static void Flush(void);
};

class StaticSortListClass
{
public:
	virtual ~StaticSortListClass(void);
	virtual void Add_To_List(RenderObjClass *obj, unsigned sort_level);
	virtual void Render_And_Clear(RenderInfoClass &rinfo);
};

extern void d_00909300(void);
typedef void (__cdecl *SetLightEnvironment)(void *light_environment);

class WW3D
{
public:
	static bool Render(RenderObjClass &obj, RenderInfoClass &rinfo);

	static bool IsInitted;
	static bool AreStaticSortListsEnabled;
	static StaticSortListClass *CurrentStaticSortLists;
};

// ?Render@WW3D@@SA_NAAVRenderObjClass@@AAVRenderInfoClass@@@Z
bool WW3D::Render(RenderObjClass &obj, RenderInfoClass &rinfo)
{
	if (!IsInitted)
		return true;

	rinfo.Camera->On_Frame_Update();
	rinfo.Camera->Apply();
	DX8Wrapper::Set_DX8_Render_State(8, 3);
	if (rinfo.light_environment != 0)
		((SetLightEnvironment)d_00909300)(rinfo.light_environment);

	TheDX8MeshRenderer->Set_Camera(rinfo.Camera);
	obj.Render(rinfo);
	TheDX8MeshRenderer->Flush();

	bool old_enable = AreStaticSortListsEnabled;
	AreStaticSortListsEnabled = false;
	CurrentStaticSortLists->Render_And_Clear(rinfo);
	AreStaticSortListsEnabled = old_enable;

	SortingRendererClass::Flush();
	TheDX8MeshRenderer->Clear_Pending_Delete_Lists();
	return true;
}
