// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

typedef unsigned char Byte;

#pragma pack(push, 1)
struct Rva0051B5F0Small
{
	unsigned m_value;
	Byte m_tail;
};

struct Rva0051B5F0Medium
{
	unsigned m_first;
	unsigned m_second;
	unsigned short m_tail;
};

struct Rva0051B5F0Large
{
	unsigned m_first;
	unsigned m_second;
	unsigned m_third;
	Byte m_tail;
};
#pragma pack(pop)

Rva0051B5F0Small g_Va01105FA8 = { 0x6E616C5F, 0x0 };
Rva0051B5F0Medium g_Va01105FB0 = { 0x696B735F, 0x73696D72, 0x68 };
Rva0051B5F0Large g_Va01105FBC = { 0x746E695F, 0x656E7265, 0x76644174, 0x0 };

class Rva0051B5F0Owner
{
public:
	void copyPreset( void *unused, void *destination, bool skip );

private:
	Byte m_opaque[0x14];
	int m_kind;
};

void Rva0051B5F0Owner::copyPreset( void *, void *destination, bool skip )
{
	if( skip )
	{
		return;
	}

	switch( m_kind )
	{
		case 1:
			*(Rva0051B5F0Small *)destination = g_Va01105FA8;
			break;
		case 2:
			*(Rva0051B5F0Medium *)destination = g_Va01105FB0;
			break;
		case 5:
			*(Rva0051B5F0Large *)destination = g_Va01105FBC;
			break;
	}
}
