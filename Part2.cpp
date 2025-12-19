#include <iostream>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

// Returns 0-25 for letter (A/a -> 0, B/b -> 1, ...), assumes input is alphabetic
int letterToIndex(char c) {
    return toupper(static_cast<unsigned char>(c)) - 'A';
}

// Convert 0-25 back to letter, preserving case
char indexToLetter(int idx, bool uppercase) {
    char base = uppercase ? 'A' : 'a';
    return static_cast<char>(base + idx);
}

// Build a repeated key stream aligned ONLY to letters in message.
// Non-letters do not consume key characters.
string buildKeyStream(const string& message, const string& keyword) {
    string cleanedKey;
    for (char c : keyword) {
        if (isalpha(static_cast<unsigned char>(c))) cleanedKey += c;
    }

    // Keyword must have at least one letter
    if (cleanedKey.empty()) return "";

    string keyStream;
    keyStream.reserve(message.size());

    int keyPos = 0;
    for (char mc : message) {
        if (isalpha(static_cast<unsigned char>(mc))) {
            keyStream += cleanedKey[keyPos % cleanedKey.size()];
            keyPos++;
        }
        else {
            keyStream += mc; // placeholder for non-letters
        }
    }
    return keyStream;
}

string vigenereEncrypt(const string& plaintext, const string& keyword) {
    string keyStream = buildKeyStream(plaintext, keyword);
    if (keyStream.empty()) return ""; // invalid keyword

    string cipher = plaintext;

    for (size_t i = 0; i < plaintext.size(); i++) {
        char p = plaintext[i];
        if (isalpha(static_cast<unsigned char>(p))) {
            int Pi = letterToIndex(p);
            int Ki = letterToIndex(keyStream[i]);
            int Ei = (Pi + Ki) % 26;

            bool isUpper = isupper(static_cast<unsigned char>(p));
            cipher[i] = indexToLetter(Ei, isUpper);
        }
        else {
            cipher[i] = p; // keep punctuation/space
        }
    }
    return cipher;
}

string vigenereDecrypt(const string& ciphertext, const string& keyword) {
    string keyStream = buildKeyStream(ciphertext, keyword);
    if (keyStream.empty()) return ""; // invalid keyword

    string plain = ciphertext;

    for (size_t i = 0; i < ciphertext.size(); i++) {
        char e = ciphertext[i];
        if (isalpha(static_cast<unsigned char>(e))) {
            int Ei = letterToIndex(e);
            int Ki = letterToIndex(keyStream[i]);
            int Di = (Ei - Ki + 26) % 26;

            bool isUpper = isupper(static_cast<unsigned char>(e));
            plain[i] = indexToLetter(Di, isUpper);
        }
        else {
            plain[i] = e; // keep punctuation/space
        }
    }
    return plain;
}

int main() {
    cout << "=== Vigenere Cipher (Encrypt / Decrypt) ===\n";
    cout << "Note: Spaces and punctuation are preserved.\n\n";

    while (true) {
        cout << "Choose an option:\n";
        cout << "  1) Encrypt\n";
        cout << "  2) Decrypt\n";
        cout << "  3) Exit\n";
        cout << "Enter choice (1-3): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a number.\n\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // consume newline

        if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        }
        if (choice != 1 && choice != 2) {
            cout << "\nInvalid choice. Try again.\n\n";
            continue;
        }

        string message, keyword;
        cout << "\nEnter message: ";
        getline(cin, message);

        cout << "Enter keyword: ";
        getline(cin, keyword);

        // Validate keyword contains at least one letter
        bool hasLetter = false;
        for (char c : keyword) {
            if (isalpha(static_cast<unsigned char>(c))) { hasLetter = true; break; }
        }
        if (!hasLetter) {
            cout << "\nERROR: Keyword must contain at least one alphabetic character (A-Z).\n\n";
            continue;
        }

        if (choice == 1) {
            string cipher = vigenereEncrypt(message, keyword);
            cout << "\nCiphertext:\n" << cipher << "\n\n";
        }
        else {
            string plain = vigenereDecrypt(message, keyword);
            cout << "\nPlaintext:\n" << plain << "\n\n";
        }
    }

    return 0;
}
