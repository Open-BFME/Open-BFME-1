// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class MultiplayerColorDefinition
{
public:
	static const FieldParse m_colorFieldParseTable[];
};

void *Rva000C25E0Get()
{
	return const_cast<FieldParse *>(MultiplayerColorDefinition::m_colorFieldParseTable);
}
