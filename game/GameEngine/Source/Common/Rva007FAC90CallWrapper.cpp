class Rva007FAC90CallWrapper
{
public:
	virtual int slot0( void *buffer, void *value ) = 0;
	virtual int slot1( void *buffer, void *value ) = 0;

	int prepareAndCall( void *unusedBuffer, void *unusedValue );

private:
	unsigned char m_padding[ 0x8C ];
	unsigned char m_buffer[ 0x44 ];
	void *m_value;
};

int Rva007FAC90CallWrapper::prepareAndCall( void *, void * )
{
	return slot1( m_buffer, m_value );
}
