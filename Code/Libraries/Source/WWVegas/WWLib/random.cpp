// WWLib random number generators, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWLib/random.cpp). Only functions located in the
// binary are defined here; BFME does not use the member (minval, maxval)
// operators, it instantiates Pick_Random_Number<T> directly.
#include "random.h"

#define ARRAY_SIZE(x) (int(sizeof(x)/sizeof(x[0])))  // from always.h

int RandomClass::operator ()(void)
{
	Seed = (Seed * MULT_CONSTANT) + ADD_CONSTANT;
	return((Seed >> THROW_AWAY_BITS) & (~((~0) << SIGNIFICANT_BITS)));
}

Random2Class::Random2Class(unsigned seed) :
	Index1(0),
	Index2(103)
{
	Random3Class random(seed);
	for (int index = 0; index < ARRAY_SIZE(Table); index++) {
		Table[index] = random;
	}
}

int Random2Class::operator() (void)
{
	Table[Index1] ^= Table[Index2];
	int val = Table[Index1];
	Index1++;
	Index2++;
	if (Index1 >= ARRAY_SIZE(Table)) Index1 = 0;
	if (Index2 >= ARRAY_SIZE(Table)) Index2 = 0;
	return(val);
}

int Random3Class::Mix1[20] = {
	0x0baa96887, 0x01e17d32c, 0x003bcdc3c, 0x00f33d1b2,
	0x076a6491d, 0x0c570d85d, 0x0e382b1e3, 0x078db4362,
	0x07439a9d4, 0x09cea8ac5, 0x089537c5c, 0x02588f55d,
	0x0415b5e1d, 0x0216e3d95, 0x085c662e7, 0x05e8ab368,
	0x03ea5cc8c, 0x0d26a0f74, 0x0f3a9222b, 0x048aad7e4
};

int Random3Class::Mix2[20] = {
	0x04b0f3b58, 0x0e874f0c3, 0x06955c5a6, 0x055a7ca46,
	0x04d9a9d86, 0x0fe28a195, 0x0b1ca7865, 0x06b235751,
	0x09a997a61, 0x0aa6e95c8, 0x0aaa98ee1, 0x05af9154c,
	0x0fc8e2263, 0x0390f5e8c, 0x058ffd802, 0x0ac0a5eba,
	0x0ac4874f6, 0x0a9df0913, 0x086be4c74, 0x0ed2c123b
};

int Random3Class::operator() (void)
{
	int loword = Seed;
	int hiword = Index++;
	for (int i = 0; i < 4; i++) {
		int hihold  = hiword;
		int temp    = hihold ^  Mix1[i];
		int itmpl   = temp   &  0xffff;
		int itmph   = temp   >> 16;
		temp    = itmpl * itmpl + ~(itmph * itmph);
		temp    = (temp >> 16) | (temp << 16);
		hiword  = loword ^ ((temp ^ Mix2[i]) + itmpl * itmph);
		loword  = hihold;
	}
	return(hiword);
}

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0df   /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

Random4Class::Random4Class(unsigned int seed)
{
	if (!seed) seed=4375;
	mt[0]= seed & 0xffffffff;
	for (mti=1; mti<N; mti++)
		mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
}

int Random4Class::operator() (void)
{
	unsigned int y;
	static unsigned int mag01[2]={0x0, MATRIX_A};
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (mti >= N) { /* generate N words at one time */
		int kk;
		for (kk=0;kk<N-M;kk++) {
			y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
			mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		for (;kk<N-1;kk++) {
			y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
			mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
		mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];

		mti = 0;
	}

	y = mt[mti++];
	y ^= TEMPERING_SHIFT_U(y);
	y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
	y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
	y ^= TEMPERING_SHIFT_L(y);
	int *x=(int *)&y;
	return *x;
}

float Random4Class::Get_Float()
{
	int x=(*this)();
	unsigned int *y=(unsigned int *) &x;
	return (*y)*2.3283064370807973754314699618685e-10f;
}

template int Pick_Random_Number<RandomClass>(RandomClass &, int, int);
template int Pick_Random_Number<Random2Class>(Random2Class &, int, int);
template int Pick_Random_Number<Random3Class>(Random3Class &, int, int);
template int Pick_Random_Number<Random4Class>(Random4Class &, int, int);
