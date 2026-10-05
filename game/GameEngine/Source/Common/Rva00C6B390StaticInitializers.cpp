// cl: /O2 /MD
// Fourteen $E dynamic-initializer stubs (seat small20260927T211619_06,
// retail 0x00C6B390..0x00C6B940, 22 bytes each). The 0x00C6B7D0
// initializer now belongs to TheSupplyAndTechImageLocations in
// SkirmishGameOptionsMenu.cpp; the remaining globals emit bare _$En bodies.
// stub is ecx = global, call thiscall ctor through its ILT thunk, push the
// teardown forwarder, atexit. The ctor is invoked through the same union
// member-pointer call the retail bytes encode (a direct call through the
// j_ ILT name the ledger already owns for that thunk); the teardown the
// compiler registers is TU-local and masked like any other relocation.
// Only the ledger name is address-derived; no semantic identity is claimed
// for any of these globals.
extern void j_00010375();
extern void j_00008c92();
extern void j_0001ea83();
extern void j_0003493c();
extern void j_0001221f();
extern void j_0003dcb2();
extern void j_00027c7d();
extern void j_0000f632();
extern void j_0001dd8b();
extern void j_00017bd9();

struct Rva00C6B390Init
{
	Rva00C6B390Init()
	{
		typedef void *(Rva00C6B390Init::*Member)();
		union { void (*function)(); Member method; } call;
		call.function = (void (*)())j_00010375;
		(this->*call.method)();
	}
	~Rva00C6B390Init();
};

struct Rva00C6B3D0Init
{
	Rva00C6B3D0Init()
	{
		typedef void *(Rva00C6B3D0Init::*Member)();
		union { void (*function)(); Member method; } call;
		call.function = (void (*)())j_00008c92;
		(this->*call.method)();
	}
	~Rva00C6B3D0Init();
};

struct Rva00C6B3F0Init
{
	Rva00C6B3F0Init()
	{
		typedef void *(Rva00C6B3F0Init::*Member)();
		union { void (*function)(); Member method; } call;
		call.function = (void (*)())j_0001ea83;
		(this->*call.method)();
	}
	~Rva00C6B3F0Init();
};

struct Rva00C6B450Init
{
	Rva00C6B450Init()
	{
		typedef void *(Rva00C6B450Init::*Member)();
		union { void (*function)(); Member method; } call;
		call.function = (void (*)())j_0003493c;
		(this->*call.method)();
	}
	~Rva00C6B450Init();
};

struct Rva00C6B4E0Init
{
	Rva00C6B4E0Init()
	{
		typedef void *(Rva00C6B4E0Init::*Member)();
		union { void (*function)(); Member method; } call;
		call.function = (void (*)())j_0001221f;
		(this->*call.method)();
	}
	~Rva00C6B4E0Init();
};

struct Rva00C6B840Init
{
	Rva00C6B840Init()
	{
		typedef void *(Rva00C6B840Init::*Member)();
		union { void (*function)(); Member method; } call;
		call.function = (void (*)())j_0003dcb2;
		(this->*call.method)();
	}
	~Rva00C6B840Init();
};

struct Rva00C6B860Init
{
	Rva00C6B860Init()
	{
		typedef void *(Rva00C6B860Init::*Member)();
		union { void (*function)(); Member method; } call;
		call.function = (void (*)())j_00027c7d;
		(this->*call.method)();
	}
	~Rva00C6B860Init();
};

struct Rva00C6B880Init
{
	Rva00C6B880Init()
	{
		typedef void *(Rva00C6B880Init::*Member)();
		union { void (*function)(); Member method; } call;
		call.function = (void (*)())j_0000f632;
		(this->*call.method)();
	}
	~Rva00C6B880Init();
};

struct Rva00C6B8A0Init
{
	Rva00C6B8A0Init()
	{
		typedef void *(Rva00C6B8A0Init::*Member)();
		union { void (*function)(); Member method; } call;
		call.function = (void (*)())j_0001dd8b;
		(this->*call.method)();
	}
	~Rva00C6B8A0Init();
};

struct Rva00C6B900Init
{
	Rva00C6B900Init()
	{
		typedef void *(Rva00C6B900Init::*Member)();
		union { void (*function)(); Member method; } call;
		call.function = (void (*)())j_00017bd9;
		(this->*call.method)();
	}
	~Rva00C6B900Init();
};

Rva00C6B390Init g_rva012F1050;
Rva00C6B3D0Init g_rva012F10DC;
Rva00C6B3F0Init g_rva012F10F4;
Rva00C6B3F0Init g_rva012F10F8;
Rva00C6B450Init g_rva012F1108;
Rva00C6B450Init g_rva012F1198;
Rva00C6B4E0Init g_rva012F1404;
Rva00C6B840Init g_rva012F1990;
Rva00C6B860Init g_rva012F19A4;
Rva00C6B880Init g_rva012F19B8;
Rva00C6B8A0Init g_rva012F19CC;
Rva00C6B900Init g_rva012F2570;
Rva00C6B900Init g_rva012F2578;
