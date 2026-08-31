// cl: /DNDEBUG /MD /EHsc

class MultiIniFieldParse;
class ModuleData;

void *__cdecl operator new(unsigned int size);

class Rva0012A170ModuleData
{
public:
	Rva0012A170ModuleData *construct();

private:
	char m_data[0x9c];
};

void __cdecl Rva0012A170BuildFieldParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(
		void *object,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

class Rva0012A170ModuleFactory
{
public:
	static ModuleData *create(INI *ini);
};

ModuleData *Rva0012A170ModuleFactory::create(INI *ini)
{
	void *memory = operator new(sizeof(Rva0012A170ModuleData));
	Rva0012A170ModuleData *data;
	if (memory != 0)
	{
		data = static_cast<Rva0012A170ModuleData *>(memory)->construct();
	}
	else
	{
		data = 0;
	}

	if (ini != 0)
		ini->initFromINIMultiProc(data, Rva0012A170BuildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
