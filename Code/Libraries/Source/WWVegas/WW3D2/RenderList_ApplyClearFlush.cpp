// cl: /DNDEBUG /MD /GR-
// ?Render_And_Flush@SimpleSceneClass@@QAEXAAVRenderInfoClass@@@Z
// Retail 0x0079DE40 size 127. Apply_Render_State_Changes, Clear(false,true,true,
// Vector3(0,0,0), 0, 1.0f, 0), iterate the RefMultiList whose Head sits at
// this+0x60 (SimpleSceneClass first list; Add_Render_Object thunk) calling
// Render at vtable+0x30, then TheDX8MeshRenderer->Flush().

class Vector3
{
public:
	float X, Y, Z;
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Apply_Render_State_Changes(void);
	static void Clear(bool clear_color, bool clear_z, bool clear_stencil,
		const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8MeshRendererClass
{
public:
	void Flush(void);
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class RenderInfoClass;

class RenderObjClass
{
public:
	virtual void v00(void);
	virtual void v01(void);
	virtual void v02(void);
	virtual void v03(void);
	virtual void v04(void);
	virtual void v05(void);
	virtual void v06(void);
	virtual void v07(void);
	virtual void v08(void);
	virtual void v09(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual void Render(RenderInfoClass &rinfo);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
	void *ListNode;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListNodeClass
{
public:
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
};

class RefRenderObjListClass
{
public:
	MultiListNodeClass Head;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SimpleSceneClass
{
	char pad[0x60];
	RefRenderObjListClass list;
public:
	void Render_And_Flush(RenderInfoClass &rinfo);
};

void SimpleSceneClass::Render_And_Flush(RenderInfoClass &rinfo)
{
	MultiListNodeClass *node;
	DX8Wrapper::Apply_Render_State_Changes();
	Vector3 color(0.0f, 0.0f, 0.0f);
	DX8Wrapper::Clear(false, true, true, color, 0.0f, 1.0f, 0);
	node = list.Head.Next;
	if (node != &list.Head) {
		RenderInfoClass &info = rinfo;
		do {
			RenderObjClass *obj = node->Object
				? (RenderObjClass *)((char *)node->Object - 8)
				: 0;
			obj->Render(info);
			node = node->Next;
		} while (node != &list.Head);
	}
	TheDX8MeshRenderer->Flush();
}
