// ?getInstance@?$ConcreteModuleClass@...@FXParticleSystem@@SAABV12@XZ (template instantiation)
// partial score=0.98 date=2026-09-06
// EXACT-MATCH recipe: this standalone model compiles to 104/104 byte-identical code.
// The real conversion belongs inside the template in
// Code/GameEngine/Source/GameClient/System/FXParticleSystem/fx_particle_system_bulk.cpp
// and yields all seventeen instantiations at once.
// PLACEMENT OBSTACLE (checked 2026-09-06): ConcreteModuleClass<...> is declared in
// fx_particle_system.h with NO data members, and that header is compiled twice -
// fx_particle_system_bulk.cpp leaves FXPS_V empty (non-polymorphic) while
// fx_particle_system.cpp defines FXPS_V as virtual (vfptr at +0). Retail's object
// needs a table pointer at +0 plus three fields, so giving the class members changes
// the layout in BOTH configurations and can disturb already-matched bodies in either
// file. Converting these seventeen is therefore a header-restructuring task, not a
// body-level one; the byte recipe below is settled and waits on that decision.
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
