// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &that);
	~AsciiString(void);

private:
	char *m_data;
};

AsciiString __cdecl bfmeSlashOrDefaultName(AsciiString &name,
	const AsciiString &fallback);

class BfmeScriptEngineSlashName
{
public:
	AsciiString bfmeName(AsciiString &name);

private:
	char m_pad[0x17088];
	AsciiString m_fallback;
};

AsciiString BfmeScriptEngineSlashName::bfmeName(AsciiString &name)
{
	return bfmeSlashOrDefaultName(name, m_fallback);
}
