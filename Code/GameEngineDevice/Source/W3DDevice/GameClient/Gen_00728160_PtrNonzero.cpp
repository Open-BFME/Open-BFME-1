// cl: /DNDEBUG /MD /EHsc

// Retail 0x00728160. Return (this+0xB8) != 0.

class Gen_00728160
{
public:
	bool nonempty(void) const;

private:
	unsigned char m_pad[0xB8];
	void *m_ptr;
};

// ?nonempty@Gen_00728160@@QBE_NXZ
bool Gen_00728160::nonempty(void) const
{
	return m_ptr != 0;
}
