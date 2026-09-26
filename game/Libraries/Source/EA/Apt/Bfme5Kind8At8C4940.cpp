// First of five adjacent Apt value-kind predicates separated by INT3.
class Gen_008C4940
{
public:
	bool bfmeIsKind8(void) const;

private:
	int m_reserved;
	unsigned m_flags;
};

bool Gen_008C4940::bfmeIsKind8(void) const
{
	return (m_flags & 0x3f) == 8 && !((unsigned char)~(unsigned char)(m_flags >> 15) & 1);
}
