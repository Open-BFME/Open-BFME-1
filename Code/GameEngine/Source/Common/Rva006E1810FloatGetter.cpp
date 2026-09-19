// cl: /O2 /Ob0

class Rva006E17F0FloatField
{
	char m_padding[0x50];
	float m_value;

public:
	float get() const;
};

float Rva006E17F0FloatField::get() const
{
	return m_value;
}

class Rva006E1810FloatField
{
	char m_padding[0x70];
	float m_value;

public:
	float get() const;
};

float Rva006E1810FloatField::get() const
{
	return m_value;
}
