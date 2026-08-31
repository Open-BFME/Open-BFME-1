// ??0W3DOverlordTankDrawModuleData@@QAE@XZ
// partial score=0.93 date=2026-08-31
// cl: /DNDEBUG /MD /EHsc
// Focused clean-C++ reconstruction of the retail BFME module-data layout.

class OTD_BaseModuleData
{
public:
	OTD_BaseModuleData();
	~OTD_BaseModuleData();

private:
	unsigned char m_data[0x68];
};

class OTD_CleanupBase
{
public:
	OTD_CleanupBase() {}
	~OTD_CleanupBase();
};

class OTD_InnerData
{
public:
	OTD_InnerData() : m_unknown00(0), m_enabled(true) {}
	~OTD_InnerData();

private:
	unsigned int m_unknown00;
	bool m_enabled;
	unsigned char m_pad05[3];
	OTD_BaseModuleData m_baseData;
};

class OTD_DieMuxData
{
public:
	OTD_DieMuxData();
	~OTD_DieMuxData();
};

class W3DOverlordTankDrawModuleData : public OTD_CleanupBase
{
public:
	W3DOverlordTankDrawModuleData();
	virtual void moduleDataAnchor();

private:
	unsigned int m_unknown04;
	unsigned int m_unknown08;
	OTD_InnerData m_innerData;
	OTD_DieMuxData m_dieMuxData;
};

W3DOverlordTankDrawModuleData::W3DOverlordTankDrawModuleData()
	: m_unknown08(0)
{
}
