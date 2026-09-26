// ?handle@Gen00269C50@@QAEXI@Z
// partial score=0.13 date=2026-09-17
// ?handle@Gen00269C50@@QAEXI@Z
// Retail 0x00269C50 / 1073 bytes.  The four interface wrappers and the
// -0x10 adjustor tail prove this address is their shared finish body, but the
// original semantic owner is not proven.  Keep the address-derived owner and
// method while preserving the observed data and filter contracts.
//
// This is a mechanical reconstruction of the body contract: module data is
// read through +0x1D0..+0x20B, the owner carries data/object at +4/+8, four
// partition-filter records install the witnessed vtables, and the result
// wrapper is reference-counted at +0x10.  The printed j_* names below are the
// only names accepted for the anonymous direct callees.

// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum DisabledType
{
	Rva00269C50DisabledType = 3
};

class Object
{
public:
	void setDisabledUntil( DisabledType, UnsignedInt );
};

class Rva00269C50Player
{
};

class Rva00269C50Update
{
};

class Rva00269C50Mode
{
};

class Rva00269C50Unknown
{
};

struct Rva00269C50IteratorNode
{
	Rva00269C50IteratorNode *next;
	unsigned char pad04[4];
	void *object;
};

struct Rva00269C50Iterator
{
	void *vtable;
	Rva00269C50IteratorNode *head;
};

struct BfmeWideResult
{
	void *value;
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(
		int, int, int, int, int );
};

struct Rva009F3C70Result
{
	void *value;
	void append( int, int );
};

struct Rva00269C50Filter
{
	void *vtable;
	Rva00269C50Filter *next;
	void *field08;
	void *field0c;
	void *field10;
};

struct Rva00269C50Data
{
	unsigned char bytes[0x20c];
};

extern void j_00001a73( void );
extern void j_000022bb( void );
extern void j_0000d3b9( void );
extern void j_0000e68d( void );
extern void j_00011f77( void );
extern void j_0001677f( void );
extern void j_0001bb21( void );
extern void j_0001f505( void );
extern void j_00020824( void );
extern void j_00022bba( void );
extern void j_0002739f( void );
extern void j_0002852e( void );
extern void j_0002923a( void );
extern void j_0003251f( void );
extern void j_0003682c( void );
extern void j_00046c13( void );
extern void j_00048c61( void );
extern void j_0009f2ae0( void );
extern void __ftol2( void );

namespace _STL
{
	template <bool Threads, int Instance>
	class __node_alloc
	{
	public:
		static void _M_deallocate( void *, unsigned int );
	};
}

void __cdecl operator delete( void * );

class Gen00269C50;

typedef void (Gen00269C50::*Rva00269C50ArgCall)( UnsignedInt );
typedef void *(Object::*Rva00269C50ObjectGet)( void );
typedef void (Object::*Rva00269C50ObjectNoArg)( void );
typedef Rva00269C50Iterator *(Object::*Rva00269C50ObjectIterator)( void );
typedef void (Object::*Rva00269C50ObjectTwoInt)( int, int );
typedef Bool (Object::*Rva00269C50ObjectOneInt)( int );
typedef void (Rva00269C50Player::*Rva00269C50PlayerOneInt)( int );
typedef void *(Rva00269C50Player::*Rva00269C50PlayerNoArg)( void );
typedef void (Rva00269C50Update::*Rva00269C50UpdateFourInt)(
	UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt );
typedef Bool (Rva00269C50Update::*Rva00269C50UpdateNoArgBool)( void );
typedef void (Rva00269C50Update::*Rva00269C50UpdateObject)(
	Object *, UnsignedInt );
typedef void (Rva00269C50Mode::*Rva00269C50ModeNoArg)( void );
typedef void (Rva00269C50Mode::*Rva00269C50ModeFiveInt)(
	int, int, int, int, int );
typedef Rva00269C50Filter *(Rva00269C50Filter::*Rva00269C50Link)(
	Rva00269C50Filter * );
typedef void (Rva00269C50Filter::*Rva00269C50FilterInit)(
	BfmeWideResult * );
typedef void (Gen00269C50::*Rva00269C50ResultCall)(
	Rva009F3C70Result * );
typedef void (Rva00269C50Iterator::*Rva00269C50IteratorDestroy)( void );

class Gen00269C50
{
public:
	void handle( UnsignedInt );
};

void Gen00269C50::handle( UnsignedInt argument )
{
	unsigned char *self = (unsigned char *)this;
	Rva00269C50Data *data = *(Rva00269C50Data **)(self + 4);
	Object *object = *(Object **)(self + 8);

	union
	{
		void (*raw)( void );
		Rva00269C50ArgCall member;
	} initialCall;
	initialCall.raw = j_00046c13;
	(this->*initialCall.member)( argument );

	initialCall.raw = j_0002739f;
	(this->*initialCall.member)( argument );

	if (*(unsigned char *)((unsigned char *)data + 0x0c) == 0)
	{
		unsigned char *virtualObject = *(unsigned char **)(self + 0x10);
		if (virtualObject != 0)
		{
			void (**vtable)( void ) = *(void (***)( void ))virtualObject;
			void (*call)( void ) = vtable[0x40 / sizeof(void *)];
			call();
		}
	}

	union
	{
		void (*raw)( void );
		Rva00269C50ObjectGet member;
	} objectGet;
	objectGet.raw = j_00020824;
	void *objectResult = (object->*objectGet.member)();
	if (objectResult != 0)
	{
		Rva00269C50Player *player =
			*(Rva00269C50Player **)((unsigned char *)data + 8);
		if (player != 0)
		{
			union
			{
				void (*raw)( void );
				Rva00269C50PlayerNoArg member;
			} playerCall;
			playerCall.raw = j_00048c61;
			void *playerResult = (player->*playerCall.member)();
			if (playerResult != 0)
			{
				union
				{
					void (*raw)( void );
					Rva00269C50PlayerOneInt member;
				} playerAdjust;
				playerAdjust.raw = j_00001a73;
				(player->*playerAdjust.member)(
					*(int *)((unsigned char *)objectResult + 0x20) );
			}
		}
	}

	Rva00269C50Data *powerData = data;
	int powerFrame = *(int *)((unsigned char *)powerData + 0x1fc);
	if (powerFrame != -1 &&
		*(Real *)((unsigned char *)powerData + 0x200) !=
			*(const Real *)0x01075350)
	{
		Real scaled = *(Real *)((unsigned char *)powerData + 0x200) *
			*(const Real *)0x01075344;
		int delta = (int)scaled;
		union
		{
			void (*raw)( void );
			Rva00269C50ObjectTwoInt member;
		} objectPair;
		objectPair.raw = j_0002852e;
		(object->*objectPair.member)( powerFrame, delta );

		if (*(unsigned char *)((unsigned char *)powerData + 0x208) != 0)
		{
			UnsignedInt frame =
				*(UnsignedInt *)(*(unsigned char **)0x012f0898 + 0x3c) +
				(UnsignedInt)delta;
			object->setDisabledUntil(
				Rva00269C50DisabledType, frame );
		}
	}

	Rva00269C50Update *update =
		*(Rva00269C50Update **)((unsigned char *)powerData + 0x1f4);
	if (update != 0)
	{
		union
		{
			void (*raw)( void );
			Rva00269C50UpdateNoArgBool member;
		} updateReady;
		updateReady.raw = j_00011f77;
		if (!argument)
		{
			if (! (update->*updateReady.member)())
			{
				union
				{
					void (*raw)( void );
					Rva00269C50UpdateFourInt member;
				} updateFour;
				updateFour.raw = j_0001bb21;
				(update->*updateFour.member)( argument, 0, 0, 0 );
			}
		}
		else if (! (update->*updateReady.member)())
		{
			union
			{
				void (*raw)( void );
				Rva00269C50UpdateObject member;
			} updateObject;
			updateObject.raw = j_00022bba;
			(update->*updateObject.member)( object, 0 );
		}
	}

	if (*(unsigned char *)((unsigned char *)powerData + 0x1e4) == 0)
		goto finish;

	if (*(unsigned char *)((unsigned char *)powerData + 0x1ee) != 0)
	{
		Rva00269C50Mode *mode = *(Rva00269C50Mode **)0x012f0fe0;
		union
		{
			void (*raw)( void );
			Rva00269C50ModeNoArg member;
		} modeReset;
		modeReset.raw = j_0003682c;
		(mode->*modeReset.member)();
		goto finish;
	}

	{
		int kind = 0;
		if (*(unsigned char *)((unsigned char *)powerData + 0x20b) != 0)
			kind = 1;
		else if (*(unsigned char *)((unsigned char *)powerData + 0x20a) != 0)
			kind = 2;
		else
			kind = 3;

		Rva00269C50Mode *mode = *(Rva00269C50Mode **)0x012f0fe0;
		union
		{
			void (*raw)( void );
			Rva00269C50ModeFiveInt member;
		} modeCall;
		modeCall.raw = j_0002923a;
		(mode->*modeCall.member)(
			kind,
			*(int *)((unsigned char *)powerData + 0x1e8),
			argument,
			(int)((unsigned char *)powerData + 0x1d0),
			(int)((unsigned char *)powerData + 0x1dc) );
	}

finish:
	{
		Coord3D location;
		if (argument != 0)
		{
			location = *(const Coord3D *)argument;
		}
		else
		{
			location.x = *(Real *)((unsigned char *)object + 0x38);
			location.y = *(Real *)((unsigned char *)object + 0x3c);
			location.z = *(Real *)((unsigned char *)object + 0x40);
		}

		int filterMode = 4;
		if (*(unsigned char *)((unsigned char *)powerData + 0x1ec) != 0)
			filterMode = 1;
		else if (*(unsigned char *)((unsigned char *)powerData + 0x1ed) != 0)
			filterMode = 7;
		else if (*(unsigned char *)((unsigned char *)powerData + 0x1ee) != 0)
			filterMode = 5;

		union
		{
			void (*raw)( void );
			Rva00269C50ObjectGet member;
		} objectAgain;
		objectAgain.raw = j_00020824;
		(object->*objectAgain.member)();

		Rva00269C50Filter relationship;
		Rva00269C50Filter root;
		Rva00269C50Filter objectFilter;
		Rva00269C50Filter rj;
		relationship.vtable = (void *)0x010a5158;
		relationship.next = 0;
		relationship.field08 = (void *)((unsigned char *)powerData + 0x1dc);
		relationship.field0c = object;
		relationship.field10 = (void *)(unsigned int)filterMode;
		root.vtable = (void *)0x01083b80;
		root.next = 0;
		root.field08 = 0;
		root.field0c = 0;
		root.field10 = 0;
		objectFilter.vtable = (void *)0x01085dd0;
		objectFilter.next = 0;
		objectFilter.field08 = object;
		objectFilter.field0c = 0;
		objectFilter.field10 = 0;
		rj.vtable = (void *)0x01085dc0;
		rj.next = 0;
		rj.field08 = object;
		rj.field0c = (void *)filterMode;
		rj.field10 = (void *)1;

		union
		{
			void (*raw)( void );
			Rva00269C50Link member;
		} link;
		link.raw = j_0009f2ae0;
		Rva00269C50Filter *head =
			(rj.*link.member)( &objectFilter );
		head = (objectFilter.*link.member)( &root );
		head = (root.*link.member)( head );

		BfmeWideResult wide;
		BfmeWideForwardC *partition =
			*(BfmeWideForwardC **)0x012ed5b8;
		wide = partition->bfmeForwardWideC(
			(int)((unsigned char *)powerData + 0x1d4),
			0, (int)&location, 1, (int)head );

		Rva009F3C70Result result;
		result.value = 0;
		if (*(unsigned char *)((unsigned char *)powerData + 0x1d8) != 0)
		{
			union
			{
				void (*raw)( void );
				Rva00269C50ObjectOneInt member;
			} objectKind;
			objectKind.raw = j_0003251f;
			if ((object->*objectKind.member)( 0x6c ))
			{
				union
				{
					void (*raw)( void );
					Rva00269C50ObjectIterator member;
				} iteratorFactory;
				iteratorFactory.raw = j_0000d3b9;
				Rva00269C50Iterator *iterator =
					(Rva00269C50Iterator *)
						(object->*iteratorFactory.member)();
				Rva00269C50IteratorNode *cursor = 0;
				if (iterator != 0)
				{
					void *vtable = *(void **)iterator;
					void (*first)( void *, Rva00269C50IteratorNode ** ) =
						*(void (**)( void *, Rva00269C50IteratorNode ** ))
							((unsigned char *)vtable + 0xf0);
					first( iterator, &cursor );
				}
				while (cursor != 0)
				{
					if (cursor->object != 0)
						result.append( (int)cursor->object, 0 );
					cursor = cursor->next;
				}
				union
				{
					void (*raw)( void );
					Rva00269C50IteratorDestroy member;
				} iteratorDestroy;
				iteratorDestroy.raw = j_0000e68d;
				(iterator->*iteratorDestroy.member)();
			}
			else
			{
				result.append( 0, 0 );
			}
		}
		else
		{
			result.append( 0, 0 );
		}

		union
		{
			void (*raw)( void );
			Rva00269C50ResultCall member;
		} consume;
		consume.raw = j_0001f505;
		(this->*consume.member)( &result );

		if (result.value != 0)
		{
			int *references = (int *)((unsigned char *)result.value + 0x10);
			--*references;
			if (*references == 0)
			{
				void *begin = *(void **)result.value;
				unsigned int bytes = *(unsigned int *)
					((unsigned char *)result.value + 8) -
					(unsigned int)begin;
				if (bytes > 0x80)
					::operator delete( begin );
				else
					_STL::__node_alloc<true, 0>::_M_deallocate(
						begin, bytes );
				::operator delete( result.value );
			}
		}
	}
}
