// readable body of ?downloadNextQueuedFile@DownloadManager@@QAEJXZ: Code/GameEngine/Source/GameNetwork/DownloadManager.cpp
// Two thunk rows were removed from this file. A 5-byte thunk row byte-verifies
// against any incremental-link entry in the image, because every one of them is
// E9 xx xx xx xx and the displacement is a REL32 the verifier fills in from the
// target -- so the name is never tested. An audit followed each thunk to its
// body and, trusting the masm row names then in the ledger, concluded the two
// thunks named the wrong function:
//
//   DownloadManager::OnError        -> body claimed as getLastLocalFile
//   DownloadManager::OnStatusUpdate -> body claimed as OnProgressUpdate
//
// That conclusion was backwards. The masm rows themselves were mislabeled: the
// bodies at 0x00626DA0 and 0x00626EE0 are really OnError (7-case
// DOWNLOADEVENT_* switch, 224B) and OnStatusUpdate (8-case DOWNLOADSTATUS_*
// switch, 226B), and clean C++ in GameNetwork/DownloadManager.cpp byte-matches
// both. The mislabeled rows are tombstoned in reverse/deleted_rows.csv and the
// functions claimed from their C++ home.
//
// downloadNextQueuedFile stays: its body is unclaimed, so nothing contradicts
// it. See tools/audit_thunk_rows.py before adding another row here.
class DownloadManager
{
public:
	long downloadNextQueuedFile();
};

class DownloadManagerDownloadNextQueuedFileShim
{
public:
	long downloadNextQueuedFile();
};

long DownloadManager::downloadNextQueuedFile()
{
	return ((DownloadManagerDownloadNextQueuedFileShim *)this)->downloadNextQueuedFile();
}
