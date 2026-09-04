// ?hide@Rva006BC750@@QAEXXZ
// partial score=0.9 date=2026-09-04
// ?hide@Rva006BC750@@QAEXXZ
// partial score=0.9 date=2026-09-02
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Hide the drawable at [this+0xC] then walk its +0x150 module array.

class Drawable
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
	virtual Drawable *getChild();
	void setDrawableHidden(bool hidden);
	void **getDrawModules();
};

class Rva006BC750Node
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
	virtual Drawable *vslotB8();
};

class Rva006BC750Item
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
	virtual void vslot40();
};

class Rva006BC750
{
public:
	void hide();

private:
	char m_pad[0xC];
	Drawable *m_drawable;
};

void Rva006BC750::hide()
{
	if (m_drawable)
	{
		Drawable *child = m_drawable->getChild();
		child->setDrawableHidden(true);
		for (Rva006BC750Node **p = (Rva006BC750Node **)child->getDrawModules(); *p; ++p)
		{
			Drawable *got = (*p)->vslotB8();
			if (got)
				((Rva006BC750Item *)got)->vslot40();
		}
	}
}
