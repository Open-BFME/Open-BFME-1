/* GameSpy SDK, 2004 vintage -- pristine upstream C source.
   Sourced from the Area 51 (Inevitable Entertainment / Midway) source release,
   github.com/bisc67/Area51, Support/NetworkMgr/GameSpy -- the only public
   carrier found with the pre-2005 SDK layout (top-level nonport.c, no common/).
   Dated by nonport.h's own marker "Added by Saad Nader on 08-02-2004".
   That vintage is not assumed, it is measured: against lotrbfme.exe this tree
   scores 440 byte-exact whole functions where the 2007 SDK (nitrocaster/GameSpy,
   GS_Aluigi) scores 51 and 48 on the same TUs.
   Retail linked the DLL CRT, so libc calls are __imp__ indirect -- /MD is what
   makes those call sites byte-exact -- and built the SDK __cdecl: /Gz collapses
   the qr2+GP+ghttp core from 108 exact hits to 6.
   Win32 headers come from inputs/reference/shims/gamespy (see its windows.h): the
   toolchain ships no PlatformSDK, and the sweep shim next door is C++-only. */
/******
gbucket.h
GameSpy Stats/Tracking SDK 
  
Copyright 1999-2001 GameSpy Industries, Inc

18002 Skypark Circle
Irvine, California 92614
949.798.4200 (Tel)
949.798.4299 (Fax)
devsupport@gamespy.com

******

Please see the GameSpy Stats and Tracking SDK for more info
You should not need to use the functions in this file, they
are used to manage the buckets by the gstats SDK.
Use the type-safe bucket functions in the gstats SDK instead.
******/ 


#ifndef _GBUCKET_H_
#define _GBUCKET_H_


#ifdef __cplusplus
extern "C" {
#endif

typedef struct bucketset_s *bucketset_t;
typedef enum {bt_int, bt_float, bt_string} BucketType;

bucketset_t NewBucketSet(void);
void FreeBucketSet(bucketset_t set);
char *DumpBucketSet(bucketset_t set);

void *BucketNew(bucketset_t set, char *name, BucketType type, void *initialvalue);
void *BucketSet(bucketset_t set, char *name,void *value);
void *BucketAdd(bucketset_t set, char *name, void *value);
void *BucketSub(bucketset_t set, char *name, void *value);
void *BucketMult(bucketset_t set, char *name, void *value);
void *BucketDiv(bucketset_t set, char *name, void *value);
void *BucketConcat(bucketset_t set, char *name, void *value);
void *BucketAvg(bucketset_t set, char *name, void *value);
void *BucketGet(bucketset_t set, char *name);

/* Helper functions */
void *bint(int i);
void *bfloat(double f);
#define bstring(a) ((void *)a)

#ifdef __cplusplus
}
#endif

#endif
