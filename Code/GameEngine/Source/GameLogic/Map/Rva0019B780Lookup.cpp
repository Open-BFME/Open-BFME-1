// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "StringInline.h"

struct Rva0019B780Key
{
	AsciiString first;
	AsciiString second;
};

struct Rva0019B780Node
{
	unsigned char m_data[0x1c];
};

class Rva0019B780Tree
{
public:
	Rva0019B780Node *find( const Rva0019B780Key &key ) const throw();

private:
	unsigned char m_tree[12];
};

extern Rva0019B780Key __cdecl Rva00194810( const AsciiString &name );

struct Rva0019B780Entry
{
	unsigned char m_data[16];
};

class Rva0019C520Member
{
public:
	int lookup( AsciiString *name, int extra );

private:
	Rva0019B780Tree m_tree;
	Rva0019B780Entry *m_entries;
};

int Rva0019C520Member::lookup( AsciiString *name, int extra )
{
	AsciiString *input;
	input = name;
	Rva0019B780Node *found;
	{
		found = m_tree.find( Rva00194810( *input ) );
	}
	if (found == *(Rva0019B780Node **)&m_tree)
		return 0;
	int index = *(int *)((char *)found + 0x18);
	Rva0019B780Entry *entry = m_entries + index;
	if (extra)
		*(int *)extra = index;
	return (int)((char *)entry + 0x0c);
}
