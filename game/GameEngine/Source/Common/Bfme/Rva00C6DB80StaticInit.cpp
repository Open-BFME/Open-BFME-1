// cl: /O2 /MD
extern void dup_00853ec0(void);

class Rva00C6DB80Init
{
public:
	Rva00C6DB80Init()
	{
		typedef void *(Rva00C6DB80Init::*Member)(void);
		union { void (*function)(void); Member method; } call;
		call.function = (void (*)(void))dup_00853ec0;
		(this->*call.method)();
	}
	~Rva00C6DB80Init();
};

Rva00C6DB80Init g_rva0130CE58;
