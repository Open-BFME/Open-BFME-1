// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <map>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
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

class Open2Held880FC0;

typedef std::map<NameKeyType, Open2Held880FC0 *, std::less<NameKeyType> > Open2Map880FC0;

class Open2Store880FC0 : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Open2Store880FC0();

private:
	Open2Map880FC0 *m_map;
};

// @??1Open2Store880FC0@@UAE@XZ 0x00880FC0
Open2Store880FC0::~Open2Store880FC0()
{
	delete m_map;
}

// The retail 30-byte wrapper at 0x00881180 is this abstract store's
// scalar-deleting destructor.  A delete expression on the pointer emits the
// compiler-owned ??_G wrapper without requiring an abstract local object.
void Force_Open2Store880FC0_DeletingDestructor(Open2Store880FC0 *value)
{
	delete value;
}

class Open2Held8F75D0;

typedef std::map<NameKeyType, Open2Held8F75D0 *, std::less<NameKeyType> > Open2Map8F75D0;

class Open2Store8F75D0 : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Open2Store8F75D0();

private:
	Open2Map8F75D0 *m_map;
};

// @??1Open2Store8F75D0@@UAE@XZ 0x008F75D0
Open2Store8F75D0::~Open2Store8F75D0()
{
	delete m_map;
}

// The retail 30-byte wrapper at 0x008F7890 is this abstract store's
// scalar-deleting destructor.  A delete expression on the pointer emits the
// compiler-owned ??_G wrapper without requiring an abstract local object.
void Force_Open2Store8F75D0_DeletingDestructor(Open2Store8F75D0 *value)
{
	delete value;
}

class Open2Held9A2680;

typedef std::map<NameKeyType, Open2Held9A2680 *, std::less<NameKeyType> > Open2Map9A2680;

class Open2Store9A2680 : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Open2Store9A2680();

private:
	Open2Map9A2680 *m_map;
};

// @??1Open2Store9A2680@@UAE@XZ 0x009A2680
Open2Store9A2680::~Open2Store9A2680()
{
	delete m_map;
}

void Force_Open2Store9A2680_DeletingDestructor(Open2Store9A2680 *value)
{
	delete value;
}
