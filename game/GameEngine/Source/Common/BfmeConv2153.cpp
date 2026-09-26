// The constructor at retail 0x0060E8A0 builds a 0x188-byte cloud/sky settings
// record.  Its C++ EH unwind map has twenty-two states: nineteen retail
// AsciiString members and three ThingRef members, all default constructed in
// declaration order, followed by one more string built from "bordercloud"
// after which nothing else can throw.

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) { }
	BFMERetailAsciiString(const char *s);                      ///< pinned 0x00888BC0
	~BFMERetailAsciiString();                                  ///< pinned 0x0000D828

	void *m_data;
};

class BfmeThingRefEQ
{
public:
	BfmeThingRefEQ() : m_data(0) { }
	~BfmeThingRefEQ();                                         ///< pinned 0x000362FF

	void *m_data;
};

class BfmeCloudBlockEQ
{
public:
	BfmeCloudBlockEQ()
	{
		m_at0C = 0;
		m_at10 = 0;
	}

	unsigned int m_at00;
	unsigned int m_at04;
	unsigned int m_at08;
	unsigned int m_at0C;
	unsigned int m_at10;
};

class BfmeFadeEQ
{
public:
	BfmeFadeEQ()
	{
		m_at00 = 0;
		m_at18 = 0;
		m_at04 = 0x3F400000;
		m_at08 = 0x3F400000;
	}

	unsigned char m_at00;
	unsigned int m_at04;
	unsigned int m_at08;
	unsigned int m_at0C;
	unsigned int m_at10;
	unsigned int m_at14;
	unsigned char m_at18;
};

class BfmeTripleEQ
{
public:
	BfmeTripleEQ()
	{
		m_at00 = 0;
		m_at04 = 0;
		m_at08 = 0;
	}

	unsigned int m_at00;
	unsigned int m_at04;
	unsigned int m_at08;
};

class BfmeSpanEQ
{
public:
	BfmeSpanEQ()
	{
		m_at00 = 10;
		m_at0C = 10;
		m_at10 = 10;
		m_at04 = 11;
		m_at08 = 25;
	}

	unsigned int m_at00;
	unsigned int m_at04;
	unsigned int m_at08;
	unsigned int m_at0C;
	unsigned int m_at10;
};

class BfmeCloudSetEQ
{
public:
	BfmeCloudSetEQ();

	BFMERetailAsciiString m_s000;
	unsigned int m_at004;
	unsigned int m_at008;
	unsigned int m_at00C;
	unsigned int m_at010;
	unsigned int m_at014;
	unsigned int m_at018;
	unsigned int m_at01C;
	BFMERetailAsciiString m_s020;
	BfmeCloudBlockEQ m_b024;
	BfmeCloudBlockEQ m_b038;
	BfmeCloudBlockEQ m_b04C;
	unsigned int m_at060;
	unsigned int m_at064;
	unsigned int m_at068;
	BFMERetailAsciiString m_s06C;
	BFMERetailAsciiString m_s070;
	BFMERetailAsciiString m_s074;
	BFMERetailAsciiString m_s078;
	BFMERetailAsciiString m_s07C;
	BFMERetailAsciiString m_s080;
	BFMERetailAsciiString m_s084;
	BFMERetailAsciiString m_s088;
	BFMERetailAsciiString m_s08C;
	BFMERetailAsciiString m_s090;
	BFMERetailAsciiString m_s094;
	BFMERetailAsciiString m_s098;
	unsigned int m_at09C;
	unsigned int m_at0A0;
	unsigned int m_at0A4;
	unsigned int m_at0A8;
	unsigned int m_at0AC;
	unsigned int m_at0B0;
	BFMERetailAsciiString m_s0B4;
	BFMERetailAsciiString m_s0B8;
	unsigned int m_at0BC;
	unsigned int m_at0C0;
	unsigned int m_at0C4;
	unsigned int m_at0C8;
	unsigned int m_at0CC;
	unsigned int m_at0D0;
	unsigned int m_at0D4;
	unsigned int m_at0D8;
	unsigned int m_at0DC;
	unsigned int m_at0E0;
	BfmeThingRefEQ m_r0E4;
	BfmeThingRefEQ m_r0E8;
	BfmeThingRefEQ m_r0EC;
	BFMERetailAsciiString m_s0F0;
	BFMERetailAsciiString m_s0F4;
	unsigned int m_at0F8;
	unsigned int m_at0FC;
	unsigned int m_at100;
	unsigned int m_at104;
	unsigned int m_at108;
	unsigned int m_at10C;
	unsigned int m_at110;
	unsigned int m_at114;
	BFMERetailAsciiString m_s118;
	BFMERetailAsciiString m_s11C;
	unsigned int m_at120;
	unsigned int m_at124;
	unsigned int m_at128;
	unsigned int m_at12C;
	unsigned int m_at130;
	unsigned int m_at134;
	unsigned int m_at138;
	unsigned int m_at13C;
	BfmeFadeEQ m_f140;
	BfmeTripleEQ m_t15C;
	BfmeSpanEQ m_p168;
	unsigned int m_at17C;
	unsigned int m_at180;
	unsigned int m_at184;
};

BfmeCloudSetEQ::BfmeCloudSetEQ()
	: m_at09C(0x3C23D70A),
	  m_at0A0(0x40400000),
	  m_at0A4(0),
	  m_at0A8(0x42C80000),
	  m_at0AC(0x42C80000),
	  m_at0B0(0x42C80000),
	  m_at0D4(0x3F800000),
	  m_at0D8(1),
	  m_at0DC(10),
	  m_at0E0(150),
	  m_at0F8(20),
	  m_at114(200),
	  m_s11C("bordercloud"),
	  m_at120(0),
	  m_at130(3),
	  m_at134(0x3F800000),
	  m_at138(0xBF800000),
	  m_at13C(0x40000000),
	  m_at17C(0),
	  m_at180(0),
	  m_at184(0)
{
	m_b024.m_at08 = 0;
	m_b024.m_at04 = 0;
	m_b024.m_at00 = 0;

	m_b038.m_at08 = 0;
	m_b038.m_at04 = 0;
	m_b038.m_at00 = 0;

	m_b04C.m_at08 = 0;
	m_b04C.m_at04 = 0;
	m_b04C.m_at00 = 0;

	m_at068 = 0;
	m_at064 = 0;
	m_at060 = 0;

	m_at0D0 = 0;
	m_at0CC = 0;
	m_at0C8 = 0;

	m_f140.m_at14 = 0;
	m_f140.m_at10 = 0;
	m_f140.m_at0C = 0;

	m_at014 = 0;
	m_at018 = 0;
	m_at01C = 0;

	m_at0BC = 0;
	m_at0C0 = 0;
	m_at0C4 = 0;

	m_at0FC = 0;
	m_at100 = 0;
	m_at104 = 0;
	m_at108 = 0;
	m_at10C = 0;
	m_at110 = 0;

	m_at124 = 0;
	m_at128 = 0;
	m_at12C = 0;
}
