// cl: /DNDEBUG /MD /EHsc

class Rva001E0C60
{
public:
	bool isClear() const;

private:
	unsigned char m_padding[0x4F0];
	unsigned m_value;
};

bool Rva001E0C60::isClear() const
{
	return m_value == 0;
}
