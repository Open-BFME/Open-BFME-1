// One more: a reset with a pair of scales, a fifth, an angle and four more
// scales at the end.

class Gen_0045C1D0
{
public:
	void bfmeReset(void);
private:
	unsigned char m_bfmeGap00[12];			// +0x00
	int m_bfme0c;						// +0x0c
	int m_bfme10;						// +0x10
	unsigned char m_bfmeGap14[12];			// +0x14
	int m_bfme20;						// +0x20
	int m_bfme24;						// +0x24
	int m_bfme28;						// +0x28
	unsigned char m_bfmeGap2c[8];			// +0x2c
	float m_bfme34;						// +0x34
	float m_bfme38;						// +0x38
	float m_bfme3c;						// +0x3c
	unsigned char m_bfmeGap40[8];			// +0x40
	int m_bfme48;						// +0x48
	int m_bfme4c;						// +0x4c
	unsigned char m_bfmeGap50[8];			// +0x50
	int m_bfme58;						// +0x58
	int m_bfme5c;						// +0x5c
	int m_bfme60;						// +0x60
	int m_bfme64;						// +0x64
	int m_bfme68;						// +0x68
	float m_bfme6c;						// +0x6c
	int m_bfme70;						// +0x70
	unsigned char m_bfme74;				// +0x74
	unsigned char m_bfme75;				// +0x75
	unsigned char m_bfme76;				// +0x76
	unsigned char m_bfmeGap77[1];			// +0x77
	int m_bfme78;						// +0x78
	int m_bfme7c;						// +0x7c
	unsigned char m_bfmeGap80[4];			// +0x80
	unsigned char m_bfme84;				// +0x84
	unsigned char m_bfmeGap85[3];			// +0x85
	int m_bfme88;						// +0x88
	int m_bfme8c;						// +0x8c
	int m_bfme90;						// +0x90
	int m_bfme94;						// +0x94
	int m_bfme98;						// +0x98
	float m_bfme9c;						// +0x9c
	float m_bfmea0;						// +0xa0
	float m_bfmea4;						// +0xa4
	float m_bfmea8;						// +0xa8
	int m_bfmeac;						// +0xac
	int m_bfmeb0;						// +0xb0
};

void Gen_0045C1D0::bfmeReset(void)
{
	m_bfme20 = 0;
	m_bfme24 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme28 = 0;
	m_bfme58 = 0;
	m_bfme5c = 0;
	m_bfme34 = 1.0f;
	m_bfme38 = 0.2f;
	m_bfme3c = 1.0f;
	m_bfme75 = 0;
	m_bfme48 = 0;
	m_bfme4c = 0;
	m_bfme60 = 0;
	m_bfme64 = 0;
	m_bfme68 = 0;
	m_bfme6c = 0.87266463f;
	m_bfme70 = 0;
	m_bfme74 = 0;
	m_bfme76 = 0;
	m_bfme78 = 0;
	m_bfme7c = 0;
	m_bfme84 = 0;
	m_bfme88 = 0;
	m_bfme8c = 0;
	m_bfme90 = 0;
	m_bfme94 = 0;
	m_bfme98 = 0;
	m_bfme9c = 1.0f;
	m_bfmea0 = 1.0f;
	m_bfmea4 = 1.0f;
	m_bfmea8 = 1.0f;
	m_bfmeac = 0;
	m_bfmeb0 = 0;
}
