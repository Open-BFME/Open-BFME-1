// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// 0x000D4870: AsciiString -> NameKeyType via TheNameKeyGenerator (ILT
// 0x0003ADD7), then std::map<NameKeyType, T*>::find at this+0x214 (ILT
// 0x0003DEAB -> 0x000D0F50, the NameKeyType rb-tree find already claimed
// as the ZH STLport instantiation). Returns the mapped pointer or null.
// Owning class is not recovered.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);	///< ILT 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;	///< retail [0x012ED600]

typedef _STL::map<NameKeyType, void *, _STL::less<NameKeyType> > Rva000D4870Map;

class Rva000D4870
{
public:
	void *find(const AsciiString &name);

private:
	unsigned char m_unmodelled_000[0x214];
	Rva000D4870Map m_map;					// +0x214
};

// ?find@Rva000D4870@@QAEPAXABVAsciiString@@@Z
void *Rva000D4870::find(const AsciiString &name)
{
	Rva000D4870Map::iterator it = m_map.find(TheNameKeyGenerator->nameToKey(name.str()));
	if (it != m_map.end())
		return it->second;
	return 0;
}
