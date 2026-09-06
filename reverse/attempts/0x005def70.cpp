// ?getInstance@?$ConcreteModuleClass@...@FXParticleSystem@@SAABV12@XZ (template instantiation)
// partial score=0.98 date=2026-09-06
// EXACT-MATCH recipe: this standalone model compiles to 104/104 byte-identical code.
// The real conversion belongs inside the template in
// Code/GameEngine/Source/GameClient/System/FXParticleSystem/fx_particle_system_bulk.cpp
// and yields all seventeen instantiations at once.
// This standalone model compiles to 104/104 byte-identical code; the real
// conversion is to write this body inside the template in
// Code/GameEngine/Source/GameClient/System/FXParticleSystem/fx_particle_system_bulk.cpp
// which yields all seventeen instantiations at once.
// cl: /EHs-c-
extern "C" void *bfmeVtFN[];
class BfmeStaticFN;
extern void **g_bfmeSrcAFN;
extern void **g_bfmeSrcBFN;
extern BfmeStaticFN *g_bfmeHeadFN;
class BfmeStaticFN
{
public:
	BfmeStaticFN(void)
	{
		void *b = *g_bfmeSrcBFN;
		void *a = *g_bfmeSrcAFN;
		m_bfmeBFN = b;
		m_bfmeAFN = a;
		m_bfmeNextFN = g_bfmeHeadFN;
		g_bfmeHeadFN = this;
		m_bfmeVtFN = bfmeVtFN;
	}
	~BfmeStaticFN(void);
	void *m_bfmeVtFN;
	void *m_bfmeAFN;
	void *m_bfmeBFN;
	BfmeStaticFN *m_bfmeNextFN;
};
BfmeStaticFN *bfmeGetFN(void)
{
	static BfmeStaticFN s_bfmeInstanceFN;
	return &s_bfmeInstanceFN;
}
