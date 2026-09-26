// cl: /O2 /Ob0

class Rva000C8E10
{
	int m_value;

public:
	int get() const;
};

int Rva000C8E10::get() const
{
	return m_value;
}

// The carved boundary at 0x000C8E00 contains only a return.
void Rva000C8E00Noop()
{
}
