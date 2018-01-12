#include <iostream>
#include <string>        

using namespace std;

bool Match(const char* s1, const char* s2)
{
    while(s1!=NULL && s2!=NULL &&
        *s1!='\0' && *s2!='\0' 
        && *s1==*s2)
    {
        s1++;
        s2++;
    }

    if(*s2=='\0') return true;

    return false;
}

int FindSubStringSlow(const char* string, const char* sub)
{
    bool found = false;
    const char* head = string;
    int loc = -1;
    while(!found && *head!='\0')
    {
        found = Match(head, sub);
        head++;
        loc++;
    }

    if(found) return loc;
    return -1;
}

int main()
{
    //self implementation of slow comparsion
    const char* s = "BBC ABCDAB ABCDABCDABD";
    const char* sub = "ABCDABD";
    int loc = FindSubStringSlow(s, sub);
    cout << "first 'ABCDABD' found at: " << loc << '\n';

    //standard libray string.find
    string str ("BBC ABCDAB ABCDABCDABD");
    string str2 ("ABCDABD");
    size_t found = str.find(str2);
    if (found!=string::npos)
    cout << "first 'ABCDABD' found at: " << found << '\n';
    
}