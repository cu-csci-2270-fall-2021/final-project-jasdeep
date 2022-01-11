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
    BranchNode * prev = NULL;
    BranchNode * temp = commitHead;
    while (temp != NULL) {
        FileNode * prevFile = NULL;
        FileNode * tempFile = temp->fileHead;
        while (tempFile != NULL) {
            prevFile = tempFile;
            tempFile = tempFile->next;
            delete prevFile;
            prevFile = NULL;
        }
        prev = temp;
        temp = temp->next;
        delete prev;
        prev = NULL;
    }
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
    if (isRecentCommit) {
        if (fs::exists(fileName)) {
            BranchNode * latestBranchNode = commitHead;
            while (latestBranchNode->next != NULL) {
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
        } else {
            cout << "Enter a file that exists" << endl;
        }
    } else {
        cout << "Please switch to the latest commit" << endl;
    }
}

void MiniGit::rm(string fileName) {
    if (isRecentCommit) {
        BranchNode * latestBranchNode = commitHead;
        while (latestBranchNode->next != NULL) {
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
    } else {
        cout << "Please switch to the latest commit" << endl;
    }
}



void MiniGit::printSearchTable()
{
     ht->printTable();
}


void MiniGit::search(string key)
{
    HashNode * temp = ht->searchItem(key);
    if (temp != NULL) {
        cout << "The commit numbers with the key: " << key << " are ";
        for(int i = 0; i < temp->commitNums.size(); i++) {
            cout << temp->commitNums.at(i) << "-->";
        }
        cout << "NULL" << endl;
    } else {
        cout << "There is no commit with this key." << endl;
    }
}



string MiniGit::commit(vector<string> messages, string msg) {
    if (isRecentCommit) {
        BranchNode * prev = NULL;
        BranchNode * temp = commitHead;
        while (temp->commitMessage != "" && temp->commitMessage != msg) {
            prev = temp;
            temp = temp->next;
        }
        if (temp->commitMessage == "") {
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
            FileNode * fileCopy = temp->fileHead;
            FileNode * prevCopy = NULL;
            while(fileCopy != NULL) {
                if (nbn->fileHead == NULL) {
                    FileNode * newNode = new FileNode;
                    nbn->fileHead = newNode;
                    newNode->name = fileCopy->name;
                    newNode->version = fileCopy->version;
                    prevCopy = newNode;
                    fileCopy = fileCopy->next;
                } else {
                    FileNode * newNode = new FileNode;
                    prevCopy->next = newNode;
                    newNode->name = fileCopy->name;
                    newNode->version = fileCopy->version;
                    prevCopy = newNode;
                    fileCopy = fileCopy->next;
                }
            }
            temp->next = nbn;
            nbn->commitMessage = "";
            commits++;
            nbn->commitID = commits;
            nbn->next = NULL;
            nbn->previous = temp;
            return "The commitID for this commit is: "+to_string(temp->commitID);
        }
        return "This commit message already exists."; //should return the commitID of the commited DLL node
    }
    return "Please switch to the latest commit.";
}

void MiniGit::checkout(string commitID) {
    BranchNode * temp = commitHead;
    while(temp != NULL && temp->commitID != stoi(commitID)) {
        temp = temp->next;
    }
    BranchNode * latestCommit = commitHead;
    while(latestCommit->next != NULL) {
        latestCommit = latestCommit->next;
    }
    if (latestCommit != temp) {
        isRecentCommit = false;
    } else {
        isRecentCommit = true;
    }
    if (temp != NULL) {
        for (const auto & entry : fs::directory_iterator(fs::current_path())) {
            if (string(fs::current_path())+"/.minigit" != entry.path() && string(fs::current_path())+"/.ipynb_checkpoints" != entry.path()) {
                fs::remove(entry.path());
            }
        }
        FileNode * tempFile = temp->fileHead;
        while(tempFile != NULL) {
            string line;
            ifstream readFile(".minigit/"+tempFile->name+"__"+to_string(tempFile->version));
            ofstream writeFile(tempFile->name);
            if (readFile && writeFile) {
                while(getline(readFile,line)){
                    writeFile << line << "\n";
                }
            } else {
                cout << "error in opening files" << endl;
            }
            tempFile = tempFile->next;
        }
    } else {
        cout << "This commit does not exist." << endl;
    }
}
