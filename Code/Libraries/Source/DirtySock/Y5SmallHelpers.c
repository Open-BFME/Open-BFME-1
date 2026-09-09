// cl: /Od /GZ /GS /MD /DNDEBUG

void *memcpy(void *dest, const void *src, unsigned int count);
void *memset(void *dest, int value, unsigned int count);
int memcmp(const void *first, const void *second, unsigned int count);
int sprintf(char *buffer, const char *format, ...);
unsigned int strlen(const char *text);
char *strcpy(char *dest, const char *src);

int Rva008118D0(void)
{
	return -1;
}

int Rva008118F0(void)
{
	return -1;
}

int Rva0080E330(void *crypto, int length)
{
	if (*(int *)crypto != 0)
		length += 8;
	return length;
}

int Rva0080E300(const int *crypto, int length)
{
	if (crypto[0] != 0 && crypto[1] != 0 && length >= 8)
		length -= 8;
	return length;
}

void Rva0080F300(void *state, unsigned char *data, int length);
void Rva0080F200(void *state, const unsigned char *key, int length, int rounds);
void Rva0080E500(unsigned char *object);
void Rva007F0030(void *object);
void Rva00812CD0(void *object);

void Rva0080E410(void *crypto, unsigned char *data, int length)
{
	if (*(int *)crypto != 0)
		Rva0080F300((unsigned char *)crypto + 0x10A, data, length);
}

void Rva0080E1C0(int *crypto, unsigned char *data, int length)
{
	if (crypto[0] != 0)
	{
		Rva0080F300((unsigned char *)crypto + 8, data, length);
		crypto[1] = 1;
	}
}

int Rva0080DFC0(int *crypto, const unsigned char *key)
{
	crypto[0] = 0;
	if (key != 0)
	{
		crypto[0] = 1;
		crypto[1] = 0;
		Rva0080F200((unsigned char *)crypto + 0x10A, key, 0x10, -1);
		Rva0080F200((unsigned char *)crypto + 8, key + 0x10, 0x10, -1);
	}
	return crypto[0];
}

void Rva0080F530(void *dest, const void *src, int length)
{
	memcpy(dest, src, length);
}

void Rva0080F3D0(unsigned char *state, const void *first, int firstLength,
	const void *second, int secondLength)
{
	*(int *)(state + 0x400) = firstLength;
	*(int *)(state + 0x488) = secondLength;
	memcpy(state + 0x404, first, firstLength);
	memcpy(state + 0x48C, second, secondLength);
}

int Rva0080FED0(unsigned short *result, int limbs,
	const unsigned char *bytes, int byteCount);
void Rva0080FB40(unsigned short *result, int count,
	const unsigned short *bits, const unsigned short *addend,
	const unsigned short *modulus);
void Rva0080FFB0(const unsigned short *limbs, int limbCount,
	unsigned char *bytes, int byteCount);

void Rva0080F5A0(unsigned char *state, unsigned char *owner,
	const unsigned char *first, int firstLength,
	const unsigned char *second, int secondLength)
{
	int i;
	int count;
	unsigned int exponent;
	unsigned short modulus[ 0x100 ];
	unsigned short base[ 0x100 ];
	unsigned short result[ 0x100 ];

	count = Rva0080FED0(modulus, -1, first, firstLength);
	Rva0080FED0(base, -1, owner, firstLength);

	exponent = 0;
	for ( i = 0; i < secondLength; i++ )
		exponent = ( exponent << 8 ) | second[ i ];

	if ( exponent == 3 )
	{
		Rva0080FB40(result, count, base, base, modulus);
		Rva0080FB40(result, count, result, base, modulus);
	}
	else if ( exponent == 0x11 )
	{
		Rva0080FB40(result, count, base, base, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, base, modulus);
	}
	else if ( exponent == 0x10001 )
	{
		Rva0080FB40(result, count, base, base, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, result, modulus);
		Rva0080FB40(result, count, result, base, modulus);
	}
	else
	{
		memset( result, 0, 0x200 );
		result[ count - 1 ] = 1;
		for ( ; exponent != 0; exponent >>= 1 )
		{
			if ( ( exponent & 1 ) != 0 )
				Rva0080FB40(result, count, result, base, modulus);
			Rva0080FB40(base, count, base, base, modulus);
		}
	}

	Rva0080FFB0(result, count, state, firstLength);
}

void Rva0080F550(unsigned char *state)
{
	Rva0080F5A0(state, state, state + 0x404, *(int *)(state + 0x400),
		state + 0x48C, *(int *)(state + 0x488));
}

int Rva0080DF70(const unsigned char *source, void *first, void *second)
{
	if (first != 0)
		memcpy(first, source, 0x20);
	if (second != 0)
		memcpy(second, source + 0x20, 0x34);
	return 1;
}

int Rva0080DC90(const unsigned char *first, const void *second,
	unsigned char *combined)
{
	memcpy(combined, first, 0x20);
	memcpy(combined + 0x20, second, 0x10);
	memcpy(combined + 0x30, first, 0x20);
	return 0x50;
}

void Rva0080E4D0(void *object)
{
	Rva0080E500(object);
	Rva007F0030(object);
}

void Rva0080F0D0(unsigned char *object)
{
	if (*(void **)(object + 0x64) != 0)
	{
		Rva00812CD0(*(void **)(object + 0x64));
		*(void **)(object + 0x64) = 0;
	}
}

void *Rva007F0000(unsigned int size);

void Rva0080EEF0(char **slot, const char *text)
{
	if (*slot != 0)
		Rva007F0030(*slot);
	*slot = (char *)Rva007F0000(strlen(text) + 1);
	strcpy(*slot, text);
}

int Rva007FDB60(void *socket, int selector, void *buffer, int bufferSize);

int Rva0080DBF0(unsigned char *object, int selector, void *buffer,
	int bufferSize)
{
	int result;

	result = -1;
	if (*(void **)object != 0)
	{
		result = Rva007FDB60(*(void **)object, selector, buffer, bufferSize);
		if (selector == 'stat' && *(int *)(object + 0x118) == 1)
			result = 0;
		if (selector == 'stat' && result > 0
			&& *(int *)(object + 0x118) != 0x14
			&& *(int *)(object + 0x118) != 0x10)
			result = 0;
	}
	return result;
}

void Rva0080DCE0(unsigned char *dest, const char *source,
	unsigned int length)
{
	unsigned int i;
	unsigned int j;
	const char *p;

	if (length >= 0x20)
		memcpy(dest, source, 0x20);
	else
	{
		p = source;
		for (i = 0, j = 0; i != length; i++)
		{
			dest[j] ^= p[i];
			j = (j + 1) % 0x20;
		}
	}
}

int NetGameUtilControl(void *object, int selector, int value);

void *Rva0080E440(void)
{
	void *object;

	object = Rva007F0000(0xC0);
	if (object != 0)
		memset(object, 0, 0xC0);
	NetGameUtilControl(object, 'mwid', 0xF0);
	NetGameUtilControl(object, 'minp', 0x20);
	NetGameUtilControl(object, 'mout', 0x20);
	return object;
}

struct Rva0080E500Callback
{
	void *field0;
	void (__cdecl *cleanup)(struct Rva0080E500Callback *callback);
};

struct Rva0080E500Slot
{
	struct Rva0080E500Callback *callback;
	int field4;
	int field8;
};

void Rva0080E500(unsigned char *object)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		if (((struct Rva0080E500Slot *)(object + 0x90))[i].callback != 0)
		{
			((struct Rva0080E500Slot *)(object + 0x90))[i].callback->cleanup(
				((struct Rva0080E500Slot *)(object + 0x90))[i].callback);
		}
		((struct Rva0080E500Slot *)(object + 0x90))[i].callback = 0;
	}
	if (*(void **)(object + 0x68) != 0)
	{
		Rva00812CD0(*(void **)(object + 0x68));
		*(void **)(object + 0x68) = 0;
	}
	if (*(void **)(object + 0x64) != 0)
	{
		Rva00812CD0(*(void **)(object + 0x64));
		*(void **)(object + 0x64) = 0;
	}
	*(int *)(object + 0x7C) = 0;
}

void Rva00810020(void *context);
void Rva00810060(void *context, const unsigned char *data, int length);
void Rva00810FF0(void *context, char *out, int outSize);

int Rva0080E350(const int *crypto, unsigned char *data, int length)
{
	unsigned char context[0x54];
	int payloadLength;

	payloadLength = length - 8;
	if (*crypto == 0)
		return 0;
	if (payloadLength < 0)
		return -1;
	Rva00810020(context);
	Rva00810060(context, data, payloadLength);
	Rva00810FF0(context, (char *)data + payloadLength, 8);
	return 0;
}

int Rva0080E200(const int *crypto, const unsigned char *data, int length)
{
	unsigned char context[0x54];
	char digest[0x10];

	if (crypto[0] == 0 || crypto[1] == 0)
		return 0;
	if (length < 8)
		return -1;
	Rva00810020(context);
	Rva00810060(context, data, length - 8);
	Rva00810FF0(context, digest, 0x10);
	if (memcmp(data + length - 8, digest, 8) != 0)
		return -2;
	return 0;
}

void Rva0080DD80(unsigned char *output, const unsigned char *key,
	int value, const char *name)
{
	unsigned char context[0x54];
	unsigned char rc4[0x102];
	char text[0x100];
	int combinedLength;

	sprintf(text, "send-%s-send", name);
	Rva00810020(context);
	Rva00810060(context, (const unsigned char *)text, -1);
	Rva00810FF0(context, (char *)output, 0x10);

	sprintf(text, "recv-%s-recv", name);
	Rva00810020(context);
	Rva00810060(context, (const unsigned char *)text, -1);
	Rva00810FF0(context, (char *)output + 0x10, 0x10);

	memcpy(output + 0x30, output, 0x20);
	*(int *)(output + 0x50) = value;

	sprintf(text, "iv-%s-iv", name);
	Rva00810020(context);
	Rva00810060(context, (const unsigned char *)text, -1);
	Rva00810FF0(context, (char *)output + 0x20, 0x10);

	combinedLength = Rva0080DC90(key, output + 0x20,
		(unsigned char *)text);
	Rva0080F200(rc4, (const unsigned char *)text, combinedLength, -1);
	Rva0080F300(rc4, output + 0x30, 0x24);
}

int Rva0080E030(int *crypto, const unsigned char *input,
	const unsigned char *key, unsigned int totalLength)
{
	unsigned char rc4[0x102];
	unsigned char header[0x34];
	int combinedLength;
	unsigned char combined[0x100];

	if (input == 0)
	{
		crypto[0] = 0;
		return 0;
	}
	memcpy(header, input, 0x34);
	combinedLength = Rva0080DC90(key, header, combined);
	Rva0080F200(rc4, combined, combinedLength, -1);
	Rva0080F300(rc4, header + 0x10, 0x24);
	if (*(unsigned int *)(header + 0x30) > totalLength
		|| totalLength - *(unsigned int *)(header + 0x30) > 0xE10)
		return -1;
	Rva0080F200((unsigned char *)crypto + 8, header + 0x10, 0x10, -1);
	Rva0080F200((unsigned char *)crypto + 0x10A, header + 0x20, 0x10, -1);
	crypto[0] = 1;
	crypto[1] = 0;
	return 1;
}

unsigned char *Rva0080C6F0(unsigned char *object);
int Rva007FDA50(void *socket, char *buffer, int length, int flags,
	void *from, int *fromLength);

int Rva0080DA50(unsigned char *object, char *output, int length)
{
	int result;
	unsigned char *state;

	result = -1;
	state = *(unsigned char **)(object + 0x120);
	if (*(int *)(object + 0x118) == 0x10)
	{
		result = 0;
		if (*(void **)(state + 0x801C) == 0)
		{
			if (*(int *)(state + 0x400C) == *(int *)(state + 0x4010))
			{
				if (*(int *)(state + 0x4010) > 4)
				{
					*(int *)(state + 0x4014) = 0;
					*(unsigned char **)(state + 0x801C) = Rva0080C6F0(object);
				}
				else if (*(int *)(object + 0x11C) != 0)
					result = -1;
			}
		}
		if (*(void **)(state + 0x801C) != 0)
		{
			result = *(int *)(state + 0x4010) - *(int *)(state + 0x4014);
			if (length < result)
				result = length;
			memcpy(output, *(unsigned char **)(state + 0x801C)
				+ *(int *)(state + 0x4014), result);
			*(int *)(state + 0x4014) += result;
			if (*(int *)(state + 0x4014) >= *(int *)(state + 0x4010))
			{
				*(int *)(state + 0x4010) = 0;
				*(int *)(state + 0x400C) = 0;
				*(void **)(state + 0x801C) = 0;
			}
		}
	}
	if (*(int *)(object + 0x118) == 0x14)
		result = Rva007FDA50(*(void **)object, output, length, 0, 0, 0);
	if (result > 0 && result < length)
		output[result] = 0;
	return result;
}

/* 0x0080C6F0 builds the next received packet from the framed input ring.
 * Rva0080DA50 is the matched caller: it invokes this helper when the ring is
 * drained and then consumes the returned packet pointer.  The backend fields
 * are the same state words used by that reader and by the Y2 comm pump. */
unsigned char *Rva0080C6F0(unsigned char *object)
{
	int length;
	unsigned char context[ 0x54 ];
	unsigned char header[ 4 ];
	unsigned char digest[ 0x10 ];
	unsigned char *state;
	unsigned char *packet;

	state = *(unsigned char **)(object + 0x120);
	packet = state + 0x4018;
	packet = packet + ( packet[ 0 ] <= 0x7F ? 3 : 2 );
	length = (int)( state + 0x4018 + *(int *)(state + 0x4010) - packet );

	if( *(int *)(state + 0x80A8) > 0 )
	{
		Rva0080F300( state + 0x86BC, packet, length );

		header[ 0 ] = (unsigned char)( *(unsigned int *)(state + 0x8018) >> 24 );
		header[ 1 ] = (unsigned char)( *(unsigned int *)(state + 0x8018) >> 16 );
		header[ 2 ] = (unsigned char)( *(unsigned int *)(state + 0x8018) >> 8 );
		header[ 3 ] = (unsigned char)*(unsigned int *)(state + 0x8018);

		Rva00810020( context );
		Rva00810060( context, state + 0x80AC,
			*(int *)(state + 0x80A8) );
		Rva00810060( context, packet + 0x10, length - 0x10 );
		Rva00810060( context, header, 4 );
		Rva00810FF0( context, (char *)digest, 0x10 );

		if( memcmp( digest, packet, 0x10 ) != 0 )
			packet = 0;
		else
		{
			packet = packet + 0x10;
			*(int *)(state + 0x4010) = length - 0x10;
			*(int *)(state + 0x400C) = *(int *)(state + 0x4010);
		}
	}

	*(unsigned int *)(state + 0x8018) =
		*(unsigned int *)(state + 0x8018) + 1;

	return packet;
}

char *strchr(const char *text, int character);
char *strstr(const char *text, const char *find);
void *Rva00812320(int entries);
void Rva008119A0(void *table, const char *name, const char *alias,
	int value, const char *templates, int extra);
extern char *g_Rva012C47A4;

void Rva0080EF50(unsigned char *object, const char *name, char *alias,
	int value)
{
	char *found;
	char *dest;
	char defaultName[0x100];
	const char *source;

	if (*(void **)(object + 0x64) == 0)
		*(void **)(object + 0x64) = Rva00812320(0x10);
	if (alias == 0 || *alias == 0)
	{
		sprintf(defaultName, "Default Name");
		if (*(char **)object != 0)
			source = *(char **)object;
		else
			source = g_Rva012C47A4;
		found = strstr(source, defaultName);
		if (found != 0)
		{
			found = strchr(found, ':') + 1;
			for (dest = defaultName; *found >= ' '; found++, dest++)
				*dest = *found;
			*dest = 0;
		}
		alias = defaultName;
	}
	strcpy((char *)object + 4, name);
	Rva008119A0(*(void **)(object + 0x64), name, alias, value,
		"TCP:~1:1024\tUDP:~1:1024", *(int *)(object + 0x8C));
}
