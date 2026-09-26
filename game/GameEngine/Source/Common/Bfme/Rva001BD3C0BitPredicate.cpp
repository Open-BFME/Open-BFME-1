// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001BD3C0 (14 bytes).

class Rva001BD3C0
{
public:
	bool isSet() const;

private:
	unsigned char m_unmodelled_000[0x344];
	unsigned char m_flags;
};

bool Rva001BD3C0::isSet() const
{
	return (m_flags >> 1) & 1;
}
