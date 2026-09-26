// ?dispatch@Rva007EAServiceList@@QAEXXZ
// partial score=0.88 date=2026-09-02
// cl: /O2
// Near miss for 0x007EA5E0: control flow, getter, vcalls and tail match.
// MSVC 7.1 parks this in ebx and ctx in ebp; retail uses ebp/ebx. The slot
// load is then `mov ecx,[esi]` instead of `mov eax,[esi] / mov ecx,eax`,
// so the inner vcall is two bytes short and every later rel32 shifts.
// Same wholesale ebx/ebp swap across /O2 /G5 /G6 /G7 /Os and a dedicated TU.

class Rva00803080
{
public:
	virtual void notify(void *ctx);
};

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual void *context();
	virtual void enter();
	virtual void leave();
};

extern Rva007E9B70Obj *Rva007E9B70Get();
void Rva007F8C90();

class Rva007EAServiceList
{
public:
	void dispatch();

private:
	char m_pad[8];
	unsigned char m_flags;
	char m_pad9[7];
	Rva00803080 *m_slots[8];
};

void Rva007EAServiceList::dispatch()
{
	Rva007E9B70Get()->enter();
	void *ctx = Rva007E9B70Get()->context();
	Rva00803080 **p = m_slots;
	int n = 8;
	do
	{
		if (*p != 0)
			(*p)->notify(ctx);
		++p;
	} while (--n);
	Rva007E9B70Get()->leave();
	if ((m_flags & 2) == 0)
		Rva007F8C90();
}
