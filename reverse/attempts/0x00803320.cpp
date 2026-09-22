// ?update@Rva00803080@@QAEXI@Z
// partial score=0.58 date=2026-09-22
// cl: /O2 /Ob0 /GX- /GS

struct Rva00807BA0Ping;
struct Rva007EB810Diag
{
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual void fail(const char *, const char *, int);
};
Rva007EB810Diag *Rva007EB810Get();
extern "C" void *memset(void *, int, unsigned int);

struct Rva00808660Result
{
	char m_text[0x14]; int m_from; int m_elapsed; int m_sequence;
	int m_icmpType; int m_server; int m_pad28;
};
int Rva00808660(Rva00807BA0Ping *, void *, int *, Rva00808660Result *);

struct Rva00803080Request
{
	int m_00; int m_04; int m_08; int m_0c;
};

class Rva00803320Reply;
class Rva00803320Callback
{
public:
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual void v0c(); virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1c(); virtual void notify(int, int);
};

class Rva00803320Reply
{
public:
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual void v0c(); virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1c(); virtual void v20();
	virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34();
	virtual Rva00803320Reply *get(int);
	char m_pad[0x48]; int m_elapsed;
};

class Rva00803320Hub
{
public:
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual void v0c(); virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1c(); virtual void v20();
	virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38();
	virtual void v3c(); virtual void v40(); virtual void v44();
	virtual void v48(); virtual void v4c(); virtual void v50();
	virtual Rva00803320Reply *find(int);
	char m_pad04[0x18]; Rva00803320Callback *m_callback;
};

class Rva00803080
{
	void *m_00; Rva00803320Hub *m_04; Rva00807BA0Ping *m_08;
	Rva00803080Request *m_0c; int m_10;
public:
	void removePendingRequest(int); void update(unsigned int);
};

void Rva00803080::update(unsigned int now)
{
	int length = 8;
	int payload[2] = { 0, 0 };
	Rva00808660Result result;
	const int sentinel = 0x7fffffff;

	memset(&result, 0, sizeof(result));
	result.m_sequence = sentinel;
	Rva00808660(m_08, payload, &length, &result);
	int sequence = result.m_sequence;
	if (sequence == sentinel)
		goto timeout_sweep;

	for (;;)
	{
		int index = 0;
		if (m_10 > 0)
		{
			while (index < m_10)
			{
				if (m_0c[index].m_00 == sequence)
					goto got_result;
				++index;
			}
			goto fetch_next;

		got_result:
			removePendingRequest(index);
			if (length != 8)
			{
				Rva007EB810Get()->fail(
					"FALSE",
					"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp",
					0xd6);
			}
			else
			{
				Rva00803320Reply *reply = m_04->find(payload[0]);
				if (reply != 0)
				{
					reply = reply->get(payload[1]);
					if (reply != 0)
					{
						reply->m_elapsed = result.m_elapsed;
						Rva00803320Callback *callback = m_04->m_callback;
						if (callback != 0)
							callback->notify(payload[0], payload[1]);
					}
				}
			}
		}

	fetch_next:
		memset(&result, 0, sizeof(result));
		result.m_sequence = sentinel;
		Rva00808660(m_08, payload, &length, &result);
		sequence = result.m_sequence;
		if (sequence == sentinel)
			break;
	}

timeout_sweep:
	{
		unsigned int timeout = now - 5000;
		int index = 0;
		if (m_10 > 0)
		{
			do
			{
				if ((unsigned int)m_0c[index].m_04 >= timeout)
					break;

				Rva00803320Reply *reply = m_04->find(m_0c[index].m_08);
				if (reply != 0)
				{
					reply = reply->get(m_0c[index].m_0c);
					if (reply != 0)
					{
						reply->m_elapsed = -3;
						Rva00803320Callback *callback = m_04->m_callback;
						if (callback != 0)
							callback->notify(m_0c[index].m_08, m_0c[index].m_0c);
					}
				}
				removePendingRequest(index);
				++index;
			}
			while (index < m_10);
		}
	}
}
