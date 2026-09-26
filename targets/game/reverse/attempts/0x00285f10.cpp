// ??0BannerCarrierUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.45 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: de-lift attempt. BannerCarrierUpdate has no Zero Hour
// counterpart (BFME-original class); field layout recovered directly from
// retail bytes at 0x00285F10 (single vtable slot, no base-class call).
// NOT LANDED: see reverse/re_attempts.log for the residual.

class Thing;
class ModuleData;

class BannerCarrierMask
{
public:
	void clear()
	{
		for (int i = 0; i < 6; ++i)
			m_words[i] = 0;
	}

private:
	unsigned int m_words[6];
};

class BannerCarrierUpdate
{
public:
	BannerCarrierUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~BannerCarrierUpdate();

private:
	int m_data04;
	int m_data08;
	int m_data0C;
	int m_data10;
	int m_data14;
	int m_data18;
	int m_data1C;
	int m_data20;
	int m_data24;
	int m_data28;
	int m_data2C;
	int m_data30;
	int m_data34;
	int m_data38;
	int m_data3C;
	int m_data40;
	int m_data44;
	int m_data48;
	int m_data4C;
	int m_data50;
	BannerCarrierMask m_kindOf;
	BannerCarrierMask m_forbiddenKindOf;
	float m_data84;
	float m_data88;
	float m_data8C;
	bool m_data90;
	float m_data94;
	int m_data98;
	int m_data9C;
};

// ??0BannerCarrierUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
BannerCarrierUpdate::BannerCarrierUpdate(Thing *thing, const ModuleData *moduleData)
	: m_data08(0), m_data0C(0), m_data10(0), m_data14(0), m_data18(0), m_data1C(0),
	  m_data20(0), m_data24(0), m_data28(0), m_data2C(0), m_data30(0), m_data34(0),
	  m_data38(0), m_data3C(0), m_data40(0), m_data44(0), m_data48(0), m_data4C(0),
	  m_data50(0)
{
	m_kindOf.clear();
	m_forbiddenKindOf.clear();
	m_data84 = 1.0f;
	m_data88 = 1.0f;
	m_data8C = 1.0f;
	m_data90 = true;
	m_data94 = 1.0f;
	m_data98 = 1;
	m_data9C = 0;
}

BannerCarrierUpdate::~BannerCarrierUpdate()
{
}
