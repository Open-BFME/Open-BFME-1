// cl: /Od /GZ /GS /MD /DNDEBUG
/* BFME-era DirtySock ProtoSSL certificate parser and verifier. */

typedef unsigned char uint8_t;

enum
{
	ASN_TYPE_INTEGER = 0x02,
	ASN_TYPE_BITSTRING = 0x03,
	ASN_TYPE_OBJECT = 0x06,
	ASN_TYPE_SEQN = 0x10,
	ASN_TYPE_SET = 0x11,
	ASN_TYPE_PRINTSTR = 0x13,
	ASN_TYPE_T61 = 0x14,
	ASN_TYPE_UTCTIME = 0x17,
	ASN_CONSTRUCT = 0x20,
	ASN_OBJ_NONE = 0,
	ASN_OBJ_COUNTRY = 1,
	ASN_OBJ_STATE = 2,
	ASN_OBJ_CITY = 3,
	ASN_OBJ_ORGANIZATION = 4,
	ASN_OBJ_UNIT = 5,
	ASN_OBJ_COMMON = 6,
	ASN_OBJ_RSA_PKCS_KEY = 7,
	ASN_OBJ_RSA_PKCS_MD5 = 8,
	ASN_OBJ_RSA_PKCS_SHA1 = 9
};

struct ProtoSSLCertIdent
{
	char country[32];
	char state[32];
	char city[32];
	char organization[32];
	char unit[32];
	char common[32];
};

struct X509Certificate
{
	int unused00;
	struct ProtoSSLCertIdent issuer;
	struct ProtoSSLCertIdent subject;
	char goodFrom[32];
	char goodTill[32];
	int serialSize;
	uint8_t serialData[32];
	int sigType;
	int sigSize;
	uint8_t sigData[128];
	int keyType;
	uint8_t unused274[64];
	int keyDataSize;
	uint8_t keyData[256];
	int keyModSize;
	uint8_t keyModData[128];
	int unused43c;
	int keyExpSize;
	uint8_t keyExpData[129];
};

struct ProtoSSLCACert
{
	const char *country;
	const char *state;
	const char *city;
	const char *organization;
	const char *unit;
	const char *common;
	const uint8_t *keyModData;
	int keyModSize;
	uint8_t keyExpData[4];
};

extern struct ProtoSSLCACert g_Rva0112CB48[];

const uint8_t *Rva0080D7A0(const uint8_t *, const uint8_t *, int *, int *);
int Rva0080D890(const void *, int);
void Rva0080D930(const char *, int, char *, int);
void Rva0080D590(const uint8_t *, int, char *);
void Rva0080D620(const uint8_t *, int, uint8_t *);
void Rva0080D6C0(struct ProtoSSLCACert *, const void *, int, void *, int);
void Rva007FE780(const char *, ...);
void *memset(void *, int, unsigned int);
void *memcpy(void *, const void *, unsigned int);
int memcmp(const void *, const void *, unsigned int);
int strcmp(const char *, const char *);

int Rva0080C960(void *state, struct X509Certificate *cert,
	const uint8_t *data, int size)
{
	int type;
	int objectType;
	const uint8_t *infoSkip;
	const uint8_t *sigSkip;
	const uint8_t *issuerSkip;
	const uint8_t *subjectSkip;
	const uint8_t *keySkip;
	const uint8_t *infoData;
	const uint8_t *last = data + size;
	int infoSize;
	int hashSize;
	uint8_t hash[20];
	uint8_t decodedHash[20];
	struct ProtoSSLCACert *ca;

	memset(cert, 0, sizeof(*cert));
	data = Rva0080D7A0(data, last, &type, &size);
	if (data == 0 || type != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -1;

	infoData = data;
	data = Rva0080D7A0(data, last, &type, &size);
	if (data == 0 || type != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -2;
	infoSize = size + 4;
	infoSkip = data + size;

	if (*data != ASN_TYPE_INTEGER)
	{
		data = Rva0080D7A0(data, last, 0, &size);
		if (data == 0)
			return -3;
		data += size;
	}

	data = Rva0080D7A0(data, infoSkip, &type, &size);
	if (data == 0 || size < 0 || (unsigned int)size > sizeof(cert->serialData))
		return -4;
	cert->serialSize = size;
	memcpy(cert->serialData, data, size);
	data += size;

	data = Rva0080D7A0(data, infoSkip, &type, &size);
	if (data == 0 || type != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -5;
	sigSkip = data + size;
	data = Rva0080D7A0(data, infoSkip, &type, &size);
	if (data == 0 || type != ASN_TYPE_OBJECT)
		return -6;
	cert->sigType = Rva0080D890(data, size);
	if (cert->sigType == ASN_OBJ_NONE)
	{
		Rva007FE780("ProtoSSL: unsupported signature algorithm\n");
		return -7;
	}
	data += size;

	data = Rva0080D7A0(sigSkip, infoSkip, &type, &size);
	if (data == 0 || type != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -8;
	issuerSkip = data + size;
	objectType = 0;
	while ((data = Rva0080D7A0(data, issuerSkip, &type, &size)) != 0)
	{
		if (type != ASN_TYPE_SEQN + ASN_CONSTRUCT && type != ASN_TYPE_SET + ASN_CONSTRUCT)
		{
			if (type == ASN_TYPE_OBJECT)
				objectType = Rva0080D890(data, size);
			if (type == ASN_TYPE_PRINTSTR || type == ASN_TYPE_T61)
			{
				if (objectType == ASN_OBJ_COUNTRY) Rva0080D930((const char *)data, size, cert->issuer.country, 32);
				if (objectType == ASN_OBJ_STATE) Rva0080D930((const char *)data, size, cert->issuer.state, 32);
				if (objectType == ASN_OBJ_CITY) Rva0080D930((const char *)data, size, cert->issuer.city, 32);
				if (objectType == ASN_OBJ_ORGANIZATION) Rva0080D930((const char *)data, size, cert->issuer.organization, 32);
				if (objectType == ASN_OBJ_UNIT) Rva0080D930((const char *)data, size, cert->issuer.unit, 32);
				if (objectType == ASN_OBJ_COMMON) Rva0080D930((const char *)data, size, cert->issuer.common, 32);
				objectType = 0;
			}
			data += size;
		}
	}

	data = Rva0080D7A0(issuerSkip, last, &type, &size);
	if (data == 0 || type != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -9;
	data = Rva0080D7A0(data, last, &type, &size);
	if (data == 0 || type != ASN_TYPE_UTCTIME)
		return -10;
	Rva0080D930((const char *)data, size, cert->goodFrom, 32);
	data += size;
	data = Rva0080D7A0(data, last, &type, &size);
	if (data == 0 || type != ASN_TYPE_UTCTIME)
		return -11;
	Rva0080D930((const char *)data, size, cert->goodTill, 32);
	data += size;

	data = Rva0080D7A0(data, last, &type, &size);
	if (data == 0 || type != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -12;
	subjectSkip = data + size;
	objectType = 0;
	while ((data = Rva0080D7A0(data, subjectSkip, &type, &size)) != 0)
	{
		if (type != ASN_TYPE_SEQN + ASN_CONSTRUCT && type != ASN_TYPE_SET + ASN_CONSTRUCT)
		{
			if (type == ASN_TYPE_OBJECT)
				objectType = Rva0080D890(data, size);
			if (type == ASN_TYPE_PRINTSTR || type == ASN_TYPE_T61)
			{
				if (objectType == ASN_OBJ_COUNTRY) Rva0080D930((const char *)data, size, cert->subject.country, 32);
				if (objectType == ASN_OBJ_STATE) Rva0080D930((const char *)data, size, cert->subject.state, 32);
				if (objectType == ASN_OBJ_CITY) Rva0080D930((const char *)data, size, cert->subject.city, 32);
				if (objectType == ASN_OBJ_ORGANIZATION) Rva0080D930((const char *)data, size, cert->subject.organization, 32);
				if (objectType == ASN_OBJ_UNIT) Rva0080D930((const char *)data, size, cert->subject.unit, 32);
				if (objectType == ASN_OBJ_COMMON) Rva0080D930((const char *)data, size, cert->subject.common, 32);
				objectType = 0;
			}
			data += size;
		}
	}

	data = Rva0080D7A0(subjectSkip, last, &type, &size);
	if (data == 0 || type != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -13;
	data = Rva0080D7A0(data, last, &type, &size);
	if (data == 0 || type != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -14;
	keySkip = data + size;
	data = Rva0080D7A0(data, keySkip, &type, &size);
	if (data == 0 || type != ASN_TYPE_OBJECT)
		return -15;
	cert->keyType = Rva0080D890(data, size);
	data = Rva0080D7A0(keySkip, last, &type, &size);
	if (data == 0 || type != ASN_TYPE_BITSTRING || size < 1 || (unsigned int)size > 256)
		return -16;
	cert->keyDataSize = size - 1;
	memcpy(cert->keyData, data + 1, size - 1);
	data += size;

	data = Rva0080D7A0(infoSkip, sigSkip, &type, &size);
	if (data == 0 || type != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -18;
	sigSkip = data + size;
	data = Rva0080D7A0(data, sigSkip, &type, &size);
	if (data == 0 || type != ASN_TYPE_OBJECT)
		return -19;
	cert->sigType = Rva0080D890(data, size);
	data = Rva0080D7A0(sigSkip, last, &type, &size);
	if (data == 0 || type != ASN_TYPE_BITSTRING || size - 1 < 0 || (unsigned int)(size - 1) > 128)
		return -20;
	cert->sigSize = size - 1;
	memcpy(cert->sigData, data + 1, size - 1);
	data += size;

	if (cert->keyType == ASN_OBJ_RSA_PKCS_KEY)
	{
		data = Rva0080D7A0(cert->keyData, cert->keyData + cert->keyDataSize, &type, &size);
		if (data == 0 || type != ASN_TYPE_SEQN + ASN_CONSTRUCT)
			return -21;
		data = Rva0080D7A0(data, cert->keyData + cert->keyDataSize, &type, &size);
		if (data == 0 || type != ASN_TYPE_INTEGER || size < 4 || (unsigned int)size > 129)
			return -22;
		if (*data == 0)
		{
			cert->keyModSize = size - 1;
			memcpy(cert->keyModData, data + 1, size - 1);
		}
		else
		{
			cert->keyModSize = size;
			memcpy(cert->keyModData, data, size);
		}
		data += size;
		data = Rva0080D7A0(data, cert->keyData + cert->keyDataSize, &type, &size);
		if (data == 0 || type != ASN_TYPE_INTEGER || size < 1 || (unsigned int)size > 129)
			return -23;
		if (*data == 0)
		{
			cert->keyExpSize = size - 1;
			memcpy(cert->keyExpData, data + 1, size - 1);
		}
		else
		{
			cert->keyExpSize = size;
			memcpy(cert->keyExpData, data, size);
		}
		data += size;
	}

	if (strcmp((const char *)state + 8, cert->subject.common) != 0)
	{
		Rva007FE780("ProtoSSL: subject mismatch %s != %s\n",
			(const char *)state + 8, cert->subject.common);
		return -24;
	}

	for (ca = g_Rva0112CB48; ca->country != 0; ca++)
	{
		if (strcmp(ca->country, cert->issuer.country) == 0 &&
			strcmp(ca->state, cert->issuer.state) == 0 &&
			strcmp(ca->city, cert->issuer.city) == 0 &&
			strcmp(ca->organization, cert->issuer.organization) == 0 &&
			strcmp(ca->common, cert->issuer.common) == 0)
			break;
	}
	if (ca->country == 0)
		return -25;
	if (ca->keyModSize != cert->sigSize)
	{
		Rva007FE780("ProtoSSL: modulus size mismatch\n");
		return -26;
	}

	switch (cert->sigType)
	{
	case ASN_OBJ_RSA_PKCS_MD5:
		Rva0080D590(infoData, infoSize, (char *)hash);
		hashSize = 16;
		break;
	case ASN_OBJ_RSA_PKCS_SHA1:
		Rva0080D620(infoData, infoSize, hash);
		hashSize = 20;
		break;
	default:
		Rva007FE780("ProtoSSL: unknown signature algorithm, should never get here\n");
		hashSize = 0;
	}

	Rva0080D6C0(ca, cert->sigData, cert->sigSize, decodedHash, hashSize);
	if (memcmp(hash, decodedHash, hashSize) != 0)
	{
		Rva007FE780("ProtoSSL: signature hash mismatch\n");
		return -27;
	}
	return 0;
}

/* Address-derived aggregate views of the retail CA backing bytes.
 * These names do not claim the original vendor array identities. */
const uint8_t g_Rva0112C9C8[384] =
{ 
	0x9f, 0x50, 0x24, 0x61, 0xed, 0xbb, 0xc5, 0x6a, 0x2d, 0x17, 0x67, 0x34, 0x6c, 0x9b, 0x59, 0xa1,
	0x2a, 0x24, 0xb4, 0x71, 0x58, 0x54, 0xc0, 0x30, 0x57, 0x9d, 0x05, 0x78, 0x14, 0x83, 0x3b, 0xa8,
	0x9c, 0x6c, 0x7a, 0x06, 0x31, 0x79, 0x3e, 0xd4, 0x9f, 0xac, 0x77, 0x0e, 0x6a, 0x43, 0x98, 0x66,
	0x75, 0xdb, 0x75, 0xe4, 0x49, 0x86, 0x3e, 0xb1, 0x62, 0x53, 0x52, 0xe7, 0xd4, 0xaa, 0x8c, 0x8d,
	0x66, 0x76, 0xb9, 0x0b, 0x1b, 0x20, 0x11, 0x33, 0x04, 0x4b, 0xd0, 0xff, 0xf0, 0x62, 0x4b, 0x50,
	0x4d, 0x3e, 0xb6, 0x17, 0x49, 0x7c, 0xd8, 0xf3, 0x9f, 0x3d, 0x95, 0x30, 0xdd, 0x6d, 0x77, 0xb0,
	0x2d, 0x37, 0xf4, 0xe4, 0xfd, 0xcd, 0x5b, 0x76, 0x94, 0xf5, 0x04, 0xf7, 0x86, 0x2f, 0xbb, 0x03,
	0x7c, 0xcc, 0x2a, 0x09, 0xce, 0x23, 0xa7, 0x3f, 0x97, 0x00, 0x55, 0xd5, 0xa0, 0x1e, 0xc5, 0xc5,
	0x92, 0x75, 0xa1, 0x5b, 0x08, 0x02, 0x40, 0xb8, 0x9b, 0x40, 0x2f, 0xd5, 0x9c, 0x71, 0xc4, 0x51,
	0x58, 0x71, 0xd8, 0xf0, 0x2d, 0x93, 0x7f, 0xd3, 0x0c, 0x8b, 0x1c, 0x7d, 0xf9, 0x2a, 0x04, 0x86,
	0xf1, 0x90, 0xd1, 0x31, 0x0a, 0xcb, 0xd8, 0xd4, 0x14, 0x12, 0x90, 0x3b, 0x35, 0x6a, 0x06, 0x51,
	0x49, 0x4c, 0xc5, 0x75, 0xee, 0x0a, 0x46, 0x29, 0x80, 0xf0, 0xd5, 0x3a, 0x51, 0xba, 0x5d, 0x6a,
	0x19, 0x37, 0x33, 0x43, 0x68, 0x25, 0x2d, 0xfe, 0xdf, 0x95, 0x26, 0x36, 0x7c, 0x43, 0x64, 0xf1,
	0x56, 0x17, 0x0e, 0xf1, 0x67, 0xd5, 0x69, 0x54, 0x20, 0xfb, 0x3a, 0x55, 0x93, 0x5d, 0xd4, 0x97,
	0xbc, 0x3a, 0xd5, 0x8f, 0xd2, 0x44, 0xc5, 0x9a, 0xff, 0xcd, 0x0c, 0x31, 0xdb, 0x9d, 0x94, 0x7c,
	0xa6, 0x66, 0x66, 0xfb, 0x4b, 0xa7, 0x5e, 0xf8, 0x64, 0x4e, 0x28, 0xb1, 0xa6, 0xb8, 0x73, 0x95,
	0x92, 0xce, 0x7a, 0xc1, 0xae, 0x83, 0x3e, 0x5a, 0xaa, 0x89, 0x83, 0x57, 0xac, 0x25, 0x01, 0x76,
	0x0c, 0xad, 0xae, 0x8e, 0x2c, 0x37, 0xce, 0xeb, 0x35, 0x78, 0x64, 0x54, 0x03, 0xe5, 0x84, 0x40,
	0x51, 0xc9, 0xbf, 0x8f, 0x08, 0xe2, 0x8a, 0x82, 0x08, 0xd2, 0x16, 0x86, 0x37, 0x55, 0xe9, 0xb1,
	0x21, 0x02, 0xad, 0x76, 0x68, 0x81, 0x9a, 0x05, 0xa2, 0x4b, 0xc9, 0x4b, 0x25, 0x66, 0x22, 0x56,
	0x6c, 0x88, 0x07, 0x8f, 0xf7, 0x81, 0x59, 0x6d, 0x84, 0x07, 0x65, 0x70, 0x13, 0x71, 0x76, 0x3e,
	0x9b, 0x77, 0x4c, 0xe3, 0x50, 0x89, 0x56, 0x98, 0x48, 0xb9, 0x1d, 0xa7, 0x29, 0x1a, 0x13, 0x2e,
	0x4a, 0x11, 0x59, 0x9c, 0x1e, 0x15, 0xd5, 0x49, 0x54, 0x2c, 0x73, 0x3a, 0x69, 0x82, 0xb1, 0x97,
	0x39, 0x9c, 0x6d, 0x70, 0x67, 0x48, 0xe5, 0xdd, 0x2d, 0xd6, 0xc8, 0x1e, 0x7b, 0x00, 0x00, 0x00
};
const char g_Rva012C4414[282] =
{ 
	0x55, 0x53, 0x00, 0x00, 0x43, 0x61, 0x6c, 0x69, 0x66, 0x6f, 0x72, 0x6e, 0x69, 0x61, 0x00, 0x00,
	0x52, 0x65, 0x64, 0x77, 0x6f, 0x6f, 0x64, 0x20, 0x43, 0x69, 0x74, 0x79, 0x00, 0x00, 0x00, 0x00,
	0x45, 0x6c, 0x65, 0x63, 0x74, 0x72, 0x6f, 0x6e, 0x69, 0x63, 0x20, 0x41, 0x72, 0x74, 0x73, 0x2c,
	0x20, 0x49, 0x6e, 0x63, 0x2e, 0x00, 0x00, 0x00, 0x4f, 0x6e, 0x6c, 0x69, 0x6e, 0x65, 0x20, 0x54,
	0x65, 0x63, 0x68, 0x6e, 0x6f, 0x6c, 0x6f, 0x67, 0x79, 0x20, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x00,
	0x4f, 0x54, 0x47, 0x33, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65,
	0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x00, 0x00, 0x55, 0x53, 0x00, 0x00,
	0x52, 0x53, 0x41, 0x20, 0x44, 0x61, 0x74, 0x61, 0x20, 0x53, 0x65, 0x63, 0x75, 0x72, 0x69, 0x74,
	0x79, 0x2c, 0x20, 0x49, 0x6e, 0x63, 0x2e, 0x00, 0x53, 0x65, 0x63, 0x75, 0x72, 0x65, 0x20, 0x53,
	0x65, 0x72, 0x76, 0x65, 0x72, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74,
	0x69, 0x6f, 0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x00, 0x00, 0x00,
	0x55, 0x53, 0x00, 0x00, 0x43, 0x61, 0x6c, 0x69, 0x66, 0x6f, 0x72, 0x6e, 0x69, 0x61, 0x00, 0x00,
	0x52, 0x65, 0x64, 0x77, 0x6f, 0x6f, 0x64, 0x20, 0x43, 0x69, 0x74, 0x79, 0x00, 0x00, 0x00, 0x00,
	0x45, 0x6c, 0x65, 0x63, 0x74, 0x72, 0x6f, 0x6e, 0x69, 0x63, 0x20, 0x41, 0x72, 0x74, 0x73, 0x2c,
	0x20, 0x49, 0x6e, 0x63, 0x2e, 0x00, 0x00, 0x00, 0x4f, 0x6e, 0x6c, 0x69, 0x6e, 0x65, 0x20, 0x54,
	0x65, 0x63, 0x68, 0x6e, 0x6f, 0x6c, 0x6f, 0x67, 0x79, 0x20, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x00,
	0x4f, 0x54, 0x47, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x20,
	0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x00
};
const char g_Rva0130ACE4[3] =
{ 
	0x00, 0x00, 0x00
};

/* Three 36-byte records followed by the retail zero sentinel. */
struct ProtoSSLCACert g_Rva0112CB48[4] =
{
	{ g_Rva012C4414 + 0, g_Rva012C4414 + 4, g_Rva012C4414 + 16, g_Rva012C4414 + 32, g_Rva012C4414 + 56, g_Rva012C4414 + 80, g_Rva0112C9C8 + 128, 128, { 0x00, 0x00, 0x00, 0x03 } },
	{ g_Rva012C4414 + 108, g_Rva0130ACE4 + 0, g_Rva0130ACE4 + 1, g_Rva012C4414 + 112, g_Rva012C4414 + 136, g_Rva0130ACE4 + 2, g_Rva0112C9C8 + 256, 125, { 0x00, 0x01, 0x00, 0x01 } },
	{ g_Rva012C4414 + 176, g_Rva012C4414 + 180, g_Rva012C4414 + 192, g_Rva012C4414 + 208, g_Rva012C4414 + 232, g_Rva012C4414 + 256, g_Rva0112C9C8 + 0, 128, { 0x00, 0x01, 0x00, 0x01 } },
	{ 0, 0, 0, 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }
};
