// cl: /Od
// Retail at 0x0082BC30 is an empty void function: push ebp, mov ebp,esp,
// pop ebp, ret.  The owning identity was not recovered.
void Rva0082BC30()
{
}

void rva0082BC40Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

class Rva0082BFD0Slot
{
public:
	Rva0082BFD0Slot *assignFrom(const int *src);

private:
	int m_value;
};

Rva0082BFD0Slot *Rva0082BFD0Slot::assignFrom(const int *src)
{
	int tmp = *src;
	m_value = tmp;
	return this;
}

int g_rva0082B120;

int rva0082B120Set(int value)
{
	int old = g_rva0082B120;
	g_rva0082B120 = value;
	return old;
}

int *rva0082BBC0Find(int *node, int value)
{
	while (node != 0 && *node != value)
		node = (int *)*node;
	return node;
}

int rva0082BAF0Count(int *node)
{
	int count = 0;
	for (; node != 0; node = (int *)*node)
		count++;
	return count;
}
