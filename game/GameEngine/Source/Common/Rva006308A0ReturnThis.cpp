// cl: /O2 /MD /EHsc-

class Rva006308A0ReturnThis
{
public:
	void *get();
};

void *Rva006308A0ReturnThis::get()
{
	return this;
}
