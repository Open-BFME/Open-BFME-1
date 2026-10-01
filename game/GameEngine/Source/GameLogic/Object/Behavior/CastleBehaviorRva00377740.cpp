// ?Rva00377740@Rva00377740Interface@@QAEHXZ
// cl: /O2 /EHsc
//
// Retail 0x00377740, 528 bytes.
//
// Owner: the CastleBehavior constructor (0x00376250) installs vftable
// 0x010E9B28 at this+0x10. Its slot 0 is ILT 0x0001B7AC -> 0x00377740, and
// this body hands ecx = its own this-0x10 (the CastleBehavior) to every
// owner call, the same relationship the matched CastleBehavior::rva00371b00
// documents from the other side. Nothing names this method, so it keeps the
// bank's address-derived spelling.
//
// Six-state update over a countdown timer. State 0 polls, states 1-3 run the
// timed pack/unpack sequence, state 4 queries and dispatches, state 5 resets.
//
// Callees: every call goes through the retail incremental-link thunk the call
// site encodes (proven by raw image decode of each thunk's `jmp body`), using
// the member-pointer-cast pattern the matched ConstructionRecovery00373B30
// TU establishes. No pin and no second declaration is needed: each `j_` name
// already resolves to its thunk through its matched gen-small row.
//   j_00002a5f4 -> 0x00377550 (poll, returns bool)
//   j_00007969 -> 0x00373ED0
//   j_000084d6 -> 0x00376590 (bool)
//   j_00040629 -> 0x00373530 (bool)
//   j_0000a19b -> 0x00374420 (two flag records)
//   j_0000b7fd -> 0x00371B00 (matched CastleBehavior::rva00371b00, returns bool)
//   j_00026094 -> 0x00371EE0 (matched CastleBehavior::rva00371ee0, int + bool)
//   j_0003df6e -> 0x00373B30 (matched Rva00373B30Receiver::update)
//   j_000427df -> 0x00376C70
//   j_0001cd41 -> 0x00377060 (CastleBehavior::rva00377060, see identity evidence)
// The two flag locals are forty bytes each; retail zeroes them with the same
// out-of-line forty-byte zeroing constructor the matched TenWordZeroing
// Constructors TU owns (j_0000156e -> 0x001701A0), invoked here through the
// same thunk-cast pattern instead of a second class declaration.

struct Rva00377740Flags
{
	unsigned words[10];
};

struct Rva00377740Data
{
	char prefix[0x28];
	float wait28;
	float wait2c;
	float wait30;
};

struct Rva00377740Owner
{
	bool rva00377550();
	void rva00373ED0();
	void rva00376590(bool);
	void rva00373530(bool);
	void rva00374420(const Rva00377740Flags &, const Rva00377740Flags &);
	void rva00371EE0(int, bool);
	bool rva00371B00();
	void rva00376C70();
	void rva00373B30();
	void rva00377060();
};

struct Rva00377740Interface
{
	int Rva00377740();
	Rva00377740Owner *owner() { return (Rva00377740Owner *)((char *)this - 0x10); }

	char prefix[0x8c];
	int state;
	char gap90[8];
	float timer;
};

extern void j_0000156e();
extern void j_00007969();
extern void j_000084d6();
extern void j_0000a19b();
extern void j_0000b7fd();
extern void j_0001cd41();
extern void j_00026094();
extern void j_0002a5f4();
extern void j_0003df6e();
extern void j_00040629();
extern void j_000427df();

class Rva00377740Calls
{
};

template <class R>
__forceinline R call0(void (*p)(), void *self)
{
	typedef R (Rva00377740Calls::*F)();
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((Rva00377740Calls *)self)->*u.f)();
}

template <class R, class A>
__forceinline R call1(void (*p)(), void *self, A a)
{
	typedef R (Rva00377740Calls::*F)(A);
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((Rva00377740Calls *)self)->*u.f)(a);
}

template <class R, class A, class B>
__forceinline R call2(void (*p)(), void *self, A a, B b)
{
	typedef R (Rva00377740Calls::*F)(A, B);
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((Rva00377740Calls *)self)->*u.f)(a, b);
}

int Rva00377740Interface::Rva00377740()
{
	bool elapsed = false;
	Rva00377740Data *data = *(Rva00377740Data **)((char *)this - 0xc);
	if (timer > 0.0f)
	{
		timer -= 0.2f;
		if (timer < 0.0f)
		{
			timer = 0;
			elapsed = true;
		}
	}
	switch (state)
	{
	case 0:
	{
		Rva00377740Owner *p = owner();
		if (call0<bool>(j_0002a5f4, p))
			state = 4;
		call0<void>(j_00007969, p);
		return 5;
	}
	case 1:
		state = 2;
		call1<void>(j_000084d6, owner(), false);
		timer = data->wait28;
		return 1;
	case 2:
		if (data->wait28 == timer + 0.2f)
			call1<void>(j_00040629, owner(), false);
		if (elapsed)
		{
			state = 3;
			Rva00377740Flags a, b;
			call0<void>(j_0000156e, &a);
			call0<void>(j_0000156e, &b);
			b.words[6] |= 0x8000;
			a.words[6] |= 0x10000;
			call2<void, const Rva00377740Flags &, const Rva00377740Flags &>(j_0000a19b, owner(), b, a);
			timer = data->wait30;
			return 1;
		}
		break;
	case 3:
		if (elapsed)
		{
			state = 4;
			Rva00377740Flags a, b;
			call0<void>(j_0000156e, &a);
			call0<void>(j_0000156e, &b);
			b.words[6] |= 0x10000;
			Rva00377740Owner *p = owner();
			call2<void, const Rva00377740Flags &, const Rva00377740Flags &>(j_0000a19b, p, b, a);
			call2<void>(j_00026094, p, 5, false);
			return 1;
		}
		break;
	case 4:
	{
		Rva00377740Owner *p = owner();
		if (call0<bool>(j_0000b7fd, p))
			call0<void>(j_000427df, p);
		else
			call0<void>(j_0003df6e, p);
		return 1;
	}
	case 5:
		if (elapsed)
		{
			state = 0;
			call0<void>(j_0001cd41, owner());
			timer = data->wait2c;
		}
		break;
	}
	return 1;
}
