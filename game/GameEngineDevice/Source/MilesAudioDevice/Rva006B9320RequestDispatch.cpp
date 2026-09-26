// ?process006B9320@Rva006B9320Owner@@QAEXPAURva006B9320Request@@PAEH@Z
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva006B9320Field
{
	char m_pad00[0x28];
	int m_field28;
	char m_pad2c[0x18];
	unsigned char m_flag44;
	char m_pad45[0x1f];
	int m_field64;
	bool check() const;
	void refresh();
	char test() const;
};

struct Rva006B9320Request
{
	int m_action;
	Rva006B9320Field *m_field;
	void *m_payload;
	char m_pad0c[4];
	unsigned char m_flag10;
	unsigned char m_flag11;
};

extern void j_00037ac9();
extern void j_0000cd01();
extern void j_00036aa7();
extern void j_00011fcc();
extern void j_00046a33();
extern void j_000147f9();
extern void j_0002d17d();
extern void j_00012c4c();
extern void j_00015fc3();
extern void j_0000578b();
extern void j_00037ce5();
extern void j_000046ab();
extern void j_0003b930();
extern void j_00017e5e();

class Rva006B9320Owner
{
public:
	void process006B9320(Rva006B9320Request *request,
		unsigned char *result, int value);

	private:
	bool validate(Rva006B9320Request *request);
	void reject(Rva006B9320Request *request);
	bool skip(Rva006B9320Request *request);
	void case0(Rva006B9320Request *request, int value);
	void case1(void *payload);
	void case2(Rva006B9320Request *request);
	void case3(Rva006B9320Request *request);
	void case4(Rva006B9320Request *request);
	void case5(int field28, int field64, int inverted);
	void case6(int field28, int field64, int inverted, int fieldState);
	void case7(int field28, int field64, int inverted);
};

void Rva006B9320Owner::process006B9320(
	Rva006B9320Request *request, unsigned char *result, int value)
{
	typedef bool (Rva006B9320Owner::*Validate)(Rva006B9320Request *);
	union
	{
		void (__cdecl *freeFunction)();
		Validate memberFunction;
	} validateCall;
	validateCall.freeFunction = ::j_00037ac9;
	if (!(this->*validateCall.memberFunction)(request))
	{
		typedef void (Rva006B9320Owner::*Reject)(Rva006B9320Request *);
		union
		{
			void (__cdecl *freeFunction)();
			Reject memberFunction;
		} rejectCall;
		rejectCall.freeFunction = ::j_0000cd01;
		(this->*rejectCall.memberFunction)(request);
		*result = 0;
		return;
	}

	if (request->m_flag11)
	{
		typedef bool (Rva006B9320Owner::*Skip)(Rva006B9320Request *);
		union
		{
			void (__cdecl *freeFunction)();
			Skip memberFunction;
		} skipCall;
		skipCall.freeFunction = ::j_00036aa7;
		if (!(this->*skipCall.memberFunction)(request))
		{
			if (request->m_action != 0 || request->m_field == 0)
				return;
			typedef bool (Rva006B9320Field::*Check)() const;
			union
			{
				void (__cdecl *freeFunction)();
				Check memberFunction;
			} checkCall;
			checkCall.freeFunction = ::j_00011fcc;
			if (!(request->m_field->*checkCall.memberFunction)())
				return;
			typedef void (Rva006B9320Field::*Refresh)();
			union
			{
				void (__cdecl *freeFunction)();
				Refresh memberFunction;
			} refreshCall;
			refreshCall.freeFunction = ::j_00046a33;
			(request->m_field->*refreshCall.memberFunction)();
			if (!(request->m_field->*checkCall.memberFunction)())
				return;
			*result = 0;
			request->m_field->m_flag44 = 1;
			return;
		}
	}

	dispatch:
	switch (request->m_action)
	{
	case 0:
	{
		typedef void (Rva006B9320Owner::*Case0)(Rva006B9320Request *, int);
		union { void (__cdecl *freeFunction)(); Case0 memberFunction; } call;
		call.freeFunction = ::j_000147f9;
		(this->*call.memberFunction)(request, value);
		break;
	}
	case 1:
	{
		typedef void (Rva006B9320Owner::*Case1)(void *);
		union { void (__cdecl *freeFunction)(); Case1 memberFunction; } call;
		call.freeFunction = ::j_0002d17d;
		(this->*call.memberFunction)(request->m_payload);
		break;
	}
	case 2:
	{
		typedef void (Rva006B9320Owner::*Case2)(Rva006B9320Request *);
		union { void (__cdecl *freeFunction)(); Case2 memberFunction; } call;
		call.freeFunction = ::j_00012c4c;
		(this->*call.memberFunction)(request);
		break;
	}
	case 3:
	{
		typedef void (Rva006B9320Owner::*Case3)(Rva006B9320Request *);
		union { void (__cdecl *freeFunction)(); Case3 memberFunction; } call;
		call.freeFunction = ::j_00015fc3;
		(this->*call.memberFunction)(request);
		break;
	}
	case 4:
	{
		typedef void (Rva006B9320Owner::*Case4)(Rva006B9320Request *);
		union { void (__cdecl *freeFunction)(); Case4 memberFunction; } call;
		call.freeFunction = ::j_0000578b;
		(this->*call.memberFunction)(request);
		break;
	}
	case 5:
	{
		Rva006B9320Field *field = request->m_field;
		typedef void (Rva006B9320Owner::*Case5)(int, int, int);
		union { void (__cdecl *freeFunction)(); Case5 memberFunction; } call;
		call.freeFunction = ::j_00037ce5;
		(this->*call.memberFunction)(field->m_field28, field->m_field64,
			!request->m_flag10);
		break;
	}
	case 6:
	{
		Rva006B9320Field *field = request->m_field;
		register int field64 = field->m_field64;
		register int field28 = field->m_field28;
		typedef char (Rva006B9320Field::*Test)() const;
		union { void (__cdecl *freeFunction)(); Test memberFunction; } testCall;
		testCall.freeFunction = ::j_000046ab;
		typedef void (Rva006B9320Owner::*Case6)(int, int, int, int);
		union { void (__cdecl *freeFunction)(); Case6 memberFunction; } caseCall;
		caseCall.freeFunction = ::j_0003b930;
		(this->*caseCall.memberFunction)(field28, field64,
			!request->m_flag10, !((field->*testCall.memberFunction)()));
		break;
	}
	case 7:
	{
		Rva006B9320Field *field = request->m_field;
		typedef void (Rva006B9320Owner::*Case7)(int, int, int);
		union { void (__cdecl *freeFunction)(); Case7 memberFunction; } call;
		call.freeFunction = ::j_00017e5e;
		(this->*call.memberFunction)(field->m_field28, field->m_field64,
			!request->m_flag10);
		break;
	}
	}
	return;
}
