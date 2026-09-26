// Seven __thiscall members that walk a NULL-terminated array of object
// pointers and make one virtual call on each element.
//
//     push esi
//     mov  esi,[ecx+0x150]      ; the array base, LOADED -- a pointer member
//     mov  ecx,[esi]
//     test ecx,ecx / je end
//     lea  ecx,[ecx]            ; 3-byte alignment nop, not source
//     mov  eax,[ecx] / call [eax+<SLOT>]
//     mov  ecx,[esi+4] / add esi,4
//     test ecx,ecx / jne loop
//   end:
//     pop esi / ret
//
// WHAT THE BYTES SHOW.  `mov esi,[ecx+0x150]` READS a dword out of the object,
// so the array is reached through a stored pointer; an array living inside the
// object would be `lea esi,[ecx+0x150]`.  The guard is `test ecx,ecx` on the
// FIRST element before the loop and again on the NEXT element at the bottom,
// which is the rotated form of `while (*it) { ...; ++it; }` -- the terminator
// is a null pointer, not a count, so no trip count is computed anywhere.
// `call dword ptr [eax+SLOT]` after `mov eax,[ecx]` is a virtual call through
// the element's own vftable: no REL32, so no callee pin and no identity.
//
// ONE AXIS, READ DIRECTLY: the vftable slot.  Seven members, seven distinct
// slots (0x1C, 0x2C, 0x30, 0x34, 0x64, 0x90, 0xD8), one array offset (0x150),
// one element type.  Nothing here distinguishes a `while` from the equivalent
// `for`; both compile to these bytes.
//
// IDENTITY IS NOT RECOVERED.  The element class is spelled as fifty-five
// declared-only virtuals purely so that the slot arithmetic lands where the
// bytes say; the count, the names and the signatures are NOT evidence -- only
// the seven called slots are.  Each caller is its own class because the bytes
// cannot show that these seven functions belong to one type; the shared 0x150
// is suggestive and nothing more.

class Rva004116C0Element
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54();
};

#define BFME_VIRTUAL_BROADCAST( NAME, SLOT )                              \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void broadcast();                                                 \
		char m_lead[0x150];                                               \
		Rva004116C0Element **m_list;                                      \
	};                                                                    \
	void NAME::broadcast()                                                \
	{                                                                     \
		Rva004116C0Element **it = m_list;                                 \
		while ( *it )                                                     \
		{                                                                 \
			(*it)->SLOT();                                                \
			++it;                                                         \
		}                                                                 \
	}

BFME_VIRTUAL_BROADCAST( Rva004116C0, v07 )   // slot 0x1C
BFME_VIRTUAL_BROADCAST( Rva00411700, v36 )   // slot 0x90
BFME_VIRTUAL_BROADCAST( Rva00412500, v13 )   // slot 0x34
BFME_VIRTUAL_BROADCAST( Rva00414140, v11 )   // slot 0x2C
BFME_VIRTUAL_BROADCAST( Rva00414170, v12 )   // slot 0x30
BFME_VIRTUAL_BROADCAST( Rva004141C0, v25 )   // slot 0x64
BFME_VIRTUAL_BROADCAST( Rva00414930, v54 )   // slot 0xD8
