// ?attachRenderObjects@Rva00980A00Owner@@QAEXPAURva00980A00Target@@@Z
class RenderObjClass;
RenderObjClass* Create_Render_Obj(const char* name);
struct Rva00980A00Ref { virtual void deleteThis(); int m_refs; void releaseRef() { if (--m_refs == 0) deleteThis(); } };
struct Rva00980A00Entry { char m_name[0x20]; char m_transform[1]; };
struct Rva00980A00Target {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void attach(RenderObjClass* robj, void* transform, int flag);
};
struct Rva00980A00Owner {
	char m_pad[0xc];
	Rva00980A00Entry** m_entries;
	char m_pad2[0x18 - 0x10];
	int m_count;
	void attachRenderObjects(Rva00980A00Target* target);
};
void Rva00980A00Owner::attachRenderObjects(Rva00980A00Target* target)
{
	for (int i = 0; i < m_count; ++i) {
		Rva00980A00Entry* e = m_entries[i];
		if (e) {
			RenderObjClass* robj = Create_Render_Obj(e->m_name);
			if (robj) {
				target->attach(robj, e->m_transform, 0);
				((Rva00980A00Ref*)robj)->releaseRef();
			}
		}
	}
}
