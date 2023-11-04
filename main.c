#include <stdio.h>
#define RAK "RBNDOMKEYHEREAA" // RANDOM_ACCESS_KEY
#define RAK_S 15 // RANDOM_ACCESS_KEY__SIZE

#include "charlist_crypter.h"


//ME [command] [file_in] [key]/ [file_out]
int main(int argv, char* argc[])
{
	int maxtype = 3, enc_res = 0;
	char* file_in = "NONE";
	char* file_out = "output";
	char* key = "creativity/";
	int work_type = 0; // 0:nothing, 1:encryption, 2:decryption, 3:packaging, 4:depackaging
	for (int i = 0;2*i+2<argv;i++)
	{
		int j = 2*i+1;
		if (string_equality(argc[j],"--command",9))
		{
			if (string_equality(argc[j+1],"enc",3)) work_type = 1;
			else if (string_equality(argc[j+1],"dec",3)) work_type = 2;
			else if (string_equality(argc[j+1],"pack",4)) work_type = 3;
			else if (string_equality(argc[j+1],"depack",6)) work_type = 4;
			else printf("COMMAND NOT UNDERSTANDED:%s\n",argc[j+1]);
		} else if (string_equality(argc[j],"--key",5)) {key = argc[j+1];}
		else if (string_equality(argc[j],"--input",7)) {file_in = argc[j+1];}
		else if (string_equality(argc[j],"--output",8)) {file_out = argc[j+1];}
		else if(string_equality(argc[j],"--maxtype",9)) maxtype = atoi(argc[j+1]);
	}
	if (work_type == 1) 
		enc_res = file_encrypt(file_in,file_out,key,get_size_Spec(key,'/'),maxtype);
	else if (work_type == 2) 
		enc_res = file_decrypt(file_in,file_out,key,get_size_Spec(key,'/'),maxtype);
	else { printf("COMMAND NOT FOUND:'%s'\n",argc[1]); return -3; }
	if (enc_res != 0) {printf("ERROR DURING CRYPTION FUNCTIONS."); return -4;}

	//if (argv < 1) {printf("ARG NOT ENOUGH:%i ARG INPUT CAME\n",argv-1); return -1;}

	return 0;
}