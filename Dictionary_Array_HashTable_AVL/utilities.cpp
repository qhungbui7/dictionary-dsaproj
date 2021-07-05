#include"utilities.h"
string encrypt(string root) {
	string enc = "";
	if (int(root[0]) == -61 || int(root[0]) == -59) {
		enc += to_string(int('O') + 1 + 666);
		root += "3NcRyPt3d";
	}
	else if (int(root[0]) == -62) {
		enc += to_string(int('L') + 1 + 666);
		root += "3NcRyPt3d";
	}
	/*else if (int(root[0]) == 'À' || int(root[0]) == 'Á') {
		cout << "A";
		enc += to_string(int('A') + 1 + 666);
		root += "3NcRyPt3d";
	}
	else if (int(root[0]) == 'È' || int(root[0]) == 'É') {
		cout << "E";
		enc += to_string(int('E') + 1 + 666);
		root += "3NcRyPt3d";
	}*/
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
