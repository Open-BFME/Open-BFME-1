// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// FXListStore constructor. GameEngine::init news this object then
// immediately calls initSubsystem<FXListStore>.

#include <hash_map>

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

class FXListStore : public SubsystemInterface
{
public:
	FXListStore();
	virtual ~FXListStore();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	_STL::hash_map<int, int> m_fxmap;
};

// ??0FXListStore@@QAE@XZ
FXListStore::FXListStore()
{
}
