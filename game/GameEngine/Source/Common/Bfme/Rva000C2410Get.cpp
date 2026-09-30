// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

class Image
{
public:
	static const FieldParse m_imageFieldParseTable[];
};

void *Rva000C2410Get()
{
	return (void *)Image::m_imageFieldParseTable;
}
