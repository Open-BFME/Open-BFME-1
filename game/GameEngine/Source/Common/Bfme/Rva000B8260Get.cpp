// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class SkyboxTextureSet
{
public:
	static const FieldParse m_fieldParseTable[];
};

void *Rva000B8260Get()
{
	return (void *)SkyboxTextureSet::m_fieldParseTable;
}
