// ?bfmeReplaceAliasedRange@Rva008312E0String@@QAEXPAD0000@Z
// partial score=0.70 date=2026-09-17
// cl: /Od /DNDEBUG /MD
// BFME retail 0x008312E0, 511 bytes.

#include <string.h>

typedef bool Bool;

void bfmeAssignChar(char *destination, const char *source);
#pragma comment(linker, "/alternatename:?bfmeAssignChar@@YAXPADPBD@Z=?assign@?$char_traits@D@_STL@@SAXAADABD@Z")

class Rva008312E0String
{
public:
	void bfmeReplaceAliasedRange(char *first, char *last,
		char *sourceFirst, char *sourceLast, char *tag);
	char *erase(char *first, char *last);
	void insertRange(char *position, char *first, char *last, char *tag);
	void replaceBase(char *first, char *last, char *sourceFirst,
		char *sourceLast, char *tag);

	char *m_start;
	char *m_finish;
};

#pragma comment(linker, "/alternatename:?erase@Rva008312E0String@@QAEPADPAD0@Z=?erase@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEPADPAD0@Z")
#pragma comment(linker, "/alternatename:?insertRange@Rva008312E0String@@QAEXPAD0000@Z=?bfmeInsertRangeV50@@YGXPAD000@Z")
#pragma comment(linker, "/alternatename:?replaceBase@Rva008312E0String@@QAEXPAD0000@Z=?bfmeReplaceV24@BfmeStrV24@@QAEPAV1@PAD000H@Z")

union Rva008312E0Inside
{
	int word;
	Bool byte;
};

void Rva008312E0String::bfmeReplaceAliasedRange(char *first, char *last,
	char *sourceFirst, char *sourceLast, char *tag)
{
	char framePad[ 0x58 ];
	int destinationLength;
	int sourceLength;
	char *sourcePosition = sourceFirst;
	Rva008312E0Inside sourceInside;
	if (sourcePosition >= m_start && sourcePosition < m_finish)
		sourceInside.word = 1;
	else
		sourceInside.word = 0;
	if (sourceInside.byte)
	{
		sourceLength = sourceLast - sourceFirst;
		destinationLength = last - first;
		if (destinationLength >= sourceLength)
		{
			char *destination = first;
			for (char *source = sourceFirst; source != sourceLast;
				++source, ++destination)
				bfmeAssignChar(destination, source);
			erase(first + sourceLength, last);
		}
		else
		{
			char *sourceMiddle = sourceFirst + destinationLength;
			if (sourceLast <= first || sourceFirst >= last)
			{
				char insertTag[ 2 ];
				insertTag[ 1 ] = 0;
				char *destination = first;
				for (char *source = sourceFirst; source != sourceMiddle;
					++source, ++destination)
					bfmeAssignChar(destination, source);
				insertRange(last, sourceMiddle, sourceLast, insertTag);
			}
			else
			{
				int destinationOffset = first - m_start;
				int sourceOffset = sourceFirst - m_start;
				char insertTag[ 2 ];
				insertTag[ 1 ] = 0;
				insertRange(last, sourceMiddle, sourceLast, insertTag);
				char *newDestination = m_start + destinationOffset;
				char *result;
				if (sourceLength == 0)
					result = newDestination;
				else
					result = (char *)memmove(
						newDestination, m_start + sourceOffset, sourceLength);
			}
		}
	}
	else
	{
		char replaceTag;
		replaceBase(first, last, sourceFirst, sourceLast, &replaceTag);
	}
}
