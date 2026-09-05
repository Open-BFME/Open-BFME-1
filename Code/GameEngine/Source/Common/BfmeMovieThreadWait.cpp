// cl: /O2 /Ob0
// cdecl movie-thread lock. String "Could not set Movie Thread Priority".
// Object layout from neighbour BfmeStrVM0 (m_3C mutex, m_40 mutex).
// Debug crash ABI from boxrobj.cpp (g_BFMEIndexBufferDebug at 0x01336E5C).
// RVA-derived type BfmeMovieLockObj: no caller/vtable name for the owner.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *);
extern "C" __declspec(dllimport) void *__stdcall GetCurrentThread(void);
extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(void *, int);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);

void W3DRadarResetLock(void);
char bfmeUnlock1179(void);
void _bfme_debugRecordCallsite(int kind);

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34();
	virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
	virtual void Slot3C(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
	virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
	virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context);
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;

class BfmeMovieLockObj
{
public:
	virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03();
	virtual int v04(); virtual int v05(); virtual int v06(); virtual int v07();
	virtual int v08(); virtual int v09(); virtual int v10(); virtual int v11();
	virtual int v12(); virtual int v13(); virtual int v14(); virtual int v15();
	virtual int v16(); virtual int v17(); virtual int v18(); virtual int v19();
	virtual int v20(); virtual int v21(); virtual int v22(); virtual int v23();
	virtual int v24(); virtual int v25(); virtual int v26(); virtual int v27();
	virtual int v28(); virtual int v29(); virtual int v30(); virtual int v31();
	virtual int v32(); virtual int v33(); virtual int v34(); virtual int v35();
	virtual int v36(); virtual int v37(); virtual int v38(); virtual int v39();
	virtual int v40(); virtual int v41(); virtual int v42(); virtual int v43();
	virtual int v44(); virtual int v45(); virtual int v46(); virtual int v47();
	virtual int v48(); virtual int v49(); virtual int v50(); virtual int v51();
	virtual int v52(); virtual int v53(); virtual int v54(); virtual int v55();
	virtual int v56(); virtual int v57(); virtual int v58(); virtual int v59();
	virtual int v60();
	virtual bool predF4();
	virtual int v62();
	virtual int v63();
	virtual void go100(int);
	virtual int v65(); virtual int v66(); virtual int v67();
	virtual int v68(); virtual int v69(); virtual int v70(); virtual int v71();
	virtual int v72(); virtual int v73(); virtual int v74(); virtual int v75();
	virtual int v76(); virtual int v77(); virtual int v78(); virtual int v79();
	virtual int v80(); virtual int v81(); virtual int v82(); virtual int v83();
	virtual int v84(); virtual int v85(); virtual int v86(); virtual int v87();
	virtual int v88();
	virtual void go164(int);

	char m_pad04[0x38];
	void *m_3C;
	void *m_40;
	char m_pad44[0x18];
	int m_5C;
};

// ?bfmeMovieThreadWait@@YAHPAVBfmeMovieLockObj@@@Z
int bfmeMovieThreadWait(BfmeMovieLockObj *self)
{
	void *gate = self->m_3C;
	unsigned char first = 1;
	WaitForSingleObject(gate, 0xFFFFFFFF);
	for (;;)
	{
		if (self->m_5C == 5)
		{
			W3DRadarResetLock();
			self->go164(3);
			bfmeUnlock1179();
			Sleep(0x21);
		}
		else if (first)
		{
			if (!self->predF4())
			{
				self->go100(1);
				Sleep(1);
			}
			else
			{
				first = 0;
				void *thread = GetCurrentThread();
				if (!SetThreadPriority(thread, -2))
				{
					_bfme_debugRecordCallsite(1);
					g_BFMEIndexBufferDebug->Begin_Report();
					BFMEIndexBufferDebugStream *stream =
						g_BFMEIndexBufferDebug->Get_Stream(0, 0);
					stream->Put_String("Could not set Movie Thread Priority")->Finish(1);
				}
				Sleep(100);
			}
		}
		else
		{
			Sleep(100);
		}

		if (WaitForSingleObject(self->m_40, 0) != 0x102)
			break;
	}
	ReleaseMutex(self->m_3C);
	return 0;
}
