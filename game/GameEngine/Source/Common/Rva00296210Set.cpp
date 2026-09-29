// cl: /O2 /Ob0

extern "C" void *bfmeVftLargeGroupAudioUpdateModuleDataBase[];
#pragma comment(linker, "/alternatename:_bfmeVftLargeGroupAudioUpdateModuleDataBase=??_7LargeGroupAudioUpdateModuleDataBase@@6B@")

class Rva00296210
{
	void *m_vptr;
	int m_04;

public:
	Rva00296210 &set(const Rva00296210 *p);
};

Rva00296210 &Rva00296210::set(const Rva00296210 *p)
{
	m_vptr = bfmeVftLargeGroupAudioUpdateModuleDataBase;
	m_04 = p->m_04;
	return *this;
}
