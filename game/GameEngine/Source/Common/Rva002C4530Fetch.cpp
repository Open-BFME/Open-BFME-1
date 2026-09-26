// cl: /O2 /Ob0

struct RvaVec3_002C4530
{
	int m_x;
	int m_y;
	int m_z;
};

class ContainRva002C4530
{
public:
	virtual void pad00();
	virtual void pad04();
	virtual void pad08();
	virtual void pad0c();
	virtual void pad10();
	virtual void pad14();
	virtual void pad18();
	virtual RvaVec3_002C4530 *fetch(RvaVec3_002C4530 *out, void *key, int *scratch); // +0x1c
	virtual void pad20();
	virtual void pad24();
	virtual void pad28();
	virtual void pad2c();
	virtual void pad30();
	virtual void pad34();
	virtual void pad38();
	virtual void pad3c();
	virtual void pad40();
	virtual void pad44();
	virtual void pad48();
	virtual void pad4c();
	virtual void pad50();
	virtual void pad54();
	virtual void pad58();
	virtual void pad5c();
	virtual void pad60();
	virtual void pad64();
	virtual ContainRva002C4530 *getInner(); // +0x68
};

class ObjRva002C4530
{
public:
	char m_lead[0x1FC];
	ContainRva002C4530 *m_contain;
};

class Rva002C4530Owner
{
public:
	void update(void *key, RvaVec3_002C4530 *out);
};

void Rva002C4530Owner::update(void *key, RvaVec3_002C4530 *out)
{
	ContainRva002C4530 *inner =
		(*(ObjRva002C4530 **)((char *)this - 0x338))->m_contain->getInner();

	if (inner != 0)
	{
		if (out != 0)
		{
			struct
			{
				int scratch;
				RvaVec3_002C4530 temp;
			} buf;

			*out = *inner->fetch(&buf.temp, key, &buf.scratch);
		}
	}
}
