// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: ResourceGatheringManager's virtual destructor.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

class ResourceGatheringManagerBase
{
public:
	virtual ~ResourceGatheringManagerBase() {}
};

class ResourceGatheringManager : public ResourceGatheringManagerBase
{
public:
	virtual ~ResourceGatheringManager();
	virtual void slot1() = 0;
	virtual const char *name() const = 0;
	virtual void seed(void *) = 0;

private:
	_STL::list<int> m_supplyWarehouses;
	_STL::list<int> m_supplyCenters;
};

// ??1ResourceGatheringManager@@UAE@XZ
ResourceGatheringManager::~ResourceGatheringManager()
{
	m_supplyWarehouses.erase(m_supplyWarehouses.begin(), m_supplyWarehouses.end());
	m_supplyCenters.erase(m_supplyCenters.begin(), m_supplyCenters.end());
}
