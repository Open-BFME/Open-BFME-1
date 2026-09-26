// The carved body at 0x00694C90 loads the first dword from this and returns it.
// No evidence proves a semantic owner, so the class name keeps the retail address.
class Rva00694C90
{
public:
	int getFirstDword() const;

private:
	int m_firstDword;
};

int Rva00694C90::getFirstDword() const
{
	return m_firstDword;
}
