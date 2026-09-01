// cl: /DNDEBUG /MD /EHsc

class MeshLoadContextClass
{
public:
	struct LegacyMaterialClass;
};

template <class T> class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
};

template <class T> __declspec(noinline) DynamicVectorClass<T>::~DynamicVectorClass() {}

template class DynamicVectorClass<MeshLoadContextClass::LegacyMaterialClass *>;

void Force_DynamicVectorLegacyMaterial_Deleting_Destructor(
	DynamicVectorClass<MeshLoadContextClass::LegacyMaterialClass *> *vector)
{
	delete vector;
}
