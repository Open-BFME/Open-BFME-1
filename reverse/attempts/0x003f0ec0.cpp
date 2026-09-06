// ?bfmeFwdBK@@YGXPAXPAVBfmeSrcBK@@0000@Z (identity unknown)
// partial score=0.9 date=2026-09-06
// 43/43 in size, structure exact: six parameters forwarded plus a dereference
// of the second and a trailing zero, seven arguments in all.
// Residue is the argument-shuttle pattern already logged at 0x0047C9F0:
// retail loads each stack parameter into edx one at a time, pushing between
// the loads (same displacement, different esp), while MSVC preloads three of
// them into eax, ecx and edx first. 0x003F0F00 is the adjacent twin.
class BfmeSrcBK
{
public:
	unsigned char m_bfmeHeadBK[0x10];
	void *m_bfmeValueBK;
};

void __stdcall bfmeRunBK(void *first, void *value, void *third, void *fourth,
	void *fifth, void *sixth, void *seventh);

void __stdcall bfmeFwdBK(void *first, BfmeSrcBK *source, void *third, void *fourth,
	void *fifth, void *sixth)
{
	bfmeRunBK(first, source->m_bfmeValueBK, third, fourth, fifth, sixth, 0);
}
