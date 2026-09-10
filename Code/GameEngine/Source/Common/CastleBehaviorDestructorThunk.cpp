// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <map>
#include <set>
#include <vector>

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
};

class ObjectModule : public Gen_dtor_00113f20
{
private:
	void *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class FoundationAIUpdateIface3
{
public:
	virtual void interface3Anchor() = 0;
};

class Gen_dtor_000b33c0
{
public:
	virtual ~Gen_dtor_000b33c0();

private:
	unsigned char m_data[0x6c];
};

class FoundationAIUpdate : public UpdateModule, public FoundationAIUpdateIface3
{
public:
	virtual ~FoundationAIUpdate();

private:
	Gen_dtor_000b33c0 m_member;
	void *m_pendingFoundation;
	bool m_pendingFlag;
};

struct Gen_t_000a3c70_p4pod
{
	int a[1];
};

bool operator==(const Gen_t_000a3c70_p4pod&, const Gen_t_000a3c70_p4pod&);
bool operator<(const Gen_t_000a3c70_p4pod&, const Gen_t_000a3c70_p4pod&);

struct Gen_t_000ef440_k4
{
	int a[1];
	Gen_t_000ef440_k4();
	Gen_t_000ef440_k4(const Gen_t_000ef440_k4&);
	~Gen_t_000ef440_k4();
	Gen_t_000ef440_k4& operator=(const Gen_t_000ef440_k4&);
};

bool operator==(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);
bool operator<(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);

class Gen_00371120
{
public:
	void bfmeClear();
};

class CastleOwnedObject;

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
	int m_length;
};

class CastleBehavior : public FoundationAIUpdate
{
public:
	virtual ~CastleBehavior();

private:
	int m_at9c;
	int m_ata0;
	unsigned char m_ata4;
	unsigned char m_ata5;
	int m_ata8;
	unsigned char m_atac;
	int m_atb0;
	int m_atb4;
	_STL::vector<CastleOwnedObject *> m_vectorB8;
	_STL::vector<CastleOwnedObject *> m_vectorC4;
	_STL::vector<CastleOwnedObject *> m_vectorD0;
	_STL::vector<CastleOwnedObject *> m_vectorDC;
	_STL::vector<CastleOwnedObject *> m_vectorE8;
	_STL::set<Gen_t_000ef440_k4> m_setF4;
	BFMERetailAsciiString m_string100;
	_STL::map<int, Gen_t_000a3c70_p4pod> m_map108;
};

// ??1CastleBehavior@@UAE@XZ
CastleBehavior::~CastleBehavior()
{
	reinterpret_cast<Gen_00371120 *>(this)->bfmeClear();
}
