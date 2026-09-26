
class Rva00322040
{
public:
	bool isPositive() const;

	char m_pad0[ 0x40 ];
	int  m_val40;
};

bool Rva00322040::isPositive() const
{
	return m_val40 > 0;
}
