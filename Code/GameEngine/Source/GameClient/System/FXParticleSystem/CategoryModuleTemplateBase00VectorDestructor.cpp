// BFME FXParticleSystem::CategoryModuleTemplateBase<1> vector-deleting
// destructor at retail RVA 0x005BF190.

void operator delete[](void *block);

namespace FXParticleSystem
{
	template<int Category> class CategoryModuleTemplateBase;

	template<> class CategoryModuleTemplateBase<1>
	{
	public:
		virtual ~CategoryModuleTemplateBase();

	private:
		int m_pad;
	};

typedef CategoryModuleTemplateBase<1> CategoryModuleTemplateBase1;

CategoryModuleTemplateBase1 *CreateCategoryModuleTemplateBase1Array()
{
	return new CategoryModuleTemplateBase1[2];
}

void DeleteCategoryModuleTemplateBase1Array(CategoryModuleTemplateBase1 *value)
{
	delete[] value;
}

}
