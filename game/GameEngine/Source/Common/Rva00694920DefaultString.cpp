// cl: /DNDEBUG /MD /EHsc
// Retail 0x00694920 returns the holder pointer or the shared empty string.

struct Rva002E5FF0Str
{
};

extern Rva002E5FF0Str Rva01336E50Str;

class Rva00694920
{
public:
	Rva002E5FF0Str *get();

	Rva002E5FF0Str *m_pointee;
};

Rva002E5FF0Str *Rva00694920::get()
{
	if (m_pointee)
		return m_pointee;
	return &Rva01336E50Str;
}
