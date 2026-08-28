// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ lift of the ProductionUpdateModuleData destructor.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_data;
};

class RefCountedThing
{
public:
	virtual ~RefCountedThing();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0) {
			delete this;
		}
	}

	long m_refCount;
};

class ThingRef
{
public:
	~ThingRef()
	{
		if (m_ptr) {
			m_ptr->Release_Ref();
		}
	}

private:
	RefCountedThing *m_ptr;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}

private:
	unsigned char m_pad[0x18];
};

// Stand-in for the non-inline 12-byte member teardown at retail 0x0003BD59.
class ProductionUpdateModuleDataBase
{
public:
	virtual ~ProductionUpdateModuleDataBase();

private:
	unsigned char m_pad[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionUpdate.h
class ProductionUpdateModuleData : public Snapshot
{
public:
	virtual ~ProductionUpdateModuleData();

private:
	ProductionUpdateModuleDataBase m_quantityModifiers;
	unsigned char m_gap[0x18];
	BFMERetailAsciiString m_name;
	ThingRef m_ref;
};

// ??1ProductionUpdateModuleData@@UAE@XZ
ProductionUpdateModuleData::~ProductionUpdateModuleData()
{
}
