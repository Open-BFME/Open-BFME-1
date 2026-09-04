// cl: /DNDEBUG /MD /EHs-c-
// partial score=0.78
//
// Open-BFME5: ScriptEngine-shaped AsciiString forwarder at retail 0x003398F0
// (42B). add ecx,0x17088 then cdecl helper ILT 0x00044E3B -> 0x001945D0.
// Without the retail push-ecx / zero-local / pop-ecx frame the body is an
// exact instruction multiset match at 35/42; volatile scratch restores the
// frame but clobbers ecx ordering. Wall is the dead default-constructed
// stack slot retail zeros and discards without a destructor.

class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &that);
	~AsciiString(void);

private:
	char *m_data;
};

AsciiString __cdecl bfmeSlashOrDefaultName(const AsciiString &name,
	const AsciiString &fallback);

class BfmeScriptEngineSlashName
{
public:
	AsciiString bfmeName(const AsciiString &name);

private:
	char m_pad[0x17088];
	AsciiString m_fallback;
};

AsciiString BfmeScriptEngineSlashName::bfmeName(const AsciiString &name)
{
	return bfmeSlashOrDefaultName(name, m_fallback);
}
