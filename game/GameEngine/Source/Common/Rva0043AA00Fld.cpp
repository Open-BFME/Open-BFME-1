// cl: /O2 /Ob0

struct Rva0043AA00Vec
{
	char m_pad[0x10];
	int m_x;
};

class Rva0043AA00Inner
{
public:
	virtual void pad0();
	virtual void pad1();
	virtual void pad2();
	virtual void pad3();
	virtual void pad4();
	virtual void pad5();
	virtual void pad6();
	virtual Rva0043AA00Vec *get();
};

class Rva0043AA00
{
	char m_pad[4];
	Rva0043AA00Inner *m_inner;

public:
	float run() const;
};

float Rva0043AA00::run() const
{
	return (float)m_inner->get()->m_x;
}
