class Rva005862C0Member
{
public:
	Rva005862C0Member(const Rva005862C0Member &other);

private:
	int m_bfmeFields[3];
};

class Gen_00587050
{
public:
	Gen_00587050(const Gen_00587050 &other);

private:
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0C;
	Rva005862C0Member m_bfmeMember;
	int m_bfme1C;
	int m_bfme20;
	bool m_bfme24;
	int m_bfme28;
	int m_bfme2C;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
};

// ??0Gen_00587050@@QAE@ABV0@@Z
Gen_00587050::Gen_00587050(const Gen_00587050 &other) :
	m_bfme00(other.m_bfme00),
	m_bfme04(other.m_bfme04),
	m_bfme08(other.m_bfme08),
	m_bfme0C(other.m_bfme0C),
	m_bfmeMember(other.m_bfmeMember),
	m_bfme1C(other.m_bfme1C),
	m_bfme20(other.m_bfme20),
	m_bfme24(other.m_bfme24),
	m_bfme28(other.m_bfme28),
	m_bfme2C(other.m_bfme2C),
	m_bfme30(other.m_bfme30),
	m_bfme34(other.m_bfme34),
	m_bfme38(other.m_bfme38)
{
}
