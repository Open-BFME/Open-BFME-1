// Report whether a 32-bit member actually changes.
class Gen_008F7BA0
{
public:
	bool bfmeSetIfChanged(int value);

private:
	int m_reserved[25];
	int m_value;
};

bool Gen_008F7BA0::bfmeSetIfChanged(int value)
{
	if (value != m_value)
	{
		m_value = value;
		return true;
	}
	return false;
}
