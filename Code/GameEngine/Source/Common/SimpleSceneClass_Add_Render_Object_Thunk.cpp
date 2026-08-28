// cl: /DNDEBUG /MD /EHsc
// readable body of ?Add_Render_Object@SimpleSceneClass@@UAEXPAVRenderObjClass@@@Z: Code/Libraries/Source/WWVegas/WW3D2/scene.cpp

// The Add twin of Remove_Render_Object, promoted from its byte dump. It notifies
// the object through the virtual at +0x64, adds its list node to the scene list
// at this+0x5C -- taking a reference if the node was not already there -- adds it
// unconditionally to the list at +0xBC, and adds it to the list at +0xD4 only if
// the object's predicate at +0x19C says so. Remove does the mirror of all four.
//
// The placeholder virtuals put the two called methods at the offsets the body
// encodes. The list wrapper exists because Internal_Add is protected: a derived
// class may call it on itself, which is how the real MultiListClass template
// reaches it.
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
	bool Internal_Add(MultiListObjectClass *obj, bool onlyonce = true);

private:
	unsigned char m_head[12];
};

class SceneListClass : public GenericMultiListClass
{
public:
	bool Add(MultiListObjectClass *obj, bool onlyonce = true)
	{
		return Internal_Add(obj, onlyonce);
	}
};

class RenderObjClass
{
public:
	virtual void slot_000(void);
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
	virtual void slot_026(void);
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
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SimpleSceneClass
{
public:
	virtual void Add_Render_Object(RenderObjClass *obj);

private:
	unsigned char m_pad0[0x58];
	SceneListClass m_updateList;      // +0x5C
	unsigned char m_pad1[0x54];
	SceneListClass m_renderList;      // +0xBC
	unsigned char m_pad2[0x0C];
	SceneListClass m_visibleList;     // +0xD4
};

// ?Add_Render_Object@SimpleSceneClass@@UAEXPAVRenderObjClass@@@Z
void SimpleSceneClass::Add_Render_Object(RenderObjClass *obj)
{
	obj->Notify_Added((SceneClass *)this);
	// Compared against true explicitly: retail tests the result with
	// cmp al,1 rather than test al,al, which is what `== true` emits.
	if (m_updateList.Add(&obj->m_node, true) == true)
		obj->m_refCount++;
	m_renderList.Add(&obj->m_node, true);
	if (obj->Is_Really_Visible())
		m_visibleList.Add(&obj->m_node, true);
}
