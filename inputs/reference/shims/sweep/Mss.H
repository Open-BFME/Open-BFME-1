#ifndef SWEEP_MSS_H
#define SWEEP_MSS_H

#define AILCALLBACK __stdcall

typedef void *HPROVIDER;
typedef void *HSAMPLE;
typedef void *H3DSAMPLE;
typedef void *H3DPOBJECT;
typedef void *HTIMER;
typedef void *HDIGDRIVER;
// The Miles header hands WWAudio a LPWAVEFORMAT and WWAudio.cpp reads three
// fields off it, so a void* stops seventeen translation units from compiling
// for the sweep. This is the Win32 WAVEFORMAT the platform header declares.
typedef struct waveformat_tag {
	unsigned short wFormatTag;
	unsigned short nChannels;
	unsigned long  nSamplesPerSec;
	unsigned long  nAvgBytesPerSec;
	unsigned short nBlockAlign;
} WAVEFORMAT, *LPWAVEFORMAT;
typedef long S32;
typedef unsigned long U32;

#endif
