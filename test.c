#include <iostream>
#include <cstring>
using namespace std;
void removespaces (char* str)
{
//run time of this algorithm will be O(N)
    char* temp_copy = str;  // making the temporary variable to copy the string in
    char* temp_chars = str;

    while (*temp_copy)
    {
        if (*temp_copy != ' ')              //if its not a space, copy the characters , by iterating through and dereferencing the address to change the value.
        {
            *temp_chars++ = *temp_copy;
        }
        temp_copy++;                    //if an space occurs, just skip over it.

    }

    *temp_chars = 0;              //reset the temp value;

};

int main()
{
  char s[20];
  strcpy(s, "hello world!");
  cout << s << endl;
  removespaces(s);
  cout << s << endl;
  return 0;
}
