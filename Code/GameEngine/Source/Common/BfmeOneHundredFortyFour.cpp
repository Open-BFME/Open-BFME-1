// Stepping a walker one place on. Most steps only move the mark; when the mark
// reaches the end of a block the walker takes the next block and starts again
// at its front.

class BfmeWalkerXP
{
public:
	void bfmeNextXP(void);

private:
	unsigned char *m_bfmeAt;		// 0x0
	unsigned char *m_bfmeFront;		// 0x4
	unsigned char *m_bfmeBack;		// 0x8
	unsigned char **m_bfmeBlock;		// 0xc
};

void BfmeWalkerXP::bfmeNextXP(void)
{
	m_bfmeAt += 0x1F0;

	if (m_bfmeAt == m_bfmeBack)
	{
		++m_bfmeBlock;
		m_bfmeFront = *m_bfmeBlock;
		m_bfmeBack = m_bfmeFront + 0x1F0;
		m_bfmeAt = m_bfmeFront;
	}
}
