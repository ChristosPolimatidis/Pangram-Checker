#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cjson/cJSON.h>

#include "pangram.h"

char* open_list()
{
	FILE* fp = fopen("list_of_1000_strings.json", "r");
	if (!fp) 
	{
        	printf("[open_list]: [Error]: File opening failed\n");
        	exit(EXIT_FAILURE);
    	}
	
	printf("[open_list]: File was opened successfully\n");
	
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);

	char* json_buffer = malloc(size + 1);
	if (!json_buffer) 
	{
		printf("[open_list]: [Error]: Malloc failed\n");
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	size_t nread = fread(json_buffer, 1, size, fp);
    	fclose(fp);
    	json_buffer[nread] = '\0';

	return json_buffer;
}

pan_string_t* pan_str_init()
{
	int i,j;
	
	pan_string_t* str_arr = malloc(JSON_STR_NUM * sizeof(pan_string_t));
	if (!str_arr) 
	{
		printf("[pan_str_init]: [Error]: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	printf("[pan_str_init]: Memory for the strings was allocated successfully\n");

	for (i = 0; i < JSON_STR_NUM; i++) 
	{
		str_arr[i].string = NULL;

		for (j = 0; j < 26; j++)  str_arr[i].alphabet_letters[j] = 0;
		
		str_arr[i].category = NON_PANGRAM;
	}
	
	printf("[pan_str_init]: Strings' properties were initialized successfully\n");
	
	return str_arr;
}

void load_strings_into_array(char* json_buffer, pan_string_t* str_arr)
{
	cJSON *root = cJSON_Parse(json_buffer);
	if (!root || !cJSON_IsArray(root)) 
	{
		printf("[load_strings_into_array]: [Error]: Invalid JSON (expected array of strings)\n");
		if (root) cJSON_Delete(root);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < JSON_STR_NUM; i++) 
	{
		cJSON *item = cJSON_GetArrayItem(root, i);

		if (!cJSON_IsString(item) || !item->valuestring)
			str_arr[i].string = strdup(""); 
		else
			str_arr[i].string = strdup(item->valuestring);
    	}

	printf("[load_strings_into_array]: JSON strings were extracted and stored succesfully\n");

	cJSON_Delete(root);
}

void pangram_checking_parser(pan_string_t* str_arr)
{
	int i;

	for(i = 0; i < JSON_STR_NUM; i++)
	{
		char* current = str_arr[i].string;
		int j = 0;

		for (j = 0; current[j] != '\0'; j++)
		{
			char lowercase_char = (unsigned char)tolower(current[j]);
			
			if(!isalpha(lowercase_char))	continue;
			
			str_arr[i].alphabet_letters[map_letter(lowercase_char)]++;
		}

		int isPangram = 0, isPerfectPangram = 0;

		for(j = 0; j < 26; j++)
		{
			if(str_arr[i].alphabet_letters[j] == 0)
			{
				str_arr[i].category = NON_PANGRAM;
				break;
			}
			else if(str_arr[i].alphabet_letters[j] > 1)
			{
				isPerfectPangram = 0;
				isPangram++;
			}
			else if(str_arr[i].alphabet_letters[j] == 1)
			{
				isPerfectPangram++;
				isPangram++;
			}
		}

		if(isPerfectPangram == 26)	str_arr[i].category = PERFECT_PANGRAM;
		else if(isPangram == 26)	str_arr[i].category = PANGRAM;
	}

	printf("[pangram_checking_parser]: Strings' letters where counted successfully\n");
	printf("[pangram_checking_parser]: All strings recieved a category value successfully\n");
}

alphabet_map_t map_letter(char character)
{
	switch(character)
	{
		case 'a':
			return A;
		case 'b':
			return B;
		case 'c':
			return C;
		case 'd':
			return D;
		case 'e':
			return E;
		case 'f':
			return F;
		case 'g':
			return G;
		case 'h':
			return H;
		case 'i':
			return I;
		case 'j':
			return J;
		case 'k':
			return K;
		case 'l':
			return L;
		case 'm':
			return M;
		case 'n':
			return N;
		case 'o':
			return O;
		case 'p':
			return P;
		case 'q':
			return Q;
		case 'r':
			return R;
		case 's':
			return S;
		case 't':
			return T;
		case 'u':
			return U;
		case 'v':
			return V;
		case 'w':
			return W;
		case 'x':
			return X;
		case 'y':
			return Y;
		case 'z':
			return Z;
		default:
			printf("[map_letter]: [Error]: Make sure you use isalpha() before using me :)\n");
			exit(EXIT_FAILURE);
	}
}

void print_results(pan_string_t* str_arr)
{
	int i = 0;
	unsigned int nonPangrams = 0, pangrams = 0, perfectPangrams = 0;

	for(i = 0; i< JSON_STR_NUM; i++)
	{
		if(str_arr[i].category == NON_PANGRAM)		nonPangrams++;
		else if(str_arr[i].category == PANGRAM)		pangrams++;
		else if(str_arr[i].category == PERFECT_PANGRAM)	perfectPangrams++;
	}

	printf("\n====================================\n");
	printf("		Results");
	printf("\n====================================\n");
	printf("Non Pangram strings: %d\n",nonPangrams);
	printf("Pangram strings: %d\n", pangrams);
	printf("Perfect Pangram strings: %d\n", perfectPangrams);
	printf("====================================\n");
}
