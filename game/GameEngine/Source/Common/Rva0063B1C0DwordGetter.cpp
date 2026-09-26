// Retail 0x0063B1C0 returns the dword at this+0.  The sole known caller is an
// incremental-link thunk, so the owning type and field semantics remain unknown.
class Rva0063B1C0DwordGetter
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

unsigned int Rva0063B1C0DwordGetter::get() const
{
	return m_value;
}
