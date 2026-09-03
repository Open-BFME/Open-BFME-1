// cl: /DNDEBUG /MD /O2
// Copy an 8-byte pair onto the stack, pass it to vslot +0xC8, write it back.

struct Rva0034C4D0Pair
{
	int m_a;
	int m_b;
	int m_pad;
};

class Rva0034C4D0Host
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual void pad47();
	virtual void pad48();
	virtual void pad49();
	virtual void applyPair(void *object, Rva0034C4D0Pair *pair);

	void invokePair(void *object, Rva0034C4D0Pair *pair);
};

// ?invokePair@Rva0034C4D0Host@@QAEXPAXPAURva0034C4D0Pair@@@Z
void Rva0034C4D0Host::invokePair(void *object, Rva0034C4D0Pair *pair)
{
	if (object)
	{
		if (pair)
		{
			Rva0034C4D0Pair tmp;
			tmp.m_a = pair->m_a;
			tmp.m_b = pair->m_b;
			applyPair(object, &tmp);
			pair->m_a = tmp.m_a;
			pair->m_b = tmp.m_b;
		}
	}
}
