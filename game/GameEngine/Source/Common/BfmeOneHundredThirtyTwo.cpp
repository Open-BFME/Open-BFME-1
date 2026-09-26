// One more: an assignment that copies twenty fields and leaves the first
// word of the object alone.

class Gen_0075EF90
{
public:
	Gen_0075EF90 &bfmeAssign(const Gen_0075EF90 &other);
private:
	int m_bfmeHead;						// +0x00
	int m_bfme04;						// +0x04
	int m_bfme08;						// +0x08
	int m_bfme0c;						// +0x0c
	int m_bfme10;						// +0x10
	int m_bfme14;						// +0x14
	int m_bfme18;						// +0x18
	int m_bfme1c;						// +0x1c
	int m_bfme20;						// +0x20
	int m_bfme24;						// +0x24
	int m_bfme28;						// +0x28
	int m_bfme2c;						// +0x2c
	int m_bfme30;						// +0x30
	int m_bfme34;						// +0x34
	unsigned char m_bfme38;				// +0x38
	unsigned char m_bfme39;				// +0x39
	unsigned char m_bfmeGap[2];			// +0x3a
	int m_bfme3c;						// +0x3c
	int m_bfme40;						// +0x40
	int m_bfme44;						// +0x44
	int m_bfme48;						// +0x48
	int m_bfme4c;						// +0x4c
};

Gen_0075EF90 &Gen_0075EF90::bfmeAssign(const Gen_0075EF90 &other)
{
	m_bfme04 = other.m_bfme04;
	m_bfme08 = other.m_bfme08;
	m_bfme0c = other.m_bfme0c;
	m_bfme10 = other.m_bfme10;
	m_bfme14 = other.m_bfme14;
	m_bfme18 = other.m_bfme18;
	m_bfme1c = other.m_bfme1c;
	m_bfme20 = other.m_bfme20;
	m_bfme24 = other.m_bfme24;
	m_bfme28 = other.m_bfme28;
	m_bfme2c = other.m_bfme2c;
	m_bfme30 = other.m_bfme30;
	m_bfme34 = other.m_bfme34;
	m_bfme38 = other.m_bfme38;
	m_bfme39 = other.m_bfme39;
	m_bfme3c = other.m_bfme3c;
	m_bfme40 = other.m_bfme40;
	m_bfme44 = other.m_bfme44;
	m_bfme48 = other.m_bfme48;
	m_bfme4c = other.m_bfme4c;

	return *this;
}
