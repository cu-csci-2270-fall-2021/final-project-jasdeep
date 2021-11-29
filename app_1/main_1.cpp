#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
using namespace std;

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. init " << endl;
    cout << " 2. add " << endl;
    cout << " 3. rm " << endl;
    cout << " 4. commit " << endl;
    cout << " 5. checkout" << endl;
    cout << " 6. search" << endl;
    cout << " 7. quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
int main(int argc, char* argv[]) {
    MiniGit git;
    while(true) {
        displayMenu();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                git.init(5);
                break;
            }case 2: {
                cout << "Enter the file you wish to add: ";
                string fileName;
                cin >> fileName;
                git.add(fileName);
                break;
            }case 3:{
                cout << "Enter the file you wish to remove: ";
                string fileName;
                cin >> fileName;
                git.rm(fileName);
                break;
            }case 4:{
                git.commit("lol");
                break;
            }case 5:{
                
                break;
            }case 6:{
                cout << "Enter a key: ";
                string key;
                cin >> key;
                git.search(key);
                break;
            }case 7:{
                return 0;
                break;
            }default:
                break;
        }
    }
}