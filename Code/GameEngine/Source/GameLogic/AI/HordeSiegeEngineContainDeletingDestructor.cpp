// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: HordeSiegeEngineContain scalar-deleting destructor at retail
// RVA 0x0024A6E0 (30 bytes). Its exact constructor at 0x0024A560, complete
// destructor at 0x0024A180, unique factories, module name, and vtable
// 0x00CB02A8 establish the class. The destructor ILT is 0x00030099.

class HordeSiegeEngineContain
{
public:
	virtual ~HordeSiegeEngineContain();
};

void forceHordeSiegeEngineContainDeletingDestructor()
{
	HordeSiegeEngineContain value;
}
