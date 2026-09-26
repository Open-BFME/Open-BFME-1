/* cl: /DNDEBUG /MD */

/* Retail 0x008872B0 -- wchar skipWhitespace, sibling of
 * ?skipWhitespace@@YAPADPAD@Z at 0x00887260.
 *
 * File-static so MSVC uses its private EAX-incoming convention. A global
 * function pointer (not a dllimport prototype) is what keeps the call as
 * `call dword ptr [iswspace]` -- the C++ / dllimport form hoists the IAT
 * into EDI and misses retail's aligned-loop shape. */

int (__cdecl *iswspace)(unsigned short);

static unsigned short *skipWhitespace(unsigned short *p)
{
	while (*p && iswspace(*p))
		++p;
	return p;
}

/* Visible call site so the static keeps the EAX convention. Not claimed. */
unsigned short *skipWhitespace_keep(unsigned short *p)
{
	return skipWhitespace(p);
}
