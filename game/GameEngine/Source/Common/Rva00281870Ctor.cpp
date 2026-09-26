// cl: /O2 /Ob0

class RespawnPolicyMember
{
public:
	RespawnPolicyMember();

private:
	int m_00;
};

class Rva00281870 : public RespawnPolicyMember
{
	int m_04;
	float m_08;

public:
	Rva00281870();
};

Rva00281870::Rva00281870()
{
	m_04 = 0;
	m_08 = 1.0f;
}
