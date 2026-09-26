// cl: /O2 /Ob0

class Rva0060A900
{
	char m_lead[4];
	char m_field;

	void callee(void *);

public:
	void run();
};

void Rva0060A900::run()
{
	callee(&m_field);
}
