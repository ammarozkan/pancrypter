#include "bytehasher.h"
#include "req_funcs.h"

char* encrypter_(char c_enc, char* key,unsigned int key_size,unsigned int enc_style)
{
	char* text = (char*)malloc(key_size+1);
	for (int i = 0;i<key_size;i++) text[i] = key[i];
	unsigned int went_enc_ = 0;

	for (;went_enc_<enc_style;went_enc_++)
	{
		char* hashed = hasher(text,key_size+1+went_enc_);
		int _pass = 0;
		for (int i = 0;i<HASH_BYTE;i++) _pass += i;
		free(hashed);
		text[_pass] = (text[_pass%(key_size+1)]+1)%256;
	}

	text[key_size] = c_enc;
	char* hashed = hasher(text,key_size+1);
	free(text);
	return hashed;
}

char decrypter_(char hash[HASH_BYTE], char* key, unsigned int key_size, unsigned int max_enc_style)
{
	for (char c_enc = 0;c_enc<256;c_enc++)
	{
		for (unsigned int enc_style=0;enc_style<max_enc_style;enc_style++)
		{
			char* temp_enc=encrypter_(c_enc,key,key_size,enc_style);
			if (string_equality(temp_enc,hash,HASH_BYTE) == 1) return c_enc;
			free(temp_enc);
		}
	}
	return '0';
}