// cl: /DNDEBUG /MD /GX /Igame/Libraries/Source/WWVegas/WWLib

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

template <typename T>
const T &minimum(const T &first, const T &second)
{
	return first < second ? first : second;
}

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

class GameSlot
{
public:
	bool isHuman() const;
	bool hasMap() const { return m_hasMap; }

private:
	char m_pad[9];
	bool m_hasMap;
};

class GameInfo
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual bool amIHost() const;
	const GameSlot *getConstSlot(int slot) const;
};

class NetworkInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID);
	virtual int sendFileAnnounce(AsciiString path, UnsignedByte playerMask);
	virtual int getFileTransferProgress(int playerID, AsciiString path);
	virtual bool areAllQueuesEmpty();
	virtual void beginFileTransfer();
	virtual void endFileTransfer();
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
};

class BfmeAptScreenMapTransfer
{
public:
	void setCurrentFilename(const AsciiString &filename);
	void processTimeout(int secondsLeft);
	void update(int percentage);
	void processProgress(int playerID, int percentage, UnicodeString state);
};

extern NetworkInterface *TheNetwork;
extern GameInfo *TheGameInfo;
extern GameTextInterface *TheGameText;
extern BfmeAptScreenMapTransfer *TheBfmeAptScreenMapTransfer;

extern "C" __declspec(dllimport) void __stdcall Sleep(UnsignedInt milliseconds);
extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime();
extern "C" void *memset(void *destination, int value, unsigned int count);

bool doFileTransfer(AsciiString filename, int mask)
{
	BfmeAptScreenMapTransfer *screen = TheBfmeAptScreenMapTransfer;
	bool fileTransferDone = false;
	int fileTransferPercent = 0;

	if (TheNetwork)
		TheNetwork->beginFileTransfer();

	if (mask)
	{
		screen->setCurrentFilename(filename);
		UnsignedInt startTime = timeGetTime();
		screen->processTimeout(600);
		screen->update(0);

		int fileCommandID = 0;
		bool sentFile = false;
		if (TheGameInfo->amIHost())
		{
			Sleep(500);
			fileCommandID = TheNetwork->sendFileAnnounce(filename, mask);
		}
		else
		{
			sentFile = true;
		}

		int lastPlayerProgress[8];
		memset(lastPlayerProgress, 0, sizeof(lastPlayerProgress));
		int lastProgressTime = timeGetTime();
		int nextSendSlot = 1;

		while (!fileTransferDone)
		{
			if (!sentFile)
			{
				int playerMask = (1 << nextSendSlot) & mask;
				if (playerMask)
					TheNetwork->sendFile(filename, playerMask, fileCommandID);
				++nextSendSlot;
				if (nextSendSlot == 8)
					sentFile = true;
			}

			fileTransferDone = true;
			fileTransferPercent = 100;
			for (int i = 1; i < 8; ++i)
			{
				if (TheGameInfo->getConstSlot(i)->isHuman() &&
					!TheGameInfo->getConstSlot(i)->hasMap())
				{
					int slotTransferPercent = TheNetwork->getFileTransferProgress(i, filename);
					fileTransferPercent = minimum(fileTransferPercent, slotTransferPercent);

					if (slotTransferPercent != lastPlayerProgress[i])
					{
						if (slotTransferPercent == 0)
							screen->processProgress(i, slotTransferPercent,
								TheGameText->fetch("MapTransfer:Preparing"));
						else if (slotTransferPercent < 100)
							screen->processProgress(i, slotTransferPercent,
								TheGameText->fetch("MapTransfer:Recieving"));
						else
							screen->processProgress(i, slotTransferPercent,
								TheGameText->fetch("MapTransfer:Done"));
						lastPlayerProgress[i] = slotTransferPercent;
						lastProgressTime = timeGetTime();
					}
				}
			}

			if (fileTransferPercent < 100)
			{
				fileTransferDone = false;
				if (fileTransferPercent == 0)
					screen->processProgress(0, fileTransferPercent,
						TheGameText->fetch("MapTransfer:Preparing"));
				else
					screen->processProgress(0, fileTransferPercent,
						TheGameText->fetch("MapTransfer:Sending"));
			}
			else
			{
				screen->processProgress(0, fileTransferPercent,
					TheGameText->fetch("MapTransfer:Done"));
			}

			int now = timeGetTime();
			if (fileTransferPercent)
			{
				if (now > lastProgressTime + 30000)
					break;
			}
			else if (now > lastProgressTime + 120000)
			{
				break;
			}
			if (now > startTime + 600000)
				break;

			screen->processTimeout((startTime + 600000 - now) / 1000);
			screen->update(fileTransferPercent);
		}

		if (!fileTransferDone)
			return false;
	}

	if (TheNetwork)
		TheNetwork->endFileTransfer();

	return true;
}
