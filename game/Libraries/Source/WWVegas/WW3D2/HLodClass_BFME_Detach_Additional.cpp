// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Clean C++ recovery of the BFME HLodClass slot-40 override at retail RVA
// 0x0097A150 (170 bytes).  The retail public name is not recovered; the
// existing RenderObjClass ABI placeholder `_bfme_ro_v40` is therefore used.
// This TU-local view records only the proven class, vector, and virtual-slot
// layout and leaves the shared HLOD headers untouched.

class SceneClass;

class RenderObjClass
{
public:
	virtual void Delete_This();
#define BFME_RENDER_SLOT(n) virtual void slot##n();
	BFME_RENDER_SLOT(001)
	BFME_RENDER_SLOT(002)
	BFME_RENDER_SLOT(003)
	BFME_RENDER_SLOT(004)
	BFME_RENDER_SLOT(005)
	BFME_RENDER_SLOT(006)
	BFME_RENDER_SLOT(007)
	BFME_RENDER_SLOT(008)
	BFME_RENDER_SLOT(009)
	BFME_RENDER_SLOT(010)
	BFME_RENDER_SLOT(011)
	BFME_RENDER_SLOT(012)
	BFME_RENDER_SLOT(013)
	BFME_RENDER_SLOT(014)
	BFME_RENDER_SLOT(015)
	BFME_RENDER_SLOT(016)
	BFME_RENDER_SLOT(017)
	BFME_RENDER_SLOT(018)
	virtual void Set_Container(void *container);
	BFME_RENDER_SLOT(020)
	BFME_RENDER_SLOT(021)
	BFME_RENDER_SLOT(022)
	BFME_RENDER_SLOT(023)
	BFME_RENDER_SLOT(024)
	BFME_RENDER_SLOT(025)
	virtual void Notify_Removed(SceneClass *scene);
#undef BFME_RENDER_SLOT

	// The reference count is the second word in every RenderObjClass object.
	int m_refs;

	void Release_Ref(void)
	{
		if (--m_refs == 0) {
			Delete_This();
		}
	}
};

// Keep the two high RenderObj slots used by this body at their retail offsets.
// The intervening slots carry no claimed public identities.
class BfmeRenderObjSlots : public RenderObjClass
{
public:
#define BFME_SLOT(n) virtual void slot##n();
	BFME_SLOT(027)
	BFME_SLOT(028)
	BFME_SLOT(029)
	BFME_SLOT(030)
	BFME_SLOT(031)
	BFME_SLOT(032)
	BFME_SLOT(033)
	BFME_SLOT(034)
	BFME_SLOT(035)
	BFME_SLOT(036)
	BFME_SLOT(037)
	BFME_SLOT(038)
	BFME_SLOT(039)
	BFME_SLOT(040)
	BFME_SLOT(041)
	BFME_SLOT(042)
	BFME_SLOT(043)
	BFME_SLOT(044)
	BFME_SLOT(045)
	BFME_SLOT(046)
	BFME_SLOT(047)
	BFME_SLOT(048)
	BFME_SLOT(049)
	BFME_SLOT(050)
	BFME_SLOT(051)
	BFME_SLOT(052)
	BFME_SLOT(053)
	BFME_SLOT(054)
	BFME_SLOT(055)
	BFME_SLOT(056)
	BFME_SLOT(057)
	BFME_SLOT(058)
	BFME_SLOT(059)
	BFME_SLOT(060)
	BFME_SLOT(061)
	BFME_SLOT(062)
	BFME_SLOT(063)
	BFME_SLOT(064)
	BFME_SLOT(065)
	BFME_SLOT(066)
	BFME_SLOT(067)
	virtual void Update_Obj_Space_Bounding_Volumes();
	BFME_SLOT(069)
	BFME_SLOT(070)
	BFME_SLOT(071)
	BFME_SLOT(072)
	BFME_SLOT(073)
	BFME_SLOT(074)
	BFME_SLOT(075)
	BFME_SLOT(076)
	BFME_SLOT(077)
	BFME_SLOT(078)
	BFME_SLOT(079)
	BFME_SLOT(080)
	BFME_SLOT(081)
	BFME_SLOT(082)
	BFME_SLOT(083)
	BFME_SLOT(084)
	BFME_SLOT(085)
	BFME_SLOT(086)
	BFME_SLOT(087)
	BFME_SLOT(088)
	BFME_SLOT(089)
	BFME_SLOT(090)
	BFME_SLOT(091)
	BFME_SLOT(092)
	BFME_SLOT(093)
	BFME_SLOT(094)
	BFME_SLOT(095)
	BFME_SLOT(096)
	BFME_SLOT(097)
	BFME_SLOT(098)
	BFME_SLOT(099)
	BFME_SLOT(100)
	BFME_SLOT(101)
	BFME_SLOT(102)
	BFME_SLOT(103)
	BFME_SLOT(104)
	BFME_SLOT(105)
	BFME_SLOT(106)
	BFME_SLOT(107)
	BFME_SLOT(108)
	BFME_SLOT(109)
	BFME_SLOT(110)
	BFME_SLOT(111)
	BFME_SLOT(112)
	BFME_SLOT(113)
	BFME_SLOT(114)
	BFME_SLOT(115)
	BFME_SLOT(116)
	BFME_SLOT(117)
	BFME_SLOT(118)
	BFME_SLOT(119)
	BFME_SLOT(120)
	BFME_SLOT(121)
	virtual bool Is_In_Scene();
	BFME_SLOT(123)
	BFME_SLOT(124)
	BFME_SLOT(125)
	BFME_SLOT(126)
	BFME_SLOT(127)
	BFME_SLOT(128)
	virtual void Update_Sub_Object_Bits();
#undef BFME_SLOT
};

struct BfmeModelNode
{
	RenderObjClass *Model;
	int BoneIndex;
	char Offset[12];
};

// DynamicVectorClass<ModelNodeClass> layout: vector vptr at +0, data at +4,
// active count at +0x10, and ModelArrayClass's metric tail after +0x18.
class BfmeModelArray
{
public:
	virtual ~BfmeModelArray();
	virtual bool operator == (const BfmeModelArray &) const;
	virtual bool Resize(int newsize, BfmeModelNode const *array = 0);
	virtual void Clear(void);
	virtual int ID(BfmeModelNode const *ptr);
	virtual int ID(BfmeModelNode const &ptr);

	BfmeModelNode *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
	int ActiveCount;
	int GrowthStep;
	float MaxScreenSize;
	float NonPixelCost;
	float PixelCostPerArea;
	float BenefitFactor;

	int Count(void) const { return ActiveCount; }
	BfmeModelNode &operator [] (int index) { return Vector[index]; }

	void Delete_All(void)
	{
		int len = VectorMax;
		Clear();
		Resize(len);
	}
};

class HLodClass : public BfmeRenderObjSlots
{
public:
#define BFME_HLOD_SLOT(n) virtual void slot##n();
	BFME_HLOD_SLOT(000)
	BFME_HLOD_SLOT(001)
	BFME_HLOD_SLOT(002)
	BFME_HLOD_SLOT(003)
	BFME_HLOD_SLOT(004)
	BFME_HLOD_SLOT(005)
	BFME_HLOD_SLOT(006)
	BFME_HLOD_SLOT(007)
	BFME_HLOD_SLOT(008)
	BFME_HLOD_SLOT(009)
	BFME_HLOD_SLOT(010)
	BFME_HLOD_SLOT(011)
	BFME_HLOD_SLOT(012)
	BFME_HLOD_SLOT(013)
	BFME_HLOD_SLOT(014)
	BFME_HLOD_SLOT(015)
	BFME_HLOD_SLOT(016)
	BFME_HLOD_SLOT(017)
	BFME_HLOD_SLOT(018)
	BFME_HLOD_SLOT(019)
	BFME_HLOD_SLOT(020)
	BFME_HLOD_SLOT(021)
	BFME_HLOD_SLOT(022)
	BFME_HLOD_SLOT(023)
	BFME_HLOD_SLOT(024)
	BFME_HLOD_SLOT(025)
	BFME_HLOD_SLOT(026)
	BFME_HLOD_SLOT(027)
	BFME_HLOD_SLOT(028)
	BFME_HLOD_SLOT(029)
	BFME_HLOD_SLOT(030)
	BFME_HLOD_SLOT(031)
	BFME_HLOD_SLOT(032)
	BFME_HLOD_SLOT(033)
	BFME_HLOD_SLOT(034)
	BFME_HLOD_SLOT(035)
	BFME_HLOD_SLOT(036)
	BFME_HLOD_SLOT(037)
	BFME_HLOD_SLOT(038)
	BFME_HLOD_SLOT(039)
	virtual void _bfme_ro_v40(void);
	BFME_HLOD_SLOT(041)
	BFME_HLOD_SLOT(042)
	BFME_HLOD_SLOT(043)
	BFME_HLOD_SLOT(044)
	BFME_HLOD_SLOT(045)
	BFME_HLOD_SLOT(046)
	BFME_HLOD_SLOT(047)
	BFME_HLOD_SLOT(048)
	BFME_HLOD_SLOT(049)
	BFME_HLOD_SLOT(050)
	BFME_HLOD_SLOT(051)
	BFME_HLOD_SLOT(052)
	BFME_HLOD_SLOT(053)
	BFME_HLOD_SLOT(054)
	BFME_HLOD_SLOT(055)
	BFME_HLOD_SLOT(056)
	BFME_HLOD_SLOT(057)
	BFME_HLOD_SLOT(058)
	BFME_HLOD_SLOT(059)
	BFME_HLOD_SLOT(060)
	BFME_HLOD_SLOT(061)
	BFME_HLOD_SLOT(062)
	BFME_HLOD_SLOT(063)
	BFME_HLOD_SLOT(064)
	BFME_HLOD_SLOT(065)
	BFME_HLOD_SLOT(066)
	BFME_HLOD_SLOT(067)
	virtual void Update_Obj_Space_Bounding_Volumes();
	BFME_HLOD_SLOT(069)
	BFME_HLOD_SLOT(070)
	BFME_HLOD_SLOT(071)
	BFME_HLOD_SLOT(072)
	BFME_HLOD_SLOT(073)
	BFME_HLOD_SLOT(074)
	BFME_HLOD_SLOT(075)
	BFME_HLOD_SLOT(076)
	BFME_HLOD_SLOT(077)
	BFME_HLOD_SLOT(078)
	BFME_HLOD_SLOT(079)
	BFME_HLOD_SLOT(080)
	BFME_HLOD_SLOT(081)
	BFME_HLOD_SLOT(082)
	BFME_HLOD_SLOT(083)
	BFME_HLOD_SLOT(084)
	BFME_HLOD_SLOT(085)
	BFME_HLOD_SLOT(086)
	BFME_HLOD_SLOT(087)
	BFME_HLOD_SLOT(088)
	BFME_HLOD_SLOT(089)
	BFME_HLOD_SLOT(090)
	BFME_HLOD_SLOT(091)
	BFME_HLOD_SLOT(092)
	BFME_HLOD_SLOT(093)
	BFME_HLOD_SLOT(094)
	BFME_HLOD_SLOT(095)
	BFME_HLOD_SLOT(096)
	BFME_HLOD_SLOT(097)
	BFME_HLOD_SLOT(098)
	BFME_HLOD_SLOT(099)
	BFME_HLOD_SLOT(100)
	BFME_HLOD_SLOT(101)
	BFME_HLOD_SLOT(102)
	BFME_HLOD_SLOT(103)
	BFME_HLOD_SLOT(104)
	BFME_HLOD_SLOT(105)
	BFME_HLOD_SLOT(106)
	BFME_HLOD_SLOT(107)
	BFME_HLOD_SLOT(108)
	BFME_HLOD_SLOT(109)
	BFME_HLOD_SLOT(110)
	BFME_HLOD_SLOT(111)
	BFME_HLOD_SLOT(112)
	BFME_HLOD_SLOT(113)
	BFME_HLOD_SLOT(114)
	BFME_HLOD_SLOT(115)
	BFME_HLOD_SLOT(116)
	BFME_HLOD_SLOT(117)
	BFME_HLOD_SLOT(118)
	BFME_HLOD_SLOT(119)
	BFME_HLOD_SLOT(120)
	BFME_HLOD_SLOT(121)
	virtual bool Is_In_Scene();
	BFME_HLOD_SLOT(123)
	BFME_HLOD_SLOT(124)
	BFME_HLOD_SLOT(125)
	BFME_HLOD_SLOT(126)
	BFME_HLOD_SLOT(127)
	BFME_HLOD_SLOT(128)
	virtual void Update_Sub_Object_Bits();
#undef BFME_HLOD_SLOT

	char RenderObjFields[0x78];
	SceneClass *Scene;
	char HlodFields[0x13c - 0x84];
	BfmeModelArray AdditionalModels;
};

// ?_bfme_ro_v40@HLodClass@@UAEXXZ
void HLodClass::_bfme_ro_v40(void)
{
	int additional_count = AdditionalModels.Count();
	if (additional_count == 0) {
		return;
	}

	for (int i = 0; i < AdditionalModels.Count(); i++) {
		RenderObjClass * model = AdditionalModels[i].Model;
		AdditionalModels[i].Model = 0;
		model->Set_Container(0);

		if (Is_In_Scene()) {
			model->Notify_Removed(Scene);
		}

		model->Release_Ref();
	}

	AdditionalModels.Delete_All();
	Update_Sub_Object_Bits();
	Update_Obj_Space_Bounding_Volumes();
}
