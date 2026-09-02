// ?rva8CCCE0ResolveValue@@YAXPAX0PAVRva8CCCE0Value@@PAPAV1@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable Apt value resolver, retail 0x008CCCE0 (118 bytes).

class Rva8CCCE0Value
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual bool slot9();

	unsigned m_flags;
	char m_gap[0x18];
	Rva8CCCE0Value *m_indirect;
};

Rva8CCCE0Value *rva8CC570Resolve(void *first, void *second, void *data);

void rva8CCCE0ResolveValue(void *first, void *second, Rva8CCCE0Value *value,
	Rva8CCCE0Value **result)
{
	unsigned flags = value->m_flags;
	int type = flags & 0x3f;
	if ((type < 12 || type > 19 ||
		((flags >>= 15),
		 (*(unsigned char *)&flags = (unsigned char)~*(unsigned char *)&flags),
		 (*(unsigned char *)&flags & 1))) && !value->slot9())
	{
		flags = value->m_flags;
		type = flags & 0x3f;
		if (type != 1 && type != 42)
			return;
		flags >>= 15;
		*(unsigned char *)&flags = (unsigned char)~*(unsigned char *)&flags;
		if (*(unsigned char *)&flags & 1)
			return;
		if (type != 1)
			value = value->m_indirect;
		*result = rva8CC570Resolve(first, second, (char *)value + 8);
		return;
	}
	*result = value;
}
