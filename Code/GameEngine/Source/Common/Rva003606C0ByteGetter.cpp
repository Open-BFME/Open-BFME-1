// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva003606C0
{
public:
	bool get() const;

private:
	char m_padding00[0x4c];
	bool m_value;
};

bool Rva003606C0::get() const
{
	return m_value;
}
