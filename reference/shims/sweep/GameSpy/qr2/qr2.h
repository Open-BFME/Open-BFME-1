/*
**	GameSpy qr2 SDK shim — minimal declarations for sweep compilation.
**	PeerThread.cpp references these through the Peer SDK chain.
*/

#pragma once

#ifndef __QR2_H__
#define __QR2_H__

typedef enum {
	key_server,
	key_player,
	key_team,
} qr2_key_type;

typedef enum {
	e_qrnoerror,
	e_qrwsockerror,
	e_qrbinderror,
	e_qrdnserror,
	e_qrconnerror,
} qr2_error_t;

typedef void *qr2_buffer_t;
typedef void *qr2_keybuffer_t;

// standard registered keys (qr2regkeys.h); ZH's custom keys start past
// NUM_RESERVED_KEYS
#define HOSTNAME_KEY    1
#define GAMENAME_KEY    2
#define GAMEVER_KEY     3
#define HOSTPORT_KEY    4
#define MAPNAME_KEY     5
#define GAMETYPE_KEY    6
#define GAMEVARIANT_KEY 7
#define NUMPLAYERS_KEY  8
#define NUMTEAMS_KEY    9
#define MAXPLAYERS_KEY  10
#define GAMEMODE_KEY    11
#define TEAMPLAY_KEY    12
#define FRAGLIMIT_KEY   13
#define TIMELIMIT_KEY   14
#define PASSWORD_KEY    15
#define PID__KEY        24

void qr2_buffer_add(qr2_buffer_t buffer, const char *value);
void qr2_buffer_add_int(qr2_buffer_t buffer, int value);
void qr2_keybuffer_add(qr2_keybuffer_t keybuffer, int keyid);
void qr2_register_key(int keyid, const char *keyname);

extern char qr2_registered_key_list[][64];

#endif // __QR2_H__
