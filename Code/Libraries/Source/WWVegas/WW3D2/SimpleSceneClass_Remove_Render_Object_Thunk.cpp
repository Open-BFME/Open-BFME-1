// cl: /DNDEBUG /MD /EHsc
// readable body of ?Remove_Render_Object@SimpleSceneClass@@UAEXPAVRenderObjClass@@@Z: Code/Libraries/Source/WWVegas/WW3D2/scene.cpp
// Open-BFME5: convert the retail scene-removal body to clean C++.
//
// The slot-3 identity is established by the paired Add_Render_Object override
// and by the inlined Notify_Removed call.  The retail scene has four list views
// at the offsets below; the first helper is an older BFME list-maintenance body
// whose generated name remains address-based, so its call ABI is described here
// without reproducing its implementation.

class SceneClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListObjectClass
{
public:
	void *m_prev;
	void *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class GenericMultiListClass
{
protected:
	bool Internal_Remove(MultiListObjectClass *obj);
};

class SceneListClass : public GenericMultiListClass
{
public:
	bool Remove(MultiListObjectClass *obj)
	{
		return Internal_Remove(obj);
	}
};

// The retail vtable keeps Delete_This at slot zero, Notify_Added at +0x64,
// Notify_Removed at +0x68, and Is_Really_Visible at +0x19c.  Only those calls
// and the reference-count field are needed by this body.
class RenderObjClass
{
public:
	virtual void Delete_This(void);
	virtual void slot_001(void);
	virtual void slot_002(void);
	virtual void slot_003(void);
	virtual void slot_004(void);
	virtual void slot_005(void);
	virtual void slot_006(void);
	virtual void slot_007(void);
	virtual void slot_008(void);
	virtual void slot_009(void);
	virtual void slot_010(void);
	virtual void slot_011(void);
	virtual void slot_012(void);
	virtual void slot_013(void);
	virtual void slot_014(void);
	virtual void slot_015(void);
	virtual void slot_016(void);
	virtual void slot_017(void);
	virtual void slot_018(void);
	virtual void slot_019(void);
	virtual void slot_020(void);
	virtual void slot_021(void);
	virtual void slot_022(void);
	virtual void slot_023(void);
	virtual void slot_024(void);
	virtual void Notify_Added(SceneClass *scene);
	virtual void Notify_Removed(SceneClass *scene);
	virtual void slot_027(void);
	virtual void slot_028(void);
	virtual void slot_029(void);
	virtual void slot_030(void);
	virtual void slot_031(void);
	virtual void slot_032(void);
	virtual void slot_033(void);
	virtual void slot_034(void);
	virtual void slot_035(void);
	virtual void slot_036(void);
	virtual void slot_037(void);
	virtual void slot_038(void);
	virtual void slot_039(void);
	virtual void slot_040(void);
	virtual void slot_041(void);
	virtual void slot_042(void);
	virtual void slot_043(void);
	virtual void slot_044(void);
	virtual void slot_045(void);
	virtual void slot_046(void);
	virtual void slot_047(void);
	virtual void slot_048(void);
	virtual void slot_049(void);
	virtual void slot_050(void);
	virtual void slot_051(void);
	virtual void slot_052(void);
	virtual void slot_053(void);
	virtual void slot_054(void);
	virtual void slot_055(void);
	virtual void slot_056(void);
	virtual void slot_057(void);
	virtual void slot_058(void);
	virtual void slot_059(void);
	virtual void slot_060(void);
	virtual void slot_061(void);
	virtual void slot_062(void);
	virtual void slot_063(void);
	virtual void slot_064(void);
	virtual void slot_065(void);
	virtual void slot_066(void);
	virtual void slot_067(void);
	virtual void slot_068(void);
	virtual void slot_069(void);
	virtual void slot_070(void);
	virtual void slot_071(void);
	virtual void slot_072(void);
	virtual void slot_073(void);
	virtual void slot_074(void);
	virtual void slot_075(void);
	virtual void slot_076(void);
	virtual void slot_077(void);
	virtual void slot_078(void);
	virtual void slot_079(void);
	virtual void slot_080(void);
	virtual void slot_081(void);
	virtual void slot_082(void);
	virtual void slot_083(void);
	virtual void slot_084(void);
	virtual void slot_085(void);
	virtual void slot_086(void);
	virtual void slot_087(void);
	virtual void slot_088(void);
	virtual void slot_089(void);
	virtual void slot_090(void);
	virtual void slot_091(void);
	virtual void slot_092(void);
	virtual void slot_093(void);
	virtual void slot_094(void);
	virtual void slot_095(void);
	virtual void slot_096(void);
	virtual void slot_097(void);
	virtual void slot_098(void);
	virtual void slot_099(void);
	virtual void slot_100(void);
	virtual void slot_101(void);
	virtual void slot_102(void);
	virtual int Is_Really_Visible(void);

	int m_refCount;
	MultiListObjectClass m_node;
	unsigned char m_pad_to_94[0x84];
	int m_bfme_unk_94;
};

// The empty list view deliberately carries no local layout: only the retail
// receiver offsets matter, and Internal_Remove supplies the real list body.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SimpleSceneClass
{
public:
	virtual void Remove_Render_Object(RenderObjClass *obj);

private:
	unsigned char m_pad_to_34[0x30];
	SceneListClass m_list_34;
	unsigned char m_pad_to_5c[0x27];
	SceneListClass m_list_5c;
	unsigned char m_pad_to_bc[0x5f];
	SceneListClass m_list_bc;
	unsigned char m_pad_to_d4[0x17];
	SceneListClass m_list_d4;
	unsigned char m_pad_to_ec[0x17];
	SceneListClass m_list_ec;
};

// Address-based callee retained as an external symbol; the cast supplies the
// observed thiscall receiver at scene+0x34 and one RenderObjClass argument.
extern void d_00943430(void);
struct BfmeListMaintenanceThunk
{
	void Call(RenderObjClass *obj);
};
typedef void (BfmeListMaintenanceThunk::*BfmeListMaintenance)(RenderObjClass *);

// ?Remove_Render_Object@SimpleSceneClass@@UAEXPAVRenderObjClass@@@Z
void SimpleSceneClass::Remove_Render_Object(RenderObjClass *obj)
{
	obj->Notify_Removed((SceneClass *)this);
	MultiListObjectClass *node = &obj->m_node;

	m_list_bc.Remove(node);
	if (obj->Is_Really_Visible())
		m_list_d4.Remove(node);

	if (m_list_ec.Remove(node)) {
		if (--obj->m_refCount == 0)
			obj->Delete_This();
	}

	if (obj->m_bfme_unk_94 >= 0)
	{
		union { void *asVoid; BfmeListMaintenance asMember; } fnCast;
		fnCast.asVoid = (void *)&d_00943430;
		(reinterpret_cast<BfmeListMaintenanceThunk *>((unsigned char *)this + 0x34)->*fnCast.asMember)(obj);
	}

	if (m_list_5c.Remove(node)) {
		if (--obj->m_refCount == 0)
			obj->Delete_This();
	}
}
