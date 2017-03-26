#include "passgen.h"

using namespace passgen;

char Passgen::getChar(bool specialChars, bool vowelChars, bool constChars, bool numChars) {

	string numbers = "0123456789";
	string constanants = "bcdfghjklmnpqrstvwxyz";
	string vowels = "aeiouy";
	string specials = "!#$&*-_.";
	string all = specials + vowels + constanants + numbers;
	string ncv = numbers + constanants + vowels;
	string cns = constanants + numbers + specials;
	string vns = vowels + numbers + specials;
	string vcs = vowels + constanants + specials;
	string vc = vowels + constanants;
	string vs = vowels + specials;
	string nc = numbers + constanants;
	string ns = numbers + specials;
	string cs = constanants + specials;
	string vn = vowels + numbers;
	int n = rand() % numbers.length();
	int v = rand() % vowels.length();
	int c = rand() % constanants.length();
	int s = rand() % specials.length();
	int a = rand() % all.length();
	int NCV = rand() % ncv.length();
	int CNS = rand() % cns.length();
	int VNS = rand() % vns.length();
	int VCS = rand() % vcs.length();
	int VC = rand() % vc.length();
	int VS = rand() % vs.length();
	int NC = rand() % nc.length();
	int NS = rand() % ns.length();
	int CS = rand() % cs.length();
	int VN = rand() % vn.length();
	char theChar;

	if (specialChars && vowelChars && constChars && numChars) {
		theChar = all[a];
	}
	else if (!specialChars && !vowelChars && !constChars && numChars) {
		theChar = numbers[n];
	}
	else if (!specialChars && !vowelChars && constChars && !numChars) {
		theChar = constanants[c];
	}
	else if (!specialChars && vowelChars && !constChars && !numChars) {
		theChar = vowels[v];
	}
	else if (specialChars && !vowelChars && !constChars && !numChars) {
		theChar = specials[s];
	}
	else if (!specialChars && vowelChars && constChars && numChars) {
		theChar = ncv[NCV];
	}
	else if (specialChars && !vowelChars && constChars && numChars) {
		theChar = cns[CNS];
	}
	else if (specialChars && vowelChars && !constChars && numChars) {
		theChar = vns[VNS];
	}
	else if (specialChars && vowelChars && constChars && !numChars) {
		theChar = vcs[VCS];
	}
	else if (!specialChars && vowelChars && constChars && !numChars) {
		theChar = vc[VC];
	}
	else if (!specialChars && !vowelChars && constChars && numChars) {
		theChar = nc[NC];
	}
	else if (!specialChars && vowelChars && !constChars && numChars) {
		theChar = vn[VN];
	}
	else if (specialChars && !vowelChars && !constChars && numChars) {
		theChar = ns[NS];
	}
	else if (specialChars && vowelChars && !constChars && !numChars) {
		theChar = vs[VS];
	}
	else if (specialChars && !vowelChars && constChars && !numChars) {
		theChar = cs[CS];
	}
	else {
		return 0;
	}
	return theChar;
}

string Passgen::password(int length, bool specialChars, bool vowelChars, bool constChars, bool numChars, bool upperOnly, bool lowerOnly) {
	string pass;
	int r = rand() % 5;

	for (int i = 1; i <= length; i++) {

		int r = rand() % 5;

		if ((upperOnly && lowerOnly) || (!upperOnly && !lowerOnly)) {
			if (r % 2 == 1) {
				pass += tolower(getChar(specialChars, vowelChars, constChars, numChars));
			}
			else {
				pass += toupper(getChar(specialChars, vowelChars, constChars, numChars));
			}
		}
		else if (upperOnly && !lowerOnly) {
			pass += toupper(getChar(specialChars, vowelChars, constChars, numChars));
		}
		else if (!upperOnly && lowerOnly) {
			pass += tolower(getChar(specialChars, vowelChars, constChars, numChars));
		}
		else {
			pass = "";
		}

	}

	return pass;
}

void Passgen::usage(char *argv[]) {
	string pass = password(10, false, true, true, true, true, false);
	cout << endl << "Usage: " << endl;
	cout << argv[0] << " length " << "(svcn(u)(l)) " << endl;
	cout << endl << "Example: ";
	cout << endl << argv[0] << " 10 vcnu" << endl;
	cout << "Output: " << pass << endl;
}

int main(int argc, char * argv[]) {
	srand(time(NULL));
	srand(rand());
	string pass;
	unsigned int length = 0;
	bool specials = false;
	bool vowels = false;
	bool consts = false;
	bool nums = false;
	bool upper = false;
	bool lower = false;
	if (argc >= 2 && argc <= 3 ) {
		length = strtol(argv[1], NULL, 10);
		if (argc == 3) {
			for (int i = 0; i <= 5; i++) {
				if (argv[2][i] == 's') { specials = true; }
				if (argv[2][i] == 'v') { vowels = true; }
				if (argv[2][i] == 'c') { consts = true; }
				if (argv[2][i] == 'n') { nums = true; }
				if (argv[2][i] == 'u') { upper = true; }
				if (argv[2][i] == 'l') { lower = true; }
			}
		}
		else {
			specials = true;
			vowels = true;
			consts = true;
			nums = true;
		}
	}
	if ((length > 0) && (specials || vowels || consts || nums)) {
		pass = Passgen::password(length, specials, vowels, consts, nums, upper, lower);
		if (pass == "") {
			Passgen::usage(argv);
		}
		else {
			cout << endl << pass << endl;
		}
	}
	else {
		Passgen::usage(argv);
	}
	return 0;
}
