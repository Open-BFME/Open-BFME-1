// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GenBeta::h00008ACB, retail 0x007C1120, 25 bytes.
//
// Delete everything on the list at this+0x08 until it is empty. The head is
// re-read after every delete, which is what makes this a while loop rather than
// a walk: each destructor unlinks its own node.

class GenBetaNode
{
public:
	virtual ~GenBetaNode();
};

class GenBeta
{
public:
	void h00008ACB(void);

private:
	unsigned char m_unmodelled_000[8];
	GenBetaNode *m_head;					// this+0x08
};

void GenBeta::h00008ACB(void)
{
	while (m_head)
	{
		delete m_head;
	}
}
