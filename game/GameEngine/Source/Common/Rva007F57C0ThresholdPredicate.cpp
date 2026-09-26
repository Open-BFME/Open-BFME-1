// Address-derived reconstruction of the 22-byte threshold predicate at 0x007F57C0.

class Rva007F57C0ThresholdPredicate
{
public:
	int isReady() const;

private:
	char m_pad00[ 0x30 ];
	int m_count;
	char m_enabled;
};

int Rva007F57C0ThresholdPredicate::isReady() const
{
	if ( m_enabled && m_count >= 5 ) {
		return 1;
	}

	return 0;
}
