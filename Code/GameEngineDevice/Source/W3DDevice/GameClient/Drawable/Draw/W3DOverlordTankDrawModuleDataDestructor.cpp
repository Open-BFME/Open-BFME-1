// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

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

class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class UpgradeModuleDataSub
{
public:
	~UpgradeModuleDataSub();

private:
	unsigned char m_padding[0x68];
};

class BfmeB1164
{
private:
	unsigned char m_data[0x2C];
};

class W3DOverlordTankDrawModuleData : public Snapshot
{
public:
	virtual ~W3DOverlordTankDrawModuleData();

private:
	unsigned char m_gap04[4];
	ThingRef m_ref;
	unsigned int m_value0C;
	bool m_enabled;
	unsigned char m_gap11[3];
	UpgradeModuleDataSub m_upgradeData;
	BfmeB1164 m_dieMuxData;
};

// ??1W3DOverlordTankDrawModuleData@@UAE@XZ
W3DOverlordTankDrawModuleData::~W3DOverlordTankDrawModuleData()
{
}
