// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Three subsystem destructors landed as relocation-blind twins of
// Code/GameEngine/Source/GameClient/FXListStoreDestructorThunk.cpp
// (0x009F2800).  Each differs from the model in four slots and three of them
// are automatic: its own EH table and its own two vtables, which are distinct
// symbols per class.  The fourth is the map deleting destructor, one per
// element type.
//
// The element type is not recoverable from these bytes -- the map is only
// destroyed here -- so each is a distinct forward-declared class named after
// the body's address.

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
