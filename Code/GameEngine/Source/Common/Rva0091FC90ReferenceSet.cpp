// Open-BFME5: clean C++ conversion of the adjusted-reference replacement.

class Rva0091FC90Reference
{
public:
	virtual void dispose();
	int m_referenceCount;
};

class Rva0091FC90Owner
{
public:
	void setReference(Rva0091FC90Reference *reference);

private:
	char m_pad00[0x9C];
	Rva0091FC90Reference *m_reference;
};

void Rva0091FC90Owner::setReference(Rva0091FC90Reference *reference)
{
	if (reference != 0)
		++reference->m_referenceCount;

	Rva0091FC90Reference *oldReference = m_reference;
	if (oldReference != 0 && --oldReference->m_referenceCount == 0)
		oldReference->dispose();

	m_reference = reference;
}
