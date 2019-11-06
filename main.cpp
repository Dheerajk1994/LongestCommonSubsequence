#include <iostream>
#include <vector>


int sizeOfLongestCommonSbsq(const std::vector<char>& firstString, const std::vector<char>& secondString, 
	int fIndex, int sIndex,
	int** lookupArray)
{
	int result = 0;
	if (fIndex == 0 || sIndex == 0) {
		return 0;
	}
	else if (lookupArray[fIndex - 1][sIndex - 1] != -1) {
		return lookupArray[fIndex - 1][sIndex - 1];
	}
	else if (firstString.at(fIndex - 1) == secondString.at(sIndex - 1)) {	
		result = (1 + sizeOfLongestCommonSbsq(firstString, secondString, fIndex - 1, sIndex - 1, lookupArray));
	}
	else {
		int leftCall = sizeOfLongestCommonSbsq(firstString, secondString, fIndex - 1, sIndex, lookupArray);
		int rightCall = sizeOfLongestCommonSbsq(firstString, secondString, fIndex, sIndex - 1, lookupArray);

		result = (leftCall > rightCall) ? leftCall : rightCall;
	}

	lookupArray[fIndex - 1][sIndex - 1] = result;
	return result;
}

void printLCS(const std::vector<char>& s1, const std::vector<char>& s2, int sizeOfLcs, int** lookupArray) {
	int col = s1.size() - 1;
	int row = s2.size() - 1;
	int charIndex = sizeOfLcs - 1;
	char* lcs = new char[sizeOfLcs];

	while (col >= 0 && row >= 0) {
		if (s1.at(col) == s2.at(row)) {
			lcs[charIndex] = s1.at(col);
			--col;
			--row;
			--charIndex;
		}
		else if (lookupArray[col - 1][row] > lookupArray[col][row - 1]) {
			--col;
		}
		else {
			--row;
		}
	}

	for (int i = 0; i < sizeOfLcs; ++i) {
		std::cout << lcs[i];
	}
	delete[] lcs;
}


int main(int argc, char* argv[]) {
	std::string firstInput = "DBBDBCABAABAACBBAA";
	std::string secondInput = "DADCDCCADABCBBBCCD";

	std::vector<char> s1(firstInput.begin(), firstInput.end());
	std::vector<char> s2(secondInput.begin(), secondInput.end());

	int** lookupArray = new int*[s1.size()];
	for (int i = 0; i < s1.size(); ++i) {
		lookupArray[i] = new int[s2.size()];
		for (int j = 0; j < s2.size(); ++j) {
			lookupArray[i][j] = -1;
		}
	}

	int sizeOfLcs = sizeOfLongestCommonSbsq(s1, s2, s1.size(), s2.size(), lookupArray);

	std::cout << "Size of LCS : "<< sizeOfLcs << std::endl;
	printLCS(s1, s2, sizeOfLcs, lookupArray);
	
	std::cout << "\n\n";

	//DEALLOCATE MEMORY
	for (int i = 0; i < s1.size(); ++i) {
		delete[] lookupArray[i];
	}
	delete[] lookupArray;

	system("PAUSE");
	return 0;
}