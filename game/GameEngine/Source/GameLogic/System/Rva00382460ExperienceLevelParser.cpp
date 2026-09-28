// cl: /DNDEBUG /DWIN32 /MD /EHsc
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
//																																				//
//	(c) 2001-2003 Electronic Arts Inc.																		//
//																																				//
////////////////////////////////////////////////////////////////////////////////

//
// Neutral address-derived carrier for the unclaimed BFME INI callback at
// retail RVA 0x00382460 (399 bytes).  The ExperienceLevel block's retail
// FieldParse table is at 0x010EAB48; its ModelConditionState entry reaches
// the matched callback at 0x0037D1A0.  The surrounding ExperienceLevel ctor,
// assignment, dtor, field layout, and ExperienceLevelSystem methods are all
// independently matched.  There is no direct named caller row for this
// callback, so the source deliberately keeps an RVA-derived free-function
// name instead of inventing a semantic parser method name.
//
// Retail's one stack argument is an INI* (plain ret, not ret 4).  When INI+8
// is 2, the callback finds the existing level, copies its final override,
// links the new override, initializes it from 0x010EAB48, and calls the
// matched system helper at 0x00380270.  Otherwise it constructs a stack
// ExperienceLevel, copies the token into its narrow name storage through the
// proven AsciiString copy-assignment body at 0x00887C90, initializes it, and
// routes it through the still-generated level insertion thunk at ILT
// 0x00041B2D.  The raw
// boundary is the ret at +0x18E followed by int3 padding; the source matches
// all 399 bytes modulo the normal relocation slots.

typedef bool Bool;
typedef int Int;

struct FieldParse;

// The retail parser's token temporary calls the shared BFME narrow-string
// constructor and releaseBuffer body.  The local spelling is AsciiString so
// the already-proven findLevel ABI remains the ordinary AsciiString reference.
class AsciiString
{
public:
	AsciiString(const char *text);
	AsciiString &operator=(const AsciiString &source);
	~AsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data != 0
			? reinterpret_cast<const char *>(m_data) + 8
			: "";
	}

	void *m_data;

private:
	void releaseBuffer();
};

class INIException
{
public:
	INIException(Int code, const char *format, ...);
	INIException(const INIException &other);

	Int m_code;
	const char *m_message;
};

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *object, const FieldParse *table);

	Int getLoadType() const
	{
		return *reinterpret_cast<const Int *>(
			reinterpret_cast<const char *>(this) + 8);
	}
};

class Overridable
{
public:
	Overridable *friend_getFinalOverride();
};

// This is a TU-local ABI view of the already-proven 0xD8 ExperienceLevel
// value.  Its constructor/assignment/destructor routes are the retail ILTs;
// no new semantic class identity is asserted by the parser carrier.
class ExperienceLevel
{
public:
	ExperienceLevel();
	ExperienceLevel &operator=(const ExperienceLevel &source);
	virtual ~ExperienceLevel();

	ExperienceLevel *m_nextOverride;
	Bool m_isOverride;
	AsciiString m_name;
	char m_tail[0xc8];
};

typedef char ExperienceLevelSizeMustBeD8[
	sizeof(ExperienceLevel) == 0xd8 ? 1 : -1];

class ExperienceLevelSystem
{
public:
	ExperienceLevel *findLevel(const AsciiString &name);
	void rva00380270(ExperienceLevel *level);
	void rva00382210(ExperienceLevel *level);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

static const FieldParse *const experienceLevelFieldParse =
	reinterpret_cast<const FieldParse *>(0x010EAB48);

void rva00382460(INI *ini)
{
	if (TheExperienceLevelSystem == 0)
		return;

	AsciiString name(ini->getNextToken(0));
	if (ini->getLoadType() == 2)
	{
		ExperienceLevel *existing = TheExperienceLevelSystem->findLevel(name);
		if (existing == 0)
			throw INIException(3,
				"Experience Level %s not found in map.ini", name.str());

		ExperienceLevel *created = new ExperienceLevel;
		ExperienceLevel *source = existing;
		if (source->m_nextOverride != 0)
		{
			source = reinterpret_cast<ExperienceLevel *>(
				reinterpret_cast<Overridable *>(source->m_nextOverride)
					->friend_getFinalOverride());
		}

		*created = *source;
		source->m_nextOverride = created;
		created->m_isOverride = true;
		ini->initFromINI(created, experienceLevelFieldParse);
		TheExperienceLevelSystem->rva00380270(created);
	}
	else
	{
		ExperienceLevel level;
		level.m_name = name;
		ini->initFromINI(&level, experienceLevelFieldParse);
		TheExperienceLevelSystem->rva00382210(&level);
	}
}
