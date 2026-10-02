// cl: /GX-
// Rva00801FB0Elem ctor: vtable, V2ZeroInt +8/+C, twin Gen_00800340 members at
// +0x10/+0x1C, body zeros, m_4C=-1. Stride 0x80 from Rva00802A10::allocate.
// Pin: ?m@Gen_00800340@@QAEPAXXZ -> 0x00800340 (this-zero3), defined in
// game/gen_small/fun_005.cpp; declared here without a body.

struct V2ZeroInt
{
	__forceinline V2ZeroInt() : m_value(0) {}
	int m_value;
};

class Gen_00800340
{
public:
	void *m();

	void *m_block;
	int m_field4;
	int m_field8;
};

class Rva00801FB0Elem
{
public:
	__declspec(noinline) Rva00801FB0Elem();
	virtual void slot();

	int m_04;
	V2ZeroInt m_08;
	V2ZeroInt m_0C;
	Gen_00800340 m_10;
	Gen_00800340 m_1C;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
	int m_58;
	int m_5C;
	int m_60;
	char m_64;
	char m_65;
	char m_pad66[2];
	int m_68;
	int m_6C;
	int m_70;
	int m_74;
	int m_78;
	int m_7C;
};

Rva00801FB0Elem::Rva00801FB0Elem()
{
	// Retail constructs the twin +0x10/+0x1C members through the member
	// function that is defined at 0x00800340; call it under its real name so
	// the two emitted calls resolve.
	m_10.m();
	m_1C.m();
	m_3C = 0;
	m_40 = 0;
	m_04 = 0;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
	m_44 = 0;
	m_50 = 0;
	m_54 = 0;
	m_58 = 0;
	m_5C = 0;
	m_64 = 0;
	m_65 = 0;
	m_68 = 0;
	m_70 = 0;
	m_74 = 0;
	m_6C = 0;
	m_78 = 0;
	m_4C = -1;
}
