#include"avlTree.h"
nodeAVL* newAVLNode(wstring keyword, wstring meaning) {
	nodeAVL* p = new nodeAVL;
	p->lChild = nullptr;
	p->rChild = nullptr;
	p->weight = 1;
	p->keyword = keyword;
	p->meaning = meaning; 
	return p;
}

int getWeight(nodeAVL* p) {
	if (!p)
		return 0;
	else
		return p->weight;
}


nodeAVL* rightRotate(nodeAVL* p) {
	nodeAVL* pivot = p->lChild;

	p->lChild = pivot->rChild;
	pivot->rChild = p;

	p->weight = 1 + max(getWeight(p->lChild), getWeight(p->rChild));
	pivot->weight = 1 + max(getWeight(pivot->lChild), getWeight(pivot->rChild));

	return pivot;
}
nodeAVL* leftRotate(nodeAVL* p) {
	nodeAVL* pivot = p->rChild;

	p->rChild = pivot->lChild;
	pivot->lChild = p;

	p->weight = 1 + max(getWeight(p->lChild), getWeight(p->rChild));
	pivot->weight = 1 + max(getWeight(pivot->lChild), getWeight(pivot->rChild));
	return pivot;
}
nodeAVL* checkAndRotate(nodeAVL* p) {
	if (getWeight(p->lChild) > 1 + getWeight(p->rChild)) { // Left
		if (getWeight(p->lChild->lChild) > getWeight(p->lChild->rChild)) // Left
			return rightRotate(p);
		else {  // right
			p->lChild = leftRotate(p->lChild);
			return rightRotate(p);
		}
	}
	else if (getWeight(p->lChild) + 1 < getWeight(p->rChild)) { //Right
		if (getWeight(p->rChild->lChild) > getWeight(p->rChild->rChild)) {// Left
			p->rChild = rightRotate(p->rChild);
			return leftRotate(p);
		}
		else // right
			return leftRotate(p);
	}
	return p;
}

nodeAVL* pushAVLNode(nodeAVL*& pos, wstring keyword, wstring meaning) {
	if (!pos) {
		pos = newAVLNode(keyword, meaning);
		return pos;
	}
	if (keyword > pos->keyword)
		pos->rChild = pushAVLNode(pos->rChild, keyword, meaning);
	else if (keyword < pos->keyword)
		pos->lChild = pushAVLNode(pos->lChild, keyword, meaning);
	else
		return pos;
	pos->weight = 1 + max(getWeight(pos->lChild), getWeight(pos->rChild));

	return checkAndRotate(pos);

}
void traverseAVL(nodeAVL* p, wfstream& fo) {
	if (p) {
		traverseAVL(p->lChild, fo);
		fo << p->keyword << " : " << p->meaning << endl;
		traverseAVL(p->rChild, fo);
	}

}
void destroyAVLTree(nodeAVL*& p) {
	if (p) {
		if (p->lChild) destroyAVLTree(p->lChild);
		if (p->rChild) destroyAVLTree(p->rChild);
		delete p;
		p = nullptr;
	}
}

void readFileAVL(AVLTree& avl) {
	wfstream fi(SOURCE_DATASET, ios::in);
	vector< hashElement > temp;
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	wstring t1, t2, t3;
	hashElement fi1, fi2, fi3;
	srand(time(NULL));
	while (getline(fi, t1))
		if (t1.length() > 2) {
			fi1 = wfilter(t1);
			break;
		}
	while (getline(fi, t2))
		if (t2.length() > 2) {
			fi2 = wfilter(t2);
			break;
		}
	while (getline(fi, t3)) {
		if (t3.length() > 2) {
			fi3 = wfilter(t3);
			if (fi2.keyword == L"Usage" && !((fi3.keyword >= fi2.keyword) && (fi1.keyword <= fi2.keyword))) {
				fi1.meaning += L"\n Usage : " + fi2.meaning;
				fi2 = fi3;
				continue;
			}
			else if (fi3.keyword == L"") {
				fi2.meaning += L"\n " + fi3.meaning;
				continue;
			}
			else if (fi2.keyword == fi3.keyword && fi2.meaning == fi3.meaning) {
				continue;
			}
			else {
				temp.push_back(fi1);
				fi1 = fi2;
				fi2 = fi3;
			}
		}
	}
	temp.push_back(fi2);
	temp.push_back(fi3);
	for (int i = temp.size() - 1; i >= 0; i--) {
		int pos = (rand() % (i + 1));
		avl.root = pushAVLNode(avl.root, temp[pos].keyword, temp[pos].meaning);
		swapHE(temp[pos], temp[i]);
	}


	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
}
void writeFileAVL(AVLTree avl) {
	wfstream fo(RESULT_SET, ios::out);
	// quickSort(dictionary, 0, size);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();

	traverseAVL(avl.root, fo);

	cout << "Save to " << RESULT_SET << " sucessfully !\n";
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fo.close();
	system(RESULT_SET);

}


nodeAVL* searchWordAVL(nodeAVL* p, wstring key) {
	if (!p)
		return nullptr;
	else {
		if (p->keyword == key)
			return p;
		else if (p->keyword < key)
			return searchWordAVL(p->rChild, key);
		else
			return searchWordAVL(p->lChild, key);
	}
}
void findingWordAVL(AVLTree avl) {
	wstring key;
	wcin.ignore();

	wfstream fi(INP_DESTINATION, ios::in);
	wfstream fo(OUT_DESTINATION, ios::out);
	cout << "Enter the word that you want to find in the " << INP_DESTINATION << ", output in the " << OUT_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, key);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	nodeAVL* p = searchWordAVL(avl.root, wformalize(key));
	if (!p) {
		fo << "Not Found\n";
		cout << "Not Found\n";
	}
	else {
		fo << p->keyword << L" : " << p->meaning << endl;
		cout << "Found\n";

	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
	fo.close();
	system(OUT_DESTINATION);
}