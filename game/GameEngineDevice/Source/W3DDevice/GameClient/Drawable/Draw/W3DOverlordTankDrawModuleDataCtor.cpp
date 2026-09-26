// cl: /DNDEBUG /MD /EHsc
// Retail 0x002D3640. Byte-true W3DModuleFactory addModule names
// ??0W3DOverlordTankDrawModuleData@@QAE@XZ, and this body stores vtable
// 0x010CBED8, which the matched destructor at 0x002D36B0 also installs.

class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class ThingRef
{
public:
	ThingRef() : m_ptr(0) {}
	__declspec(nothrow) ~ThingRef();

private:
	void *m_ptr;
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub() throw();
	~UpgradeModuleDataSub();

private:
	unsigned char m_data[0x68];
};

class Rva002551A0DieMuxData
{
public:
	Rva002551A0DieMuxData();
	~Rva002551A0DieMuxData();

private:
	unsigned char m_data[0x2c];
};

class W3DOverlordTankDrawModuleData : public Snapshot
{
public:
	W3DOverlordTankDrawModuleData();
	virtual ~W3DOverlordTankDrawModuleData();

private:
	unsigned char m_gap04[4];
	ThingRef m_ref;
	unsigned int m_value0C;
	bool m_enabled;
	unsigned char m_gap11[3];
	UpgradeModuleDataSub m_upgradeData;
	Rva002551A0DieMuxData m_dieMuxData;
};

W3DOverlordTankDrawModuleData::W3DOverlordTankDrawModuleData()
	: m_value0C(0),
	  m_enabled(true)
{
}
