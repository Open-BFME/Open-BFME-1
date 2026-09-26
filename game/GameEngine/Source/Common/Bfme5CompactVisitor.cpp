// Compacts the owner's pointer vector, then presents each surviving entry to
// the supplied visitor.  The vector layout is shared with the exact compact
// body at 0x0018BC70.

class BfmeItemBF;

class BfmeVisitorBF
{
public:
	void bfmeVisit(BfmeItemBF *item);
};

class BfmeVecAK
{
public:
	BfmeItemBF **m_start;
	BfmeItemBF **m_finish;
	BfmeItemBF **m_end;
};

class Gen_0018BC70
{
public:
	BfmeVecAK *bfmeCompact(bool restart);
	void bfmeVisitAll(BfmeVisitorBF *visitor);

private:
	int m_head[4];
	BfmeVecAK m_vector;
};

// ?bfmeVisitAll@Gen_0018BC70@@QAEXPAVBfmeVisitorBF@@@Z
void Gen_0018BC70::bfmeVisitAll(BfmeVisitorBF *visitor)
{
	if (visitor)
	{
		bfmeCompact(true);

		BfmeItemBF **it = m_vector.m_start;
		while (it != m_vector.m_finish)
		{
			visitor->bfmeVisit(*it);
			++it;
		}
	}
}
