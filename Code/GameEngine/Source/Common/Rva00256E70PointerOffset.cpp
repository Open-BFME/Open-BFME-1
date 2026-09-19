// The carved body proves only a pointer load followed by an eight-byte offset.
// Keep the owner and accessor address-derived because no caller names them.

class Rva00256E70Owner
{
public:
	void *getOffset8() const;

private:
	void *m_pointer;
};

void *Rva00256E70Owner::getOffset8() const
{
	return (char *)m_pointer + 8;
}
