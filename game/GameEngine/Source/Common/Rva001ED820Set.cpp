// cl: /O2 /Ob0

class RetailLayoutString
{
public:
	void set(const char *text, int length);
};

class Rva001ED820
{
	char m_lead[0x20];
	RetailLayoutString m_layout;

public:
	void run();
};

void Rva001ED820::run()
{
	m_layout.set("", 0);
}
