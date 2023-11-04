#ifndef PEN_BYTE_HASHER
#define PEN_BYTE_HASHER

#ifndef EFFECT_CONST
#define EFFECT_CONST 1.05
#endif

#ifndef LEC // LIT_EFFECT_CONST
#define LEC 3500
#endif

#ifndef EFFECT_COUNT
#define EFFECT_COUNT 10
#endif

#ifndef HASH_BYTE 
#define HASH_BYTE 4
#endif

#include <stdlib.h>

char* hasher(char* input, unsigned int size)
{
	char *result = (char*)malloc(HASH_BYTE);
	for (unsigned int i = 0;i<16;i++) result[i] = 0;

	//Hashing
	for (unsigned int i = 0;i<size;i++)
	{
		result[i%HASH_BYTE] = (result[i%HASH_BYTE]+LEC*input[i%size]);
		for (unsigned int j = i;j-i<EFFECT_COUNT;j++)
		{
			float addition = LEC*(float)input[i%size]/(EFFECT_CONST*(j-i));
			result[(i+j)%HASH_BYTE] = (result[(i+j)%HASH_BYTE]+(int)addition);
		}
	}

	return result;
}

#else
#endif