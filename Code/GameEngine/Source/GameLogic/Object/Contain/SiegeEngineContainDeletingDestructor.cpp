// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: SiegeEngineContain scalar-deleting destructor at retail RVA
// 0x0022BDB0 (30 bytes). Its exact constructor at 0x0022BC50, complete
// destructor at 0x0022B870, unique factories, module name, and vtable
// 0x00CAD088 establish the class. The destructor ILT is 0x0004AB47.

class SiegeEngineContain
{
public:
	virtual ~SiegeEngineContain();
};

void forceSiegeEngineContainDeletingDestructor()
{
	SiegeEngineContain value;
}
