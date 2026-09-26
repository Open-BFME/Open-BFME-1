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

extern BfmeRef006e2480 *g_bfmeObj006e1be0;

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
