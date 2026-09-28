// cl: /DNDEBUG /MD /EHsc
// Real C++ reconstruction of the save-list callback at retail RVA 0x00111C40.
//
// The matched GameState::populateSaveGameListbox body at 0x001121A0 names this
// callback through the reference iterateSaveFiles(addGameToAvailableList, ...)
// registration.  The complete retail boundary is 0x118 bytes: ret at +0x117,
// followed by the separately claimed Rva00111D58Get body.  The call through ILT
// 0x000083D7 at +0x4B tests AL, so this TU preserves the observed BFME Bool ABI
// even though the older ledger row for the reader still carries its stale QAEX
// (void) decoration.
//
// SaveGameInfo follows the verified reference field order and the local
// StringBase view used by the landed GameState save/load conversions.  The
// assignment is routed through the already matched 0x0010CFF0 body because the
// retail SaveGameInfo assignment symbol is still represented by that neutral
// ABI view in this TU.
// Its destructor is declaration-only so the compiler emits one true
// `this`-carrying call to ??1SaveGameInfo@@QAE@XZ.  That symbol's pin is the
// ILT 0x0000AB78 call target 0x0010D700; the target releases these same six
// StringBase members.  It must not be modeled as a no-argument free call
// followed by implicit member destruction.

typedef unsigned short UnsignedShort;
typedef bool Bool;

template <typename T> struct BfmeStringData
{
	int refs;
	UnsignedShort length;
	UnsignedShort capacity;
	T text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

protected:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }

	private:
	void set(const StringBase<T> &other);
	BfmeStringData<T> *m_data;

	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void set(const AsciiString &other)
	{
		StringBase<char>::set(other);
	}
};

class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() : StringBase<UnsignedShort>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<UnsignedShort>(other) {}
	~UnicodeString() {}
};

struct SaveDate
{
	UnsignedShort year;
	UnsignedShort month;
	UnsignedShort day;
	UnsignedShort dayOfWeek;
	UnsignedShort hour;
	UnsignedShort minute;
	UnsignedShort second;
	UnsignedShort milliseconds;

	Bool isNewerThan(SaveDate *other);
};

class Rva0010CFF0
{
public:
	Rva0010CFF0 &operator=(const Rva0010CFF0 &other);
};

class SaveGameInfo
{
public:
	SaveGameInfo() throw();
	~SaveGameInfo();

	AsciiString saveGameMapName;
	AsciiString pristineMapName;
	AsciiString mapLabel;
	SaveDate date;
	AsciiString campaignSide;
	int missionNumber;
	UnicodeString description;
	int saveFileType;
	AsciiString missionMapName;
};

struct AvailableGameInfo
{
	AsciiString filename;
	SaveGameInfo saveGameInfo;
	AvailableGameInfo *next;
	AvailableGameInfo *prev;
};

class GameState
{
public:
	Bool getSaveGameInfoFromFile(AsciiString filename,
		SaveGameInfo *saveGameInfo);
};

#define TheGameState (*(GameState **)0x012EF190)

// ?addGameToAvailableList@@YAXVAsciiString@@PAX@Z
void addGameToAvailableList(AsciiString filename, void *userData)
{
	AvailableGameInfo **listHead = (AvailableGameInfo **)userData;

	try
	{
		SaveGameInfo saveGameInfo;
		if (TheGameState->getSaveGameInfoFromFile(filename, &saveGameInfo))
		{
			AvailableGameInfo *newInfo = new AvailableGameInfo;
			newInfo->prev = 0;
			newInfo->next = 0;
			reinterpret_cast<Rva0010CFF0 *>(&newInfo->saveGameInfo)->operator=(
				*reinterpret_cast<const Rva0010CFF0 *>(&saveGameInfo));
			newInfo->filename.set(filename);

			if (*listHead == 0)
			{
				*listHead = newInfo;
			}
			else
			{
				AvailableGameInfo *curr;
				AvailableGameInfo *prev;
				prev = 0;
				for (curr = *listHead; curr != 0; curr = curr->next)
				{
					prev = curr;
					if (newInfo->saveGameInfo.date.isNewerThan(
						&curr->saveGameInfo.date))
					{
						if (curr->prev)
							curr->prev->next = newInfo;
						else
							*listHead = newInfo;
						newInfo->prev = curr->prev;
						curr->prev = newInfo;
						newInfo->next = curr;
						break;
					}
				}

				if (curr == 0)
				{
					prev->next = newInfo;
					newInfo->prev = prev;
				}
			}
		}
	}
	catch (...)
	{
	}
}
