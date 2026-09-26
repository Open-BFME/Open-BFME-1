// cl: /O2 /Ob0

class Rva0060A910
{
	char m_lead[8];
	char m_field;

	void callee(void *);

public:
	void run();
};

void Rva0060A910::run()
{
	callee(&m_field);
}
