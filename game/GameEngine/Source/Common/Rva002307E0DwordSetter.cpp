// Retail at 0x002307E0 copies one four-byte argument into this+0x100 and
// callee-cleans that argument. The owning type was not recovered.
class Rva002307E0
{
public:
	void apply(int value);
	char m_lead[0x100];
	unsigned int m_value;
};

void Rva002307E0::apply(int value)
{
	m_value = value;
}
