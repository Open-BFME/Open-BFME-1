// cl: /DNDEBUG /MD /EHsc

// The carved body at 0x00409510 only reads this-relative offset 0x04 and
// returns the dword. The caller and boundary prove the body, but they do not
// identify its owning class, so the class and method keep the address token.

class Rva00409510Owner
{
public:
	int getField04() const;

private:
	char m_padding00[4];
	int m_field04;
};

int Rva00409510Owner::getField04() const
{
	return m_field04;
}
