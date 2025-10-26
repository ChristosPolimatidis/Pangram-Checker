#include <stdio.h>
#include <stdlib.h>

#include "pangram.h"

int main(void)
{
	char* json_buffer = open_list();

	//printf("[open_list]: [Debug]: Json buffer content %s\n", json_buffer);

	pan_string_t* str_arr = pan_str_init();
	
	load_strings_into_array(json_buffer, str_arr);

	free(json_buffer);
	
	pangram_checking_parser(str_arr);

	print_results(str_arr);

	for (int i = 0; i < JSON_STR_NUM; i++) free(str_arr[i].string);
	free(str_arr);
	
	return 0;
}
