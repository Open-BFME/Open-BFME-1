class Rva0090E470Thing
{
public:
	Rva0090E470Thing(const char *name, int first, int second);

	unsigned char m_bfmePadCX[0x44];
};

void __cdecl Add_Prototype(void *thing);

void __cdecl bfmeRegisterCX(const char *name, int first, int second)
{
	if (name != 0 && first != 0)
		Add_Prototype(new Rva0090E470Thing(name, first, second));
}
