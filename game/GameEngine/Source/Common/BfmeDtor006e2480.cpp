// cl: /DNDEBUG /MD /EHsc

class BfmeRef006e2480
{
public:
	virtual void Delete_This(void);
	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}

private:
	int m_refs;
};

// 0X012F8048 is retail's global dword (?g_get_00710fb0@@3HA, defined in
// W3DDevice/GameClient/Gen_00710fb0_Global.cpp).  Retail reloads it each
// time, so this TU reads and writes it as the pointer it holds.
extern int g_get_00710fb0;
#define g_bfmeObj006e1be0 (*reinterpret_cast<BfmeRef006e2480 **>(&g_get_00710fb0))

class Gen_dtor_0040ba10
{
public:
	virtual ~Gen_dtor_0040ba10(void);
};

class Gen006E2310 : public Gen_dtor_0040ba10
{
public:
	virtual ~Gen006E2310(void);
};

// ??1Gen006E2310@@UAE@XZ
Gen006E2310::~Gen006E2310(void)
{
	if (g_bfmeObj006e1be0)
	{
		g_bfmeObj006e1be0->Release_Ref();
		g_bfmeObj006e1be0 = 0;
	}
}
