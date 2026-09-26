// Kind predicate followed by an independent zeroing function in retail.
class Gen_008D5660
{
public:
	bool bfmeIsKind22(void) const;

private:
	int m_unused;
	unsigned m_flags;
};

bool Gen_008D5660::bfmeIsKind22(void) const
{
	return (m_flags & 0x3f) == 0x22;
}