// cl: /O2 /Ob0

struct Rva00597F30Item
{
	int first;
	int unused;
	void *made;
	float width;
	int x;
	unsigned char y;
};

class Rva00597F30
{
public:
	void init();

private:
	int m_zero;
	int m_zero2;
	unsigned char m_flags[ 0x14 ];
	Rva00597F30Item m_items[ 12 ];
};

class Rva005638D0
{
public:
	void init();

private:
	unsigned char m_beforeMember[ 0x17C ];
	Rva00597F30 m_member;
};

void Rva005638D0::init()
{
	m_member.init();
}
