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
#ifndef _SB_CRYPT_H
#define _SB_CRYPT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GOACryptState
{
    unsigned char cards[256];       // A permutation of 0-255.
    unsigned char rotor;            // Index that rotates smoothly
    unsigned char ratchet;                    // Index that moves erratically
    unsigned char avalanche;                  // Index heavily data dependent
    unsigned char last_plain;                 // Last plain text byte
    unsigned char last_cipher;                // Last cipher text byte
} GOACryptState;



void GOACryptInit(GOACryptState *state, unsigned char *key, unsigned char keysize);
void GOAHashInit(GOACryptState *state);
unsigned char GOAEncryptByte(GOACryptState *state, unsigned char b);   // Encrypt byte
void GOAEncrypt(GOACryptState *state, unsigned char *bp, int len);   // Encrypt byte array
unsigned char GOADecryptByte(GOACryptState *state, unsigned char b);       // Decrypt byte.
void GOADecrypt(GOACryptState *state,unsigned char *bp, int len);   // decrypt byte array
void GOAHashFinal(GOACryptState *state, unsigned char *hash, unsigned char hashlength); // Hash length (16-32)

#ifdef __cplusplus
}
#endif


#endif
