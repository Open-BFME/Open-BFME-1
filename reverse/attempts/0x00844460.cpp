// ?bfmeMakeES@@YGPAVBfmeCtorES@@PAV1@PAX1@Z (identity unknown)
// partial score=0.9 date=2026-09-06
// 91/87. Placement new + placement delete recover the SEH frame and the whole
// shape; the only excess is MSVC null-checking the placement pointer (4 bytes).
// EH unwind map (FuncInfo 0x00E44CE8, maxState 1): the single funclet does
//   mov ecx,[ebp+4]; jmp 0x00032D85
// so the object destroyed on unwind is *arg1 and the class destructor is at
// 0x00032D85 -- that is what proves this is placement construction into the
// first stack argument rather than a thiscall constructor.
inline void *__cdecl operator new(unsigned int size, void *place) { return place; }
inline void __cdecl operator delete(void *block, void *place) {}

class BfmeCtorES
{
public:
	BfmeCtorES(void *first, void *second, void **out)
	{
		m_bfmeAES = 0;
		m_bfmeBES = 0;
		m_bfmeCES = 0;
		bfmeStartES(first, second, out);
	}
	~BfmeCtorES(void);

	void bfmeStartES(void *first, void *second, void **out);

	int m_bfmeAES;
	int m_bfmeBES;
	int m_bfmeCES;
};

BfmeCtorES * __stdcall bfmeMakeES(BfmeCtorES *self, void *first, void *second)
{
	return new (self) BfmeCtorES(first, second, (void **)&self);
}
