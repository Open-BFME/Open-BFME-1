// cl: /O2 /DNDEBUG /DWIN32 /MD /EHs
// Retail 0x0060E7F0 (135 B): format a BattleMarker name and return it by value
// (the caller supplies the hidden sret destination).  The caller-visible symbol
// is kept RVA-derived because no named owner for this generated entry is proven.

#include <new>

extern "C" __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);

template <typename T> class StringBase
{
	friend class BFMERetailAsciiString;

private:
	StringBase(const T *text);
	StringBase(const StringBase &other);
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other) : StringBase<char>(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
};

extern "C" BFMERetailAsciiString rva0060E7F0(int marker)
{
	char buffer[64];
	sprintf(buffer, "BattleMarker%04d", marker);
	BFMERetailAsciiString value(buffer);
	return BFMERetailAsciiString(value);
}
