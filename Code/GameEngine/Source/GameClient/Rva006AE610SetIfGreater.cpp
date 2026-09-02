// cl: /DNDEBUG /MD
//
// Retail 0x006AE610: thiscall with three stack arguments.  If the incoming
// value is greater than the dword at +0xAC4[index], call helper(index, extra)
// and store the value.

class Rva006AE610
{
public:
	void setIfGreater(int index, int value, void *extra);

private:
	void helper(int index, void *extra);

	char m_lead[0xAC4];
	int m_array[1];
};

void Rva006AE610::setIfGreater(int index, int value, void *extra)
{
	if (value > m_array[index])
	{
		helper(index, extra);
		m_array[index] = value;
	}
}
