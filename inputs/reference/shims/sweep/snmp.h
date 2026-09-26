/*
**  snmp.h shim — MS PSDK SNMP API declarations (asn/RFC1157 structs),
**  transcribed from the public header layout.  StagingRoomGameInfo.cpp
**  walks bind_ptr->value.asnValue.address.stream, so the struct layout
**  must match the real PSDK exactly.
*/

#pragma once

#ifndef __SNMP_H__
#define __SNMP_H__

#include <windows.h>

#pragma pack(push,4)

typedef struct {
    BYTE *stream;
    UINT  length;
    BOOL  dynamic;
} AsnOctetString;

typedef struct {
    UINT  idLength;
    UINT *ids;
} AsnObjectIdentifier;

typedef LONG           AsnInteger32;
typedef AsnInteger32   AsnInteger;
typedef ULONG          AsnUnsigned32;
typedef AsnUnsigned32  AsnUnsigned;
typedef ULARGE_INTEGER AsnCounter64;
typedef AsnUnsigned32  AsnCounter32;
typedef AsnUnsigned32  AsnGauge32;
typedef AsnUnsigned32  AsnTimeticks;
typedef AsnOctetString AsnBits;
typedef AsnOctetString AsnSequence;
typedef AsnOctetString AsnImplicitSequence;
typedef AsnOctetString AsnIPAddress;
typedef AsnOctetString AsnNetworkAddress;
typedef AsnOctetString AsnDisplayString;
typedef AsnOctetString AsnOpaque;

typedef struct {
    BYTE asnType;
    union {
        AsnInteger32        number;
        AsnUnsigned32       unsigned32;
        AsnCounter64        counter64;
        AsnOctetString      string;
        AsnBits             bits;
        AsnObjectIdentifier object;
        AsnSequence         sequence;
        AsnIPAddress        address;
        AsnCounter32        counter;
        AsnGauge32          gauge;
        AsnTimeticks        ticks;
        AsnOpaque           arbitrary;
    } asnValue;
} AsnAny;

typedef AsnObjectIdentifier AsnObjectName;
typedef AsnAny              AsnObjectSyntax;

typedef struct {
    AsnObjectName   name;
    AsnObjectSyntax value;
} SnmpVarBind;

typedef struct {
    SnmpVarBind *list;
    UINT         len;
} SnmpVarBindList;

// legacy RFC1157 names — aliases of the above, as in the MS PSDK header
typedef SnmpVarBind     RFC1157VarBind;
typedef SnmpVarBindList RFC1157VarBindList;

#pragma pack(pop)

#define ASN_UNIVERSAL   0x00
#define ASN_APPLICATION 0x40
#define ASN_CONTEXT     0x80
#define ASN_PRIVATE     0xc0
#define ASN_PRIMITIVE   0x00
#define ASN_CONSTRUCTOR 0x20

#define ASN_INTEGER          (ASN_UNIVERSAL   | ASN_PRIMITIVE   | 0x02)
#define ASN_OCTETSTRING      (ASN_UNIVERSAL   | ASN_PRIMITIVE   | 0x04)
#define ASN_OBJECTIDENTIFIER (ASN_UNIVERSAL   | ASN_PRIMITIVE   | 0x06)
#define ASN_SEQUENCE         (ASN_UNIVERSAL   | ASN_CONSTRUCTOR | 0x10)
#define ASN_IPADDRESS        (ASN_APPLICATION | ASN_PRIMITIVE   | 0x00)
#define ASN_COUNTER32        (ASN_APPLICATION | ASN_PRIMITIVE   | 0x01)

#define ASN_RFC1157_GETREQUEST     (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x00)
#define ASN_RFC1157_GETNEXTREQUEST (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x01)
#define ASN_RFC1157_GETRESPONSE    (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x02)
#define ASN_RFC1157_SETREQUEST     (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x03)
#define ASN_RFC1157_TRAP           (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x04)

#define SNMP_PDU_GET      ASN_RFC1157_GETREQUEST
#define SNMP_PDU_GETNEXT  ASN_RFC1157_GETNEXTREQUEST
#define SNMP_PDU_RESPONSE ASN_RFC1157_GETRESPONSE
#define SNMP_PDU_SET      ASN_RFC1157_SETREQUEST
#define SNMP_PDU_TRAP     ASN_RFC1157_TRAP

#endif // __SNMP_H__
