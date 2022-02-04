#include <iostream>
#include <vector>

using namespace std;

String encodeStringArr(vector<String> arr) {
  String encoded = "";
  for (auto &a : arr) {
    encoded += a;
    encoded += "#";
  }
  return encoded;
}


vector<String> split(String str, String token) {
  vector<String> result;
  while (str.length()) {
    int index = str.indexOf(token);
    if (index != -1) {
      result.push_back(str.substring(0, index));
      str = str.substring(index + token.length());
    }
    else {
      result.push_back(str);
      str = "";
    }
  }
  return result;
}

vector<String> decodeStringArr(String s) {
  return split(s, "#");
}
