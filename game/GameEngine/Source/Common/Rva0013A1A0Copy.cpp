// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva0013A1A0
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	Rva0036CA00Str m_10;
	int m_14;
	int m_18;
	Rva0036CA00Str m_1C;
	Rva0036CA00Str m_20;
	int m_24;
	Rva0036CA00Str m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	Rva0036CA00Str m_3C;
	int m_40;
	Rva0036CA00Str m_44;

public:
	void copyTo(Rva0013A1A0 &dest) const;
};

void Rva0013A1A0::copyTo(Rva0013A1A0 &dest) const
{
	dest.m_00 = m_00;
	dest.m_04 = m_04;
	dest.m_08 = m_08;
	dest.m_0C = m_0C;
	dest.m_10 = m_10;
	dest.m_14 = m_14;
	dest.m_18 = m_18;
	dest.m_1C = m_1C;
	dest.m_20 = m_20;
	dest.m_24 = m_24;
	dest.m_28 = m_28;
	dest.m_2C = m_2C;
	dest.m_30 = m_30;
	dest.m_34 = m_34;
	dest.m_38 = m_38;
	dest.m_3C = m_3C;
	dest.m_40 = m_40;
	dest.m_44 = m_44;
}
