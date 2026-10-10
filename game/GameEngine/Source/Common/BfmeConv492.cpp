// Retail 0x002937B0 (26 bytes) default-constructs { int, AsciiString }: the
// int is zeroed and the name is built by StringBase<char>(const char *)
// (0x00888BC0) from the pinned empty-string literal (symbols.csv
// ?g_Rva0107301CEmptyString@@3QBDB, RVA 0x00C7301C). Owner unknown.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern const char g_Rva0107301CEmptyString[];

class Rva002937B0
{
public:
	Rva002937B0();
	int m_value;
	AsciiString m_name;
};

Rva002937B0::Rva002937B0()
	: m_value(0), m_name(g_Rva0107301CEmptyString)
{
}
