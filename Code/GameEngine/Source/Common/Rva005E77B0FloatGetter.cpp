// cl: /DNDEBUG /MD /EHsc

class Rva005E77B0FloatField
{
public:
	float get() const;

	char m_beforeValue[0x1c];
	float m_value;
};

float Rva005E77B0FloatField::get() const
{
	return m_value;
}
