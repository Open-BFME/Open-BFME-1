// cl: /DNDEBUG /MD /EHsc

void * __cdecl operator new(unsigned int);
void Add_Prototype(void *prototype);

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual void handle();

private:
	char m_pad[0x10];
};

class Rva00972880 : public GenBase009EB7D0
{
public:
	Rva00972880() {}
};

void Create_Rva00972880_Prototype()
{
	Rva00972880 *p = new Rva00972880;
	Add_Prototype(p);
}
