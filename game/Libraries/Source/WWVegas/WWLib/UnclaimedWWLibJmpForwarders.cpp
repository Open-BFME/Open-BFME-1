// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
//
// Seventeen unreferenced 5-byte WWLib forwarders: each is a lone `jmp rel32`
// after int3 padding, and no call, jump, ILT entry, table slot or code
// immediate in the image reaches its address. They are the shape of the
// MultiListClass<T> inline wrappers (Add/Add_Tail/Add_After/Remove/
// Remove_Head forward to the GenericMultiListClass Internal_* members with the
// same arguments, so VC7.1 emits a tail jmp) and of a Random3Class /
// Random4Class call forwarder. The jump targets are read off the retail bytes
// and every one is a matched row.
//
// IDENTITY IS NOT RECOVERED: the template argument of each MultiListClass
// wrapper does not show in the bytes, so every name is derived from the
// forwarder's own address.
#include "multilist.h"
#include "random.h"

#define BFME_MULTILIST_FORWARDERS( NAME )                                    \
	class NAME : public GenericMultiListClass                                \
	{                                                                        \
	public:                                                                  \
		bool add( MultiListObjectClass *obj, bool onlyonce );                \
		bool addTail( MultiListObjectClass *obj, bool onlyonce );            \
		bool addAfter( MultiListObjectClass *obj,                            \
			const MultiListObjectClass *existing, bool onlyonce );           \
		bool remove( MultiListObjectClass *obj );                            \
		MultiListObjectClass *removeHead();                                  \
	};

BFME_MULTILIST_FORWARDERS( Rva00944C90MultiList )
BFME_MULTILIST_FORWARDERS( Rva00944D30MultiList )
BFME_MULTILIST_FORWARDERS( Rva00944DF0MultiList )
BFME_MULTILIST_FORWARDERS( Rva00944E70MultiList )

bool Rva00944C90MultiList::add( MultiListObjectClass *obj, bool onlyonce ) { return Internal_Add( obj, onlyonce ); }
bool Rva00944C90MultiList::addTail( MultiListObjectClass *obj, bool onlyonce ) { return Internal_Add_Tail( obj, onlyonce ); }
bool Rva00944C90MultiList::addAfter( MultiListObjectClass *obj, const MultiListObjectClass *existing, bool onlyonce ) { return Internal_Add_After( obj, existing, onlyonce ); }
bool Rva00944C90MultiList::remove( MultiListObjectClass *obj ) { return Internal_Remove( obj ); }
MultiListObjectClass *Rva00944C90MultiList::removeHead() { return Internal_Remove_List_Head(); }

bool Rva00944D30MultiList::add( MultiListObjectClass *obj, bool onlyonce ) { return Internal_Add( obj, onlyonce ); }
bool Rva00944D30MultiList::addTail( MultiListObjectClass *obj, bool onlyonce ) { return Internal_Add_Tail( obj, onlyonce ); }
bool Rva00944D30MultiList::addAfter( MultiListObjectClass *obj, const MultiListObjectClass *existing, bool onlyonce ) { return Internal_Add_After( obj, existing, onlyonce ); }
bool Rva00944D30MultiList::remove( MultiListObjectClass *obj ) { return Internal_Remove( obj ); }
MultiListObjectClass *Rva00944D30MultiList::removeHead() { return Internal_Remove_List_Head(); }

bool Rva00944DF0MultiList::addTail( MultiListObjectClass *obj, bool onlyonce ) { return Internal_Add_Tail( obj, onlyonce ); }
MultiListObjectClass *Rva00944DF0MultiList::removeHead() { return Internal_Remove_List_Head(); }

bool Rva00944E70MultiList::add( MultiListObjectClass *obj, bool onlyonce ) { return Internal_Add( obj, onlyonce ); }
bool Rva00944E70MultiList::remove( MultiListObjectClass *obj ) { return Internal_Remove( obj ); }
MultiListObjectClass *Rva00944E70MultiList::removeHead() { return Internal_Remove_List_Head(); }

class Rva0095C6D0Random { public: int draw(); };
int Rva0095C6D0Random::draw() { return ( *reinterpret_cast<Random3Class *>( this ) )(); }

class Rva00984710Random { public: int draw(); };
int Rva00984710Random::draw() { return ( *reinterpret_cast<Random4Class *>( this ) )(); }
