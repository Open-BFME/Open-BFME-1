// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

// ZH GameClient/Image.h keeps the table protected (Image.cpp emits
// ?m_imageFieldParseTable@Image@@1QBUFieldParse@@B).
class Image
{
	friend void *Rva000C2410Get();

protected:
	static const FieldParse m_imageFieldParseTable[];
};

void *Rva000C2410Get()
{
	return (void *)Image::m_imageFieldParseTable;
}
