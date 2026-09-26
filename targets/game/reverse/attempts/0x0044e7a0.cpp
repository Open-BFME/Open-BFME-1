// ?init@LanguageFilter@@UAEXXZ
// partial score=0.55 date=2026-09-10
// ?init@LanguageFilter@@UAEXXZ
// Complete semantic source attempt for retail 0x0044E7A0 (310 bytes).

#include "PreRTS.h"
#include "GameClient/LanguageFilter.h"
#include "Common/FileSystem.h"
#include "Common/File.h"

void LanguageFilter::init()
{
	m_wordList.clear();

	File *file1 = TheFileSystem->openFile(BadWordFileName, File::READ | File::BINARY);
	if (file1 == NULL) {
		return;
	}

	wchar_t word[128];
	while (readWord(file1, word)) {
		Int wordLen = wcslen(word);
		if (wordLen == 0) {
			continue;
		}
		for (Int i = 0; i < wordLen; ++i) {
			word[i] = word[i] ^ LANGUAGE_XOR_KEY;
		}
		UnicodeString uniword(word);
		unHaxor(uniword);
		m_wordList[uniword] = true;
	}

	file1->close();
	file1 = NULL;
}
