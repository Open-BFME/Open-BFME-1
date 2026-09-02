// ?set@ScreenZoomFilter@@QAEHH@Z
// partial score=0.4 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x007D1AA0 size 760: ScreenBWFilter::set.  Fade ladder byte-matches
// retail once EH is on (prolog + if(mode>0) + both fade directions +
// TheTacticalView vtable +0xB0/+0xB8) except retail uses ebx as the zero
// register (later cmp byte ptr [flag], bl) while this TU uses edi.
// Still missing the inlined DX8Wrapper::Set_Material (refcount assign at
// 0x1340EC4 or 0x4000 into render_state_changed), Set_Shader, BoxSetTexture
// with a TextureClass*& local, Apply_Render_State_Changes, and two inlined
// Set_DX8_Render_State (D3DRS_ZFUNC=0x17/D3DCMP_ALWAYS=8 then
// D3DRS_ZWRITEENABLE=0x0E/FALSE) each expanding to the snapshot StringClass
// (0,true) + Get_DX8_Render_State_Value_Name path. Twin 0x007D31C0 is the
// same shape with a different fade-static cluster (0x13071C0 family).

class StringClass
{
public:
	StringClass(int size, bool hint);
	~StringClass();
};

class VertexMaterialClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType preset);
	int m_ref;
	virtual void Release_Ref();
};

void BoxSetTexture(unsigned stage, VertexMaterialClass **texture);
void Apply_Render_State_Changes(void);

class TacticalViewFadeShim
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual bool setViewFilterMode(int mode);
	virtual void unused45();
	virtual bool setViewFilter(int filter);
};

extern TacticalViewFadeShim *TheTacticalViewFadeShim;

extern int m_fadeDirection;
extern int m_curFadeFrame;
extern int m_fadeFrames;
extern float m_curFadeValue;
extern float g_one;

class ScreenBWFilter
{
public:
	int set(int mode);
};

int ScreenBWFilter::set(int mode)
{
	if (mode > 0) {
		if (m_fadeDirection > 0) {
			++m_curFadeFrame;
			int fade = m_curFadeFrame;
			if (fade < m_fadeFrames)
				m_curFadeValue = (float)fade / (float)m_fadeFrames;
			else {
				m_curFadeFrame = 0;
				m_curFadeValue = 1.0f;
				m_fadeDirection = 0;
			}
		} else if (m_fadeDirection < 0) {
			++m_curFadeFrame;
			int fade = m_curFadeFrame;
			if (fade < m_fadeFrames)
				m_curFadeValue = 1.0f - (float)fade / (float)m_fadeFrames;
			else {
				m_curFadeValue = 0.0f;
				TheTacticalViewFadeShim->setViewFilterMode(0);
				TheTacticalViewFadeShim->setViewFilter(0);
				m_curFadeFrame = 0;
				m_fadeDirection = 0;
			}
		}

		StringClass snapshot(0, true);
		VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		if (vmat)
			++vmat->m_ref;
		VertexMaterialClass *unused = 0;
		BoxSetTexture(0, (VertexMaterialClass **)&unused);
		Apply_Render_State_Changes();
		Apply_Render_State_Changes();
		if (vmat) {
			if (--vmat->m_ref == 0)
				vmat->Release_Ref();
		}
		return 1;
	}
	return 0;
}
