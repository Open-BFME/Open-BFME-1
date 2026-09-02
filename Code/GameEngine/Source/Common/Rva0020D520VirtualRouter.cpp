// Open-BFME5: clean C++ conversion of the embedded virtual-event router.

class Rva0020D520Owner
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void routeThird();
	virtual void routeSecond();
};

class Rva0020D520EmbeddedRouter
{
public:
	void route(int first, int second, int third);
};

void Rva0020D520EmbeddedRouter::route(int first, int second, int third)
{
	if (third == 2)
		reinterpret_cast<Rva0020D520Owner *>(
			reinterpret_cast<char *>(this) - 0x20)->routeThird();
	else if (second == 2)
		reinterpret_cast<Rva0020D520Owner *>(
			reinterpret_cast<char *>(this) - 0x20)->routeSecond();
}
