// The carved body at 0x005DCB10 loads the first dword from this and returns it.
// No evidence proves a semantic owner, so the class name keeps the retail address.
class Rva005DCB10
{
public:
	int getFirstDword() const;

private:
	int m_firstDword;
};

int Rva005DCB10::getFirstDword() const
{
	return m_firstDword;
}
