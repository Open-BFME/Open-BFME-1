// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x0022ECE0 calls HordeSiegeEngineContainModuleDataBase::~HordeSiegeEngineContainModuleDataBase through ILT 0x000179B8.

class HordeSiegeEngineContainModuleDataBase
{
public:
	virtual ~HordeSiegeEngineContainModuleDataBase();
};

__declspec(noinline) HordeSiegeEngineContainModuleDataBase::~HordeSiegeEngineContainModuleDataBase() {}

void Force_HordeSiegeEngineContainModuleDataBase_Deleting_Destructor(HordeSiegeEngineContainModuleDataBase *data)
{
	delete data;
}
