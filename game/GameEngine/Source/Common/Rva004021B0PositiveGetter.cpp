// cl: /O2 /Ob0

class Rva004021B0PositiveGetter
{
public:
	bool get() const;

	int m_value;
};

bool Rva004021B0PositiveGetter::get() const
{
	return m_value > 0;
}
