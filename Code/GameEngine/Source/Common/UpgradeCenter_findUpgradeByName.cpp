// cl: /DNDEBUG /DWIN32 /MD /EHsc

// BFME's name-based convenience entry point accepts a raw string, owns the
// temporary AsciiString across lookup, and permits calls before subsystem init.

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

const UpgradeTemplate *bfmeFindUpgradeByName(const char *name)
{
	if (TheUpgradeCenter != 0)
	{
		AsciiString key(name);
		return TheUpgradeCenter->findUpgrade(key);
	}
	return 0;
}
