// cl: /DNDEBUG /MD /EHsc

class MaterialInfoClass
{
public:
	virtual ~MaterialInfoClass();
};

__declspec(noinline) MaterialInfoClass::~MaterialInfoClass() {}

void Force_MaterialInfoClass_Deleting_Destructor(MaterialInfoClass *material_info)
{
	delete material_info;
}
