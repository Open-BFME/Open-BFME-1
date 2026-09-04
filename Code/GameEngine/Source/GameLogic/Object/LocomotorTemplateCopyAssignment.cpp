// cl: /O2 /Ob1 /DNDEBUG /MD
// BFME retail LocomotorTemplate::operator= (RVA 0x001B4250).

class ScienceInfoBase
{
public:
	ScienceInfoBase &operator=(const ScienceInfoBase &other);

private:
	char m_head[0x0c];
};

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	void *m_data;
};

class LocomotorTemplate : public ScienceInfoBase
{
public:
	LocomotorTemplate &operator=(const LocomotorTemplate &other);

private:
	AsciiString m_name;
	unsigned int m_d10;
	unsigned int m_d14;
	unsigned char m_c18;
	unsigned int m_d1c;
	unsigned int m_d20;
	unsigned int m_d24;
	unsigned int m_d28;
	unsigned int m_d2c;
	unsigned int m_d30;
	unsigned int m_d34;
	unsigned int m_d38;
	unsigned int m_d3c;
	unsigned int m_d40;
	unsigned int m_d44;
	unsigned int m_d48;
	unsigned int m_d4c;
	unsigned int m_d50;
	unsigned int m_d54;
	unsigned int m_d58;
	unsigned int m_d5c;
	unsigned int m_d60;
	unsigned int m_d64;
	unsigned int m_d68;
	unsigned int m_d6c;
	unsigned int m_d70;
	unsigned int m_d74;
	unsigned int m_d78;
	unsigned int m_d7c;
	unsigned int m_d80;
	unsigned int m_d84;
	unsigned int m_d88;
	unsigned int m_d8c;
	unsigned int m_d90;
	unsigned int m_d94;
	unsigned int m_d98;
	unsigned int m_d9c;
	unsigned int m_da0;
	unsigned int m_da4;
	unsigned int m_da8;
	unsigned int m_dac;
	unsigned int m_db0;
	unsigned int m_db4;
	unsigned int m_db8;
	unsigned int m_dbc;
	unsigned int m_dc0;
	unsigned char m_c4;
	unsigned int m_dc8;
	unsigned char m_cc;
	unsigned char m_cd;
	unsigned char m_ce;
	unsigned char m_cf;
	unsigned char m_d0;
	unsigned int m_dc4;
	unsigned char m_d8;
	unsigned int m_ddc;
	unsigned int m_de0;
	unsigned int m_de4;
	unsigned char m_de8;
	unsigned char m_de9;
	unsigned int m_dec;
	unsigned int m_df0;
	unsigned int m_df4;
	unsigned int m_df8;
	unsigned char m_dfc;
	unsigned char m_dfd;
	unsigned char m_dfe;
	unsigned int m_e00;
	unsigned int m_e04;
	unsigned int m_e08;
	unsigned int m_e0c;
	unsigned int m_e10;
	unsigned int m_e14;
	unsigned int m_e18;
	unsigned int m_e1c;
	unsigned int m_e20;
	unsigned int m_e24;
	unsigned int m_e28;
	unsigned int m_e2c;
	unsigned char m_e30;
	unsigned int m_e34;
	unsigned int m_e38;
	unsigned int m_e3c;
};

LocomotorTemplate &LocomotorTemplate::operator=(const LocomotorTemplate &other)
{
	ScienceInfoBase::operator=(other);
	m_name = other.m_name;
	m_d10 = other.m_d10;
	m_d14 = other.m_d14;
	m_c18 = other.m_c18;
	m_d1c = other.m_d1c;
	m_d20 = other.m_d20;
	m_d24 = other.m_d24;
	m_d28 = other.m_d28;
	m_d2c = other.m_d2c;
	m_d30 = other.m_d30;
	m_d34 = other.m_d34;
	m_d38 = other.m_d38;
	m_d3c = other.m_d3c;
	m_d40 = other.m_d40;
	m_d44 = other.m_d44;
	m_d48 = other.m_d48;
	m_d4c = other.m_d4c;
	m_d50 = other.m_d50;
	m_d54 = other.m_d54;
	m_d58 = other.m_d58;
	m_d5c = other.m_d5c;
	m_d60 = other.m_d60;
	m_d64 = other.m_d64;
	m_d68 = other.m_d68;
	m_d6c = other.m_d6c;
	m_d70 = other.m_d70;
	m_d74 = other.m_d74;
	m_d78 = other.m_d78;
	m_d7c = other.m_d7c;
	m_d80 = other.m_d80;
	m_d84 = other.m_d84;
	m_d88 = other.m_d88;
	m_d8c = other.m_d8c;
	m_d90 = other.m_d90;
	m_d94 = other.m_d94;
	m_d98 = other.m_d98;
	m_d9c = other.m_d9c;
	m_da0 = other.m_da0;
	m_da4 = other.m_da4;
	m_da8 = other.m_da8;
	m_dac = other.m_dac;
	m_db0 = other.m_db0;
	m_db4 = other.m_db4;
	m_db8 = other.m_db8;
	m_dbc = other.m_dbc;
	m_dc0 = other.m_dc0;
	m_c4 = other.m_c4;
	m_dc8 = other.m_dc8;
	m_cc = other.m_cc;
	m_cd = other.m_cd;
	m_ce = other.m_ce;
	m_cf = other.m_cf;
	m_d0 = other.m_d0;
	m_dc4 = other.m_dc4;
	m_d8 = other.m_d8;
	m_ddc = other.m_ddc;
	m_de0 = other.m_de0;
	m_de4 = other.m_de4;
	m_de8 = other.m_de8;
	m_de9 = other.m_de9;
	m_dec = other.m_dec;
	m_df0 = other.m_df0;
	m_df4 = other.m_df4;
	m_df8 = other.m_df8;
	m_dfc = other.m_dfc;
	m_dfd = other.m_dfd;
	m_dfe = other.m_dfe;
	m_e00 = other.m_e00;
	m_e04 = other.m_e04;
	m_e08 = other.m_e08;
	m_e0c = other.m_e0c;
	m_e10 = other.m_e10;
	m_e14 = other.m_e14;
	m_e18 = other.m_e18;
	m_e1c = other.m_e1c;
	m_e20 = other.m_e20;
	m_e24 = other.m_e24;
	m_e28 = other.m_e28;
	m_e2c = other.m_e2c;
	m_e30 = other.m_e30;
	m_e34 = other.m_e34;
	m_e38 = other.m_e38;
	m_e3c = other.m_e3c;
	return *this;
}
