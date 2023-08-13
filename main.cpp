/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
 #include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cmath>

using namespace std;

string generateRandomText(int length) {
    const string availableChars = "abcdefghijklmnopqrstuvwxyz ";
    string randomText;
    
    for (int i = 0; i < length; ++i) {
        int index = rand() % availableChars.length();
        randomText += availableChars[index];
    }
    
    return randomText;
}

int calculateLevenshteinDistance(const string& str1, const string& str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    
    int dp[len1 + 1][len2 + 1];
    
    for (int i = 0; i <= len1; ++i) {
        for (int j = 0; j <= len2; ++j) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else {
                dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1),
                               dp[i - 1][j - 1] + (str1[i - 1] != str2[j - 1]));
            }
        }
    }
    
    return dp[len1][len2];
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    string targetText = generateRandomText(50);
    
    cout << "Welcome to Typing Master!\n";
    cout << "Type the following text:\n";
    cout << targetText << endl;
    cout << "Press Enter when you're ready to start typing...";
    cin.get();
    
    cout << "Typing has started. Type the text exactly as shown:\n";
    
    auto start = chrono::high_resolution_clock::now();
    
    string typedText;
    getline(cin, typedText);
    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    
    int distance = calculateLevenshteinDistance(targetText, typedText);
    int targetLength = targetText.length();
    
    double accuracy = ((targetLength - distance) / static_cast<double>(targetLength)) * 100;
    double typingSpeed = (targetLength / duration.count()) * 60;
    
    cout << "\nTime taken: " << duration.count() << " seconds\n";
    cout << "Accuracy: " << accuracy << "%\n";
    cout << "Typing speed: " << typingSpeed << " characters per minute\n";
    
    while (true) {
        cout << "\nDo you want to try again? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            targetText = generateRandomText(50);
            
            cout << "\nType the following text:\n";
            cout << targetText << endl;
            cout << "Press Enter when you're ready to start typing...";
            cin.get();
            
            cout << "Typing has started. Type the text exactly as shown:\n";
            
            start = chrono::high_resolution_clock::now();
            
            typedText.clear();
            cin.ignore(); // Clear newline character from previous input
            getline(cin, typedText);
            
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::seconds>(stop - start);
            
            distance = calculateLevenshteinDistance(targetText, typedText);
            targetLength = targetText.length();
            
            accuracy = ((targetLength - distance) / static_cast<double>(targetLength)) * 100;
            typingSpeed = (targetLength / duration.count()) * 60;
            
            cout << "\nTime taken: " << duration.count() << " seconds\n";
            cout << "Accuracy: " << accuracy << "%\n";
            cout << "Typing speed: " << typingSpeed << " characters per minute\n";
        } else {
            cout << "Thank you for playing Typing Master! Goodbye.\n";
            break;
        }
    }
    
    return 0;
}

 

