/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: NameKeyGenerator.h ///////////////////////////////////////////////////////////////////////
// Created:    Michael Booth, May 2001
//						 Colin Day, May 2001
// Desc:       Name key system to translate between names and unique key ids
///////////////////////////////////////////////////////////////////////////////////////////////////

// BFME shadow shim (TU-scoped; only Common/NameKeyGenerator.cpp uses this -I path).
// Proven from retail lotrbfme.exe bytes against the ZH GeneralsMD reference:
//   - init/reset's `m_nextID = 1` store lands at retail this+0x2bf44, i.e.
//     this+8+45007*4 -- SOCKET_COUNT is NOT drifted, matches ZH exactly, and
//     m_sockets starts at [this+8] (right after the inherited SubsystemInterface
//     vtable ptr (+0) and SubsystemInterface::m_name (+4)).
//   - nameToKey(const AsciiString&)@0x4a1dd is a real out-of-line retail body
//     (dereferences the AsciiString, +8 to the char buffer per the established
//     AsciiString ABI, or a literal empty string) that tail-jumps into
//     nameToKey(const char*) -- so retail did NOT inline this overload the way
//     the ZH header's in-class body implies; declare it out-of-line here so
//     Common/NameKeyGenerator.cpp can define a matching standalone body.
//   - keyToName(NameKeyType) and nameToKey(const char*) also drift (retail adds
//     an unidentified auxiliary key->Bucket index structure after m_sockets/
//     m_nextID); those two are NOT covered by this shim and stay unconverted.

#pragma once

#ifndef __NAMEKEYGENERATOR_H_
#define __NAMEKEYGENERATOR_H_

#include "Lib/BaseType.h"
#include "Common/SubsystemInterface.h"
#include "Common/GameMemory.h"
#include "Common/AsciiString.h"
#include "Common/STLTypedefs.h"		// BFME-only: rts::hash<NameKeyType>/rts::equal_to<NameKeyType> + <hash_map>, for the aux key->Bucket index below

//-------------------------------------------------------------------------------------------------
/**
	Note that NameKeyType isn't a "real" enum, but an enum type used to enforce the
	fact that NameKeys are really magic cookies, and aren't really interchangeable
	with ints. NAMEKEY_INVALID is always a legal value, but all other values are dynamically
	determined at runtime. (The generated code is basically identical, of course.)
*/
//-------------------------------------------------------------------------------------------------
enum NameKeyType
{
	NAMEKEY_INVALID					= 0,
	NAMEKEY_MAX							= 1<<23,					// max ordinal value of a NameKey (some code relies on these fitting into 24 bits safely)
	FORCE_NAMEKEYTYPE_LONG	= 0x7fffffff	// a trick to ensure the NameKeyType is a 32-bit int
};

//-------------------------------------------------------------------------------------------------
/** A bucket entry for the name key generator */
//-------------------------------------------------------------------------------------------------
// BFME: NOT a MemoryPoolObject. Retail's freeSockets/keyToName/nameToKey bodies
// (0x8FCE0/0x8FD30/0x8FFC0) delete/construct Bucket with a SINGLE virtual call
// (`push 1; call [vtbl]`) with no separate getObjectMemoryPool() virtual call --
// i.e. plain `delete b;` through a lone virtual dtor slot, not
// MemoryPoolObject::deleteInstance()'s getObjectMemoryPool()+dtor+freeBlock 3-call
// sequence. Matches the already-documented BFME model (this file's own
// MP_GLUE_ALLOCATE comment: "BFME's retail exe has no pool-backed allocations at
// newInstance sites") and the DisplayString precedent (reference/shims/displaystring)
// of retail dropping MEMORY_POOL_GLUE's extra getObjectMemoryPool vtable slot.
// Keep the already-matched placement operator new/delete (??2Bucket/??3Bucket,
// 14B/12B) verbatim -- only the base class + the extra virtual are dropped.
class Bucket
{
public:

	enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED = 0 };

	inline void *operator new(size_t s, BucketMagicEnum e)
	{
		return ::operator new(s);
	}
	inline void operator delete(void *p, BucketMagicEnum e)
	{
		::operator delete(p);
	}

	Bucket();
	virtual ~Bucket();

	Bucket				*m_nextInSocket;
	NameKeyType		m_key;
	AsciiString		m_nameString;
};

inline Bucket::Bucket() : m_nextInSocket(NULL), m_key(NAMEKEY_INVALID) { }
inline Bucket::~Bucket() { }

//-------------------------------------------------------------------------------------------------
/** This class implements the conversion of an arbitrary string into a unique
	* integer "key". Calling the nameToKey() method with the same string is
	* guaranteed to return the same key. Also, all keys generated by an
	* instance of this class are guaranteed to be unique with respect to that
	* instance's catalog of names.  Multiple instances of this class can be
	* created to service multiple namespaces. */
//-------------------------------------------------------------------------------------------------
class NameKeyGenerator : public SubsystemInterface
{

public:

	NameKeyGenerator();
	virtual ~NameKeyGenerator();

	virtual void init();
	virtual void reset();
	virtual void update() { }

	/// Given a string, convert into a unique integer key.
	// BFME: retail has a standalone out-of-line body for this overload (see
	// shim header comment above) -- declare only, define out-of-line in the .cpp.
	NameKeyType nameToKey(const AsciiString& name);
	NameKeyType nameToLowercaseKey(const AsciiString& name) { return nameToLowercaseKey(name.str()); }

	/// Given a string, convert into a unique integer key.
	NameKeyType nameToKey(const char* name);
	NameKeyType nameToLowercaseKey(const char *name);

	/**
		given a key, return the name. this is almost never needed,
		except for a few rare cases like object serialization. also
		note that it's not particularly fast; it does a dumb linear
		search for the key.
	*/
	AsciiString keyToName(NameKeyType key);

  // Get a string out of the INI. Store it into a NameKeyType
  static void parseStringAsNameKeyType( INI *ini, void *instance, void *store, const void* userData );

private:

	enum
	{
		// Proven byte-exact via NameKeyGenerator::init/reset's `m_nextID = 1` store
		// (retail offset this+0x2bf44 == this+8+45007*4): SOCKET_COUNT is NOT
		// drifted in BFME, matches the ZH reference exactly.
		SOCKET_COUNT = 45007
	};

	void freeSockets();

	Bucket*				m_sockets[SOCKET_COUNT];			///< Catalog of all Buckets already generated
	UnsignedInt		m_nextID;											///< Next available ID

	// BFME-only O(1) reverse key->Bucket index (this+0x2bf48, right after m_nextID;
	// NO ZH equivalent). Proven from retail bytes: ctor (0x90380) placement-constructs
	// it via a helper at 0x8FF00 that is textually std::hash_map's default ctor
	// (_M_ht(100,...) -- pushes literal 100); freeSockets (0x8FCE0) tail-jumps into
	// its clear() (0x8f880: per-bucket node delete + zero + m_num_elements=0, exactly
	// stl/_hashtable.c's hashtable<>::clear(), never frees the bucket vector's own
	// buffer); keyToName (0x8FD30) inlines hashtable<>::_M_find's `_M_hash(k) %
	// buckets.size()` bucket-array walk with NO separate hash call (matches
	// rts::hash<NameKeyType> forwarding to the identity std::hash<UnsignedInt>);
	// nameToKey(const char*) (0x8FFC0) calls resize(count+1) then insert_unique_noresize
	// (0x8FB70/0x8FAB0), i.e. hash_map::insert(value_type(key,bucket)). Node layout
	// {next@0,key@4,Bucket*@8}=0xC matches _Hashtable_node<pair<const NameKeyType,Bucket*>>
	// exactly; struct sizeof=0x14 (3-word vector<void*> bucket array @+4/+8/+0xc,
	// flanked by the empty hasher/equal/get_key functors folded into the leading 4B
	// and the num_elements counter trailing @+0x10) matches STLport's hashtable<> member
	// order (_M_hash,_M_equals,_M_get_key,_M_buckets,_M_num_elements) exactly.
	//
	// It is modeled as raw storage rather than a real hash_map member because the
	// ALREADY-MATCHED clean-C++ ~NameKeyGenerator (0x168710, 79B) is just
	// freeSockets() with no member-dtor call -- a normal hash_map member would force
	// the compiler to emit an implicit ~hash_map() call there and grow the dtor past
	// 79B. Retail leaks the bucket-vector buffer at destruction (never observed being
	// freed anywhere); this storage does too, by construction. Same technique as
	// WWDebug/wwmemlog.cpp's `char _MemLogCriticalSectionHandle[sizeof(CRITICAL_SECTION)]`.
	typedef std::hash_map<NameKeyType, Bucket*, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > KeyToBucketMap;
	UnsignedInt		m_keyToBucketStorage[(sizeof(KeyToBucketMap) + sizeof(UnsignedInt) - 1) / sizeof(UnsignedInt)];
	KeyToBucketMap& keyToBucketMap() { return *reinterpret_cast<KeyToBucketMap*>(m_keyToBucketStorage); }

};  // end class NameKeyGenerator

//-------------------------------------------------------------------------------------------------
//           Externals
//-------------------------------------------------------------------------------------------------
extern NameKeyGenerator *TheNameKeyGenerator;  ///< just one namespace for now

// typing "TheNameKeyGenerator->nameToKey()" is awfully wordy. Here are shorter synonyms:
inline NameKeyType NAMEKEY(const AsciiString& name) { return TheNameKeyGenerator->nameToKey(name); }
inline NameKeyType NAMEKEY(const char* name) { return TheNameKeyGenerator->nameToKey(name); }

inline AsciiString KEYNAME(NameKeyType nk) { return TheNameKeyGenerator->keyToName(nk); }

//-------------------------------------------------------------------------------------------------
class StaticNameKey
{
private:
	mutable NameKeyType m_key;
	const char* m_name;
public:
	StaticNameKey(const char* p) : m_key(NAMEKEY_INVALID), m_name(p) {}
	NameKeyType key() const;
	// ugh, this is a little hokey, but lets us pretend that a StaticNameKey == NameKeyType
	inline operator NameKeyType() const { return key(); }
};

#endif // __NAMEKEYGENERATOR_H_
