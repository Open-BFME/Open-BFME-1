// Open-BFME5: clean C++ conversion of the override-resolved string accessor.

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	char m_pad00[4];
	const Overridable *m_nextOverride;
	char m_pad08[4];
	AsciiString m_value;
};

class Rva001B6070Owner
{
public:
	AsciiString getResolvedValue() const;

private:
	char m_pad00[4];
	const Overridable *m_value;
};

AsciiString Rva001B6070Owner::getResolvedValue() const
{
	const Overridable * volatile unused = 0;
	const Overridable *value = m_value;
	if (value != 0 && value->m_nextOverride != 0)
		value = value->m_nextOverride->getFinalOverride();

	return value->m_value;
}
