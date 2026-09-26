// cl: /DNDEBUG /MD /EHsc /O2 /Ob0

// Open-BFME5: implicit destructor at 0x00078460. Retail is the 16-byte
// `eh vector destructor iterator' (??_M at 0x009F6D76) setup: destroy 8
// elements of 0x14 bytes at ecx, element dtor ILT 0x0001F951.

struct Rva00078460Elem
{
	~Rva00078460Elem();
	char m_body[0x14];
};

class Rva00078460
{
	Rva00078460Elem m_items[8];

public:
	~Rva00078460();
};

Rva00078460::~Rva00078460()
{
}
