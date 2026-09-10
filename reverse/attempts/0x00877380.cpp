// ?DoHuffIteration@@YAKPAD00KKPAUhuff_node@@@Z
// partial score=0.86 date=2026-09-10
// cl: /O2 /G7 /GS /MD /GR- /EHsc- -Ivendor/nbench

#include <strings.h>

typedef unsigned long ulong;
typedef unsigned long u32;
typedef unsigned char u8;

typedef struct huff_node
{
	unsigned char c;
	float freq;
	int parent;
	int left;
	int right;
} huff_node;

static huff_node *g_hufftree;

extern const float g_bfmeDefaultBU;
extern const float BfmeZeroRange;
extern const float g_bfmeUint32Scale;
#define BfmeHuffInitial (*(const float *)0x01088830)

extern void ji_008793a0(void);
extern unsigned long Rva008793B0(unsigned long);

#define StartStopwatch ((ulong (__cdecl *)())ji_008793a0)
#define StopStopwatch ((ulong (__cdecl *)(ulong))Rva008793B0)

static void SetCompBit(u8 *comparray, u32 bitoffset, char bitchar)
{
	u32 byteoffset;
	int bitnumb;

	byteoffset=bitoffset>>3;
	bitnumb=bitoffset % 8;
	if(bitchar=='1')
		comparray[byteoffset]|=(1<<bitnumb);
	else
		comparray[byteoffset]&=~(1<<bitnumb);
}

static int GetCompBit(u8 *comparray, u32 bitoffset)
{
	u32 byteoffset;
	int bitnumb;

	byteoffset=bitoffset>>3;
	bitnumb=bitoffset % 8;
	return((1<<bitnumb) & comparray[byteoffset]);
}

// ?DoHuffIteration@@YAKPAD00KKPAUhuff_node@@@Z
static ulong DoHuffIteration(char *plaintext,
	char *comparray,
	char *decomparray,
	ulong arraysize,
	ulong nloops,
	huff_node *hufftree)
{
	unsigned int i;
	long j;
	int root;
	float lowfreq1, lowfreq2;
	int lowidx1, lowidx2;
	long bitoffset;
	long textoffset;
	long maxbitoffset;
	long bitstringlen;
	int c;
	char bitstring[30];
	ulong elapsed;
	elapsed=StartStopwatch();
	if(nloops)
	{
	do
	{
		--nloops;
		for(i=0;i<256;i=i+1)
		{
			hufftree[i].freq=(float)0.0;
			hufftree[i].c=(unsigned char)i;
		}

		for(j=0;j<arraysize;++j)
			hufftree[(int)plaintext[j]].freq+=g_bfmeDefaultBU;

		for(i=0;i<256;++i)
			if(hufftree[i].freq != BfmeZeroRange)
				hufftree[i].freq/=(float)arraysize;

		bzero((char *)&hufftree[256], sizeof(huff_node) * 256);

		for(i=0;i<512;++i)
		{
			if(hufftree[i].freq==BfmeZeroRange)
				hufftree[i].parent=32000L;
			else
				hufftree[i].parent=hufftree[i].left=hufftree[i].right=-1;
		}

		root=255;
		while(1)
		{
			lowfreq1=BfmeHuffInitial;
			lowfreq2=BfmeHuffInitial;
			lowidx1=-1;
			lowidx2=-1;

			for(i=0;i<=root;++i)
				if(hufftree[i].parent<0)
					if(hufftree[i].freq<lowfreq1)
					{
						lowfreq1=hufftree[i].freq;
						lowidx1=i;
					}

			if(lowidx1==-1) break;

			for(i=0;i<=root;++i)
				if((hufftree[i].parent<0) && (i!=lowidx1))
					if(hufftree[i].freq<lowfreq2)
					{
						lowfreq2=hufftree[i].freq;
						lowidx2=i;
					}

			if(lowidx2==-1) break;

			root++;
			hufftree[lowidx1].parent=root;
			hufftree[lowidx2].parent=root;
			hufftree[root].freq=lowfreq1+lowfreq2;
			hufftree[root].left=lowidx1;
			hufftree[root].right=lowidx2;
			hufftree[root].parent=-2;
		}

		bitoffset=0L;
		for(i=0;i<arraysize;++i)
		{
			c=(int)plaintext[i];
			bitstringlen=0;
			while(hufftree[c].parent!=-2)
			{
				if(hufftree[hufftree[c].parent].left==c)
					bitstring[bitstringlen]='0';
				else
					bitstring[bitstringlen]='1';
				c=hufftree[c].parent;
				bitstringlen++;
			}

			while(bitstringlen--)
			{
				SetCompBit((u8 *)comparray,(u32)bitoffset,bitstring[bitstringlen]);
				++bitoffset;
			}
		}

		maxbitoffset=bitoffset;
		bitoffset=0;
		textoffset=0;
		do {
			i=root;
			while(hufftree[i].left!=-1)
			{
				if(GetCompBit((u8 *)comparray,(u32)bitoffset)==0)
					i=hufftree[i].left;
				else
					i=hufftree[i].right;
				bitoffset++;
			}
			decomparray[textoffset]=hufftree[i].c;
			++textoffset;
		} while(bitoffset<maxbitoffset);
	} while(nloops);
	}
	return(StopStopwatch(elapsed));
}

ulong Rva00877380ProbeAnchor(char *plaintext, char *comparray,
	char *decomparray, ulong arraysize, ulong nloops, huff_node *tree)
{
	g_hufftree=tree;
	return DoHuffIteration(plaintext, comparray, decomparray, arraysize,
		nloops, g_hufftree);
}
