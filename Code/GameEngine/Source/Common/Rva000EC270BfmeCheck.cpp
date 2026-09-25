// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

struct BfmeNodeEC
{
	unsigned char m_bfmeHeadEC[0x25c];
	void *m_bfme25CEC;
	void *m_bfme260EC;
};

class BfmeHostEC
{
public:
	int bfmeCheckEC(BfmeNodeEC *node);

	unsigned char m_bfmeHeadEC[0xc];
	BfmeNodeEC *m_bfme0CEC;
};

int BfmeHostEC::bfmeCheckEC(BfmeNodeEC *node)
{
	if (m_bfme0CEC == node || node->m_bfme25CEC != 0 || node->m_bfme260EC != 0)
		return 1;

	return 0;
}


struct Rva000EC220List
{
	BfmeNodeEC *m_head;
};

class Rva000EC220Node : public BfmeNodeEC
{
public:
	int isInList(const Rva000EC220List *list) const;
};

int Rva000EC220Node::isInList(const Rva000EC220List *list) const
{
	if (list->m_head == this || m_bfme25CEC != 0 || m_bfme260EC != 0)
		return 1;

	return 0;
}
