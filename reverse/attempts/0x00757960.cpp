// ??0SpectreGunshipUpdateModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct SpectreGunshipDefaults
{
	int m_slot08;
	int m_slot0C;
	void *m_slot10;
	float m_slot14;
	unsigned int m_slot18;
	bool m_slot1C;
	unsigned char m_pad1D[3];
	unsigned int m_slot20;
	unsigned int m_slot24;
	unsigned int m_slot28;
	unsigned int m_slot2C;
	unsigned int m_slot30;
	unsigned int m_slot34;
	unsigned int m_slot38;
	unsigned int m_slot3C;
	unsigned int m_slot40;
	float m_slot44;
	unsigned int m_slot48;
	float m_slot4C;
	float m_slot50;
	float m_slot54;
	unsigned int m_slot58;
	unsigned int m_slot5C;
	unsigned int m_slot60;
	unsigned int m_slot64;
	int m_slot68;
	int m_slot6C;
	unsigned int m_slot70;

	__forceinline SpectreGunshipDefaults()
	{
		m_slot08 = -1;
		m_slot0C = -1;
		m_slot2C = 0;
		m_slot30 = 0;
		m_slot34 = 0;
		m_slot68 = -1;
		m_slot6C = -1;
		m_slot58 = 0;
		m_slot70 = 0;
		_ReadWriteBarrier();
		m_slot4C = 1.0f;
		m_slot50 = 1.0f;
		m_slot54 = 1.0f;
		m_slot5C = 1;
		m_slot60 = 1;
		m_slot64 = 1;
		m_slot14 = 1.0f;
		m_slot44 = 1.0f;
		m_slot10 = 0;
		m_slot20 = 1;
		m_slot24 = 0;
		m_slot28 = 0;
		m_slot18 = 0;
		m_slot1C = false;
		m_slot38 = 1;
		m_slot3C = 0;
		m_slot40 = 0;
		m_slot48 = 0;
		_ReadWriteBarrier();
		m_slot58 = 0;
		m_slot70 = 0;
	}
};

class SpectreGunshipUpdateModuleData
{
public:
	SpectreGunshipUpdateModuleData();
	virtual ~SpectreGunshipUpdateModuleData();

private:
	unsigned int m_unmodelled_04;
	SpectreGunshipDefaults m_defaults;
};

// ??0SpectreGunshipUpdateModuleData@@QAE@XZ
SpectreGunshipUpdateModuleData::SpectreGunshipUpdateModuleData()
{
}
