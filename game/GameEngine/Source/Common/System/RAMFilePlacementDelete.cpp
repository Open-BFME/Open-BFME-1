// cl: /DNDEBUG /MD /EHsc

// RAMFile's and StreamingArchiveFile's pool-glue placement delete are the
// shared 12-byte body at 0x007EFFF0 (retail folds every class's glue delete
// onto it; see BucketPlacementDelete.cpp). Win32BIGFile.cpp's Zero Hour
// openFile used to be the only object that emitted them, as a side effect of
// newInstance. Keep the declarations local and force each inline body by
// taking its address.
extern "C" void __cdecl free(void *);

class RAMFile
{
public:
	enum RAMFileMagicEnum { RAMFile_GLUE_NOT_IMPLEMENTED = 0 };

	inline void operator delete(void *p, RAMFileMagicEnum)
	{
		free(p);
	}
};

class StreamingArchiveFile
{
public:
	enum StreamingArchiveFileMagicEnum { StreamingArchiveFile_GLUE_NOT_IMPLEMENTED = 0 };

	inline void operator delete(void *p, StreamingArchiveFileMagicEnum)
	{
		free(p);
	}
};

void (*bfme_ramfile_placement_delete)(void *, RAMFile::RAMFileMagicEnum) =
	&RAMFile::operator delete;

void (*bfme_streamingarchivefile_placement_delete)(void *, StreamingArchiveFile::StreamingArchiveFileMagicEnum) =
	&StreamingArchiveFile::operator delete;
