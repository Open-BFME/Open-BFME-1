// cl: /O2 /Ob0

class Rva000946B0G
{
public:
	void bar(void *);
};

extern void *TheOptionGroupTarget;

class Rva000946B0
{
public:
	void run();
};

void Rva000946B0::run()
{
	reinterpret_cast<Rva000946B0G *>(TheOptionGroupTarget)->bar(this);
}
