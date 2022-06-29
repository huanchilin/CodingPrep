
#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <string>

using namespace std;

bool isDuplicate(const std::string& str) {

	if (str.size() <= 1) return false;
	if (str.size() > 128) return true;

	std::array<bool, 128> arrCheck;
	arrCheck.fill(false);

	for (int i = 0; i<str.size(); i++) {
		char c = str.at(i);
		if (arrCheck[(int)c])
			return true;
		else 
			arrCheck[(int)c] = true;
	}
	return false;
}

#include <unordered_set>
// approach 2
bool isDuplicate2(const std::string& str) {
	unordered_set<char> set;

	for (int i(0); i<str.size(); i++) {
		auto iter = set.find(str.at(i));
		if (iter == set.end()) {
			set.insert(str.at(i));
		}
		else
			return true;
}

return false;
}

bool isPermutation(const string& a, const string& b) {
	if  (a.size() != b.size() ) return false;
	
	std::array<int, 128> arrTime;
	arrTime.fill(0);

	for (int i(0); i<a.size(); i++) {
		char c = a.at(i);
		arrTime[(int)c]++;
	}

	for (int i(0); i<b.size(); i++) {
		char c = b.at(i);
		arrTime[(int)c]--;

		if (arrTime[(int)c] < 0) 
			return false;
	}

    // Dont need this. Because some number will be -1
	// if (any_of(arrTime.begin(), arrTime.end(), [](int nTime){return nTime > 0;}) )
	// 	return false;
	/* else */ return true;
}

bool isPermutation2(const string& a, const string& b) {
	if  (a.size() != b.size() ) return false;
	
	string sortA = a;
    string sortB = b;

    std::sort(sortA.begin(), sortA.end());
    std::sort(sortB.begin(), sortB.end());

	for (int i(0); i<sortA.size(); i++) {
		if (sortA.at(i) !=  sortB.at(i)) return false;
	}	
	return true;
}

void uRLify(string& str, const int length) {
	string rep = "%20";
    int trueLength = length;
    for (int i(0); i<trueLength; i++) {
        if (str.at(i) == ' ') {
            str.replace(i, 1, rep);
            i+=2;
            trueLength +=2;
        }
    }
	
}

void uRLify2(string& str, const int length) {
	// find true length
	int spaceCount = 0;
	for (int i(0); i < length; i++) {
		if (str.at(i) == ' ') {
			spaceCount++;
        }
    }

    int trueLength = length + 2 * spaceCount;
    int index = trueLength - 1;

    for (int i = length - 1; i >= 0; i--) {
        if (str.at(i) == ' ') {
            str[index] = '0';
            str[index - 1] = '2';
            str[index - 2] = '%';
            index -=3;
        }
        else {
            str[index] = str[i];
            index--;
        }
    }
}

int getCharacterValue(const char c) {
    char result = tolower(c);

    if ('a' <= result && result <= 'z') {
        return result - 'a';
    }
    else 
        return -1;
}

#include <unordered_map>
// think about u dont need to iterate to find space
// and only need to allow one odd, because even string will have two odds
bool isPermuteOfPalindrome(const string& str) {

    std::array<int, 'z' - 'a' + 1> timeCount;
    timeCount.fill(0);

    for (int i(0); i< str.size(); i++) {
        int charVal = getCharacterValue(str.at(i));
        if (charVal != -1)
            timeCount[charVal]++;
    }

	int oddCount = 0;
    for (int i(0); i<timeCount.size(); i++) {
        if (timeCount.at(i) % 2 == 1)
            oddCount++;

            if (oddCount > 1) return false;
    }    
	return true;
}

// make sure to check the total length greater than 1 as that is more than 1 move. 
// control short and long string. 
#include <math.h>
bool oneAway(const string& A, const string& B) {
    if (std::abs((int)(A.size() - B.size())) > 1) 
        return false;

	bool isSameLength(A.size() == B.size());
	string shortString, longString;
    if (!isSameLength) {
        shortString = A.size() <= B.size()? A : B;
        longString = A.size() > B.size()? A : B;
    }
    else {
        shortString = A;
        longString = B;
    }

	int j(0);
	int nDiff(0);
	for (int i(0); i<shortString.size(); i++) {
		if (shortString.at(i) != longString.at(j)) {
            if (!isSameLength && nDiff > 1 ) {
                j++;
                nDiff++;
            }
            else 
                nDiff++;
        }
        else {
            j++;
        }
        if (nDiff > 1 ) return false;
	}
	return true;
}

int compressedStrLen(const string& str) {
    if (str.size() == 0) return 0;

    int outputLength(1);
    char sameChar = str.at(0);
    for (int i(1); i < str.size(); i++) {
        if (sameChar != str.at(i)) {
            outputLength +=2;
            sameChar = str.at(i);
        }
    }
    outputLength++;

    return outputLength;
}

// remember when switch to different letter you need to add it to the string first
// remember at the end you need to add the last accumulated number
// downside of this method is the insertion of += is O(n^2), so the whole algo takes O(str.size() + n^2)
// we can know the compressed string length beforehand
string stringCompressed(const string& str) {
	if (str.size() <=1 ) return str;

	int oldSize = str.size();
    int outputLength = compressedStrLen(str);
    if (oldSize < outputLength) return str;

    //

	string strOutput(outputLength, ' ');
    strOutput.at(0) = str.at(0);
	char c = str.at(0);
	int accuTime(1);
    int index(1);

	for (int i(1); i < str.size(); i++) {
		if (str.at(i) != c) {
			strOutput.at(index) = *to_string(accuTime).data();
            index++;

			accuTime = 1;

			c = str.at(i);
            strOutput.at(index) = c; 
            index++;
		}
		else {
			accuTime++;
		}
	}
    strOutput.at(index) = *to_string(accuTime).data();

	return strOutput;
}

// when we face rotating matrix, very important about the index, and offset.
// make sure we place hold the first one 
// This problem need REDO AND DRAW ON BOARD
// REDO!
bool rotateMatrix(int mat[5][5]) {
	int layers = 5 / 2;
	for (int layer(0); layer<layers; layer++) {
		int first  = layer;
		int last = 5 - layer - 1;
		for (int i(first); i<last; i++) {
			int offset = i - first;
			int temp = mat[first][i];
			//left to top
			mat[first][i] = mat[last - offset][first];
			// bot to left
			mat[last - offset][first] = mat[last][last - offset];
			// right to bot
			mat[last][last - offset] = mat[i][last];
			// top to bot
			mat[i][last] = temp;
		}
	}

	return true;
}

#include <unordered_set>
bool zeroMatrix (int matrix[5][5]){
	unordered_set<int> row, col;
	
    // search MN matrix for zeroes
	for (int i(0); i<5; i++)  {  // row 
		for (int j(0); j<5; j++) {  // col
			if ( matrix[i][j] == 0 ) {
				if (row.find(i) == row.end())
					row.insert(i);
				if (col.find(j) == col.end())
					col.insert(j);
			}
		}
	}
    
    // fill zeroes
	auto rowIter = row.begin(); 
	while (rowIter != row.end() ) {
		for (int i(0); i< 5; i++) {
			matrix[*rowIter][i] = 0;
		}
		rowIter++;
	}	

    // fill zeroes
	auto colIter = col.begin(); 
	while (colIter!= col.end() ) {
		for (int i(0); i< 5; i++) {
			matrix[i][*colIter] = 0;
		}
		colIter++;
	}	
	return true;
}

std::string removeKToMin(const std::string& str, int k) {
    if (k > str.size()) return str;

    string outStr = str;

    int index = 0;
    while (k > 0 && index < outStr.size() - 1) {
        if (outStr.at(index) >= outStr.at(index + 1)) {
            outStr.erase(index, 1);
            k--;
        }
        else {
            index ++;
        }
    }

    if (k > 0) {
        outStr.erase(outStr.size() - k, k);
    }

    return to_string(stoi(outStr));
}