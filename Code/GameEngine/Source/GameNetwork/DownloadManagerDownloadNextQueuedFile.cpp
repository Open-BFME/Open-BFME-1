// cl: /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "StringInline.h"
#include <list>

typedef long HRESULT;
typedef bool Bool;

class QueuedDownload
{
public:
	AsciiString server;
	AsciiString userName;
	AsciiString password;
	AsciiString file;
	AsciiString localFile;
	AsciiString regKey;
	Bool tryResume;

	QueuedDownload &operator=(const QueuedDownload &other);
	~QueuedDownload();
};

class DownloadManagerDownloadNextQueuedFileShim
{
public:
	virtual ~DownloadManagerDownloadNextQueuedFileShim();
	virtual HRESULT OnError(int error);
	virtual HRESULT OnEnd();
	virtual HRESULT OnQueryResume();
	virtual HRESULT OnProgressUpdate(int bytesread, int totalsize, int timetaken, int timeleft);
	virtual HRESULT OnStatusUpdate(int status);
	virtual HRESULT downloadFile(AsciiString server, AsciiString username, AsciiString password,
		AsciiString file, AsciiString localfile, AsciiString regkey, Bool tryResume);

	HRESULT downloadNextQueuedFile();

private:
	Bool m_winsockInit;
	void *m_download;
	Bool m_wasError;
	Bool m_sawEnd;
	unsigned char m_errorString[4];
	unsigned char m_statusString[4];

protected:
	std::list<QueuedDownload> m_queuedDownloads;
};

HRESULT DownloadManagerDownloadNextQueuedFileShim::downloadNextQueuedFile()
{
	QueuedDownload q;
	std::list<QueuedDownload>::iterator it = m_queuedDownloads.begin();
	if (it != m_queuedDownloads.end())
	{
		q = *it;
		m_queuedDownloads.pop_front();
		m_wasError = m_sawEnd = false;
		return downloadFile(q.server, q.userName, q.password, q.file, q.localFile, q.regKey, q.tryResume);
	}
	return 0;
}
