//
// secure.h -- EnOcean security module header
//
#pragma once

#include "../dpride/typedefs.h"

//#include "eoif.h"

#define KEY_SIZE (128/8) //16
#define RLC_SIZE (4)
#define CMAC_SIZE (4)

//int eo_encrypt(uint8_t *key, uint8_t *in, uint8_t *out);
//int eo_decrypt(uint8_t *key, uint8_t *in, uint8_t *out);

typedef enum {
	NO_ENTRY = 0,
	FIRST_COME = 1,
	REGISTERED = 2
} PACKET_ENTRY;

typedef void *SEC_HANDLE;

INT SecInit(void);

SEC_HANDLE SecCreate(BYTE *Rlc, BYTE *Key);
void SecFree(SEC_HANDLE h);

INT SecUpdate(SEC_HANDLE h);
INT SecCheck(SEC_HANDLE h, BYTE *Rlc);
INT SecInspect(SEC_HANDLE h, BYTE *Packet);
INT SecGetRlc(SEC_HANDLE h, BYTE *Rlc);

INT SecEncrypt(SEC_HANDLE h, BYTE *Data, INT Length, BYTE *Cypher);
INT SecDecrypt(SEC_HANDLE h, BYTE *Packet, INT Length, BYTE *Data);

//
// Publickey supporting stuff
//
typedef struct _pulickey {
	UINT Id;
	BYTE Rlc[RLC_SIZE];
	BYTE Key[KEY_SIZE];
	CHAR *RlcPath;
	INT Option; // for advanced use to hide keys
} PUBLICKEY;

//
// Security supporting stuff
//
typedef struct _secure_register {
	UINT Id;
	PACKET_ENTRY Status;
	INT Info;
	INT Slf;
	SEC_HANDLE Sec;
	BYTE Rlc[RLC_SIZE];
	BYTE Key[KEY_SIZE];
} SECURE_REGISTER;

#define SECURE_REGISTER_SIZE (4)

void InitSecureRegister(void);
SECURE_REGISTER *NewSecureRegister(void);
SECURE_REGISTER *GetSecureRegister(UINT Id);
SECURE_REGISTER *ClearSecureRegister(UINT Id);

#define PUBLICKEY_TABLE_SIZE (128)
extern PUBLICKEY *PublickeyTable;

VOID ReloadPublickey(char *PublickeyPath);
VOID DeletePublickey(char *PublickeyPath);

PUBLICKEY *AddPublickey(EO_CONTROL *p, UINT Id, BYTE *Rlc, BYTE *Key);
PUBLICKEY *GetPublickey(UINT Id);
PUBLICKEY *ClearPublickey(UINT Id);
#if SEC_DEVELOP	
VOID ReadRlc(PUBLICKEY *pt);
VOID WriteRlc(PUBLICKEY *pt);
PUBLICKEY *UpdateRlc(UINT Id, BYTE *Rlc);
#endif