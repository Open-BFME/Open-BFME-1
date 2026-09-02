// cl: /DNDEBUG /MD /EHsc

void * __cdecl operator new(unsigned int);
void Add_Prototype(void *prototype);
bool Render_Obj_Exists(const char *name);

class Rva009723C0Proto
{
public:
	Rva009723C0Proto(const char *name, int first, int second);

private:
	unsigned char m_data[0x24];
};

void Register_Rva009723C0_Prototype(const char *name, int first, int second)
{
	if (name && !Render_Obj_Exists(name))
		Add_Prototype(new Rva009723C0Proto(name, first, second));
}
