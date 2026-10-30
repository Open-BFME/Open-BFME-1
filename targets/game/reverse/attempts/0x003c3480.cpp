// ?d_003c3480@@YAXXZ
// partial score=0.3249 date=2026-10-30
// ?vector003C3480@Transfer003C3D90@@QAEXPAVXfer@@PAX@Z
// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>

// Retail Xfer slots used here: IsLoading +0x04, operator==(int &) +0x78 and
// the named enum transfer +0x90 (LivingWorldPlayerArmyXfer.cpp's view).
class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual void slot02(); virtual void slot03(); virtual void slot04();
	virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27(); virtual void slot28();
	virtual void slot29();
	virtual Xfer &operator==(int &value);
	virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35();
	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
};

class Rva003C2280Item
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	virtual void slot04();
	virtual void slot05();
	virtual int getType();
};

class Rva003BD6D0 : public Rva003C2280Item
{
public:
	Rva003BD6D0() : m_value(0) {}
	virtual void xfer(Xfer *xfer);
	char m_gap04[8];
	int m_value;
};

class Rva003BEA00 : public Rva003C2280Item
{
public:
	Rva003BEA00() : m_value(0) {}
	virtual void xfer(Xfer *xfer);
	char m_gap04[8];
	int m_value;
};

class Rva003BD6F0 : public Rva003C2280Item
{
public:
	Rva003BD6F0() {}
	virtual void xfer(Xfer *xfer);
	char m_gap04[0x1c];
};

class Rva003C2F40Owner : public Rva003C2280Item
{
public:
	Rva003C2F40Owner();
	char m_gap04[0x18];
};

class Transfer003C3D90
{
public:
	void vector003C3480(Xfer *xfer, void *items);
};

void Transfer003C3D90::vector003C3480(Xfer *xfer, void *itemsArg)
{
	std::vector<Rva003C2280Item *> *items = (std::vector<Rva003C2280Item *> *)itemsArg;
	int count = items->size();
	*xfer == count;
	if (xfer->IsLoading())
	{
		for (int i = 0; i < count; ++i)
		{
			int type;
			xfer->XferEnum("DelayedEventType", &type, sizeof(type));
			Rva003C2280Item *item;
			switch (type)
			{
				case 1: item = new Rva003BD6D0; break;
				case 2: item = new Rva003BEA00; break;
				case 4: item = new Rva003BD6F0; break;
				case 8: item = new Rva003C2F40Owner; break;
				default: continue;
			}
			item->xfer(xfer);
			items->push_back(item);
		}
	}
	else
	{
		for (int i = 0; i < count; ++i)
		{
			int type = (*items)[i]->getType();
			xfer->XferEnum("DelayedEventType", &type, sizeof(type));
			(*items)[i]->xfer(xfer);
		}
	}
}
