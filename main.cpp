#include <iostream>
#include <vector>
using namespace std;

const int BUFFER = 200;

void fillMatrix(char (&key)[10], int, int, vector<vector<char>> &matrix, vector<char> &used);
void removeSpaces(char *);
void removeRepeat(char *,vector<char> &);
void encryptText(vector<char> &, char(&message)[BUFFER]);

int main() {
    vector<char> used;
    vector<char> monoalpha;
    //char key[] = "star wars";
    char key[10];
    char message[BUFFER];
    //int i = 0, j = 0;

    memset(key, '\0', 10);
    cout << "Enter Monoalphabetic cipher key:\n";
    cin.getline(key, 10);

    removeSpaces(key);
    removeRepeat(key, used);
    int cols = strlen(key);
    int rows = (26/strlen(key))+1;
    vector<vector<char>> matrix(rows, vector<char>(cols));
    fillMatrix(key, rows, cols,matrix, used);

    for(int i=0; i<cols; i++){
        for(int j=0; j<rows;j++){
            if(matrix[j][i] != NULL){
                monoalpha.push_back(matrix[j][i]);
            }
        }
    }

    // GET MESSAGE TO ENCRYPT
    cout << "Enter message to encrypt:\n";
    cin.getline(message, BUFFER);
    //removeSpaces(message);

    encryptText(monoalpha, message);
}

void  removeSpaces(char * c){
    int i = 0, j = 0, cnt = 0;
    while(c[i] != NULL){
        if(c[i] == ' '){
            i++;
            cnt++;
        }
        else{
            c[j] = c[i];
            i++; j++;
        }
    }
    for (int a=cnt; a>0; a--){
        c[strlen(c)-1] = NULL;
    }
}
void  removeRepeat(char * c, vector<char> &used){
    int i = 0, j = 0, cnt = 0;
    while(c[i] != NULL){
        if((find (used.begin(), used.end(), c[i]) != used.end()) || c[i] == 'j'){
            i++;
            cnt++;
        }
        else{
            used.push_back(c[i]);
            c[j] = c[i];
            i++; j++;
        }
    }
    for (int a=cnt; a>0; a--){
        c[strlen(c)-1] = NULL;
    }
}
void fillMatrix(char (&key)[10], int rows, int cols, vector<vector<char>> &matrix, vector<char> &used){
    char letter = 'a';

    int i = 0, j = 0;

    // PUTTING KEY INTO MATRIX
    for (auto x : key)  {
        if(x != NULL) {
            matrix[i][j] = x;
            j++;
        }
    }
    i++;

    // FILLING THE REST OF THE MATRIX
    for(; i<rows; i++){
        for (j=0;j<cols; j++) {
            if (letter < 'z') {
                while (find(used.begin(), used.end(), letter) != used.end()) {
                    letter++;
                }
                matrix[i][j] = letter;
                used.push_back(letter);
            }
        }
        j = 0;
    }

    // PRINTING MATRIX FOR TESTING
    for (int k=0;k<rows;k++) {
        for (int l=0;l<cols;l++){
            cout << matrix[k][l] << " ";
        }
        cout << endl;
    }
}
void encryptText(vector<char> &mono, char (&message)[BUFFER]) {
    vector<char> alpha = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                          't', 'u', 'v', 'w', 'x', 'y', 'z'};
    vector<char> encrypted;
    int index;

    //  PRINT ALPHABETS AND MONOALPHABETS FOR CHECKING
    /*for (auto m:mono){
        cout << m << " ";
    }
    cout << endl;
    for (auto n:alpha){
        cout << n << " ";
    }
    cout << endl;
     */

    for (auto x:message) {
        if (x == ' ') {
            encrypted.push_back(x);
        }
        else {
            auto it = find(alpha.begin(), alpha.end(), x);
            if (it != alpha.end()) {
                index = it - alpha.begin();
                encrypted.push_back(mono[index]);
            }
        }
    }

    cout << "Encrypted message:\n";
    for (auto y:encrypted){
        cout << y;
    }
}