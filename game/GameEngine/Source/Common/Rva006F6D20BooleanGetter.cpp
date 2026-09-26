// cl: /O2 /Ob0

class Rva006F6D20BooleanGetter
{
public:
	bool get() const;

	char m_padding[0x90];
	int m_value;
};

bool Rva006F6D20BooleanGetter::get() const
{
	return m_value != 0;
}
