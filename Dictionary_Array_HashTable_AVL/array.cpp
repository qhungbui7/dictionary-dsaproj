#include"array.h"
void swap(word& a, word& b) {
	word c = a;
	a = b;
	b = c;
}
void quickSort(word dic[], int left, int right) {
	word mid = dic[(left + right) / 2];
	int i = left, j = right;
	while (i <= j) {
		while (dic[i].encrypted < mid.encrypted) i++;
		while (dic[j].encrypted > mid.encrypted) j--;
		if (i <= j) {
			swap(dic[i], dic[j]);
			i++;
			j--;
		}
	}
	if (left < j) quickSort(dic, left, j);
	if (i < right) quickSort(dic, i, right);
}
word filter(string raw) {
	word t;
	for (int i = 0; i < raw.length() - 1; i++)
		if (raw[i] == ' ' && raw[i + 1] == ' ') {
			t.in = raw.substr(0, i);
			if (t.in[0] == '-' || t.in[0] =='\'') {
				t.cmp = t.in.substr(1, t.in.size() - 1 + 1);
				t.cmp[0] = toupper(t.cmp[0]);
				string tc = t.cmp + OUTLIER_HASHING_STRING; 
				t.encrypted = encrypt(tc);
			}
			else {
				while (t.in[0] == ' ') {
					t.in.erase(0, 1); 
				}
				t.cmp = t.in;
				t.encrypted = encrypt(formalize(t.in));
			}
			t.mean = raw.substr(i + 2, raw.length() - 1 - (i + 2) + 1);
			break; 
		} 

	return t;
}
int binarySearch(word dictionary[], int left, int right, string key) {
	string k = encrypt(key); 
	if (right < left) return -1;
	int mid = (left + right) / 2;
	if (dictionary[mid].encrypted == k)
		return mid;
	else if (dictionary[mid].encrypted > k)
		return binarySearch(dictionary, left, mid - 1, key);
	else
		return binarySearch(dictionary, mid + 1, right, key);
}
void readFileArray(word*& dictionary, int &size, word dicT[]) {
	duration<double, milli> ms_duration; 
	auto st = steady_clock::now();
	fstream fi(SOURCE_DATASET, ios::in);
	string temp;
	while (getline(fi, temp)) {
		if (!(temp.length() <= 2)) {
			word fil = filter(temp);
			if (dictionary[size].in == "Usage" && !(fil.in < "Usage" && dictionary[size - 1].in > "Usage")) {
				dictionary[size - 1].mean += "\n  " + dictionary[size].in + " : " + dictionary[size].mean;
				dictionary[size] = fil;
				continue;
			}
			if (fil.in == "") {
				dictionary[size].mean += "\n  " + fil.mean;
				continue;
			}
			size++;
			dictionary[size] = fil;

		}
	}
	quickSort(dictionary, 0, size);
	dicT[1] = dictionary[1];
	int sizeT = 1;
	for (int i = 2; i <= size; i++) {
		if (dictionary[i - 1].in == dictionary[i].in && dictionary[i - 1].mean == dictionary[i].mean)
			continue;
		dicT[++sizeT] = dictionary[i];
		// cout << dictionary[i].encrypted <<endl; 
	}
	fi.close();
	delete[] dictionary;
	dictionary = dicT;
	size = sizeT;
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl ;
}
void writeFileArray(word* dictionary, int size) {
	fstream fo(RESULT_SET, ios::out);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	for (int i = 1; i <= size; i++) {
		fo << dictionary[i].in << " : " << dictionary[i].mean << endl;
	}
	cout << "Save to " << RESULT_SET << " sucessfully !\n";
	fo.close();
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	system(RESULT_SET);
}
void findingWordArray(word* dictionary, int size) {
	string key;
	wcin.ignore();

	fstream fi(INP_DESTINATION, ios::in);
	fstream fo(OUT_DESTINATION, ios::out);
	cout << "Enter the word that you want to find in the " << INP_DESTINATION << ", output in the " << OUT_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, key);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	int pos = binarySearch(dictionary, 1, size, formalize(key));
	if (pos == -1) {
		fo << "Not Found\n";
		cout << "Not Found\n";
	}
	else {
		fo << dictionary[pos].in << " : " << dictionary[pos].mean << endl;
		cout << "Found\n";
	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
	fo.close();
	system(OUT_DESTINATION);
	
}
void insertingWordArray(word *dictionary, int size) {
	string temp;
	wcin.ignore();
	fstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the word that you want to insert in the " << INP_DESTINATION << "\nFormat: Keyword  Meaning\n";
	system(INP_DESTINATION);
	getline(fi, temp);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	temp = formalize(temp);
	word fil = filter(temp);
	int j = ++size - 1;
	while (fil.encrypted <= dictionary[j].encrypted) {
		dictionary[j + 1] = dictionary[j];
		j--;
	}
	dictionary[j + 1] = fil;
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
}
void editingWordArray(word *dictionary, int size) {
	string temp;
	wcin.ignore();
	fstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the keyword and the new meaning that you want to edit in the " << INP_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, temp);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	word fil = filter(temp);
	int pos = binarySearch(dictionary, 1, size , formalize(fil.in));
	if (pos == -1) {
		cout << "Not Found\n";
	}
	else {
		cout << "Edited!\n";
		dictionary[pos] = fil;
	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
}
void deletingWordArray(word* dictionary, int size) {
	string key;
	wcin.ignore();
	fstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the word that you want to delete in the " <<INP_DESTINATION <<"\n";
	system(INP_DESTINATION);
	getline(fi, key);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	int pos = binarySearch(dictionary, 0, size - 1, formalize(key));
	if (pos == -1) {
		cout << "Not Found\n";
	}
	else {
		cout << "Deleted!\n";
		size--;
		for (int i = pos; i <= size; i++)
			dictionary[i] = dictionary[i + 1];
	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
}