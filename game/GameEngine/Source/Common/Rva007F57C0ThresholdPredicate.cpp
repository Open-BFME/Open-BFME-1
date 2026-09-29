// Address-derived reconstruction of the 22-byte threshold predicate at 0x007F57C0.
// The slot before it (0x007F57A0) is the same test against a threshold of 3.

class Rva007F57C0ThresholdPredicate
{
public:
	int isReadyAtThree() const;
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

int Rva007F57C0ThresholdPredicate::isReadyAtThree() const
{
	if ( m_enabled && m_count >= 3 ) {
		return 1;
	}

	return 0;
}
