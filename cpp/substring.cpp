
#include <iostream>
#include <string>        

using namespace std;

bool Match(const char* s1, const char* s2, int& matched)
{
	matched = 0;
	while (s1 != NULL && s2 != NULL &&
		*s1 != '\0' && *s2 != '\0'
		&& *s1 == *s2)
	{
		s1++;
		s2++;
		matched++;
	}

	if (*s2 == '\0') return true;

	return false;
}
bool Match(const char* s1, const char* s2)
{
	while (s1 != NULL && s2 != NULL &&
		*s1 != '\0' && *s2 != '\0'
		&& *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s2 == '\0') return true;

	return false;
}

int FindSubStringSlow(const char* string, const char* sub)
{
	bool found = false;
	const char* head = string;
	int loc = 0;
	while (head!=NULL && *head != '\0')
	{
		found = Match(head, sub);
		if (found) break;
		head++;
		loc++;
	}

	if (found) return loc;
	return -1;
}

int  GetPartiallyMatchedNum(const char* str, int len)
{
	if (len <= 1) return 0;

	for (int i = 1; i < len; i++)
	{
		const char* prefix = str;
		const char* suffix = str;
		int j = i;
		while (j-- > 0) suffix++;

		bool fullloop = true;
		for (int iter = 0; iter < len - i; iter++)
		{
			if (prefix[iter] != suffix[iter])
			{
				fullloop = false;
				break;
			}
		}

		if (fullloop)
			return len - i;
	}

	return 0;
}

//Find the explanation of the KMP algorithm in the following aritcle
//http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html
int FindSubStringKMP(const char* string, const char* sub)
{
	//build up sub's partially matched table
	int len = 0;
	const char* counter = sub;
	while (counter != NULL && *counter != '\0')
	{
		counter++;
		len++;
	}
	int* pmTable = new int[len]; 
	int j = len;
	while (j-- >= 0) pmTable[j] = 0;

	for (int i = len; i > 0; i--) {
		pmTable[i - 1] = GetPartiallyMatchedNum(sub, i);
	}

	//find the sub string
	bool found = false;
	const char* head = string;
	int loc = 0;
	while (head!=NULL && *head != '\0') //this can be improved
	{
		int matched = 0;
		found = Match(head, sub, matched);
		if (found) break;
		if (matched == 0)
		{
			head++;
			loc++;
		}
		else
		{
			head = head + (matched - pmTable[matched-1]);
			loc = loc + (matched - pmTable[matched-1]);
		}
	}

	if (found) return loc;
	return -1;
}

int main()
{
	//self implementation of KMP
	const char* s = "BBC ABCDAB ABCDABCDABD";
	const char* sub = "ABCDABD";
	int loc = FindSubStringKMP(s, sub);
	cout << "first 'ABCDABD' found at: " << loc << '\n';


	//self implementation of slow comparsion
	loc = FindSubStringSlow(s, sub);
	cout << "first 'ABCDABD' found at: " << loc << '\n';

	//standard libray string.find
	string str("BBC ABCDAB ABCDABCDABD");
	string str2("ABCDABD");
	size_t found = str.find(str2);
	if (found != string::npos)
		cout << "first 'ABCDABD' found at: " << found << '\n';

}