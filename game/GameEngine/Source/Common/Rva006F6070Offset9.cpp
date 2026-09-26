// cl: /DNDEBUG /MD /EHsc

class Rva006F6070Offset9
{
public:
	void *get()
	{
		return (char *)this + 9;
	}
};

typedef void *(Rva006F6070Offset9::*Rva006F6070Offset9Getter)();
Rva006F6070Offset9Getter g_rva006F6070Offset9Getter = &Rva006F6070Offset9::get;
