// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail returns at +0x289 and begins INT3 padding at +0x28A.
// The matched MilesAudioManager caller at 0x006B86D0 calls this zero-argument member through ILT 0x00044661.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <set>
#include <stdlib.h>

#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/LatchRestore.h"

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64 *timer);

extern void j_0003e045();
extern void j_0000a3fd();
extern void j_0002cda9();
extern void j_00029a64();
extern void j_0002f1d5();
extern void j_00044661();

class Rva006B86D0MutexGuard
{
public:
	Rva006B86D0MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B86D0MutexGuard()
	{
		if (m_owned)
		{
			ReleaseMutex(m_handle);
			m_owned = 0;
		}
	}

private:
	void *m_handle;
	char m_owned;
};

struct Rva006B86D0Pair
{
	int dword_0;
	int dword_4;
};

struct AudioSettings
{
	char m_pad00[0x28];
	int m_sampleCount2D;
	int m_sampleCount3D;
	char m_pad30[0x6c - 0x30];
	int dword_6c;
};

class Rva006B86D0Slot
{
public:
	char m_pad[0x1c4];
};

class Rva006B86D0Table
{
public:
	char m_pad[0x14];
};

class MilesAudioManager
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08();
	virtual void rva006B86D0(unsigned int which);
	virtual void vslot10(); virtual void vslot11(); virtual void vslot12(); virtual void vslot13();
	virtual void vslot14(); virtual void vslot15(); virtual void vslot16(); virtual void vslot17();
	virtual void vslot18(); virtual void vslot19(); virtual void vslot20(); virtual void vslot21();
	virtual void vslot22(); virtual void vslot23(); virtual void vslot24(); virtual void vslot25();
	virtual void vslot26(); virtual void vslot27(); virtual void vslot28(); virtual void vslot29();
	virtual void vslot30(); virtual void vslot31(); virtual void vslot32(); virtual void vslot33();
	virtual void vslot34(); virtual void vslot35(); virtual void vslot36(); virtual void vslot37();
	virtual void vslot38(); virtual void vslot39(); virtual void vslot40(); virtual void vslot41();
	virtual void vslot42(); virtual void vslot43(); virtual void vslot44(); virtual void vslot45();
	virtual void vslot46(); virtual void vslot47(); virtual void vslot48(); virtual void vslot49();
	virtual void vslot50(); virtual void vslot51(); virtual void vslot52(); virtual void vslot53();
	virtual void vslot54(); virtual void vslot55(); virtual void vslot56(); virtual void vslot57();
	virtual void vslot58(); virtual void vslot59(); virtual void vslot60(); virtual void vslot61();
	virtual void vslot62(); virtual void vslot63(); virtual void vslot64(); virtual void vslot65();
	virtual void vslot66(); virtual void vslot67(); virtual void vslot68(); virtual void vslot69();
	virtual void vslot70(); virtual void vslot71(); virtual void vslot72(); virtual void vslot73();
	virtual void vslot74(); virtual void vslot75(); virtual void vslot76(); virtual void vslot77();
	virtual void vslot78(); virtual void vslot79(); virtual void vslot80(); virtual void vslot81();
	virtual void vslot82(); virtual void vslot83(); virtual void vslot84(); virtual void vslot85();
	void rva006B7AE0();

private:
	char m_pad008[0x0c - 0x08];
	AudioSettings *m_audioSettings;
	char m_pad010[0x48 - 0x10];
	int dword_48;
	char m_pad04c[0xb8 - 0x4c];
	Rva006B86D0Slot m_slots[3];
	char m_pad604[0x61c - 0x604];
	unsigned int dword_61c;
	char m_pad620[0x624 - 0x620];
	unsigned int dword_624;
	char m_pad628[0x636 - 0x628];
	unsigned char byte_636;
	char m_pad637[0x63c - 0x637];
	int dword_63c[3];
	int dword_648[3];
	char m_pad654[0x95c - 0x654];
	void *m_mutex;
	char m_pad960[0x96c - 0x960];
	Rva006B86D0Table m_table96c;
	_STL::vector<UnicodeString> m_unicode980;
	_STL::vector<AsciiString> m_ascii98c;
	_STL::set<AsciiString> m_sets[3];
	char m_pad9bc[0xac4 - 0x9bc];
	int dword_ac4[3];
	char m_padad0[0xadc - 0xad0];
	_STL::vector<Rva006B86D0Pair> m_pairs;
	char m_padae8[0xb5c - 0xae8];
	unsigned int dword_b5c;
	char m_padb60[0xb68 - 0xb60];
	__int64 qword_b68;
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &other);
	~XferException();
	char *text;
	int tagValue;
};

class BfmeActivationStream
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2();
	virtual void slot3(); virtual void slot4();
};

class Gen009D6300
{
public:
	bool bfmeTryActivate(BfmeActivationStream *stream, int enabled, bool flags);
};

class Gen009D6DD0
{
public:
	void bfmeClose();
};

class BfmePeer
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void *bfmeValue();
};

class Rva006B7AE0AttachView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void *bfmeAttach(BfmePeer *peer);
};

class Gen_009D83D0
{
public:
	virtual ~Gen_009D83D0();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11();
	virtual Gen_009D83D0 *bfmeAttach(BfmePeer *peer);
	Gen_009D83D0();

private:
	char m_payload[0x3c];
};

class BfmeMade_009CB5F0;
BfmeMade_009CB5F0 *bfmeMake_009CB5F0(void *owner);

class BfmeThingEC
{
public:
	int bfmeTakeEC(int *size);
};

static inline char *rva006B7AE0TakeECData(BfmeThingEC *data, int *size)
{
	return reinterpret_cast<char *>(data->bfmeTakeEC(size));
}

class File
{
public:
	virtual ~File();
	virtual bool open(const char *name, int flags);
	virtual void close();
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);
	virtual int seek(int bytes, int mode);
	virtual void nextLine(char *buffer, int size);
	virtual bool scanInt(int &value);
	virtual bool scanReal(float &value);
	virtual bool scanString(void *value);
	virtual bool print(const char *format, ...);
	virtual int size();
	virtual int position();
	virtual char *readEntireAndClose();
	virtual File *convertToRAMFile();
	virtual void lock();
	virtual void unlock();
};

File *createMemoryReadFile(char *data, int size);

class Gen009D8CA0
{
public:
	virtual ~Gen009D8CA0();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11();
	virtual Gen009D8CA0 *bfmeAttach(BfmePeer *peer);
	Gen009D8CA0(int first, int second, int third);
	bool readAt009D89E0(File *file, void *output);

private:
	char m_payload[0x1c];
};

class Rva009D8AA0
{
public:
	void apply();
};

class Rva006B7AE0Node
{
public:
	Rva006B7AE0Node *m_next;
	int m_pad;
	int m_value;
};

class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34();
	virtual BfmeAwakenLog *v38(const char *message);
	virtual void slot3c(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void v4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void v60();
	virtual void slot64(); virtual void slot68();
	virtual BfmeAwakenLog *v6c(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);
extern void j_0000be88(void);
extern void j_00010db6(void);
extern void j_000183b8(void);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

void MilesAudioManager::rva006B7AE0(void)
{
	LatchRestore<bool> latch(*reinterpret_cast<bool *>(reinterpret_cast<char *>(this) + 0xb70), true);
	BfmeMade_009CB5F0 *factoryData = bfmeMake_009CB5F0(0);
	BfmeMade_009CB5F0 * volatile saveData = factoryData;
	if (factoryData == 0)
		return;

	try
	{
		Gen_009D83D0 writer;
		reinterpret_cast<Gen009D6300 *>(&writer)->bfmeTryActivate(
			reinterpret_cast<BfmeActivationStream *>(saveData), 0, false);
		BfmePeer *peer = this != 0
			? reinterpret_cast<BfmePeer *>(reinterpret_cast<char *>(this) + 8)
			: 0;
		reinterpret_cast<Rva006B7AE0AttachView *>(&writer)->bfmeAttach(peer);
		reinterpret_cast<Gen009D6DD0 *>(&writer)->bfmeClose();
	}
	catch (const XferException &error)
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->v60();
			TheBfmeAwakenDebug->v6c(0, 0)
				->v38("reinitializeAudioSystem: internal xfer save failed: ")
				->v38(error.text)->v4c(2);
		}
	}

	Rva006B7AE0Node **head = reinterpret_cast<Rva006B7AE0Node **>(
		reinterpret_cast<char *>(this) + 0x9c8);
	Rva006B7AE0Node *node = (*head)->m_next;
	while (node != *head)
	{
		typedef void (MilesAudioManager::*Call)(int *);
		union
		{
			void (__cdecl *function)();
			Call member;
		} call;
		call.function = ::j_00010db6;
		(this->*call.member)(&node->m_value);
		node = node->m_next;
	}

	head = reinterpret_cast<Rva006B7AE0Node **>(
		reinterpret_cast<char *>(this) + 0x9cc);
	node = (*head)->m_next;
	while (node != *head)
	{
		typedef void (MilesAudioManager::*Call)(int *);
		union
		{
			void (__cdecl *function)();
			Call member;
		} call;
		call.function = ::j_00010db6;
		(this->*call.member)(&node->m_value);
		node = node->m_next;
	}

	typedef void (MilesAudioManager::*VoidCall)();
	union
	{
		void (__cdecl *function)();
		VoidCall member;
	} noArgCall;
	noArgCall.function = ::j_0000be88;
	(this->*noArgCall.member)();
	Sleep(10);
	noArgCall.function = ::j_000183b8;
	(this->*noArgCall.member)();

	int dataSize;
	dataSize = 0;
	char *data = rva006B7AE0TakeECData(
		reinterpret_cast<BfmeThingEC *>(saveData), &dataSize);
	File *file = createMemoryReadFile(data, dataSize);
	try
	{
		Gen009D8CA0 reader(0, 0, 0);
		int version;
		reader.readAt009D89E0(file, &version);
		reinterpret_cast<Rva006B7AE0AttachView *>(&reader)->bfmeAttach(
			reinterpret_cast<BfmePeer *>(reinterpret_cast<char *>(this) + 8));
		reinterpret_cast<Rva009D8AA0 *>(&reader)->apply();
		*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x638) = 1;
		reinterpret_cast<BfmePeer *>(reinterpret_cast<char *>(this) + 8)->slot1();
	}
	catch (const XferException &error)
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->v60();
			TheBfmeAwakenDebug->v6c(0, 0)
				->v38("reinitializeAudioSystem: internal xfer load failed: ")
				->v38(error.text)->v4c(2);
		}
	}

	free(data);
	delete file;
	vslot05();
}
