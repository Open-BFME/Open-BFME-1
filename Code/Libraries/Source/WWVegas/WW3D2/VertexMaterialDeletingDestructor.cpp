// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.h
class VertexMaterialClass
{
public:
	virtual ~VertexMaterialClass();
};

__declspec(noinline) VertexMaterialClass::~VertexMaterialClass() {}

void Force_VertexMaterial_Deleting_Destructor(VertexMaterialClass *material)
{
	delete material;
}
