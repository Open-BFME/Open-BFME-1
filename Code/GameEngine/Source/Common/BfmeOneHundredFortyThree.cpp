// Joining a link to the front of a chain: it takes the old front as its
// follower, has nothing before it, and tells the old front who came first. An
// empty chain also gains an end.

class BfmeLinkXN
{
public:
	void bfmeInsertXN(BfmeLinkXN **last, BfmeLinkXN **first);

private:
	unsigned char m_bfmeGap[0x88];		// 0x00
	BfmeLinkXN *m_bfmeBefore;		// 0x88
	BfmeLinkXN *m_bfmeAfter;		// 0x8c
};

void BfmeLinkXN::bfmeInsertXN(BfmeLinkXN **last, BfmeLinkXN **first)
{
	BfmeLinkXN *front = *first;

	m_bfmeAfter = front;
	m_bfmeBefore = 0;

	if (front != 0)
		front->m_bfmeBefore = this;

	if (*last == 0)
		*last = this;

	*first = this;
}
