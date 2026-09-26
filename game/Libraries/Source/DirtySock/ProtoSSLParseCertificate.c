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
