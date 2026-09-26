// ?initFromINIMulti@INI@@QAEXPAXABVMultiIniFieldParse@@@Z
// partial score=0.431319 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /Ireference/shims/ini_parser /Ireference/shims/ini_inline /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/INI.h"

// Retail body at 0x00851910. The diagnostics below follow the INIException
// variadic constructor and preserve the AsciiString temporaries returned by
// getFilename(); formatting into a fixed char buffer loses both behaviours.
static INIFieldParseProc findFieldParse(const FieldParse* parseTable, const char* token, int& offset, const void*& userData)
{
	for (const FieldParse* parse = parseTable; parse->token; ++parse)
	{
		if (strcmp(parse->token, token) == 0)
		{
			offset = parse->offset;
			userData = parse->userData;
			return parse->parse;
		}
	}
	if (!parse->token && parse->parse)
	{
		offset = parse->offset;
		userData = token;
		return parse->parse;
	}
	return NULL;
}

// Existing byte-verified address-qualified accessors preserve retail's
// out-of-line filename return and indexed source-line lookup.
class Rva00093F40StringAccessor { public: virtual AsciiString getString(); };
class Gen_009CBC90 { public: int bfmeAt(int index) const; };

void INI::initFromINIMulti(void *what, const MultiIniFieldParse& parseTableList)
{
	Bool done = FALSE;
	if (what == NULL)
	{
		DEBUG_ASSERTCRASH(0, ("INI::initFromINI - Invalid parameters supplied!\n"));
		throw INIException(1, "INI::initFromINI - Invalid parameters supplied!");
	}

	while (!done)
	{
		readLine();
		const char *field = strtok(m_buffer, getSeps());
		if (field != NULL)
		{
			if (stricmp(field, m_blockEndToken) == 0)
				done = TRUE;
			else
			{

			Bool found = FALSE;
			for (Int tableIndex = 0; tableIndex < parseTableList.getCount(); ++tableIndex)
			{
				Int offset = 0;
				const void *userData = NULL;
				INIFieldParseProc parse = findFieldParse(
					parseTableList.getNthFieldParse(tableIndex), field, offset, userData);
				if (parse == NULL)
					continue;

				try
				{
					parse(this, what,
						(char *)what + offset + parseTableList.getNthExtraOffset(tableIndex),
						userData);
				}
				catch (INIException& e)
				{
					AsciiString filename = ((Rva00093F40StringAccessor *)this)->Rva00093F40StringAccessor::getString();
					DEBUG_CRASH(("[LINE: %d - FILE: '%s'] Error reading field '%s' of block '%s'\n",
						((const Gen_009CBC90 *)&m_lines)->bfmeAt(m_lineNum), filename.str(), field, m_curBlockStart));
					throw INIException(e.m_argCount,
						"%s\n\nError parsing field '%s' in block '%s' in file '%s', line %i.\n",
						e.mFailureMessage, field, m_curBlockStart, filename.str(),
						((const Gen_009CBC90 *)&m_lines)->bfmeAt(m_lineNum));
				}
				catch (...)
				{
					AsciiString filename = ((Rva00093F40StringAccessor *)this)->Rva00093F40StringAccessor::getString();
					DEBUG_CRASH(("[LINE: %d - FILE: '%s'] Error reading field '%s' of block '%s'\n",
						((const Gen_009CBC90 *)&m_lines)->bfmeAt(m_lineNum), filename.str(), field, m_curBlockStart));
					throw INIException(8,
						"Unknown error parsing field '%s' in block '%s' in file '%s', line %i.\n",
						field, m_curBlockStart, filename.str(), ((const Gen_009CBC90 *)&m_lines)->bfmeAt(m_lineNum));
				}

				found = TRUE;
				break;
			}

			if (!found)
			{
				AsciiString filename = ((Rva00093F40StringAccessor *)this)->Rva00093F40StringAccessor::getString();
				DEBUG_ASSERTCRASH(0,
					("[LINE: %d - FILE: '%s'] Unknown field '%s' in block '%s'\n",
					((const Gen_009CBC90 *)&m_lines)->bfmeAt(m_lineNum), filename.str(), field, m_curBlockStart));
				throw INIException(5, "Unknown field '%s' in block '%s'.\n\n"
					"Error parsing field '%s' in block '%s' in file '%s', line %i.\n",
					field, m_curBlockStart, field, m_curBlockStart,
					filename.str(), ((const Gen_009CBC90 *)&m_lines)->bfmeAt(m_lineNum));
			}
			}
		}

		if (!done && isEOF())
		{
			AsciiString filename = ((Rva00093F40StringAccessor *)this)->Rva00093F40StringAccessor::getString();
			DEBUG_ASSERTCRASH(FALSE,
				("Error parsing block '%s', in INI file '%s'. Missing '%s' token\n",
				m_curBlockStart, filename.str(), m_blockEndToken));
			throw INIException(4, "Missing '%s' token.\n\n"
				"Error parsing block '%s' in file '%s', line %i.\n",
				m_blockEndToken, m_curBlockStart, filename.str(), ((const Gen_009CBC90 *)&m_lines)->bfmeAt(m_lineNum));
		}
	}
}
