// cl: /O2 /Ob0

class Rva007BAA90G
{
public:
	void bar(void *);
};

Rva007BAA90G *g_rva007baa90;

class Rva007BAA90
{
public:
	void run();
};

void Rva007BAA90::run()
{
	g_rva007baa90->bar(this);
}
