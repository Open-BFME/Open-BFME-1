// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva00889690Obj
{
	char m_pad[0x9F4C];
	char m_flag;
};

// Retail 0x01336E5C is ?g_Rva00F36E5C@@3PAXA (data_rows.csv,
// debug/Rva00F36E5C.cpp); g_rva00889690 was only a pin.
extern void *g_Rva00F36E5C;
#define g_rva00889690 ( *(Rva00889690Obj **)&g_Rva00F36E5C )

void rva00889690Set()
{
	g_rva00889690->m_flag = 1;
}
