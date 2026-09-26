// ?rva008B8F80AtoiOrZero@@YAHPBD@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Static ESI-arg helper: true when atoi(text) is nonzero, or when atoi
// returns 0 and the first character is '0'.

extern "C" int __cdecl atoi(const char *text);

static int rva008B8F80AtoiOrZero(const char *text)
{
	if (atoi(text) == 0)
		return *text == '0';
	return 1;
}

// absent-from-retail: keeps the static alive with the ESI argument convention.
int rva008B8F80AtoiOrZeroCaller(const char *text)
{
	if (text)
		return rva008B8F80AtoiOrZero(text);
	return 0;
}
