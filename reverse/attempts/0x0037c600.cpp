// ?bfmeStop@BfmeStopF@@QAEXXZ
// partial score=0.35 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Scratch reconstruction for the ASM-backed BfmeStopF::bfmeStop body at
// retail RVA 0x0037C600.  This file is intentionally outside Code/.

typedef unsigned char UnsignedByte;

template <typename T> class RvaStringBase
{
	protected:
	RvaStringBase() : m_data( 0 ) {}
	RvaStringBase( const RvaStringBase &other ) : m_data( other.m_data ) {}
	~RvaStringBase();
	void releaseBuffer();
	void *m_data;
};

class RvaStopString : private RvaStringBase<char>
{
public:
	RvaStopString() : RvaStringBase<char>() {}
	RvaStopString( const RvaStopString &other ) : RvaStringBase<char>( other ) {}
	~RvaStopString() {}
	void *data() const { return m_data; }
};

struct RvaStopState;
class RvaStopObject;
class RvaStopModule;

class RvaStopMap
{
	public:
	unsigned int &operator[]( void *key );

	unsigned int m_head;
	unsigned int m_count;
	unsigned int m_compare;
};

class RvaStopFxList
{
public:
	virtual void slot00();
	virtual void slot01();
};

class RvaStopObject
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
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void *slot19();

	UnsignedByte m_bfmeObjectBody[0x120];
	unsigned int m_bfmeFlags124;
	UnsignedByte m_bfmeObjectGap128[0xDC];
	RvaStopModule *m_bfmeModule;
	void apply( const RvaStopString &value, unsigned int frame );
};

class RvaStopModule
{
};

struct RvaStopState
{
	UnsignedByte m_bfmeHead[0x10];
	unsigned int m_bfme10;
	unsigned int m_bfme14;
	unsigned int m_bfme18;
	UnsignedByte m_bfmeGap1C[0x1C];
	RvaStopFxList *m_bfme38;
	unsigned int m_bfme3C;
	unsigned int m_bfme40;
	UnsignedByte m_bfme44;
	UnsignedByte m_bfmeGap45[3];
	unsigned int m_bfme48;
	unsigned int m_bfme4C;
	UnsignedByte m_bfmeGap50[0x2C];
	void *m_bfme7C;
	UnsignedByte m_bfmeGap80[0x4C];
	void *m_bfmeCC;
	RvaStopString getBridgeModelNameDamaged();
};

struct Rva00367E30Logic
{
	UnsignedByte m_bfmeHead[0x3C];
	unsigned int m_bfmeFrame;
};

#define TheBfmeGameLogic (*(Rva00367E30Logic **)0x012F0898)

extern void j_000033aa();
extern void j_00028d0d();
extern void j_0002be77();
extern void j_0001f253();
extern void j_00011f77();
extern void j_00022bba();
extern void j_000486fd();
extern void j_0001028a();
extern void j_000095ed();
extern void j_0002191d();
extern void j_00041bf0();
extern void j_00037a56();

class BfmeStopF
{
public:
	void bfmeStop();

	RvaStopObject *m_bfmeObject;
	RvaStopState *m_bfmeState;
	void *m_bfme08;
	unsigned short m_bfme0C;
	unsigned short m_bfme0E;
	unsigned int m_bfme10;
	RvaStopMap m_bfme14;
	RvaStopMap m_bfme20;
	UnsignedByte m_bfmeGap2C[4];
	unsigned int m_bfme30;
};

typedef RvaStopObject *(RvaStopObject::*RvaGetObjectCall)();
typedef RvaStopObject *(Rva00367E30Logic::*RvaFindObjectCall)( void * );
typedef bool (RvaStopFxList::*RvaFxPredicateCall)();
typedef void (RvaStopFxList::*RvaDoFxCall)( RvaStopObject *, RvaStopObject * );
typedef void (RvaStopModule::*RvaModuleCall)();
typedef void (RvaStopObject::*RvaObjectPairCall)( void *, void * );
typedef void (RvaStopObject::*RvaObjectNotifyCall)();

// ?bfmeStop@BfmeStopF@@QAEXXZ
void BfmeStopF::bfmeStop()
{
	if (m_bfmeState->m_bfme10)
	{
		m_bfme10 = TheBfmeGameLogic->m_bfmeFrame + m_bfmeState->m_bfme10;

		unsigned int frame;
		unsigned int state14 = m_bfmeState->m_bfme14;
		if (state14 && m_bfme08)
		{
			frame = TheBfmeGameLogic->m_bfmeFrame;
			m_bfme14[ &m_bfme08 ] = state14 + frame;
		}
	}

	unsigned int frame;
	unsigned int state18 = m_bfmeState->m_bfme18;
	if (state18 && m_bfme0C)
	{
		frame = TheBfmeGameLogic->m_bfmeFrame;
		m_bfme20[ &m_bfme0C ] = state18 + frame;
	}

	if (m_bfmeState->m_bfme38)
	{
		RvaStopObject *object = m_bfmeObject;
		RvaGetObjectCall getObjectCall;
		union { void *asVoid; RvaGetObjectCall asMember; } getObjectCast;
		getObjectCast.asVoid = (void *)j_0002be77;
		getObjectCall = getObjectCast.asMember;
		RvaStopObject *related = (object->*getObjectCall)();
		void *relatedValue = 0;
		if (related)
			relatedValue = related->slot19();

		RvaFindObjectCall findObjectCall;
		union { void *asVoid; RvaFindObjectCall asMember; } findObjectCast;
		findObjectCast.asVoid = (void *)j_0001f253;
		findObjectCall = findObjectCast.asMember;
		RvaStopObject *found = (TheBfmeGameLogic->*findObjectCall)( m_bfme08 );
		if ((found || !m_bfme08) && !relatedValue)
		{
			RvaFxPredicateCall predicateCall;
			union { void *asVoid; RvaFxPredicateCall asMember; } predicateCast;
			predicateCast.asVoid = (void *)j_00011f77;
			predicateCall = predicateCast.asMember;
			if (!(m_bfmeState->m_bfme38->*predicateCall)())
			{
				RvaDoFxCall doFxCall;
				union { void *asVoid; RvaDoFxCall asMember; } doFxCast;
				doFxCast.asVoid = (void *)j_00022bba;
				doFxCall = doFxCast.asMember;
				(m_bfmeState->m_bfme38->*doFxCall)( object, found );
			}
		}
	}

	RvaStopModule *module = m_bfmeObject->m_bfmeModule;
	if (module)
	{
		if (m_bfmeState->m_bfme4C > 1 && m_bfmeState->m_bfme4C <= 5)
		{
			RvaModuleCall moduleCall;
			union { void *asVoid; RvaModuleCall asMember; } moduleCast;
			moduleCast.asVoid = (void *)j_000486fd;
			moduleCall = moduleCast.asMember;
			(module->*moduleCall)();
		}

		RvaGetObjectCall getObjectCall;
		union { void *asVoid; RvaGetObjectCall asMember; } getObjectCast;
		getObjectCast.asVoid = (void *)j_0002be77;
		getObjectCall = getObjectCast.asMember;
		RvaStopObject *related = (m_bfmeObject->*getObjectCall)();
		RvaObjectPairCall applyCall;
		union { void *asVoid; RvaObjectPairCall asMember; } applyCast;
		if (related)
		{
			applyCast.asVoid = (void *)j_0001028a;
			applyCall = applyCast.asMember;
			(m_bfmeObject->*applyCall)( &m_bfmeState->m_bfme7C, &m_bfmeState->m_bfmeCC );
		}
		else
		{
			applyCast.asVoid = (void *)j_000095ed;
			applyCall = applyCast.asMember;
			(m_bfmeObject->*applyCall)( &m_bfmeState->m_bfme7C, &m_bfmeState->m_bfmeCC );
		}

		if ((m_bfmeObject->m_bfmeFlags124 & 0x40000000) != 0)
		{
			m_bfmeObject->m_bfmeFlags124 &= 0xBFFFFFFF;
			RvaObjectNotifyCall notifyCall;
			union { void *asVoid; RvaObjectNotifyCall asMember; } notifyCast;
			notifyCast.asVoid = (void *)j_0002191d;
			notifyCall = notifyCast.asMember;
			(m_bfmeObject->*notifyCall)();
		}
	}

	RvaStopString first = m_bfmeState->getBridgeModelNameDamaged();
	RvaStopString &firstResult = first;
	bool ready;
	if (firstResult.data() && *(unsigned short *)((unsigned char *)firstResult.data() + 4))
		ready = TheBfmeGameLogic->m_bfmeFrame >= m_bfmeState->m_bfme40 + m_bfme30 && m_bfmeState->m_bfme44;
	else
		ready = false;

	if (ready)
	{
		m_bfmeObject->apply( m_bfmeState->getBridgeModelNameDamaged(), m_bfmeState->m_bfme48 );
	}
}
