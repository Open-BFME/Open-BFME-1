// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <map>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	~Snapshot() {}
	virtual void crc() = 0;
	virtual void xfer() = 0;
	virtual void loadPostProcess() = 0;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class TeamPrototype;
typedef std::map<NameKeyType, TeamPrototype *, std::less<NameKeyType> > FXListMap;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXListStore : public SubsystemInterface, public Snapshot
{
public:
	virtual ~FXListStore();

private:
	FXListMap *m_fxmap;
};

// ??1FXListStore@@UAE@XZ
FXListStore::~FXListStore()
{
	delete m_fxmap;
}
