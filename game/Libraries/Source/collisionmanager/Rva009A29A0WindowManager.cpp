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

Rva009A29A0Record::Rva009A29A0Record(
    Rva009A29A0Window *window, void *ownerArgument)
{
	void *owner = ownerArgument;
	*(Rva009A29A0Window **)((char *)this + 4) = window;
	*(void **)this = owner;
	*(int *)((char *)this + 0x20) = 0;
	*(int *)((char *)this + 0xA0) = 0;
	++*(int *)((char *)owner + 4);
	*(void **)((char *)this + 8) = owner;
	void *head = *(void **)owner;
	*(void **)((char *)this + 0xC) = head;
	if (head != 0)
		*(void **)((char *)head + 8) = (char *)this + 0xC;
	*(void **)owner = this;
	owner = (char *)owner + 8;
	*(void **)((char *)this + 0x2C) = this;
	*(int *)((char *)this + 0x30) = 1;
	*(int *)((char *)this + 0x34) = 0;
	*(int *)((char *)this + 0x24) = 0;
	*(void **)((char *)this + 0x40) = this;
	*(int *)((char *)this + 0x44) = 0;
	*(int *)((char *)this + 0x48) = 0;
	*(int *)((char *)this + 0x38) = 0;
	*(void **)((char *)this + 0x54) = this;
	*(int *)((char *)this + 0x58) = 3;
	*(int *)((char *)this + 0x5C) = 0;
	*(int *)((char *)this + 0x4C) = 0;
	*(void **)((char *)this + 0x68) = this;
	*(int *)((char *)this + 0x6C) = 2;
	*(int *)((char *)this + 0x70) = 0;
	*(int *)((char *)this + 0x60) = 0;
	*(void **)((char *)this + 0x7C) = this;
	*(int *)((char *)this + 0x80) = 5;
	*(int *)((char *)this + 0x84) = 0;
	*(int *)((char *)this + 0x74) = 0;
	*(void **)((char *)this + 0x90) = this;
	*(int *)((char *)this + 0x94) = 4;
	*(int *)((char *)this + 0x98) = 0;
	*(int *)((char *)this + 0x88) = 0;
	*(void **)((char *)this + 0x10) = owner;
	head = *(void **)owner;
	*(void **)((char *)this + 0x14) = head;
	if (head != 0)
		*(void **)((char *)head + 0x10) = (char *)this + 0x14;
	*(void **)owner = this;
	*(void **)((char *)this + 0x9C) =
		(*(Rva009A29A0Window **)((char *)this + 4))->slot4();
	*(void **)((char *)this + 0xA0) =
		(*(Rva009A29A0Window **)((char *)this + 4))->slot5();
}
