// Rva003BF540::applyOwner, retail RVA 0x003BF190.
// partial score=0.9 date=2026-09-11

typedef bool Bool;
typedef unsigned short WideChar;

template <typename T>
class StringBase
{
public:
	void set(const StringBase<T> &source);
	void releaseBuffer();
	Bool isEmpty() const;

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString *copyFrom(const AsciiString &source)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&source);
		return this;
	}

	AsciiString &operator=(const char *source);

	Bool isEmpty() const
	{
		return ((const StringBase<char> *)this)->isEmpty();
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
};

class Rva003BD700String
{
public:
	void set(const Rva003BD700String &source)
	{
		((StringBase<WideChar> *)this)->set(
			*(const StringBase<WideChar> *)&source);
	}

	~Rva003BD700String()
	{
		((StringBase<WideChar> *)this)->releaseBuffer();
	}

	void *m_data;
};

class Rva003BD770String
{
public:
	~Rva003BD770String();

	void *m_data;
};

class Rva003BD770
{
public:
	~Rva003BD770();

	int m_head;
	Rva003BD700String m_text;
	int m_id;
};

class Rva003BF010Arg
{
public:
	char m_pad00[0x44];
	Bool m_at44;
};

class Gen003BD7D0Node : public Rva003BF010Arg
{
};

class Rva003BF540
{
public:
	void applyOwner(Gen003BD7D0Node *owner);
};

class Rva0060D480CampaignGate
{
};

class Gen00609320
{
};

class Rva00367E30Logic
{
};

class ControlBar
{
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual Rva003BD770String fetch(AsciiString label, Bool *exists = 0);
};

extern Rva0060D480CampaignGate *g_bfmeGameCW;
extern Gen00609320 *g_bfmeStateDF;
extern Rva00367E30Logic *TheBfmeGameLogic;
extern ControlBar *TheControlBar;
extern GameTextInterface *TheGameText;

extern void j_0000c752();
extern void j_000228db();
extern void j_0000cced();
extern void j_00025a77();
extern void j_0003d2d5();
extern void j_00043702();
extern void j_00047488();
extern void j_000485d1();
extern void j_00048c4d();
extern void j_0004958a();
extern void j_0000ea7f();
extern void j_00045c87();
extern void j_000326d2();

typedef void (Rva003BF540::*RunCall)(Rva003BF010Arg *);
typedef Bool (Rva0060D480CampaignGate::*OpenCall)() const;
typedef Bool (Rva003BF540::*AllowedCall)();
typedef Bool (Gen00609320::*DisabledCall)() const;
typedef Bool (Rva003BF540::*ReadyCall)() const;
typedef AsciiString *(Gen003BD7D0Node::*CopyCall)(AsciiString *);
typedef int (Rva00367E30Logic::*LookupCall)(AsciiString *);
typedef AsciiString *(Rva00367E30Logic::*BuildCall)(AsciiString *, void *);
typedef AsciiString &(AsciiString::*AssignCall)(const char *);
typedef Rva003BD770 *(Rva003BD770::*MessageCtor)(
	const Rva003BD700String &, int);
typedef void (ControlBar::*ShowCall)(Rva003BD770 *);

template <typename Member>
struct RawMember
{
	union
	{
		void (*raw)();
		Member member;
	};
};

static void runForOwner(Rva003BF540 *self, Rva003BF010Arg *owner)
{
	RawMember<RunCall> call;
	call.raw = j_0003d2d5;
	(self->*call.member)(owner);
}

static Bool gameIsOpen(Rva0060D480CampaignGate *game)
{
	RawMember<OpenCall> call;
	call.raw = j_000485d1;
	return (game->*call.member)();
}

static Bool ownerIsAllowed(Rva003BF540 *self)
{
	RawMember<AllowedCall> call;
	call.raw = j_00025a77;
	return (self->*call.member)();
}

static Bool gameIsDisabled(Gen00609320 *state)
{
	RawMember<DisabledCall> call;
	call.raw = j_00048c4d;
	return (state->*call.member)();
}

static Bool ownerIsReady(const Rva003BF540 *self)
{
	RawMember<ReadyCall> call;
	call.raw = j_0000ea7f;
	return (self->*call.member)();
}

static AsciiString *copyOwnerName(Gen003BD7D0Node *owner,
	AsciiString *out)
{
	RawMember<CopyCall> call;
	call.raw = j_0004958a;
	return (owner->*call.member)(out);
}

static int lookupOwner(Rva00367E30Logic *logic, AsciiString *name)
{
	RawMember<LookupCall> call;
	call.raw = j_00045c87;
	return (logic->*call.member)(name);
}

static AsciiString *buildOwner(Rva00367E30Logic *logic,
	AsciiString *out, void *name)
{
	RawMember<BuildCall> call;
	call.raw = j_000228db;
	return (logic->*call.member)(out, name);
}

static void setLabel(AsciiString *label, const char *text)
{
	RawMember<AssignCall> call;
	call.raw = j_000326d2;
	(label->*call.member)(text);
}

static Rva003BD770 *constructMessage(Rva003BD770 *message,
	const Rva003BD700String &text, int id)
{
	RawMember<MessageCtor> call;
	call.raw = j_0000cced;
	return (message->*call.member)(text, id);
}

static void showMessage(ControlBar *bar, Rva003BD770 *message)
{
	RawMember<ShowCall> call;
	call.raw = j_00043702;
	(bar->*call.member)(message);
}

// ?applyOwner@Rva003BF540@@QAEXPAVGen003BD7D0Node@@@Z
void Rva003BF540::applyOwner(Gen003BD7D0Node *owner)
{
	Rva003BF010Arg *arg = owner;
	runForOwner(this, arg);

	if (owner == 0)
		return;
	if (!gameIsOpen(g_bfmeGameCW))
		return;
	if (!ownerIsAllowed(this))
		return;
	if (gameIsDisabled(g_bfmeStateDF))
		return;
	if (ownerIsReady(this))
		return;
	if (TheControlBar == 0)
		return;

	AsciiString label;
	StringBase<char> name;
	int id = lookupOwner(TheBfmeGameLogic,
		copyOwnerName(owner, &name));
	name.releaseBuffer();
	if (id < 0)
		return;

	buildOwner(TheBfmeGameLogic, &label,
		copyOwnerName(owner, &name));
	name.releaseBuffer();
	if (!owner->m_at44)
		setLabel(&label, (const char *)0x010EDB88);
	if (label.isEmpty())
		return;

	Rva003BD700String text;
	Rva003BD770String fetched =
		TheGameText->fetch(label, 0);
	text.set(*(Rva003BD700String *)&fetched);

	Rva003BD770 message;
	constructMessage(&message, text, id);
	showMessage(TheControlBar, &message);
}
