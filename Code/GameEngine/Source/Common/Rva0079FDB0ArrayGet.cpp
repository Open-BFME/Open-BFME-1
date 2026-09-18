// cl: /O2

class Rva0079FDB0Array
{
public:
	void *getElement(int index);

private:
	char m_padding[4];
	void *m_data;
};

void *Rva0079FDB0Array::getElement(int index)
{
	return (char *)m_data + index * 4;
}
