// ?d_005c8e90@@YAXXZ
// partial score=0.99 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>

class FXParticleValueSupplier
{
public:
	virtual ~FXParticleValueSupplier();
	virtual void unused();
	virtual void *getValue(void *context) = 0;
};

class FXParticleValueCollector
{
public:
	void collect(std::vector<void *> &output, void *context);

private:
	unsigned char m_pad[0xc0];
	std::vector<FXParticleValueSupplier *> m_suppliers;
};

void FXParticleValueCollector::collect(
	std::vector<void *> &output, void *context)
{
	std::vector<void *> values;
	values.reserve(m_suppliers.size());
	for (std::vector<FXParticleValueSupplier *>::iterator it = m_suppliers.begin();
		it != m_suppliers.end(); ++it)
	{
		values.push_back((*it)->getValue(context));
	}
	output.swap(values);
}
