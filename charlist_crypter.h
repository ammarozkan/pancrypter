#include "crypter.h"

char *charlist_encrypt_(char* entry,unsigned int entry_size, char* key, unsigned int key_size)
{
	char* result = (char*)malloc(entry_size*HASH_BYTE);
	for (unsigned int i = 0;i<entry_size;i++)
	{
		char* temp_enc = encrypter_(entry[i],key,key_size,i%20);
		for (unsigned int j = 0;j<HASH_BYTE;j++) result[i*HASH_BYTE + j] = temp_enc[j];
		free(temp_enc);
	}
	return result;
}

char *charlist_decrypt_(char* data,unsigned int data_size, char* key, unsigned int key_size)
{
	char* result = (char*)malloc(data_size/HASH_BYTE);
	for(unsigned int i = 0;i<data_size/HASH_BYTE;i++)
		result[i] = decrypter_(&data[i*HASH_BYTE],key,key_size,20);
	return result;
}

int file_encrypt(char* in,char* out, char* key, unsigned int key_size,unsigned int max_style)
{
	int r = 0;
	FILE *f_in,*f_out;
	f_in = fopen(in,"rb");
	f_out = fopen(out,"wb");

	char inchar;
	int nob = fread(&inchar,1,1,f_in);
	int i = 0;
	while (nob!=0)
	{
		char* temp_enc = encrypter_(inchar,key,key_size,i++%max_style);
		if (!fwrite(temp_enc,HASH_BYTE,1,f_out)) { r = -1; break; }
		free(temp_enc);
		nob = fread(&inchar,1,1,f_in);
		printf("Encrypted %i characters.\n",i+1);
	}

	fclose(f_in);
	fclose(f_out);
	return r;
}

int file_decrypt(char* in, char* out, char* key, unsigned int key_size,unsigned int max_style)
{
	int r = 0;
	FILE *f_in,*f_out;
	f_in = fopen(in,"rb");
	f_out = fopen(out,"wb");

	
	int i = 0;
	char* encrypted = (char*)malloc(HASH_BYTE);
	int nob = fread(encrypted,1,4,f_in);
	while(nob != 0)
	{
		char temp_denc = decrypter_(encrypted,key,key_size,max_style);
		printf("Decrypted %i characters.\n\n",i);
		if (!fwrite(&temp_denc,1,1,f_out)) { r = -1; break; }
		printf("Writed:%c(DIGIT:%d)\n",temp_denc,temp_denc);
		
		int nob = fread(encrypted,1,4,f_in);
		printf("Readed");
		for (int j = 0;j<HASH_BYTE;j++) printf(":%d",encrypted[j]);
		printf(" C:%i\n",nob);
		if (nob == 0) break;

		i++;
	}

	printf("end#\n");

	free(encrypted);

	fclose(f_in);
	fclose(f_out);
	return r;
}