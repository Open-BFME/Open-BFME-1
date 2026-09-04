// cl: /DNDEBUG /DWIN32 /MD /EHsc

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

struct UpgradeWithDelay
{
	const UpgradeTemplate *m_upgrade;
	unsigned int m_delay;
};

class INI
{
public:
	const char *getNextToken(const char *separators);
	const char *getNextTokenOrNull(const char *separators);
	const char *getNextTokenOrNull()
	{
		return getNextTokenOrNull(getSeparators());
	}
	const char *getSeparators() const { return m_separators; }
	static unsigned int scanUnsignedInt(const char *token);
	static void bfmeParseUpgradeWithDelay(INI *ini, void *instance,
		void *store, const void *userData);

	unsigned char m_unmodelled000[0x41C];
	const char *m_separators;
};

void INI::bfmeParseUpgradeWithDelay(INI *ini, void *, void *store,
	const void *)
{
	const char *name = ini->getNextToken(0);
	if (TheUpgradeCenter == 0)
		return;

	UpgradeWithDelay *value = static_cast<UpgradeWithDelay *>(store);
	{
		AsciiString key(name);
		value->m_upgrade = TheUpgradeCenter->findUpgrade(key);
	}

	const char *option = ini->getNextTokenOrNull();
	if (option != 0 && strcmp(option, "Delay") == 0)
	{
		const char *delay = ini->getNextToken(0);
		if (delay != 0)
		{
			unsigned int rawDelay = scanUnsignedInt(delay);
			value->m_delay = static_cast<unsigned short>(
				ceil(static_cast<double>(rawDelay * 0.005f)));
		}
	}
}
