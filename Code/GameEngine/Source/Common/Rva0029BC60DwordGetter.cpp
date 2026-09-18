// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

// The carved boundary at 0x0029BC60 reads one dword at this plus 0x30 and
// returns it. No caller or class table names the owner.
class Rva0029BC60DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0x30];
	unsigned int m_value;
};

unsigned int Rva0029BC60DwordGetter::get() const
{
	return m_value;
}
