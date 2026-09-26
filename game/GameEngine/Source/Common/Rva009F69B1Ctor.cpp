// cl: /O2 /Ob0

class Rva009F69B1Subobject
{
public:
	Rva009F69B1Subobject();

private:
	unsigned char storage[0x18];
};

class Rva009F69B1
{
public:
	Rva009F69B1();

private:
	unsigned char reserved[0x18];
	Rva009F69B1Subobject subobject;
	int first;
	int count;
	int capacity;
};

Rva009F69B1::Rva009F69B1()
{
	first = 0;
	count = 0;
	capacity = 0;
}
