// ?dispatch@Rva003C3AE0Owner@@QAEXPAX@Z
// cl: /DNDEBUG /MD /EHsc

extern void j_0002e14a();
extern void j_00044df5();
extern void j_00013b51();
extern void j_0004115a();
extern "C" void bfmeHook1052(void);

class Rva003C3AE0Record
{
public:
	char m_pad00[ 0x14 ];
	unsigned char m_value;
};

class Rva003C3AE0Sub
{
};

class Glo012F4B98Type
{
public:
	void report( void *value, const char *text );
};

class AptPalantir;
extern AptPalantir *TheAptPalantir;

class Rva003C3AE0Owner
{
public:
	void dispatch( void *value );

private:
	char m_pad00[ 0x28 ];
	Rva003C3AE0Sub *m_sub;
	char m_pad2c[ 0x18 ];
	unsigned char m_value;
};

void Rva003C3AE0Owner::dispatch( void *value )
{
	typedef Rva003C3AE0Record *(Rva003C3AE0Sub::*Find)( void * );
	union
	{
		void (__cdecl *freeFunction)();
		Find memberFunction;
	} find;
	find.freeFunction = ::j_0002e14a;
	Rva003C3AE0Record *record = (m_sub->*find.memberFunction)( value );
	if ( record != 0 )
	{
		typedef void (Rva003C3AE0Owner::*Release)( Rva003C3AE0Record * );
		union
		{
			void (__cdecl *freeFunction)();
			Release memberFunction;
		} release;
		release.freeFunction = ::j_00044df5;
		(this->*release.memberFunction)( record );
		return;
	}

	typedef Rva003C3AE0Record *(Rva003C3AE0Owner::*Create)( void * );
	union
	{
		void (__cdecl *freeFunction)();
		Create memberFunction;
	} create;
	create.freeFunction = ::j_00013b51;
	record = (this->*create.memberFunction)( value );
	if ( record != 0 )
	{
		reinterpret_cast<Glo012F4B98Type *>(TheAptPalantir)->report( (void *)((char *)record + 0x0C), (const char *)bfmeHook1052 );
		m_value = record->m_value;

		typedef void (Rva003C3AE0Owner::*Finish)( Rva003C3AE0Record * );
		union
		{
			void (__cdecl *freeFunction)();
			Finish memberFunction;
		} finish;
		finish.freeFunction = ::j_0004115a;
		(this->*finish.memberFunction)( record );
	}
}
