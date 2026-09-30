// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Address-derived body at retail RVA 0x009AAD20, 208 bytes.
// Four INT3 bytes precede entry; every branch stays inside the body and the
// last complete RET is at +0xCF, immediately before the next entry at 0x009AADF0.
// Clears the 128-byte buffer pointed to by context+0x270, then dispatches
// through mapped callback cells.
// Layout and dispatch follow the separately matched body at 0x009B5830.
#include <string.h>
struct Rva009AAD20State {
 unsigned char pad0[8]; int m_08;
 unsigned char padC[0x70-0xc]; int m_70,m_74;
 unsigned char pad78[0x24c-0x78];
 unsigned char *m_24c; unsigned pad250;
 unsigned char *m_254; unsigned pad258;
 unsigned char *m_25c; unsigned char pad260[0x270-0x260];
 void *m_270; unsigned char pad274[0x284-0x274]; void *m_284;
};
struct Rva009B5830State;
extern void *g_bfmeSlotD84;
extern void *g_bfmeSlotD88;
extern void *g_bfmeSlotD8C;
extern int g_rva00ED7770Vp6ModeDispatch[];

typedef void (__cdecl *Rva009AAD20CallD84)(
	void *, unsigned char *, unsigned char *, void *, int);
typedef void (__cdecl *Rva009AAD20CallD88)(
	void *, void *, unsigned char *, int);
typedef void (__cdecl *Rva009AAD20CallD8C)(
	void *, unsigned char *, void *, int);

// Retail 0x009B5530 reads the state, m_284, and block arguments at
// incoming [esp+4], [esp+8], and [esp+0xc]; declare that real body
// with the cdecl ABI instead of casting the generated no-argument row.
extern void __cdecl Rva009B5530Prepare(Rva009B5830State *, void *, int);

void Rva009AAD20(Rva009AAD20State *state, int block)
{
	memset(state->m_270,0,128);
	if (state->m_08 == 0) {
		((Rva009AAD20CallD84)g_bfmeSlotD84)(state->m_284,
			state->m_25c + state->m_70,
			state->m_254 + state->m_70,
			state->m_270, state->m_74);
	} else if (g_rva00ED7770Vp6ModeDispatch[state->m_08] != 0) {
		Rva009B5530Prepare((Rva009B5830State*)state, state->m_284, block);
		((Rva009AAD20CallD88)g_bfmeSlotD88)(state->m_284,
			state->m_270, state->m_25c + state->m_70,
			state->m_74);
	} else if (state->m_08 == 5) {
		((Rva009AAD20CallD84)g_bfmeSlotD84)(state->m_284,
			state->m_25c + state->m_70,
			state->m_24c + state->m_70,
			state->m_270, state->m_74);
	} else {
		((Rva009AAD20CallD8C)g_bfmeSlotD8C)(state->m_284,
			state->m_25c + state->m_70,
			state->m_270, state->m_74);
	}
}
