#ifndef PASSGEN_H
#define PASSGEN_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <string>
#include <cctype>

using namespace std;
namespace passgen {
	class Passgen {
		public:
			static string password(int length, bool specialChars, bool vowelChars, bool constChars, bool numChars, bool upperOnly, bool lowerOnly);
			static void usage(char *argv[]);
		private:
			static char getChar(bool specialChars, bool vowelChars, bool constChars, bool numChars);
	};
}
#endif
