// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x00887300: file-static wide-character scan. File-static
// scope is what keeps the pointer in EAX and the character in DX
// (mov cx,[eax] / cmp cx,dx) instead of stack slots. The do-while
// spelling with two early returns is what reproduces retail's
// test-first loop and twin je targets.

// Retail 0x008872E0 (21 B), immediately before the wide scan: the narrow
// twin of the same file-static scan (pointer in EAX, character in DL),
// likewise unreferenced in retail and kept by a visible call site. Body
// from the BFME 2 donor Code/Libraries/Source/WWVegas/WWLib/WideStrLenSource.cpp
// (open-bfme-2 20a0cb6173, its 0x00035840), which carried it beside this
// file's wide scan.
static const char *Rva008872E0Scan(const char *s, char c)
{
	char v;
	do
	{
		v = *s;
		if (!v)
			return 0;
		if (v == c)
			return s;
		++s;
	} while (1);
}

// Visible call site so the static is emitted; not claimed.
const char *Rva008872E0Keep(const char *s, char c)
{
	return Rva008872E0Scan(s, c);
}

static const unsigned short *Rva00887300Scan(const unsigned short *s, unsigned short c)
{
	unsigned short v;
	do
	{
		v = *s;
		if (!v)
			return 0;
		if (v == c)
			return s;
		++s;
	} while (1);
}

// Visible call site so the static is emitted; not claimed.
const unsigned short *Rva00887300Keep(const unsigned short *s, unsigned short c)
{
	return Rva00887300Scan(s, c);
}
