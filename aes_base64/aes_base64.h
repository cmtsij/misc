#ifndef PKI_CLIENT_H
#define PKI_CLIENT_H

#include "openssl/sha.h"
#include "openssl/aes.h"
#include "aes.h"
#include "base64.h"


#define METHOD_AES	(0x01)
#define METHOD_BASE64	(0x02)

#define FILE_ENV_CERT	"/tmp/clientcert.tmp"
#define FILE_ENV_KEY	"/tmp/clientkey.tmp"

#define COMMAND_GET_CERT	"fw_printenv clientcert > "FILE_ENV_CERT
#define COMMAND_GET_KEY		"fw_printenv clientcert > "FILE_ENV_KEY


#endif	//PKI_CLIENT_H
