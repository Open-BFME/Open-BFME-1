// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class ControlBarSchemeManager
{
public:
	static const FieldParse m_controlBarSchemeFieldParseTable[];
};

void *Rva000B8060Get()
{
	return (void *)ControlBarSchemeManager::m_controlBarSchemeFieldParseTable;
}
