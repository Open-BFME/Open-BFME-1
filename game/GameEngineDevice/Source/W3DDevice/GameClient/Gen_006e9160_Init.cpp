// Retail 0x006E9160.  Fill the three-dword output with the three fixed
// runtime values returned by the neighboring global accessors.

extern int Rva00937270Get( void );
extern int Rva00937250Get( void );
extern int Rva009372C0Get( void );

struct Gen_006e9160_Triple
{
	int m_0;
	int m_4;
	int m_8;
};

void __stdcall Rva006E9160Init( Gen_006e9160_Triple *output )
{
	output->m_0 = Rva00937270Get();
	output->m_4 = Rva00937250Get();
	output->m_8 = Rva009372C0Get();
}
