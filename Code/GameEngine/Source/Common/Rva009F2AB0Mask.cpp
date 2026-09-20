// Retail walks a linked list, ANDs each node's slot-2 virtual result, and
// returns all bits set when the receiver is null. The binary proves the
// address and operation, but it does not prove the owning class or method
// name.

class Rva009F2AB0Mask
{
public:
	virtual int unused0(void) = 0;
	virtual int unused1(void) = 0;
	virtual int value(void) = 0;

	Rva009F2AB0Mask *m_next;

	int getMask(void);
};

int Rva009F2AB0Mask::getMask(void)
{
	int result = -1;
	Rva009F2AB0Mask *node = this;
	if (node)
	{
		do
		{
			result &= node->value();
			node = node->m_next;
		}
		while (node);
	}

	return result;
}
