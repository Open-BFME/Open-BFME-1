// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class MultiplayerSettings
{
public:
	static const FieldParse m_multiplayerSettingsFieldParseTable[];
};

void *Rva000C25F0Get()
{
	return const_cast<FieldParse *>(MultiplayerSettings::m_multiplayerSettingsFieldParseTable);
}
