// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva0068D3E0Slot
{
	char m_body[0x68];
};

class Rva0068D3E0Arr
{
public:
	Rva0068D3E0Slot *at(int index);

private:
	char m_pad[0x58];
	Rva0068D3E0Slot m_items[8];
};

Rva0068D3E0Slot *Rva0068D3E0Arr::at(int index)
{
	if (index < 0 || index >= 8)
		return 0;
	return &m_items[index];
}
