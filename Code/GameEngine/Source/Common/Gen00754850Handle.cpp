// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The symbols.csv pin names this body Gen00754850::handle.  The caller at
// 0x00755A70 reaches the same body through its ILT, and the retail body owns
// two reference-counted pointer vectors plus an STLport list.
#include <list>
#include <vector>

class Gen00754850First
{
public:
	virtual void slot0();
	int m_refs;
	unsigned char m_pad[0x30C];
	int m_314;
};

class Gen00754850Second
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58(int value);
	int m_refs;
};

class Gen_t_007546f0_p12cd
{
public:
	~Gen_t_007546f0_p12cd();

private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class Gen00754850
{
public:
	void handle();

private:
	unsigned char m_head[0x0C];
	_STL::list<Gen_t_007546f0_p12cd> m_list;
	_STL::vector<Gen00754850First *> m_first;
	_STL::vector<Gen00754850Second *> m_second;
};

// ?handle@Gen00754850@@QAEXXZ
void Gen00754850::handle()
{
	for (Gen00754850First **it = m_first.begin(); it != m_first.end(); ++it)
	{
		Gen00754850First *object = *it;
		int refs = object->m_refs;
		--refs;
		object->m_314 = 0;
		object->m_refs = refs;
		if (refs == 0)
			object->slot0();
	}

	for (Gen00754850Second **it = m_second.begin(); it != m_second.end(); ++it)
	{
		Gen00754850Second *object = *it;
		object->slot58(0);
		--object->m_refs;
		if (object->m_refs == 0)
			object->slot0();
	}

	m_first.clear();
	m_second.clear();
	m_list.clear();
}
