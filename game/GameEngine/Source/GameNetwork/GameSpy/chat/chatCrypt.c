// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
/* GameSpy Chat SDK -- chatCrypt.c.  Reconstructed from the 2007 SDK
   (nitrocaster/GameSpy, src/GameSpy/Chat/chatCrypt.c); see peerCallbacks.c in
   the peer/ directory next door for why the 2004 text is not in hand.

   Placement is a whole-image byte scan, not a neighbourhood argument: each of
   the three bodies compiles with ZERO relocations, and each compiled body
   occurs EXACTLY ONCE in retail's .text -- gs_prepare_key at 0x008693F0,
   gs_crypt at 0x00869550, gs_xcode_buf at 0x00869620 -- so the bytes place
   themselves and no pin is involved.

   The FILE, as opposed to the bodies, is the weaker half of the claim and is
   recorded as such.  Against it: these three sit between rows belonging to
   sb_serverlist.c and sb_queryengine.c, which is not where a chat TU would be
   expected.  For it: nothing in the vendored 2004 serverbrowsing (or anywhere
   else under this directory) references gs_prepare_key/gs_crypt/gs_xcode_buf,
   and in the 2007 SDK the only pre-common/ carrier of this exact code is
   Chat/chatCrypt.c -- common/gsRC4.c is the later refactor of the same
   routine and did not exist in 2004.  If a better-placed owner turns up, the
   names stay right and only this file's name is wrong. */
typedef struct
{
	unsigned char state[256];
	unsigned char x;
	unsigned char y;
} gs_crypt_key;

void gs_prepare_key(const unsigned char *key_data_ptr, int key_data_len, gs_crypt_key *key);
void gs_crypt(unsigned char *buffer_ptr, int buffer_len, gs_crypt_key *key);
void gs_xcode_buf(char *buf, int len, char *enckey);


#define swap_byte(x,y) t = *(x); *(x) = *(y); *(y) = t

void gs_prepare_key(const unsigned char *key_data_ptr, int key_data_len, gs_crypt_key *key)
{
	unsigned char t;
	unsigned char index1;
	unsigned char index2;
	unsigned char* state;
	int counter;
	
	state = &key->state[0];
	for(counter = 0; counter < 256; counter++)
		state[255 - counter] = (unsigned char)counter; //crt - we fill reverse of normal
	key->x = 0;
	key->y = 0;
	index1 = 0;
	index2 = 0;
	for(counter = 0; counter < 256; counter++)
	{
		index2 = (unsigned char)((key_data_ptr[index1] + state[counter] + index2) % 256);
		swap_byte(&state[counter], &state[index2]);
		index1 = (unsigned char)((index1 + 1) % key_data_len);
	}
}

void gs_crypt(unsigned char *buffer_ptr, int buffer_len, gs_crypt_key *key)
{
	unsigned char t;
	unsigned char x;
	unsigned char y;
	unsigned char* state;
	unsigned char xorIndex;
	int counter;
	
	x = key->x;
	y = key->y;
	state = &key->state[0];
	for(counter = 0; counter < buffer_len; counter++)
	{
		x = (unsigned char)((x + 1) % 256);
		y = (unsigned char)((state[x] + y) % 256);
		swap_byte(&state[x], &state[y]);
		xorIndex = (unsigned char)((state[x] + state[y]) % 256);
		buffer_ptr[counter] ^= state[xorIndex];
	}
	key->x = x;
	key->y = y;
}


void gs_xcode_buf(char *buf, int len, char *enckey)
{
	int i;
	char *pos = enckey;

	for (i = 0 ; i < len ; i++)
	{
		buf[i] ^= *pos++;
		if (*pos == 0)
			pos = enckey;
	}

}
