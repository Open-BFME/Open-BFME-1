// ?rva003c22e0@Rva003C2530Owner@@QAEXXZ
// partial score=0.183932 date=2026-09-23
// Address-derived GameClient update reconstruction at 0x003C2530.
// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _M_insert_overflow j_00007e96
#include <vector>
#undef _M_insert_overflow

class BfmeB1083
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	char bfmeChk1083();
	char m_pad18[ 0x19C ];
	int m_frameCounter;
};

extern BfmeB1083 *g_bfmeSwitchDR;
extern BfmeB1083 *g_bfmeGameCW;
// Retail's frame-counter owner is TheBfmeGameLogic at 0x012F0898. The final
// slot14 dispatch below uses the distinct living-world singleton at 0x012F706C.
extern BfmeB1083 *TheBfmeGameLogic;

class Gen_00609320
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual unsigned char slot50();
	virtual unsigned char slot54(); virtual void slot58(); virtual void slot5C();
	char m_pad04[ 4 ];
	unsigned char m_flag08;
};

extern Gen_00609320 *g_bfmeStateDF;
extern void setFPMode();
extern void j_000322e5();
extern void j_000309ea();
extern void j_00016dec();
extern void j_00028d08();
extern void j_00001e4c();
extern void j_0003f3c3();
extern void j_0002a64e();
extern void j_0001d688();
extern void j_00048cb6();
extern void j_00009831();
extern void j_0000d6d9();

class Rva003C2280Item
{
public:
	virtual void slot00( unsigned int );
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual bool slot10();
	virtual bool slot14( bool );
	unsigned int m_counter04;
	bool m_flag;
};

class Rva003C2530Owner
{
public:
	void update();
	void rva003c22e0();
	void prepare();
	void frameA();
	void frameB();
	void frameC();
	void frameD();
	void frameE();

private:
	char m_pad00[ 0x28 ];
	void *m_callback;
	unsigned char m_enabled;
	unsigned char m_ready;
	char m_pad2e[ 0x22 ];
	_STL::vector<Rva003C2280Item *> m_first;
	_STL::vector<Rva003C2280Item *> m_second;
	char m_pad68[ 0x10 ];
	unsigned char m_byte78;
};

class Rva003C2530Callback
{
public:
	void notify();
};

void Rva003C2530Owner::update()
{
	typedef void (Rva003C2530Owner::*OwnerCall)();
	typedef void (Rva003C2530Callback::*CallbackCall)();
	union
	{
		void (*plain)();
		OwnerCall member;
	} ownerCall;
	union
	{
		void (*plain)();
		CallbackCall member;
	} callbackCall;
	if( m_enabled )
	{
		if( g_bfmeSwitchDR != 0 )
			g_bfmeSwitchDR->slot14();

		if( TheBfmeGameLogic->bfmeChk1083() )
			return;

		ownerCall.plain = j_000322e5;
		( this->*ownerCall.member )();
		if( !m_ready )
			return;

		BfmeB1083 *game = TheBfmeGameLogic;
		int &frameCounter = game->m_frameCounter;
		if( frameCounter == 0 )
			setFPMode();
		++frameCounter;
		callbackCall.plain = j_00028d08;
		if( m_callback != 0 )
			( ( ( Rva003C2530Callback * )m_callback )->*callbackCall.member )();
		ownerCall.plain = j_00001e4c;
		( this->*ownerCall.member )();
		ownerCall.plain = j_0003f3c3;
		( this->*ownerCall.member )();
		ownerCall.plain = j_0002a64e;
		( this->*ownerCall.member )();
		ownerCall.plain = j_0001d688;
		( this->*ownerCall.member )();
		ownerCall.plain = j_00048cb6;
		( this->*ownerCall.member )();
		g_bfmeGameCW->slot14();
		--TheBfmeGameLogic->m_frameCounter;
	}
}

void Rva003C2530Owner::prepare()
{
	typedef void (BfmeB1083::*GameCall)();
	typedef void (BfmeB1083::*GameArgumentCall)(void *);
	union
	{
		void (*plain)();
		GameCall member;
	} gameCall;
	union
	{
		void (*plain)();
		GameArgumentCall member;
	} gameArgumentCall;

	if (g_bfmeStateDF->slot50())
	{
		g_bfmeStateDF->slot58();

		void *value = *(void **)((char *)m_callback + 8);
		if (value != 0)
		{
			gameArgumentCall.plain = j_000309ea;
			(g_bfmeGameCW->*gameArgumentCall.member)(value);
		}
	}

	if (g_bfmeStateDF->slot54())
	{
		g_bfmeStateDF->slot5C();
		gameCall.plain = j_00016dec;
		(g_bfmeGameCW->*gameCall.member)();
	}

	__asm
	{
		mov al, byte ptr [esi + 2Dh]
		test al, al
		mov ecx, dword ptr [g_bfmeStateDF]
		je not_ready
		mov dl, byte ptr [ecx + 8]
		test dl, dl
		jne ready
		mov byte ptr [esi + 2Dh], 0
		pop esi
		ret
	ready:
		test al, al
		jne done
	not_ready:
		mov al, byte ptr [ecx + 8]
		test al, al
		je done
		mov byte ptr [esi + 2Dh], 1
	done:
	}
}

// ?rva003c22e0@Rva003C2530Owner@@QAEXXZ
void Rva003C2530Owner::rva003c22e0()
{
	typedef unsigned ( Rva003C2280Item::*DecrementCall )();
	union
	{
		void ( *plain )();
		DecrementCall member;
	} decrementCall;
	typedef Rva003C2280Item ** ( __cdecl *FindCall )( Rva003C2280Item **, Rva003C2280Item **, Rva003C2280Item * const &, const _STL::random_access_iterator_tag & );
	union
	{
		void ( *plain )();
		FindCall typed;
	} findCall;
	_STL::vector<Rva003C2280Item *> selected;

	decrementCall.plain = j_00009831;
	findCall.plain = j_0000d6d9;
	if ( *( unsigned int * )( ( char * )g_bfmeStateDF + 4 ) == 1 && *( unsigned char * )( ( char * )g_bfmeGameCW + 0x288 ) == 0 && !m_byte78 )
	{
		for ( unsigned int i = 0; i < m_first.size(); ++i )
		{
			Rva003C2280Item *item = m_first[ i ];
			if ( ( item->m_counter04 != 0 && ( item->*decrementCall.member )() == 0 && item->slot10() ) || item->slot14( item->m_counter04 == 0 ) )
				selected.push_back( item );
		}

		for ( unsigned int i = 0; i < selected.size(); ++i )
		{
			Rva003C2280Item *item = selected[ i ];
			_STL::random_access_iterator_tag tag;
			Rva003C2280Item **found = findCall.typed( m_first.begin(), m_first.end(), item, tag );
			if ( found != m_first.end() )
			{
				if ( *found != 0 )
					( *found )->slot00( 1 );
				m_first.erase( found );
			}
		}
	}
}
