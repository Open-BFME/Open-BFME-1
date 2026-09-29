// cl: /O2 /GR- /EHsc-
// nbench sysspec.c file helpers, LINUX branch, verbatim (inputs/vendor/nbench/
// sysspec.c). readfile at 0x008792C0 and writefile at 0x00879320, 90 B each,
// sit right after CloseFile (0x008792A0, Rva008792A0CloseFile.cpp). Upstream's
// writefile really does report ERROR_FILEWRITE when the write succeeds.

struct FILE;
typedef unsigned int size_t;
extern "C" __declspec(dllimport) int __cdecl fseek(FILE *, long, int);
extern "C" __declspec(dllimport) size_t __cdecl fread(void *, size_t, size_t, FILE *);
extern "C" __declspec(dllimport) size_t __cdecl fwrite(const void *, size_t, size_t, FILE *);

#define SEEK_SET 0
#define ERROR_FILEREAD 11
#define ERROR_FILEWRITE 12
#define ERROR_FILESEEK 14

void readfile(FILE *fhandle,            /* File handle */
	unsigned long offset,           /* Offset into file */
	unsigned long nbytes,           /* # of bytes to read */
	void *buffer,                   /* Buffer to read into */
	int *errorcode)                 /* Returned error code */
{
long newoffset;                         /* New offset by fseek */
size_t nelems;                          /* Expected return code from read */
size_t readcode;                        /* Actual return code from read */

*errorcode=0;
newoffset=fseek(fhandle,(long)offset,SEEK_SET);
if(newoffset==-1L)
{       *errorcode=ERROR_FILESEEK;
	return;
}
nelems=(size_t)(nbytes & 0xFFFF);
readcode=fread(buffer,(size_t)1,nelems,fhandle);
if(readcode!=nelems)
	*errorcode=ERROR_FILEREAD;
return;
}

void writefile(FILE *fhandle,           /* File handle */
	unsigned long offset,           /* Offset into file */
	unsigned long nbytes,           /* # of bytes to read */
	void *buffer,                   /* Buffer to read into */
	int *errorcode)                 /* Returned error code */
{
long newoffset;                         /* New offset by lseek */
size_t nelems;                          /* Expected return code from write */
size_t writecode;                       /* Actual return code from write */

*errorcode=0;
newoffset=fseek(fhandle,(long)offset,SEEK_SET);
if(newoffset==-1L)
{       *errorcode=ERROR_FILESEEK;
	return;
}
nelems=(size_t)(nbytes & 0xFFFF);
writecode=fwrite(buffer,(size_t)1,nelems,fhandle);
if(writecode==nelems)
	*errorcode=ERROR_FILEWRITE;
return;
}
