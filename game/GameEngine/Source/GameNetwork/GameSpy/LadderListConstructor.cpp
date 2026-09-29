// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Copyright 2025 Electronic Arts Inc.
// SPDX-License-Identifier: GPL-3.0-or-later
// BFME LadderList constructor, 0x0062C020; companion to the verified ladder parser.
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}
inline UnicodeString::UnicodeString(const wchar_t *s)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)
		->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
	return *this;
}

#include "Common/GameType.h"
#include <algorithm>
#include <list>
#include <string>
#include <stdlib.h>
#include "GameNetwork/GameSpy/LadderDefs.h"
#include "GameNetwork/GameSpy/GSConfig.h"
#define DEBUG_LOG(x)
#define NEW new
template <> inline bool StringBase<char>::isEmpty()const {return !m_data||m_data->length==0;}
template <> inline char StringBase<char>::getCharAt(int n)const {return m_data?m_data->data[n]:0;}
inline UnicodeString& UnicodeString::operator=(const wchar_t *s) {
 ((StringBase<unsigned short>*)this)->set((const unsigned short*)s,s?wcslen(s):0);return *this;
}
#include <string.h>
#pragma intrinsic(strlen)
template <> inline bool StringBase<char>::startsWith(const char *s)const {return startsWith(s,s?strlen(s):0);}
template <> inline void StringBase<char>::set(const char *s) {set(s,s?strlen(s):0);}
inline AsciiString& AsciiString::operator=(const char *s) {StringBase<char>::set(s);return *this;}

LadderInfo *parseLadder(AsciiString);
template <> inline void StringBase<char>::concat(char c) {concat(&c,1);}
template <> inline void StringBase<char>::concat(const StringBase<char>&s) {
 const int len=s.m_data?s.m_data->length:0;
 const char *data=s.m_data?s.m_data->data:"";
 concat(data,len);
}
template <> inline int StringBase<char>::compare(const char *str, int len) const {
 const int myLen=m_data?m_data->length:0;
 const char *data=m_data?&m_data->data[0]:"";
 int result=memcmp(data,str,myLen<len?myLen:len);
 if(result!=0)return result;
 return myLen-len;
}
template <> inline int StringBase<char>::compare(const char *str)const {
 return compare(str,str?strlen(str):0);
}
LadderList::LadderList()
{
	//Int profile = TheGameSpyInfo->getLocalProfileID();

	AsciiString rawMotd = TheGameSpyConfig->getLeftoverConfig();
	AsciiString line;
	Bool inLadders = FALSE;
	Bool inSpecialLadders = FALSE;
	Bool inLadder = FALSE;
	LadderInfo *lad = NULL;
	Int index = 1;
	AsciiString rawLadder;

	while (rawMotd.nextToken(&line, "\n"))
	{
		if (line.getCharAt(line.getLength()-1) == '\r')
			line.removeLastChar();	// there is a trailing '\r'

		line.trim();

		if (line.isEmpty())
			continue;

		if (!inLadders && ((const StringBase<char>&)line).compare("<Ladders>") == 0)
		{
			inLadders = TRUE;
			rawLadder.clear();
		}
		else if (inLadders && ((const StringBase<char>&)line).compare("</Ladders>") == 0)
		{
			inLadders = FALSE;
		}
		else if (!inSpecialLadders && ((const StringBase<char>&)line).compare("<SpecialLadders>") == 0)
		{
			inSpecialLadders = TRUE;
			rawLadder.clear();
		}
		else if (inSpecialLadders && ((const StringBase<char>&)line).compare("</SpecialLadders>") == 0)
		{
			inSpecialLadders = FALSE;
		}
		else if (inLadders || inSpecialLadders)
		{
			if (line.startsWith("<Ladder ") && !inLadder)
			{
				inLadder = TRUE;
				rawLadder.clear();
				rawLadder.concat(line);
				rawLadder.concat('\n');
			}
			else if (((const StringBase<char>&)line).compare("</Ladder>") == 0 && inLadder)
			{
				inLadder = FALSE;
				rawLadder.concat(line);
				rawLadder.concat('\n');
				if ((lad = parseLadder(rawLadder)) != NULL)
				{
					lad->index = index++;
					if (inLadders)
					{
						DEBUG_LOG(("Adding to standard ladders\n"));
						m_standardLadders.push_back(lad);
					}
					else
					{
						DEBUG_LOG(("Adding to special ladders\n"));
						m_specialLadders.push_back(lad);
					}
				}
				rawLadder.clear();
			}
			else if (inLadder)
			{
				rawLadder.concat(line);
				rawLadder.concat('\n');
			}
		}
	}

	// look for local ladders
	loadLocalLadders();

	DEBUG_LOG(("After looking for ladders, we have %d local, %d special && %d normal\n", m_localLadders.size(), m_specialLadders.size(), m_standardLadders.size()));
}

