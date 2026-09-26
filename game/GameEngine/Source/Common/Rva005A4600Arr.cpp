// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva005A4600Slot
{
	char m_body[0x54];
};

class Rva005A4600Arr
{
public:
	Rva005A4600Slot *slot();

private:
	char m_pad[0x48];
	Rva005A4600Slot m_items[1];
	char m_gap[0x4DA8 - 0x48 - 0x54];
	int m_index;
};

Rva005A4600Slot *Rva005A4600Arr::slot()
{
	return &m_items[m_index];
}
