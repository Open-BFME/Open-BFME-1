// ?d_0052ba20@@YAXXZ
// partial score=0.91 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// partial score=0.9
// 85/85 exact size and every retail instruction is positionally present. The
// residue is ONE invariant three-way register rotation:
//   retail  out=edx begin=eax end/count=esi  (push esi shrink-wrapped to +0x20)
//   ours    out=esi begin=edx end/count=eax  (push esi in the prologue)
// Because MSVC gives out the callee-saved esi it must save esi at entry, where
// retail saves it only on the path that uses it. Everything else lines up.
//
// KEEP: volatile on m_bfmeBeginXK. It is what forces retail's second load of
// +0x258 for the subscript. Without it the body is 79 bytes, six short, and
// volatile on m_bfmeEndXK instead does not substitute.
//
// KEEP: the __declspec(dllimport) fixed-arity sprintf alias. It is the project
// idiom that resolves __imp_?bfmeSpf1070@@YAHPAD0H@Z at 0x00F5948C and gives
// retail's `call dword ptr [IAT]`. The earlier stash used a function-pointer
// global, which does not resolve.
//
// RULED OUT -- every one of these leaves the rotation and the 36-byte residue
// bit for bit identical, so do not spend a worker on them again:
//   * variadic sprintf declaration instead of the fixed-arity alias
//   * inlined strcpy(out "0") and memcpy(out "0" 2) for the word store
//     (both do compile to retail's single `mov word ptr [reg] 0x30`)
//   * volatile on end only / on both / on neither
//   * locals declared at the top and assigned later (definition-order lever)
//   * a separate out local; a separate index local; a separate count local
//   * nested guards vs a flat && chain
//   * reversed compare operands; end declared before begin
//   * the register keyword on begin and end
//   * an unsigned short * out parameter; &out[0]; *(begin + index)
//   * this copied into a local before the member reads
//   * sixteen flag sets: O1 Ox Og Os Ot G5 G6 G7 GB Gy Oi Ob0 Ob1 Oy- GX and
//     the plain default. Only the default and its equivalents reach 85 bytes.
//
// What is left to try is something that changes WHICH value MSVC judges worth a
// callee-saved register, not another spelling of this same shape.
extern "C" char g_bfmeFormatXK[];

__declspec(dllimport) int __cdecl bfmeSpf1070(char *b, char *f, int a);

class BfmeOwnerXK
{
public:
	void bfmeFormatXK(unsigned int index, char *out, char flag);

	unsigned char m_bfmeHeadXK[0x258];
	int *volatile m_bfmeBeginXK;
	int *m_bfmeEndXK;
	void *m_bfmeCapXK;
	int m_bfmeModeXK;
};

void BfmeOwnerXK::bfmeFormatXK(unsigned int index, char *out, char flag)
{
	*(unsigned short *)out = 0x30;

	if (flag != 0)
		return;

	if (m_bfmeModeXK != 1)
		return;

	int *begin = m_bfmeBeginXK;
	int *end = m_bfmeEndXK;

	if (begin == end)
		return;

	if (index >= (unsigned int)(end - begin))
		return;

	bfmeSpf1070(out, g_bfmeFormatXK, m_bfmeBeginXK[index]);
}
