// cl: /DNDEBUG /MD /EHsc
// Retail 0x006D6050 (91 bytes). Zeros dword 0 then 6-arg init. A trailing
// member with a destructor forces the EH frame around the init call.

class Rva006D6050Guard
{
public:
	~Rva006D6050Guard();
};

class Rva006D6050
{
public:
	Rva006D6050(int a, int b);
	void init(int, int, int, int, int, int);

private:
	int m_00;
	Rva006D6050Guard m_guard;
};

Rva006D6050::Rva006D6050(int a, int b)
	: m_00(0)
{
	init(0x800, a, 0x15, b, 1, 0);
}
