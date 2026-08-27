// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the byte-block state accumulator at retail RVA 0x009D6330.

class Gen009D6330
{
public:
	void bfmeBaseUpdate(void *context, const void *bytes, unsigned int count);
	void bfmeUpdate(void *context, const void *bytes, unsigned int count);

private:
	unsigned char m_pad[0x44];
	unsigned int m_state;
};

void Gen009D6330::bfmeUpdate(void *context, const void *rawBytes, unsigned int count)
{
	if (rawBytes == 0 && count != 0)
		return;

	bfmeBaseUpdate(context, rawBytes, count);
	const unsigned char *bytes = static_cast<const unsigned char *>(rawBytes);
	while (count >= 4)
	{
		m_state = m_state * 2 + (m_state >> 31) + *reinterpret_cast<const unsigned int *>(bytes);
		bytes += 4;
		count -= 4;
	}
	while (count != 0)
	{
		m_state = m_state * 2 + (m_state >> 31) + *bytes;
		++bytes;
		--count;
	}
}
