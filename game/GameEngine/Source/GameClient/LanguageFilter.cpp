// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/languagefilter /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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


#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/LanguageFilter.h"
#include "Common/FileSystem.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


// BFME's `File`, as this translation unit has to see it, declared here rather
// than included.  The vendored GeneralsMD/Code/GameEngine/Include/Common/file.h
// carries MEMORY_POOL_GLUE_ABC, which declares `virtual ~File()`, on top of
// `class File : public MemoryPoolObject`, and that does not reproduce retail's
// index arithmetic: the byte-matched LanguageFilter::readWord (0x0044CB40)
// dispatches `File::read` through [vtable+0x0C], index 3, and retail 0x0044E7A0
// dispatches `close()` through [vtable+0x08], index 2.  Every index below is
// read straight out of the retail File vtables -- 0x01143AF8 (File, abstract),
// 0x01143C10 (Win32LocalFile), 0x01143C58 (RAMFile), 0x01143CA8
// (StreamingArchiveFile), 0x01143D38 (LocalFile) -- where one destructor entry
// sits at 0, ?open@File at 1, ?close@File at 2, and LocalFile's own overrides
// ?open@LocalFile, ?read@LocalFile, ?write@LocalFile, ?seek@LocalFile,
// ?nextLine@LocalFile, ?scanInt@LocalFile, ?scanReal@LocalFile,
// ?readEntireAndClose@LocalFile and ?convertToRAMFile@LocalFile land in exactly
// slots 1, 3, 4, 5, 6, 7, 8, 13 and 14.  15 and 16 are BFME's two additions,
// lock and unlock.
//
// The member offsets are retail's too, read off ?close@File@@UAEXXZ at
// 0x009CB880 (`mov al, byte ptr [esi + 0xc]` then `lea ecx, [esi + 4]`) and
// ?open@File@@UAE_NPBDH@Z at 0x009CB800, which probes the same +0xc byte: the
// AsciiString name at +0x04, m_access at +0x08, m_open at +0x0C and
// m_deleteOnClose at +0x0D.  `deleteOnClose()` is inline in ZH as well, and it
// is the one statement in init() that compiles to a store rather than a call:
// `mov byte ptr [ebp + 0xd], 1`.
//
// The `-Iinputs/reference/shims/languagefilter` directory is shared by ten
// translation units, none of which is this one, so the declaration stays here.
class AsciiString;

class File
{
public:

	enum access
	{
		NONE		= 0x00000000,
		READ		= 0x00000001,
		WRITE		= 0x00000002,
		APPEND		= 0x00000004,
		CREATE		= 0x00000008,
		TRUNCATE	= 0x00000010,
		TEXT		= 0x00000020,
		BINARY		= 0x00000040,
		READWRITE	= (READ | WRITE),
		ONLYNEW		= 0x00000080,
		STREAMING	= 0x00000100
	};

	enum seekMode
	{
		START,
		CURRENT,
		END
	};

	virtual ~File() { }														///< 0

	virtual Bool	open(const Char *filename, Int access = 0) = 0;			///< 1
	virtual void	close() = 0;												///< 2
	virtual Int		read(void *buffer, Int bytes) = 0;						///< 3
	virtual Int		write(const void *buffer, Int bytes) = 0;					///< 4
	virtual Int		seek(Int bytes, seekMode mode = CURRENT) = 0;			///< 5
	virtual void	nextLine(Char *buf = NULL, Int bufSize = 0) = 0;			///< 6
	virtual Bool	scanInt(Int &newInt) = 0;									///< 7
	virtual Bool	scanReal(Real &newReal) = 0;								///< 8
	virtual Bool	scanString(AsciiString &newString) = 0;					///< 9
	virtual Bool	print(const Char *format, ...) = 0;						///< 10
	virtual Int		size() = 0;												///< 11
	virtual Int		position() = 0;											///< 12
	virtual char*	readEntireAndClose() = 0;									///< 13
	virtual File*	convertToRAMFile() = 0;									///< 14
	virtual void	lock() = 0;												///< 15 BFME
	virtual void	unlock() = 0;												///< 16 BFME

	void	deleteOnClose()		{ m_deleteOnClose = TRUE; }

protected:
	File() : m_nameStr(0), m_access(0), m_open(FALSE), m_deleteOnClose(FALSE) { }
	File(const File &) : m_nameStr(0), m_access(0), m_open(FALSE), m_deleteOnClose(FALSE) { }

	Int				m_nameStr;			///< +0x04  an AsciiString in retail; a dword for the offset
	Int				m_access;			///< +0x08
	Bool			m_open;				///< +0x0C
	Bool			m_deleteOnClose;	///< +0x0D
};


LanguageFilter *TheLanguageFilter = NULL;

LanguageFilter::LanguageFilter() 
{
	//Modified by Saad
	//Unnecessary
	//m_wordList.clear();
}

LanguageFilter::~LanguageFilter() {
	m_wordList.clear();
}

// BFME diverges from the vendored ZH body here, and the binary says so three
// ways: it calls the zero-argument File* returner convertToRAMFile() on the
// opened file and reads through that instead, it sets the file's +0x0D
// delete-on-close byte, and it closes through a vtable slot. See the notes in
// inputs/reference/shims/languagefilter/Common/File.h for what each call site
// measures.
void LanguageFilter::init() {
	m_wordList.clear();

	// read in the file already.
	File *file1 = TheFileSystem->openFile(BadWordFileName, File::READ | File::BINARY);
	if (file1 == NULL) {
		return;
	}

	File *file2 = file1->convertToRAMFile();
	if (file2 != NULL) {
		file2->deleteOnClose();

		wchar_t word[128];
		while (readWord(file2, word)) {
			Int wordLen = wcslen(word);
			if (wordLen == 0) {
				continue;
			}
			for (Int i = 0; i < wordLen; ++i) {
				word[i] = word[i] ^ LANGUAGE_XOR_KEY;
			}
			UnicodeString uniword(word);
			unHaxor(uniword);
			//DEBUG_LOG(("Just read %ls from the bad word file.  Entered as %ls\n", word, uniword.str()));
			m_wordList[uniword] = true;
		}

		file2->close();
	}
}

void LanguageFilter::reset() {
	init();
}

void LanguageFilter::update() {
}

wchar_t ignoredChars[] = L"-_*'\"";

// LanguageFilter::filterLine: retail 0x0044DB90 lives in LanguageFilter_filterLine.cpp.

// ?unHaxor@LanguageFilter@@IAEXAAVUnicodeString@@@Z present-unmatched
void LanguageFilter::unHaxor(UnicodeString &word) {
	Int len = word.getLength();
	UnicodeString newWord(L"");
	for (Int i = 0; i < len; ++i) {
		wchar_t c = word.getCharAt(i);
		if ((c == L'p') || (c == L'P')) {
			if (((i + 1) < len) && ((word.getCharAt(i+1) == L'h') || (word.getCharAt(i+1) == L'H'))) {
				newWord.concat(L'f');
				++i; // skip the h
			} else {
				// not a problem at all.
				newWord.concat(c);
			}
		} else if (c == L'1') {
			newWord.concat(L'l');
		} else if (c == L'3') {
			newWord.concat(L'e');
		} else if (c == L'4') {
			newWord.concat(L'a');
		} else if (c == L'5') {
			newWord.concat(L's');
		} else if (c == L'6') {
			newWord.concat(L'b');
		} else if (c == L'7') {
			newWord.concat(L't');
		} else if (c == L'0') {
			newWord.concat(L'o');
		} else if (c == L'@') {
			newWord.concat(L'a');
		} else if (c == L'$') {
			newWord.concat(L's');
		} else if (c == L'+') {
			newWord.concat(L't');
		} else if (wcsrchr(ignoredChars, c) == NULL) {
			newWord.concat(c);
		}
	}
	word.set(newWord);
}

LanguageFilter * createLanguageFilter() 
{
	return NEW LanguageFilter;
}
