// Return whether the recorded ping success ratio reaches the requested
// threshold.  The retail implementation intentionally uses x87 status-word
// testing, including the true result for a nonpositive sent count.

typedef float Real;

class BFMEDisconnectManager
{
public:
	bool hasPingSuccessRatioAtLeast(Real ratio);

private:
	char m_bfmeHead[0x260];
	int m_pingsSent;					// +0x260
	int m_pingsReceived;					// +0x264
};

// ?hasPingSuccessRatioAtLeast@BFMEDisconnectManager@@QAE_NM@Z
bool BFMEDisconnectManager::hasPingSuccessRatioAtLeast(Real ratio)
{
	if (m_pingsSent > 0 &&
		(Real)m_pingsReceived / (Real)m_pingsSent < ratio)
		return false;

	return true;
}
