// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class DrawGroupInfo
{
public:
	static const FieldParse s_fieldParseTable[];
};

void *Rva000B8150Get()
{
	return (void *)DrawGroupInfo::s_fieldParseTable;
}
