// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x00887300: file-static wide-character scan. File-static
// scope is what keeps the pointer in EAX and the character in DX
// (mov cx,[eax] / cmp cx,dx) instead of stack slots. The do-while
// spelling with two early returns is what reproduces retail's
// test-first loop and twin je targets.

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
