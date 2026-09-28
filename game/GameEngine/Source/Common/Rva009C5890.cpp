// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggTheora SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE Theora SOURCE CODE IS COPYRIGHT (C) 2002-2003                *
 * by the Xiph.Org Foundation http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

  function:
  last mod: $Id: idct.c,v 1.6 2003/12/03 08:59:41 arc Exp $

 ********************************************************************/

/*
Copyright (c) 2002, Xiph.org Foundation

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

- Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

- Neither the name of the Xiph.org Foundation nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
// Reference: libtheora-1.0alpha3/lib/idct.c (Xiph official release).
// Opaque linkage identity; retail constants, both passes and dequant call witnessed.
typedef short ogg_int16_t;
typedef short Q_LIST_ENTRY;
typedef int ogg_int32_t;
void Rva009C54A0DequantZigzag(const short *, const short *, int *);
#define IdctAdjustBeforeShift 8
#define xC1S7 64277
#define xC2S6 60547
#define xC3S5 54491
#define xC4S4 46341
#define xC5S3 36410
#define xC6S2 25080
#define xC7S1 12785

void Rva009C5890(  Q_LIST_ENTRY * InputData,
                ogg_int16_t *QuantMatrix,
                ogg_int16_t * OutputData ) {
  ogg_int32_t IntermediateData[64];
  ogg_int32_t * ip = IntermediateData;
  ogg_int16_t * op = OutputData;

  ogg_int32_t _A, _B, _C, _D, _Ad, _Bd, _Cd, _Dd, _E, _F, _G, _H;
  ogg_int32_t _Ed, _Gd, _Add, _Bdd, _Fd, _Hd;
  ogg_int32_t t1, t2;

  int loop;

  Rva009C54A0DequantZigzag( QuantMatrix, InputData, IntermediateData);

  /* Inverse DCT on the rows now */
  for ( loop = 0; loop < 8; loop++){
    /* Check for non-zero values */
    if ( ip[0] | ip[1] | ip[2] | ip[3] | ip[4] | ip[5] | ip[6] | ip[7] ) {
      t1 = (xC1S7 * ip[1]);
      t2 = (xC7S1 * ip[7]);
      t1 >>= 16;
      t2 >>= 16;
      _A = t1 + t2;

      t1 = (xC7S1 * ip[1]);
      t2 = (xC1S7 * ip[7]);
      t1 >>= 16;
      t2 >>= 16;
      _B = t1 - t2;

      t1 = (xC3S5 * ip[3]);
      t2 = (xC5S3 * ip[5]);
      t1 >>= 16;
      t2 >>= 16;
      _C = t1 + t2;

      t1 = (xC3S5 * ip[5]);
      t2 = (xC5S3 * ip[3]);
      t1 >>= 16;
      t2 >>= 16;
      _D = t1 - t2;

      t1 = (xC4S4 * (_A - _C));
      t1 >>= 16;
      _Ad = t1;

      t1 = (xC4S4 * (_B - _D));
      t1 >>= 16;
      _Bd = t1;


      _Cd = _A + _C;
      _Dd = _B + _D;

      t1 = (xC4S4 * (ip[0] + ip[4]));
      t1 >>= 16;
      _E = t1;

      t1 = (xC4S4 * (ip[0] - ip[4]));
      t1 >>= 16;
      _F = t1;

      t1 = (xC2S6 * ip[2]);
      t2 = (xC6S2 * ip[6]);
      t1 >>= 16;
      t2 >>= 16;
      _G = t1 + t2;

      t1 = (xC6S2 * ip[2]);
      t2 = (xC2S6 * ip[6]);
      t1 >>= 16;
      t2 >>= 16;
      _H = t1 - t2;


      _Ed = _E - _G;
      _Gd = _E + _G;

      _Add = _F + _Ad;
      _Bdd = _Bd - _H;

      _Fd = _F - _Ad;
      _Hd = _Bd + _H;

      /* Final sequence of operations over-write original inputs. */
      ip[0] = (ogg_int16_t)((_Gd + _Cd )   >> 0);
      ip[7] = (ogg_int16_t)((_Gd - _Cd )   >> 0);

      ip[1] = (ogg_int16_t)((_Add + _Hd )  >> 0);
      ip[2] = (ogg_int16_t)((_Add - _Hd )  >> 0);

      ip[3] = (ogg_int16_t)((_Ed + _Dd )   >> 0);
      ip[4] = (ogg_int16_t)((_Ed - _Dd )   >> 0);

      ip[5] = (ogg_int16_t)((_Fd + _Bdd )  >> 0);
      ip[6] = (ogg_int16_t)((_Fd - _Bdd )  >> 0);

    }

    ip += 8;                    /* next row */
  }

  ip = IntermediateData;

  for ( loop = 0; loop < 8; loop++){
    /* Check for non-zero values (bitwise or faster than ||) */
    if ( ip[0 * 8] | ip[1 * 8] | ip[2 * 8] | ip[3 * 8] |
         ip[4 * 8] | ip[5 * 8] | ip[6 * 8] | ip[7 * 8] ) {

      t1 = (xC1S7 * ip[1*8]);
      t2 = (xC7S1 * ip[7*8]);
      t1 >>= 16;
      t2 >>= 16;
      _A = t1 + t2;

      t1 = (xC7S1 * ip[1*8]);
      t2 = (xC1S7 * ip[7*8]);
      t1 >>= 16;
      t2 >>= 16;
      _B = t1 - t2;

      t1 = (xC3S5 * ip[3*8]);
      t2 = (xC5S3 * ip[5*8]);
      t1 >>= 16;
      t2 >>= 16;
      _C = t1 + t2;

      t1 = (xC3S5 * ip[5*8]);
      t2 = (xC5S3 * ip[3*8]);
      t1 >>= 16;
      t2 >>= 16;
      _D = t1 - t2;

      t1 = (xC4S4 * (_A - _C));
      t1 >>= 16;
      _Ad = t1;

      t1 = (xC4S4 * (_B - _D));
      t1 >>= 16;
      _Bd = t1;


      _Cd = _A + _C;
      _Dd = _B + _D;

      t1 = (xC4S4 * (ip[0*8] + ip[4*8]));
      t1 >>= 16;
      _E = t1;

      t1 = (xC4S4 * (ip[0*8] - ip[4*8]));
      t1 >>= 16;
      _F = t1;

      t1 = (xC2S6 * ip[2*8]);
      t2 = (xC6S2 * ip[6*8]);
      t1 >>= 16;
      t2 >>= 16;
      _G = t1 + t2;

      t1 = (xC6S2 * ip[2*8]);
      t2 = (xC2S6 * ip[6*8]);
      t1 >>= 16;
      t2 >>= 16;
      _H = t1 - t2;

      _Ed = _E - _G;
      _Gd = _E + _G;

      _Add = _F + _Ad;
      _Bdd = _Bd - _H;

      _Fd = _F - _Ad;
      _Hd = _Bd + _H;

      _Gd += IdctAdjustBeforeShift;
      _Add += IdctAdjustBeforeShift;
      _Ed += IdctAdjustBeforeShift;
      _Fd += IdctAdjustBeforeShift;

      /* Final sequence of operations over-write original inputs. */
      op[0*8] = (ogg_int16_t)((_Gd + _Cd )   >> 4);
      op[7*8] = (ogg_int16_t)((_Gd - _Cd )   >> 4);

      op[1*8] = (ogg_int16_t)((_Add + _Hd )  >> 4);
      op[2*8] = (ogg_int16_t)((_Add - _Hd )  >> 4);

      op[3*8] = (ogg_int16_t)((_Ed + _Dd )   >> 4);
      op[4*8] = (ogg_int16_t)((_Ed - _Dd )   >> 4);

      op[5*8] = (ogg_int16_t)((_Fd + _Bdd )  >> 4);
      op[6*8] = (ogg_int16_t)((_Fd - _Bdd )  >> 4);
    }else{
      op[0*8] = 0;
      op[7*8] = 0;
      op[1*8] = 0;
      op[2*8] = 0;
      op[3*8] = 0;
      op[4*8] = 0;
      op[5*8] = 0;
      op[6*8] = 0;
    }

    ip++;                       /* next column */
    op++;
  }
}
