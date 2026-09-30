// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class UpgradeTemplate
{
	friend void *Rva0010A720Get();

protected:
	static const FieldParse m_upgradeFieldParseTable[];
};

void *Rva0010A720Get()
{
	return (void *)UpgradeTemplate::m_upgradeFieldParseTable;
}
