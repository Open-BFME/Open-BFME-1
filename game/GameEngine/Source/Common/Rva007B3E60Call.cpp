// cl: /O2 /Ob0

class Rva007B3E60G
{
public:
	void bar(void *);
};

Rva007B3E60G *g_rva007b3e60;

class Rva007B3E60
{
public:
	void run();
};

void Rva007B3E60::run()
{
	g_rva007b3e60->bar(this);
}
