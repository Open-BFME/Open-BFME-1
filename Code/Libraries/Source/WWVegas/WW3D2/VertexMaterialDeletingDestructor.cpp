// cl: /DNDEBUG /MD /EHsc

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
