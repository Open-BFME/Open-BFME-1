// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva0022B680Node
{
	Rva0022B680Node *next;
	Rva0022B680Node *prev;
	void *value;
};

class Rva0022B680Obj
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void accept(void *value, int flag);

	void walk(int unused);

private:
	char m_lead[0xC4 - 4];
	Rva0022B680Node *m_list;
};

void Rva0022B680Obj::walk(int unused)
{
	Rva0022B680Node *sent = m_list;
	Rva0022B680Node *n = sent->next;
	while (n != sent)
	{
		void *value = n->value;
		if (value)
			accept(value, 0);
		sent = m_list;
		n = sent->next;
	}
}
