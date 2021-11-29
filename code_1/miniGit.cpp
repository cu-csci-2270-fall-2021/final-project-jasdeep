#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>

MiniGit::MiniGit() {
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
}

MiniGit::~MiniGit() {   
    // Any postprocessing that may be required

}

void MiniGit::init(int hashtablesize) {
    ht = new HashTable(5);
    BranchNode * nbn = new BranchNode;
    commitHead = nbn;
    nbn->commitMessage = "";
    nbn->commitID = 0;
    nbn->next = NULL;
    nbn->previous = NULL;
    nbn->fileHead = NULL;
    commits = 0;
}

void MiniGit::add(string fileName) {
    if (fs::exists(fileName)) {
        BranchNode * latestBranchNode = commitHead;
        while (commitHead->next != NULL) {
            latestBranchNode = latestBranchNode->next;
        }
        if (latestBranchNode->fileHead != NULL) {
            FileNode * tempNode = latestBranchNode->fileHead;
            FileNode * prev = NULL;
            while (tempNode != NULL && tempNode->name != fileName) {
                prev = tempNode;
                tempNode = tempNode->next;
            }
            if (tempNode == NULL) {
                FileNode * newNode = new FileNode;
                newNode->name = fileName;
                newNode->version = 0;
                newNode->next = NULL;
                prev->next = newNode;
                while(fs::exists(".minigit/"+newNode->name+"__"+to_string(newNode->version))) {
                    fstream file1(fileName), file2(".minigit/"+newNode->name+"__"+to_string(newNode->version));
                    char string1[256], string2[256];
                    while(!file1.eof()) {
                        file1.getline(string1,256);
                        file2.getline(string2,256);
                        if(strcmp(string1,string2) != 0) {
                            newNode->version++;
                            cout << "File has been added." << endl;
                            return;
                        }
                    }
                    break;
                }
                cout << "File has been added." << endl;
            } else {
                if (fs::exists(".minigit/"+fileName+"__"+to_string(tempNode->version))) {
                    fstream file1(fileName), file2(".minigit/"+fileName+"__"+to_string(tempNode->version));
                    char string1[256], string2[256];
                    while(!file1.eof()) {
                        file1.getline(string1,256);
                        file2.getline(string2,256);
                        if(strcmp(string1,string2) != 0) {
                            tempNode->version++;
                            cout << "File has been added." << endl;
                            return;
                        }
                    }
                    cout << "File has been added already." << endl;
                } else {
                    cout << "File has been added already." << endl;
                }
            }
        } else {
            FileNode * newNode = new FileNode;
            newNode->name = fileName;
            newNode->version = 0;
            newNode->next = NULL;
            latestBranchNode->fileHead = newNode;
            while(fs::exists(".minigit/"+newNode->name+"__"+to_string(newNode->version))) {
                fstream file1(fileName), file2(".minigit/"+newNode->name+"__"+to_string(newNode->version));
                char string1[256], string2[256];
                while(!file1.eof()) {
                    file1.getline(string1,256);
                    file2.getline(string2,256);
                    if(strcmp(string1,string2) != 0) {
                        newNode->version++;
                        cout << "File has been added." << endl;
                        return;
                    }
                }
                break;
            }
            cout << "File has been added." << endl;
        }
        cout << latestBranchNode->fileHead->version << endl;
    } else {
        cout << "Enter a file that exists" << endl;
    }
}

void MiniGit::rm(string fileName) {
    BranchNode * latestBranchNode = commitHead;
    while (commitHead->next != NULL) {
        latestBranchNode = latestBranchNode->next;
    }
    FileNode * prev = NULL;
    FileNode * temp = latestBranchNode->fileHead;
    while (temp != NULL && temp->name != fileName) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        cout << "File does not exist." << endl;
    } else if (prev == NULL) {
        latestBranchNode->fileHead = temp->next;
        delete temp;
        temp = NULL;
    } else {
        prev->next = temp->next;
        delete temp;
        temp = NULL;
    }
}



void MiniGit::printSearchTable()
{
     ht->printTable();
}


void MiniGit::search(string key)
{
    HashNode * temp = ht->searchItem(key);
    cout << "The commit numbers with the key: " << key << " are ";
    for(int i = 0; i < temp->commitNums.size(); i++) {
        cout << temp->commitNums.at(i) << "-->";
    }
    cout << "NULL" << endl;
}



string MiniGit::commit(string msg) {
    vector<string> messages = {"bruh", "lol", "okay"};
    BranchNode * prev = NULL;
    BranchNode * temp = commitHead;
    while (temp->next != NULL && temp->commitMessage != msg) {
        prev = temp;
        temp = temp->next;
    }
    if (temp->commitMessage != msg && temp->next == NULL) {
        temp->commitMessage = msg;
        temp->previous = prev;
        FileNode * tempFile = temp->fileHead;
        while (tempFile != NULL) {
            if (!fs::exists(".minigit/"+tempFile->name+"__"+to_string(tempFile->version))) {
                string line;
                ifstream readFile(tempFile->name);
                ofstream writeFile(".minigit/"+tempFile->name+"__"+to_string(tempFile->version));
                if (readFile && writeFile) {
                    while(getline(readFile,line)){
                        writeFile << line << "\n";
                    }
                } else {
                    cout << "error in opening files" << endl;
                }
            }
            tempFile = tempFile->next;
        }
        for (int i = 0; i < messages.size(); i++) {
            ht->insertItem(messages.at(i), temp->commitID);
        }
        BranchNode * nbn = new BranchNode;
        temp->next = nbn;
        nbn = temp;
        nbn->commitMessage = "";
        nbn->commitID = commits+1;
        nbn->next = NULL;
        nbn->previous = temp;
        commits++;
        return ""+temp->commitID;
    } else {
        cout << "This commit message already exists." << endl;
    }
    return " "; //should return the commitID of the commited DLL node
}

void MiniGit::checkout(string commitID) {
   

}
