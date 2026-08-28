// cl: /Oy-
// A message laid out into the record's own buffer. When the record still holds
// the first kind it is flushed first, and the kind is written down before the
// laying out. The callee is pinned by address.

extern "C" __declspec(dllimport) int __stdcall wvsprintfA(char *out, const char *how, char *rest);

struct BfmeThingQO
{
	void bfmeFlushQO(int how);

	unsigned char m_bfmeHead[0x9cf4];	// 0x0000
	int m_bfmeKind;				// 0x9cf4
	char m_bfmeBuf[4];			// 0x9cf8
};

void bfmeLogQO(BfmeThingQO *what, int kind, const char *how, ...)
{
	if (what->m_bfmeKind == 1)
		what->bfmeFlushQO(1);

	what->m_bfmeKind = kind;

	wvsprintfA(what->m_bfmeBuf, how, (char *)(&how + 1));
}
