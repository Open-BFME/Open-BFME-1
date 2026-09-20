// Retail 0x00191B90 reads the first dword of its receiver and returns it.
// The carved boundary proves the getter, but no identity evidence names its
// owning type.
// ?get@Rva00191B90DwordGetter@@QBEIXZ present-unmatched
class Rva00191B90DwordGetter
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

unsigned int Rva00191B90DwordGetter::get() const
{
	return m_value;
}
