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

extern Rva0051B5F0Small g_rva0051B5F0Small;
extern Rva0051B5F0Medium g_rva0051B5F0Medium;
extern Rva0051B5F0Large g_rva0051B5F0Large;

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
			*(Rva0051B5F0Small *)destination = g_rva0051B5F0Small;
			break;
		case 2:
			*(Rva0051B5F0Medium *)destination = g_rva0051B5F0Medium;
			break;
		case 5:
			*(Rva0051B5F0Large *)destination = g_rva0051B5F0Large;
			break;
	}
}
