// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x009CC330 returns this + strlen(this+8) + 9: the NUL-terminated
// name at this+8 is measured with strlen and the base re-added.
// IDENTITY IS NOT RECOVERED: the name keeps its address token.
extern "C" __declspec(dllimport) unsigned int __cdecl strlen(const char *s);

class Rva009CC330Box
{
public:
	char *end();
	char m_pad[8];
	char m_name[1];
};

char *Rva009CC330Box::end()
{
	return m_name + strlen(m_name) + 1;
}
