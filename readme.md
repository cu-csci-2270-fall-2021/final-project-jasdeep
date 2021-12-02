# CSCI 2275 – Data Structures - Final Project

Jasdeep Singh

### Description
The function of this program is to create a "lite" or "mini" version of git. Git is a version control system that keeps track of edited files, directories, servers, etc. In regular Git, you can keep track of changes to a certain file, you can keep track of what files are added to a directory, you can even revert back to a last saved instance. 

The minigit doesnt use a remote server like Git does. Minigit creates a hidden folder within the current working directory that stores all files that are commited. With the minigit program a user is able to add files, remove files, commit, checkout, and search for a commit.

### Functions

The program displays a menu when first ran. The menu consists of 7 options: init, add, remove, commit, checkout, search, and quit.

**init**: The init function should be used once every time the program is ran. Additionally it should be ran at the starting of each run. What the init function does is create a new hidden directory called minigit. This directory will be used to store files that have been committed. The init function also creates a new commit DLL (doubly linked list) Node which will be the head. 

**add**: The add function is used to add a file to the latest commit DLL Node. But before adding the file to the latest commit DLL Node, it will check whether a file with the exact contents already exist within the minigit directory. If the file already exists then it will print a message saying the file has already been added. Else it will add the file with a version of 0 if there is no file within the hidden minigit directory that has the same name or it will increment the version if there is a file within the hidden minigit directory that has the same name. Also a file cannot be added twice as a FileNode LL (linked list)to the DLL unless its a different version.

**remove**: The remove function is used to remove a Node from the FileNode LL. If a node with the file name exists then it will remove that node else it will print a message saying that file does not exist in the commit.

**commit**: The commit function takes the current uncommitted DLL Node and commits all the files to the hidden minigit directory. A user will provide a commit message that will be stored in that uncommitted DLL Node. Each word of that commit message will also be inserted into a Hash Table. But before it does that, it has to check whether a file with the same name and version number exists. If there is already a file with the same name and version number then it will not add that file because it would end up as a duplicate. If there is not a file with the same name and version number then it will create a file within the minigit directory that has the FileNode's name and version. The naming convention is filename.txt__fileversion. Running this function will also create a new uncommitted DLL Node as the old one has just been commited.

**checkout**: The checkout function allows a user to overwrite all files in the current directory with a previous commit's files. The checkout function will delete all files except for the minigit directory. Then it will find the user specified commit DLL. After that it will go through each node in the SLL and add each file from the hidden minigit directory to the current working directory. A user cannot use the commit, add, or remove functions if they are in a DLL Node that is not the current uncommitted commit Node.

**search**: The search function returns all the commitID's based on a key that the user specified. 


### Hash Table
The function of the Hash Table is to be able to search what commits are stored under a key. The hash table consists of each commit message's words broken up and stored into the hash table. The collision resolution that the hash table uses is chaining. This means that within each index, if there is a collision, then it will add each collision to the end of a linked list within the index.

