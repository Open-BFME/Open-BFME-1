// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva007A61E0Arr
{
public:
	unsigned int *at(unsigned int index);

	char m_pad[0x24];
	unsigned int m_items[6];
};

unsigned int *Rva007A61E0Arr::at(unsigned int index)
{
	if (index >= 6)
		index = 5;
	return m_items + index;
}
