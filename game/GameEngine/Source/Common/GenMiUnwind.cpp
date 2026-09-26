// cl: /EHsc
//
// Anonymous MSVC 7.1 multiple-inheritance destructor unwind bodies.
// Retail labels them Unwind@; no parent identity survives.

struct Gen_uw_00001c80 {
	virtual void f() = 0;
	~Gen_uw_00001c80();
};

struct Gen_uw_000246ae {
	virtual void f() = 0;
	~Gen_uw_000246ae();
};

struct Gen_uwm_00046cb8 {
	virtual void f() = 0;
	~Gen_uwm_00046cb8();
};

struct GenMiUnwindBase4 {
	virtual void f() = 0;
	~GenMiUnwindBase4();
};

struct GenMiUnwindBase8 {
	virtual void f() = 0;
	int x;
	~GenMiUnwindBase8();
};

struct GenMiUnwindObj4s : GenMiUnwindBase4, Gen_uw_00001c80 {
	~GenMiUnwindObj4s();
};

struct GenMiUnwindObj4g : GenMiUnwindBase4, Gen_uw_000246ae {
	~GenMiUnwindObj4g();
};

struct GenMiUnwindObj8g : GenMiUnwindBase8, Gen_uwm_00046cb8 {
	~GenMiUnwindObj8g();
};

extern void gen_mi_unwind_ext();

// ??1GenMiUnwindObj4s@@QAE@XZ absent-from-retail
GenMiUnwindObj4s::~GenMiUnwindObj4s()
{
	gen_mi_unwind_ext();
}

// ??1GenMiUnwindObj4g@@QAE@XZ absent-from-retail
GenMiUnwindObj4g::~GenMiUnwindObj4g()
{
	gen_mi_unwind_ext();
}

// ??1GenMiUnwindObj8g@@QAE@XZ absent-from-retail
GenMiUnwindObj8g::~GenMiUnwindObj8g()
{
	gen_mi_unwind_ext();
}
