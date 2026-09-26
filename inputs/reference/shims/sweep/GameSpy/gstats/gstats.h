/*
**	GameSpy gstats SDK shim — minimal declarations for sweep compilation.
**	PersistentStorageThread.cpp references these through the gstats chain.
*/

#pragma once

#ifndef __GSTATS_H__
#define __GSTATS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	GE_NOERROR,
	GE_NOSOCKET,
	GE_NODNS,
	GE_DATATYPE,
	GE_NOCONNECT,
	GE_BUSY,
} GSTATSRESULT;

int InitStatsConnection(int gameport);
int IsStatsConnected(void);
void CloseStatsConnection(void);

char *GetChallenge(void *data);
void GenerateAuth(const char *challenge, char *password, char *response);

typedef void (*AuthCallBackFn)(int localid, int profileid, int authenticated,
	char *errmsg, void *instance);

void PreAuthenticatePlayerPM(int localid, int profileid, char *validate,
	AuthCallBackFn authfn, void *instance);
void PreAuthenticatePlayerCD(int localid, const char *keyname, char *keyhash,
	char *validate, AuthCallBackFn authfn, void *instance);

// game snapshot reporting
typedef void *game_t;
#define SNAP_SEND  0
#define SNAP_FINAL 1
game_t NewGame(int readonly);
int SendGameSnapShot(game_t game, const char *snapshot, int flags);
void FreeGame(game_t game);

#ifdef __cplusplus
}
#endif

#endif // __GSTATS_H__
