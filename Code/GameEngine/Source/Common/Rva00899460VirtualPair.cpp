// Clean reconstruction of the retail virtual pair at RVA 0x00899460.

class Gen0089C880
{
public:
	void handle();
};

class Rva00899460Object
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16(int first, int second);
	void process();

	char padding[4];
	Gen0089C880 subobject;
};

void Rva00899460Object::process()
{
	subobject.handle();
	slot16(0, 0);
}
