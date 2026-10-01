/* cl: /DNDEBUG /MD */

/* Retail 0x008872B0: private EAX-incoming scan, returning its pointer in EAX.
 * The external pointer below views the native import-library-owned IAT cell;
 * it allocates no local function-pointer object. Its loads match retail's
 * FF15 through MSVCR71!iswspace at IAT VA0x01359438. */

/* Canonical imported IAT cell, declared as an external pointer view only.
 * C external _imp__iswspace emits canonical COFF __imp__iswspace.
 * wint_t is unsigned short in the native MSVCR71 ABI. */
extern int (__cdecl *_imp__iswspace)(unsigned short);
#define iswspace _imp__iswspace

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
