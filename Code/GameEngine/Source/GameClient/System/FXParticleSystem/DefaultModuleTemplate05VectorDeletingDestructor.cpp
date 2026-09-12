// cl: /O2
// BFME FXParticleSystem::DefaultModuleTemplate<6> vector-deleting
// destructor at retail RVA 0x005D5830. The scalar destructor is matched at
// 0x005D5760 and the wrapper reaches it through ILT 0x00013101.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class DefaultModuleTemplate;

template <> class DefaultModuleTemplate<6>
{
public:
	virtual ~DefaultModuleTemplate();

private:
	int m_pad[2];
};

DefaultModuleTemplate<6> *MakeDefaultModuleTemplate05Array()
{
	return new DefaultModuleTemplate<6>[2];
}

void DeleteDefaultModuleTemplate05Array(DefaultModuleTemplate<6> *array)
{
	delete[] array;
}
}
