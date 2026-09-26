// The constructor at 0x006DF550 and its adjacent float accessors establish
// this object's scalar layout.  Retail reads the field at this plus 0x04.

class Rva006DF550
{
public:
	float getField04() const;

private:
	char m_pad00[4];
	float m_field04;
};

float Rva006DF550::getField04() const
{
	return m_field04;
}
