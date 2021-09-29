#include <iostream>
#include <string>
#include <cstring>

static const std::string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

using namespace std;

string encode(char* input, int length){
    string output;
    int first,second,third,fourth;
    if (length % 3 ==0) {
        for (int i = 0; i < length; i += 3) {
            first = *(input + i) >> 2;
            second = ((*(input + i) & 3) << 4) | ((*(input + i + 1)) >> 4);
            third = ((*(input + i + 1) & 15) << 2) | (*(input + i + 2) >> 6);
            fourth = (*(input + i + 2) & 63);
            output += base64[first];
            output += base64[second];
            output += base64[third];
            output += base64[fourth];
        }
    }
    else if (length % 3 == 1){
        for (int i = 0; i < length-1; i += 3) {
            first = *(input + i) >> 2;
            second = ((*(input + i) & 3) << 4) | ((*(input + i + 1)) >> 4);
            third = ((*(input + i + 1) & 15) << 2) | (*(input + i + 2) >> 6);
            fourth = (*(input + i + 2) & 63);
            output += base64[first];
            output += base64[second];
            output += base64[third];
            output += base64[fourth];
        }
        first = *(input + length-1) >> 2;
        second = ((*(input + length-1) & 3) << 4);
        output += base64[first];
        output += base64[second];
        output += "=";
        output += "=";
    }
    else {
        for (int i = 0; i < length-2; i += 3) {
            first = *(input + i) >> 2;
            second = ((*(input + i) & 3) << 4) | ((*(input + i + 1)) >> 4);
            third = ((*(input + i + 1) & 15) << 2) | (*(input + i + 2) >> 6);
            fourth = (*(input + i + 2) & 63);
            output += base64[first];
            output += base64[second];
            output += base64[third];
            output += base64[fourth];
        }
        first = *(input + length-2) >> 2;
        second = ((*(input + length-2) & 3) << 4) | ((*(input + length-1))>>4);
        third = ((*(input + length -1 )& 15) << 2);
        output += base64[first];
        output += base64[second];
        output += base64[third];
        output += "=";

    }
    return output;

}

string decode(char* input, int length){
    string output;
    int first,second,third;
    char f,s,th;
    for (int i =0; i < length; i+=4){
        first = (base64.find(*(input+i))<<2) | ((base64.find(*(input+i+1))&48)>>4);
        second =((base64.find(*(input+i+1))&15)<<4) | ((base64.find(*(input+i+2))&60) >>2);
        third = ((base64.find(*(input+i+2))&3) <<6) | (base64.find(*(input+i+3)));
        f = first;
        output+=f;
        if (base64.find(*(input+i+2))!=-1) {
            s = second;
            output += s;
        }
        if (base64.find(*(input+i+3))!=-1) {
        th = third;
        output+=th;
        }
    }

    return output;
}

int main() {
    string inputText;
    getline(cin,inputText);
    int length = inputText.length();
    char inText[length];
    strcpy(inText,inputText.c_str());
    string result = encode(inText,length);
    cout << result << endl;
    length = result.length();
    strcpy(inText,result.c_str());
    result = decode(inText,length);
    cout << result << endl;
    char c = result[0];
    int g = base64.find('=');
    cout << g << endl;
    cout << base64[g];
    return 0;
}
