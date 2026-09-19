// cl: /DNDEBUG /MD /EHsc

// Retail loads the first dword from ECX and returns it.
// The carved boundary proves the shape, but no evidence proves the owner.
class Rva00087950DwordGetter
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

unsigned int Rva00087950DwordGetter::get() const
{
	return m_value;
}
