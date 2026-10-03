// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: BroadcastStealthUpdate module-data constructor.
//
// The named friend_newModuleData factory at retail 0x0012A350 allocates 0x94
// bytes and calls this constructor.  Its field-parse method applies the shared
// upgrade table at +0x2C, identifying the 0x68-byte upgrade subobject reached
// through the same constructor used by the upgrade module-data family.
// Retail compiled this constructor without C++ unwind state; destruction stays
// in the separately matched destructor TU, so this local view models only the
// construction ABI.

// The +0x2C upgrade subobject's constructor is reached through retail's ILT
// thunk at 0x0000F0A6 (the ledger's ?j_0000f0a6@@YAXXZ, the shared upgrade
// module-data handle constructor), so the constructor here is inline and
// forwards to that thunk. The local view class carries a name of its own:
// `UpgradeModuleDataSub` is pinned to 0x0000F0A6, and an in-class body under
// that name would claim the address retail's `?j_` thunk already holds. The
// upgrade-family TUs keep their own view of the same 0x68-byte subobject.
extern void j_0000f0a6();

class BroadcastStealthMask
{
public:
	BroadcastStealthMask()
	{
		for ( int i = 0; i != 6; ++i )
			m_words[ i ] = 0;
	}

	void clear()
	{
		for ( int i = 0; i != 6; ++i )
			m_words[ i ] = 0;
	}

private:
	unsigned int m_words[ 6 ];
};

class BroadcastStealthPolicy
{
public:
	BroadcastStealthPolicy() : m_value( 0 ) {}

private:
	unsigned int m_value;
};

class BroadcastStealthUpgradeSub
{
public:
	BroadcastStealthUpgradeSub() { ((void (__fastcall *)(BroadcastStealthUpgradeSub *))j_0000f0a6)(this); }

private:
	unsigned char m_unmodelled[ 0x68 ];
};

class BroadcastStealthUpdateModuleDataBase
{
public:
	virtual ~BroadcastStealthUpdateModuleDataBase() {}

private:
	unsigned int m_unmodelled_04;
};

class BroadcastStealthUpdateModuleData
	: public BroadcastStealthUpdateModuleDataBase
{
public:
	BroadcastStealthUpdateModuleData();
	virtual ~BroadcastStealthUpdateModuleData();

private:
	BroadcastStealthMask m_kindOf;       // +0x08
	float m_broadcastRadius;              // +0x20
	unsigned int m_unmodelled_24;
	BroadcastStealthPolicy m_policy;      // +0x28
	BroadcastStealthUpgradeSub m_upgradeData;   // +0x2C
};

// ??0BroadcastStealthUpdateModuleData@@QAE@XZ
BroadcastStealthUpdateModuleData::BroadcastStealthUpdateModuleData()
{
	m_kindOf.clear();
	m_broadcastRadius = 100.0f;
	m_unmodelled_24 = 0;
}
