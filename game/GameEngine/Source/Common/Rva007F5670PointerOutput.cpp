// Address-derived reconstruction of the 12-byte pointer output helper at 0x007F5670.

class Rva007F5670PointerOutput
{
public:
	void **writeValue( void **output ) const;

private:
	char m_pad00[ 0x18 ];
	void *m_value;
};

void **Rva007F5670PointerOutput::writeValue( void **output ) const
{
	*output = m_value;
	return output;
}
