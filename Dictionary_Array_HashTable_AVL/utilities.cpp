#include"utilities.h"
void swapHE(hashElement& a, hashElement& b) {
	hashElement c = a;
	a = b;
	b = c;
}
string encrypt(string root) {
	string enc = "";
	if (int(root[0]) == -61 || int(root[0]) == -59) {
		enc += to_string(int('O') + 1 + 666);
		root += UTF8_ENCRYPTED_MASK;
	}
	else if (int(root[0]) == -62) {
		enc += to_string(int('L') + 1 + 666);
		root += UTF8_ENCRYPTED_MASK;
	}
	for (int i = 0; i < root.length(); i++) {
		if (root[i] == '-' || root[i] == '\'') {
			enc += "000"; 
			continue; 
		}
		string te = to_string(int(root[i]) + 666);
		while (te.length() < 3)
			te = '0' + te; 
		enc +=  te;
	}
	//cout << enc <<" " <<root<<" " <<endl; 
	return enc;

}
string formalize(string w) { 
	if (w[0] == '-')
		w =	 w.substr(1, w.length()); 
	w[0] = toupper(w[0]); 
	for (int i = 1; i < w.length(); i++)
		w[i] = tolower(w[i]);
	return w; 
}
int locatePrime(int size) {
	int p = size;
	while (true) {
		bool chk = true;
		for (int i = 2; i < int(sqrt(size)); i++)
			if (p % i == 0) {
				chk = false;
				break;
			}
		if (chk)
			return p;
		p--;
	}
}
wstring wformalize(wstring w) {
	if (w[0] == '-')
		w = w.substr(1, w.length());
	w[0] = toupper(w[0]);
	for (int i = 1; i < w.length(); i++)
		w[i] = tolower(w[i]);
	return w;
}
hashElement wfilter(wstring raw) {
	hashElement t;
	for (int i = 0; i < raw.length() - 1; i++)
		if (raw[i] == ' ' && raw[i + 1] == ' ') {
			t.keyword = raw.substr(0, i);
			while (t.keyword[0] == ' ') {
				t.keyword.erase(0, 1);
			}
			t.keyword = wformalize(t.keyword);
			t.meaning = raw.substr(i + 2, raw.length() - 1 - (i + 2) + 1);
			break;
		}

	return t;
}