// cl: /DNDEBUG /DWIN32 /MD /EHs-c-
// INI::getNextTokenPreprocess -- retail 0x008525C0 (86B) from d_00849530.asm.
//
// BFME-only helper: same shape as getNextToken (0x00850970) but the success
// path runs preprocessMacro on the token before returning. Sole caller at
// 0x00369C30 takes an attribute name via plain getNextToken, then the value
// via this so macros expand before scanReal/scanPercentToReal.
//
// Throw shape from BitFlagsParseToken: variadic INIException at 0x00850600
// then _CxxThrowException. m_seps lives at +0x414.

typedef int Int;

class INIException
{
public:
	INIException(Int code, const char *msg, ...);
	INIException(const INIException &other);

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	const char *getNextTokenPreprocess(const char *seps);
	static const char *preprocessMacro(const char *token);

private:
	char m_beforeSeps[0x414];
	const char *m_seps;
};

extern "C" __declspec(dllimport) char *__cdecl strtok(char *s, const char *delim);

const char *INI::getNextTokenPreprocess(const char *seps)
{
	if (!seps)
		seps = m_seps;
	const char *token = strtok(0, seps);
	if (!token)
		throw INIException(3, "Expected additional data after '%s'", seps);
	return preprocessMacro(token);
}
