// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
protected:
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoInput : public Snapshot
{
public:
	DamageInfoInput();

private:
	unsigned char m_unreconstructed[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoOutput : public Snapshot
{
public:
	DamageInfoOutput()
	{
		m_actualDamageDealt = 0;
		m_actualDamageClipped = 0;
		m_noEffect = false;
	}

private:
	float m_actualDamageDealt;
	float m_actualDamageClipped;
	bool m_noEffect;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo : public Snapshot
{
public:
	DamageInfo();

private:
	DamageInfoInput in;
	DamageInfoOutput out;
};

DamageInfo::DamageInfo()
{
}
