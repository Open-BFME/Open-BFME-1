class Rva00564A10
{
public:
	static void go();
};

class BfmeThingBEH
{
public:
	void bfmeGoBEH();
	bool m_bfmeFlag;
};

void BfmeThingBEH::bfmeGoBEH()
{
	if (m_bfmeFlag)
	{
		Rva00564A10::go();
		m_bfmeFlag = false;
	}
}
