// cl: /DNDEBUG /MD /EHsc /O2 /Ob0
// Retail 0x0078C7D0.  The surrounding type identity is not recoverable, but
// the member layout and ABI are complete: a four-byte header precedes a
// contiguous array of four-byte elements.

class Rva0078C7D0Array
{
public:
	int *at(int index);

private:
	int m_head;
	int *m_data;
};

int *Rva0078C7D0Array::at(int index)
{
	return m_data + index;
}
