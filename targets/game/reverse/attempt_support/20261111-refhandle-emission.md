# Apt reference-handle destructor emission

BFME 1 base ee250d0772; BFME 2 donor 76f0baefa6f285d54bc1ca922397674312a5913f. Reviewed donor Code/Libraries/Source/Apt/Rva006D0C60.cpp and history: counted owner destruction has the same role but different layout and allocator. No donor offset, name or body imported. Emission technique follows the reviewed donor kindof-emission-link-20261015 record.

BFME 1 prior evidence re_attempts.log entry at 0x784A70+35 describes the out-of-line destructor versus specialized Apt inline copies. In Rva00895B20Dependencies.cpp imported forceinline removes only the destructor emitter; the normal gate preserves all existing rows. COFF inspection shows no destructor symbol or new __imp_ reference. The constructor, member layout and destructor body stay unchanged.

The same trial in Rva00893030ManagerFind.cpp and Rva00895A00CreateHandle.cpp fails their unwind rows 0xC570B8 and 0xC570E8 (25 bytes); original funclets disappear and no masked-equal replacement exists. Both sources restored byte-for-byte. Suppression cannot be generalized to their EH context. Original source remains available at the base revision; the minimal failed trial adds __declspec(dllimport) __forceinline to the first destructor declaration. Normal build of the three-unit trial: 4/6 rows pass, these two fail.

Linking gain is unknown pending current dependency closure; census queue estimates are not progress. This removes one wrong COMDAT emitter, not the whole destructor family.
