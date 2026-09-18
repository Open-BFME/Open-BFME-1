// cl: /DNDEBUG /MD /EHsc

struct Rva001ADD30Owner
{
	char m_padding[0x34];
	int m_value;

	int getField() const;
};

int Rva001ADD30Owner::getField() const
{
	return m_value;
}
