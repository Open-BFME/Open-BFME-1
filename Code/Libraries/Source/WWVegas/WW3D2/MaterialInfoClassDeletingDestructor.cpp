// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/matinfo.h
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
