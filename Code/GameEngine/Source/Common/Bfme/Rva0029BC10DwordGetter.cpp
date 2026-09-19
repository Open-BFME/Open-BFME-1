// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

// Retail RVA 0x0029BC10 reads one dword at this plus 0x20.
// The carved boundary proves no semantic owner.
class Rva0029BC10DwordGetter
{
public:
	int get() const;

private:
	char m_padding[0x20];
	int m_value;
};

int Rva0029BC10DwordGetter::get() const
{
	return m_value;
}
