// cl: /O2 /Ob0

// The callee at 0x00093050 (BfmeOneHundredEightyEight.cpp), via ILT 0x0001A7DF.
class BfmeThingDN
{
public:
	void bfmeTellDN(void *);
};

extern void *TheOptionGroupTarget;

class Rva000946B0
{
public:
	void run();
};

void Rva000946B0::run()
{
	reinterpret_cast<BfmeThingDN *>(TheOptionGroupTarget)->bfmeTellDN(this);
}
