// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class CommandButton
{
public:
	static const FieldParse m_commandButtonFieldParseTable[];
};

void *Rva000B7F60Get()
{
	return (void *)CommandButton::m_commandButtonFieldParseTable;
}
