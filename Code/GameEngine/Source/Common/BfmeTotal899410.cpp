// cl: /O2
// A total built from a sub-object's own accessor plus the low byte of a later
// field. The sub-object is a member, so its address is what reaches ecx.

class Rva0089CC10Object
{
public:
	int get() const;
};

class BfmeThing899410
{
public:
	int bfmeTotal899410() const;

private:
	int m_zero;
	int m_four;
	Rva0089CC10Object m_source;
	char m_pad[0x10];
	int m_extra;
};

int BfmeThing899410::bfmeTotal899410() const
{
	return m_source.get() + (m_extra & 0xff);
}
