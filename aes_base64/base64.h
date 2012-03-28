#ifndef BASE64_H
#define BASE64_H

extern int BASE64_ENC(unsigned char *in, int in_len, unsigned char **out );
extern int BASE64_DEC(unsigned char *in, int in_len, unsigned char **out );

#endif	//BASE64_H
