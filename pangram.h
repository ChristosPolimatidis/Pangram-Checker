#ifndef __PANGRAM_CHECKER_H__

	#define __PANGRAM_CHECKER_H__

	#define JSON_STR_NUM 1000

	/**
	 * @enum alphabet_map
	 * @brief Maps each lowercase English letter to an index 0–25.
	 */
	enum alphabet_map 
	{
	    A = 0,
	    B = 1,
	    C = 2,
	    D = 3,
	    E = 4,
	    F = 5,
	    G = 6,
	    H = 7,
	    I = 8,
	    J = 9,
	    K = 10,
	    L = 11,
	    M = 12,
	    N = 13,
	    O = 14,
	    P = 15,
	    Q = 16,
	    R = 17,
	    S = 18,
	    T = 19,
	    U = 20,
	    V = 21,
	    W = 22,
	    X = 23,
	    Y = 24,
	    Z = 25
	};

	typedef enum alphabet_map alphabet_map_t;

	/**
	 * @enum str_category
	 * @brief Represents the classification of a string.
	 * NON_PANGRAM: does not contain all letters.
	 * PANGRAM: contains all letters (one or more).
	 * PERFECT_PANGRAM: contains each letter exactly once.
	 */
	enum str_category
	{
		NON_PANGRAM = 0,
		PANGRAM = 1,
		PERFECT_PANGRAM = 2
	};

	typedef enum str_category str_category_t;

	/**
	 * @struct pan_string
	 * @brief Holds the string, its letter counts, and its pangram category.
	 */
	struct pan_string
	{
		char* string;
		int alphabet_letters[26];
		str_category_t category;
	};

	typedef struct pan_string pan_string_t;

	/**
	 * @brief Opens the JSON file and returns its contents as a buffer.
	 * @return Pointer to allocated buffer containing JSON data.
	 */
	char* open_list();

	/**
	 * @brief Allocates and initializes an array of pan_string_t.
	 * @return Pointer to allocated array of pan_string_t.
	 */
	pan_string_t* pan_str_init();

	/**
	 * @brief Loads JSON strings into the given array of pan_string_t.
	 * @param json_buffer The raw JSON buffer containing strings.
	 * @param str_arr The array to populate with strings.
	 */
	void load_strings_into_array(char* json_buffer, pan_string_t* str_arr);

	/**
	 * @brief Parses each string and classifies it as NON_PANGRAM, PANGRAM, or PERFECT_PANGRAM.
	 * @param str_arr The array of strings to analyze.
	 */
	void pangram_checking_parser(pan_string_t* str_arr);

	/**
	 * @brief Maps a lowercase English character to its alphabet index.
	 * @param character The lowercase character to map.
	 * @return The corresponding alphabet_map_t index, or 0 if invalid.
	 */
	alphabet_map_t map_letter(char character);

	/**
	 * @brief Prints the overall results of pangram classification.
	 * @param str_arr The array of classified strings.
	 */
	void print_results(pan_string_t* str_arr);
#endif
