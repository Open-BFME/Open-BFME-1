// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The BFME store owns a vector of WeaponTemplate pointers. Its complete
// destructor deletes those pointers, clears the vector, and destroys the base.

#include <vector>

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

class WeaponTemplate
{
public:
	virtual ~WeaponTemplate();
};

class WeaponStore : public SubsystemInterface
{
public:
	virtual ~WeaponStore();

private:
	std::vector<WeaponTemplate *> m_weaponTemplateVector;
};

// ??1WeaponStore@@UAE@XZ
WeaponStore::~WeaponStore()
{
	for (unsigned int i = 0; i < m_weaponTemplateVector.size(); ++i)
	{
		WeaponTemplate *wt = m_weaponTemplateVector[i];
		if (wt)
			delete wt;
	}
	m_weaponTemplateVector.clear();
}
