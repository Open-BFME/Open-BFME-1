// cl: /DNDEBUG /MD /EHsc

class Gen0035F050
{
public:
	bool poll(int a, int limit, int c, int d, int e);
	int step(void);

private:
	void *m_unused0;
	int m_value;
};

// step is reached through ILT 0x00049AE4 (body 0x0035EE70, still a gen dump), which
// the ledger defines as ?j_00049ae4@@YAXXZ; the call names it through a member pointer.
extern void j_00049ae4(void);

bool Gen0035F050::poll(int, int limit, int, int, int)
{
	union { void (*raw)(void); int (Gen0035F050::*member)(void); } stepCall;
	stepCall.raw = j_00049ae4;
	if (m_value > limit)
	{
		do
		{
			if (!(this->*stepCall.member)())
				return false;
		} while (m_value > limit);
	}
	return true;
}
