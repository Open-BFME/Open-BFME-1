/*
**	GameSpy Persistent Storage SDK shim — minimal declarations for sweep compilation
**	The real Persist SDK headers are not available; this supplies the types
**	that ZH's headers reference so the sweep build can proceed.
*/

#pragma once

#ifndef __GPERSIST_H__
#define __GPERSIST_H__

typedef enum persisttype_e {
	pd_public_ro,
	pd_public_rw,
	pd_private_ro,
	pd_private_rw,
} persisttype_t;

void PersistThink();
void GetPersistDataValues(int localid, int profileid, persisttype_t type,
	int index, const char* keys, void(*callback)(int, int, persisttype_t, int, int, char*, int, void*),
	void* instance);
void SetPersistDataValues(int localid, int profileid, persisttype_t type,
	int index, const char* data, void(*callback)(int, int, persisttype_t, int, int, void*),
	void* instance);

#include "GameSpy/gstats/gstats.h"

// gstats gcd (cdkey) SDK globals written by PersistentStorageThread
extern char gcd_secret_key[256];
extern char gcd_gamename[256];

#endif // __GPERSIST_H__
