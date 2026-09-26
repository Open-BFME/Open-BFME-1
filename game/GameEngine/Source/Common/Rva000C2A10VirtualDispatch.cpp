// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: address-derived wrapper at 0x000C2A10.

struct Rva000C2A10Object
{
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
	virtual void slot14(void *argument);
	Rva000C2A10Object *virtualDispatch(void *argument);
};

Rva000C2A10Object *Rva000C2A10Object::virtualDispatch(void *argument)
{
	slot14(argument);
	return this;
}
