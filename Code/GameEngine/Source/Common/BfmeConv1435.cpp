// cl: /O2 /Ob0

extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);

class BfmeStrVM0
{
public:
	virtual int v0();
	virtual int v1();
	virtual int v2();
	virtual int v3();
	virtual int v4();
	virtual int v5();
	virtual int v6();
	virtual int v7();
	virtual int v8();
	virtual int v9();
	virtual int v10();
	virtual int v11();
	virtual int v12();
	virtual int v13();
	virtual int v14();
	virtual int v15();
	virtual int v16();
	virtual int v17();
	virtual int v18();
	virtual int v19();
	virtual int v20();
	virtual int v21();
	virtual int v22();
	virtual int v23();
	virtual int v24();
	virtual int v25();
	virtual int v26();
	virtual int v27();
	virtual int v28();
	virtual int v29();
	virtual int v30();
	virtual int v31();
	virtual int v32();
	virtual int v33();
	virtual int v34();
	virtual int v35();
	virtual int v36();
	virtual int v37();
	virtual int v38();
	virtual int v39();
	virtual int v40();
	virtual int v41();
	virtual int v42();
	virtual int v43();
	virtual int v44();
	virtual int v45();
	virtual int v46();
	virtual int v47();
	virtual int v48();
	virtual int v49();
	virtual int v50();
	virtual int v51();
	virtual int v52();
	virtual int v53();
	virtual int v54();
	virtual int v55();
	virtual int v56();
	virtual int v57();
	virtual int v58();
	virtual int v59();
	virtual bool bfmePredVM0();
	void bfmeGoVM0(int);
	void bfmeTickVM0();
	void bfmeRelVM0();
	void bfmeRelBareVM0();
	void bfmeFlagVM0(unsigned char);
	char m_pad[0x38];
	void *m_3C;
	void *m_40;
};

void BfmeStrVM0::bfmeTickVM0()
{
	if (bfmePredVM0())
		bfmeGoVM0(3);
}

void BfmeStrVM0::bfmeRelVM0()
{
	if (bfmePredVM0())
	{
		if (m_40)
		{
			ReleaseMutex(*(void * volatile *)&m_40);
			WaitForSingleObject(m_3C, 0xffffffff);
			ReleaseMutex(m_3C);
			m_40 = 0;
			m_3C = 0;
		}
	}
}

void BfmeStrVM0::bfmeRelBareVM0()
{
	if (m_40)
	{
		ReleaseMutex(*(void * volatile *)&m_40);
		WaitForSingleObject(m_3C, 0xffffffff);
		ReleaseMutex(m_3C);
		m_40 = 0;
		m_3C = 0;
	}
}

void BfmeStrVM0::bfmeFlagVM0(unsigned char on)
{
	if (on)
		bfmeGoVM0(5);
	else if (m_40)
	{
		ReleaseMutex(*(void * volatile *)&m_40);
		WaitForSingleObject(m_3C, 0xffffffff);
		ReleaseMutex(m_3C);
		m_40 = 0;
		m_3C = 0;
	}
}
