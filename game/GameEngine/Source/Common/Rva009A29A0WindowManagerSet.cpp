// cl: /EHsc /MD

struct Rva009A29A0Record;

struct Rva009A29A0Window
{
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void *slot4() = 0;
	virtual void *slot5() = 0;
	virtual void apply(Rva009A29A0Record *) = 0;
	virtual void *isReady() = 0;
};

struct Rva009A29A0Record
{
	Rva009A29A0Record(Rva009A29A0Window *, void *);
	char m_padding[0xA4];
};

class Rva009A29A0WindowManager
{
public:
	void set(Rva009A29A0Window *window);
};

void Rva009A29A0WindowManager::set(Rva009A29A0Window *window)
{
	if (window == 0)
		return;
	if (window->isReady() != 0)
		return;

	Rva009A29A0Record *record = new Rva009A29A0Record(window, this);
	window->apply(record);
}
