// An independent eight-byte setter after two INT3 alignment bytes.
class Gen_008D5670
{
public:
	void bfmeResetValue(void);

private:
	int m_unused[8];
	void *m_value;
};

void Gen_008D5670::bfmeResetValue(void)
{
	m_value = 0;
}
