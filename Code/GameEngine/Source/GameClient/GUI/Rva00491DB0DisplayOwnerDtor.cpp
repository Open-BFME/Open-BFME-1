// cl: /DNDEBUG /DWIN32 /MD /EHsc

class Rva00491DB0Display
{
public:
	virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
	virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
	virtual void f08(); virtual void f09(); virtual void f10(); virtual void f11();
	virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
	virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
	virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
	virtual void f24(); virtual void f25(); virtual void f26(); virtual void f27();
	virtual void f28(); virtual void f29(); virtual void f30(); virtual void f31();
	virtual void f32(); virtual void f33(); virtual void f34(); virtual void f35();
	virtual void f36(); virtual void f37(); virtual void f38(); virtual void f39();
	virtual void f40(); virtual void f41(); virtual void f42(); virtual void f43();
	virtual void f44(); virtual void f45(); virtual void f46(); virtual void f47();
	virtual void f48(); virtual void f49(); virtual void f50(); virtual void f51();
	virtual void f52(); virtual void f53(); virtual void f54(); virtual void f55();
	virtual void f56(); virtual void f57(); virtual void f58();
	virtual void releaseOwner(void);
};

extern Rva00491DB0Display *TheDisplay;

class Rva00491DB0String
{
public:
	~Rva00491DB0String();
private:
	char *m_data;
};

class Rva00491DB0Base
{
public:
	virtual ~Rva00491DB0Base();
private:
	unsigned char m_padding[0x10];
};

class Rva00491DB0DisplayOwner : public Rva00491DB0Base
{
public:
	virtual ~Rva00491DB0DisplayOwner();
private:
	Rva00491DB0String m_name;
};

Rva00491DB0DisplayOwner::~Rva00491DB0DisplayOwner()
{
	TheDisplay->releaseOwner();
}
