class Rva0090E570Thing
{
public:
	Rva0090E570Thing(const char *name, int first, int second);

	unsigned char m_bfmePadCY[0x44];
};

void __cdecl Add_Prototype(void *thing);

void __cdecl bfmeRegisterCY(const char *name, int first, int second)
{
	if (name != 0 && first != 0)
		Add_Prototype(new Rva0090E570Thing(name, first, second));
}
