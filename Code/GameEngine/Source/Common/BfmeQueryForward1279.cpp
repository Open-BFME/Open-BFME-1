class BfmeQuery1279
{
public:
	void bfmeQuery1279(void *value, int zero, void **other, void **result);
};

struct BfmeInput1279
{
	void *m_value;
};

class BfmeWrapper1279
{
public:
	void bfmeProcess1279(void *value);
	void bfmeForward1279(BfmeInput1279 *input);

private:
	BfmeQuery1279 *m_query;
};

void BfmeWrapper1279::bfmeForward1279(BfmeInput1279 *input)
{
	void *other;
	m_query->bfmeQuery1279(input->m_value, 0, &other, (void **)&input);
	bfmeProcess1279(input);
}
