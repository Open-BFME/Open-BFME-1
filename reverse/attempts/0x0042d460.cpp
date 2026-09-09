// ?doFXObj@BuffNuggetFXNugget@@UBEXPBVObject@@0@Z
// partial score=0.94 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// BuffNuggetFXNugget object dispatch at retail 0x0042D460.
// The BuffNugget vtable at 0x010F356C sends slot 2 through ILT 0x00033FB4
// to this body. Object slot 10 supplies the Drawable, and the five
// BfmeThingAIA questions select the six template strings from the parser.
// Fixed vs the prior 0.96 stash: the "operator->()" call at +0x010f is
// actually operator*() -- ??D?$OVERRIDE@VThingTemplate@@@@QBEPBVThingTemplate@@XZ
// at 0x00097E70 (ControlBar.cpp), not ??C.../operator-> at 0x00132830
// (Thing.cpp). rva00412530 and "rva00412530Complex" are the SAME callee
// (0x00412530, thiscall, 5 args, 2nd arg is 0 for the complex path or the
// found ThingTemplate* otherwise) -- declaring two separate extern methods
// broke both call sites' relocations. One declaration + a
// reverse/symbols.csv pin on ?rva00412530@Drawable@@QAEXHPAXHPBURGBColor@@M@Z
// -> 0x00412530 gets the exact call bytes. With both fixes this reaches the
// exact 435-byte size with ONLY register-choice diffs left (16 lines, all
// lea/push register identity in the six-branch findTemplate selector plus
// two ecx-vs-eax orderings ahead of the two rva00412530 calls) -- classified
// register-save/allocation mismatch, matching docs/argument-shuttle-register:
// tried named locals for the receiver in both declaration orders, hoisting
// the selector into one shared local+call (regressed to 430B, do not
// retry), and a /G7 sweep (regressed to 434B with a cmp/mov swap at
// +0x38, do not retry). No source reshaping moved any of the 16 register
// picks. Re-pin ?rva00412530@Drawable@@QAEXHPAXHPBURGBColor@@M@Z,0x00412530
// on the next attempt (pin_consistency: consistent) before touching the
// register-choice residue.

typedef bool Bool;
struct RGBColor
{
	float red;
	float green;
	float blue;
};

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString()
	{
		releaseBuffer();
	}

	void releaseBuffer();

	char *m_data;
};

class BfmeD975
{
public:
	char bfmeGo975D(int value);
};

class ThingTemplate : public BfmeD975
{
};

template <class T>
class OVERRIDE
{
public:
	const T *operator->() const;
	const T *operator*() const;

	T *m_overridable;
};

class Drawable
{
public:
	void rva00412530(int buffType, void *templateObject, int count,
		const RGBColor *color, float extrusion) throw();
	void forward4125F0(int slot, Bool immediately);
};

#define BFME_OBJECT_SLOT(name) virtual void name();
class Object
{
public:
	BFME_OBJECT_SLOT(v00)
	BFME_OBJECT_SLOT(v04)
	BFME_OBJECT_SLOT(v08)
	BFME_OBJECT_SLOT(v0C)
	BFME_OBJECT_SLOT(v10)
	BFME_OBJECT_SLOT(v14)
	BFME_OBJECT_SLOT(v18)
	BFME_OBJECT_SLOT(v1C)
	BFME_OBJECT_SLOT(v20)
	BFME_OBJECT_SLOT(v24)
	virtual Drawable *getDrawable() const;

	OVERRIDE<ThingTemplate> m_template;
};
#undef BFME_OBJECT_SLOT

class BfmeThingAIA
{
public:
	Bool bfmeAskAIA(int kind);
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *Rva0020AA00TheRegistry;

class FXNugget
{
public:
	virtual void v00();
	virtual void doFXPos();
};

class BuffNuggetFXNugget : public FXNugget
{
public:
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	unsigned char m_pad00B0[0xB0];
	int m_buffType;
	Bool m_isComplexBuff;
	unsigned char m_pad00B9[3];
	int m_buffLifeTime;
	AsciiString m_buffThingTemplate;
	AsciiString m_buffOrcTemplate;
	AsciiString m_buffInfantryTemplate;
	AsciiString m_buffCavalryTemplate;
	AsciiString m_buffTrollTemplate;
	AsciiString m_buffMumakilTemplate;
	float m_extrusion;
	RGBColor m_color;
};

void BuffNuggetFXNugget::doFXObj(const Object *primary, const Object *) const
{
	if (!primary)
		goto cleanup;

	Drawable *drawable = primary->getDrawable();
	if (!drawable)
		goto cleanup;

	if (m_isComplexBuff)
	{
		if (m_buffLifeTime > 0)
		{
			drawable->rva00412530(m_buffType, 0, m_buffLifeTime,
				&m_color, m_extrusion);
		}
		else
			goto forward;
		goto complete;
	}

	if (((BfmeThingAIA *)primary)->bfmeAskAIA(0x6C))
		goto cleanup;

	const ThingTemplate *found;
	if (((BfmeThingAIA *)primary)->bfmeAskAIA(9))
	{
		found = Rva0020AA00TheRegistry->findTemplate(m_buffCavalryTemplate);
	}
	else if (((BfmeThingAIA *)primary)->bfmeAskAIA(0x6B))
	{
		found = Rva0020AA00TheRegistry->findTemplate(m_buffOrcTemplate);
	}
	else if (((BfmeThingAIA *)primary)->bfmeAskAIA(8))
	{
		found = Rva0020AA00TheRegistry->findTemplate(m_buffInfantryTemplate);
	}
	else if (((BfmeThingAIA *)primary)->bfmeAskAIA(0xAE))
	{
		found = Rva0020AA00TheRegistry->findTemplate(m_buffTrollTemplate);
	}
	else
	{
		char useMumakil;
		{
			AsciiString invalidThing("INVALID_THING");
			int invalidThingAddress = (int)&invalidThing;
			useMumakil = const_cast<ThingTemplate *>(
				primary->m_template.operator*())->bfmeGo975D(
					invalidThingAddress);
		}
		if (useMumakil)
			found = Rva0020AA00TheRegistry->findTemplate(m_buffMumakilTemplate);
		else
			found = Rva0020AA00TheRegistry->findTemplate(m_buffThingTemplate);
	}

	if (!found)
		goto cleanup;
	if (m_buffLifeTime > 0)
	{
		drawable->rva00412530(m_buffType, (void *)found,
			m_buffLifeTime, &m_color, m_extrusion);
		goto complete;
	}
	goto forward;

complete:
	return;

forward:
	drawable->forward4125F0(m_buffType, false);

cleanup:
	return;
}
