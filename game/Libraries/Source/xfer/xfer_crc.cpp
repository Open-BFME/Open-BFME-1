// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the byte-block state accumulator at retail RVA 0x009D6330.

// Retail 0x009D6E50 is the block writer matched as XferSave::XferEnum in
// xfer_save.cpp, and the caller reaches it as a direct call on `this` (the
// retail body is `mov ecx, esi; call 0x009D6E50`), so the call is qualified --
// which keeps it non-virtual and leaves the accumulator at +0x44. XferSave's
// real declaration is not in a game header, so this is the same local view the
// sibling xfer_load.cpp gives Xfer.
class XferSave
{
public:
	virtual void XferEnum(void *context, const void *bytes, unsigned int count);
};

class XferMD5CRC
{
public:
	void XferImpl(void *context, const void *bytes, unsigned int count);

private:
	unsigned char m_pad[0x44];
	unsigned int m_state;
};

void XferMD5CRC::XferImpl(void *context, const void *rawBytes, unsigned int count)
{
	if (rawBytes == 0 && count != 0)
		return;

	reinterpret_cast< XferSave * >( this )->XferSave::XferEnum(context, rawBytes, count);
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
