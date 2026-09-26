// cl: /O2 /Ob0

class Rva000946B0G
{
public:
	void bar(void *);
};

Rva000946B0G *g_rva000946b0;

class Rva000946B0
{
public:
	void run();
};

void Rva000946B0::run()
{
	g_rva000946b0->bar(this);
}
