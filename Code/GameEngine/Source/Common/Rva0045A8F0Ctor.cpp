// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot();
	virtual void handle();

private:
	int m_04;
};

class Rva0045A8F0 : public Snapshot
{
	int m_08;
	int m_0C;
	float m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	char m_3C;
	char m_3D;
	int m_40;
	char m_44;
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
	int m_58;
	int m_5C;
	int m_60;
	int m_64;

public:
	Rva0045A8F0();
};

Rva0045A8F0::Rva0045A8F0()
{
	m_08 = 0;
	m_0C = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
	m_3D = 0;
	m_40 = 0;
	m_44 = 0;
	m_48 = 0;
	m_4C = 0;
	m_50 = 0;
	m_54 = 0;
	m_58 = 0;
	m_5C = 0;
	m_60 = 0;
	m_64 = 0;
	m_10 = 1.0f;
	m_3C = 1;
}
