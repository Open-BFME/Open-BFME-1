// cl: /O2 /Ob1 /DNDEBUG /MD

class BfmeBlockVKQ
{
public:
	char bfmeAnyVKQ(const BfmeBlockVKQ &other);

	int m_bfmeArr[10];
};

char BfmeBlockVKQ::bfmeAnyVKQ(const BfmeBlockVKQ &other)
{
	BfmeBlockVKQ intersection = other;
	for (int i = 0; i < 10; ++i)
		intersection.m_bfmeArr[i] &= m_bfmeArr[i];

	for (unsigned int i = 0; i < 10; ++i)
	{
		if (intersection.m_bfmeArr[i])
			return true;
	}
	return false;
}
