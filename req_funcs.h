int string_equality(char* p1, char* p2,unsigned int size)
{
	for (int i = 0;i<size;i++) if (p1[i] != p2[i]) return 0;
	return 1;
}

unsigned int get_size(char*c)
{
	int result = -1;
	while(c[++result]!='\n');
	return result;
}

unsigned int get_size_Spec(char*c,char end)
{
	int result = -1;
	while(c[++result]!=end);
	return result;
}