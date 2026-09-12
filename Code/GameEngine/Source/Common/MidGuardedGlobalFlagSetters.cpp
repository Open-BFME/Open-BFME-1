// 22 identical 22-byte __cdecl predicates:
//
//     mov eax,[<DIR32>] / test eax,eax / je +7
//     mov byte ptr [eax+<OFF>],<0|1> / mov eax,1 / ret
//
// WHAT THE BYTES SHOW.  All 22 read the SAME global pointer (0x012ED5C8), skip
// the store when it is null, and return 1 either way -- the return value does
// not report whether the store happened, so it is a fixed success code, not the
// flag.  `mov eax,1` rather than `mov al,1` proves an int-width return: a `bool`
// return of `true` compiles to `mov al,1` at 3 bytes and would be two bytes
// shorter.  The store is byte-wide, so the flag is a byte member.
//
// TWO AXES: the byte offset (22 distinct values from 0xA74 to 0x11FC) and the
// stored value (0 in three members, 1 in the other nineteen).  Because the same
// global is named by every member, one extern serves all 22 and the DIR32
// consistency check sees a single symbol resolving to a single address.
//
// THE GLOBAL IS TheWritableGlobalData.  The DIR32 is 0x012ED5C8, the same
// pointer already pinned as `GlobalData *TheWritableGlobalData` in
// T3CommandLineParsers.cpp and Rva002F08C0Set.cpp.  Function names stay
// address-derived -- they are the claimed `?Rva...@@YAHXZ` pins.  Members are
// named from the INI table at 0x00C77018 where it votes GlobalData, and as
// `m_flagXXXX` (T3's convention) where it does not.

class GlobalData
{
public:
	char m_pad_00[ 0xA74 ];
	bool m_disableCameraMovement;					///< retail this+0xA74, INI DisableCameraMovements
	char m_pad_A75[ 0xA7C - 0xA75 ];
	bool m_flagA7C;									///< retail this+0xA7C
	bool m_flagA7D;									///< retail this+0xA7D
	bool m_flagA7E;									///< retail this+0xA7E
	bool m_flagA7F;									///< retail this+0xA7F
	char m_pad_A80[ 0xA8F - 0xA80 ];
	bool m_flagA8F;									///< retail this+0xA8F, INI ShowTooltips
	char m_pad_A90[ 0xA95 - 0xA90 ];
	bool m_flagA95;									///< retail this+0xA95
	char m_pad_A96[ 0xA97 - 0xA96 ];
	bool m_flagA97;									///< retail this+0xA97
	char m_pad_A98[ 0xA9C - 0xA98 ];
	bool m_flagA9C;									///< retail this+0xA9C
	bool m_flagA9D;									///< retail this+0xA9D
	bool m_flagA9E;									///< retail this+0xA9E
	bool m_flagA9F;									///< retail this+0xA9F
	bool m_flagAA0;									///< retail this+0xAA0
	char m_pad_AA1[ 0xAAC - 0xAA1 ];
	bool m_flagAAC;									///< retail this+0xAAC
	char m_pad_AAD[ 0xB7D - 0xAAD ];
	bool m_flagB7D;									///< retail this+0xB7D
	char m_pad_B7E[ 0xBC4 - 0xB7E ];
	bool m_flagBC4;									///< retail this+0xBC4
	bool m_flagBC5;									///< retail this+0xBC5
	char m_pad_BC6[ 0xC0A - 0xBC6 ];
	bool m_flagC0A;									///< retail this+0xC0A
	char m_pad_C0B[ 0xC70 - 0xC0B ];
	bool m_flagC70;									///< retail this+0xC70
	char m_pad_C71[ 0xDBC - 0xC71 ];
	bool m_flagDBC;									///< retail this+0xDBC
	char m_pad_DBD[ 0xE54 - 0xDBD ];
	bool m_flagE54;									///< retail this+0xE54, INI UseHelpTextSystem
	char m_pad_E55[ 0x11FC - 0xE55 ];
	bool m_flag11FC;									///< retail this+0x11FC
};

extern GlobalData *TheWritableGlobalData;

#define BFME_GUARDED_FLAG_SET( NAME, MEMBER, VALUE )                      \
	int NAME( void )                                                      \
	{                                                                     \
		if( TheWritableGlobalData )                                       \
			TheWritableGlobalData->MEMBER = VALUE;                        \
		return 1;                                                         \
	}

BFME_GUARDED_FLAG_SET( Rva000608E0, m_flagBC4, 0 )
BFME_GUARDED_FLAG_SET( Rva000609E0, m_flagE54, 1 )
BFME_GUARDED_FLAG_SET( Rva00060AE0, m_flagA7D, 1 )
BFME_GUARDED_FLAG_SET( Rva00060B00, m_flagA7E, 1 )
BFME_GUARDED_FLAG_SET( Rva00060D80, m_flagB7D, 1 )
BFME_GUARDED_FLAG_SET( Rva00060DA0, m_flagA7F, 0 )
BFME_GUARDED_FLAG_SET( Rva00060DC0, m_flagAAC, 1 )
BFME_GUARDED_FLAG_SET( Rva00060DE0, m_disableCameraMovement, 1 )
BFME_GUARDED_FLAG_SET( Rva00060E00, m_flagA95, 1 )
BFME_GUARDED_FLAG_SET( Rva00060E20, m_flagA97, 1 )
BFME_GUARDED_FLAG_SET( Rva00060E40, m_flagA9C, 1 )
BFME_GUARDED_FLAG_SET( Rva00060E60, m_flagA9D, 1 )
BFME_GUARDED_FLAG_SET( Rva00060E80, m_flagA9E, 1 )
BFME_GUARDED_FLAG_SET( Rva00060EA0, m_flagA9F, 1 )
BFME_GUARDED_FLAG_SET( Rva00060EC0, m_flagAA0, 1 )
BFME_GUARDED_FLAG_SET( Rva00060F20, m_flagBC5, 1 )
BFME_GUARDED_FLAG_SET( Rva00060F80, m_flagA7C, 1 )
BFME_GUARDED_FLAG_SET( Rva00060FE0, m_flagC0A, 1 )
BFME_GUARDED_FLAG_SET( Rva000610D0, m_flagC70, 1 )
BFME_GUARDED_FLAG_SET( Rva000610F0, m_flagDBC, 1 )
BFME_GUARDED_FLAG_SET( Rva00061160, m_flagA8F, 0 )
BFME_GUARDED_FLAG_SET( Rva00061560, m_flag11FC, 1 )
