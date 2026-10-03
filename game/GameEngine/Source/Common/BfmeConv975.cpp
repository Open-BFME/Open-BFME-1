// Open-BFME5 conversions.

#include "../GameLogic/command_source_type.h"

struct Coord3D;

// ILT 0x0002D6F5 reaches the protected virtual at 0x00278280.
// The caller uses a qualified call to that implementation.
class AIUpdateInterface
{
	friend class BfmeB975;

protected:
	virtual void privateMoveToPosition(const Coord3D *position, CommandSourceType commandSource);
};

struct BfmeObj975A
{
	char m_bfmePad[0x344];
	char m_bfmeFlags;
};

class BfmeA975
{
public:
	virtual void bfmeV0975();
	virtual void bfmeV1975();
	virtual void bfmeV2975();
	virtual void bfmeV3975();
	virtual void bfmeV4975();
	virtual void bfmeV5975();
	virtual void bfmeV6975();
	virtual void bfmeV7975();
	virtual void bfmeV8975();
	virtual void bfmeV9975();
	virtual void bfmeV10975();
	virtual void bfmeV11975();
	virtual void bfmeV12975();
	virtual void bfmeStart975A(BfmeObj975A *o);
	virtual void bfmeStop975A(BfmeObj975A *o);

	void bfmeGo975A(BfmeObj975A *o);
};

void BfmeA975::bfmeGo975A(BfmeObj975A *o)
{
	if (o && !(o->m_bfmeFlags & 1)) {
		bfmeStart975A(o);
		bfmeStop975A(o);
	}
}

class BfmeMgr975B
{
public:
	virtual void bfmeV0975();
	virtual void bfmeV1975();
	virtual void bfmeV2975();
	virtual void bfmeV3975();
	virtual void bfmeV4975();
	virtual void bfmeV5975();
	virtual void bfmeV6975();
	virtual void bfmeV7975();
	virtual void bfmeV8975();
	virtual void bfmeV9975();
	virtual void bfmeV10975();
	virtual void bfmeV11975();
	virtual void bfmeV12975();
	virtual void bfmeV13975();
	virtual void bfmeV14975();
	virtual void bfmeV15975();
	virtual void bfmeV16975();
	virtual void bfmeV17975();
	virtual void bfmeV18975();
	virtual void bfmeV19975();
	virtual void bfmeV20975();
	virtual void bfmeV21975();
	virtual void bfmeV22975();
	virtual void bfmeV23975();
	virtual void bfmeV24975();
	virtual void bfmeV25975();
	virtual int bfmeReady975B();
};

struct BfmeHold975B
{
	char m_bfmePad[0x1fc];
	BfmeMgr975B *m_bfmeMgr;
};

class BfmeB975
{
public:
	void bfmeGo975B(int a, int b);

	char m_bfmePad[8];
	BfmeHold975B *m_bfmeHold;
};

void BfmeB975::bfmeGo975B(int a, int b)
{
	BfmeMgr975B *m = m_bfmeHold->m_bfmeMgr;

	if (m && m->bfmeReady975B())
		reinterpret_cast<AIUpdateInterface *>(this)->AIUpdateInterface::privateMoveToPosition(
			reinterpret_cast<const Coord3D *>(a), static_cast<CommandSourceType>(b));
}

class AsciiString;

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
};

// ILTs 0x00028560 and 0x0003E80B reach these matched definitions at
// 0x00137E80 and 0x0013FE10 respectively.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

// Retail global 0x012EF1D8 is EA's ThingFactory singleton, defined once in
// Common/Thing/ThingFactory.cpp; this TU keeps only its own view of it.
class ThingFactory;

extern ThingFactory *TheThingFactory;

class BfmeD975
{
public:
	char bfmeGo975D(int a);
};

char BfmeD975::bfmeGo975D(int a)
{
	const ThingTemplate *p = reinterpret_cast<BfmeThingFactory *>(TheThingFactory)->findTemplate(
		*reinterpret_cast<const AsciiString *>(a));

	if (p)
		return reinterpret_cast<const ThingTemplate *>(this)->isEquivalentTo(p);

	return 0;
}
