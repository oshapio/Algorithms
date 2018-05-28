#include <iostream>
#include <map>

using namespace std;
struct node{
    map<char,node> exs;
    bool end;
    int cnt;
}startNode;

void insTrie(node *root, string const &str){
    int deep = 0;
    int length = str.length();

    node *currNode = root;

    for(deep = 0; deep < length; deep++){
        if(currNode->exs.find(str[deep]) == currNode->exs.end()){
            // insert new node
            node newNode;
            newNode.end = false;
            newNode.cnt = 0;
            currNode->exs[str[deep]] = newNode;
            currNode=&currNode->exs[str[deep]];
        }else{
            // append to the node
            currNode = &currNode->exs[str[deep]];
        }
    }
    currNode->end = true;
    currNode->cnt++;

}

bool findString(node* root, string const &str){
    int len = str.length();
    node *currNode = root;
    for(int i = 0; i < len; i++){
        if(currNode->exs.find(str[i]) != currNode->exs.end())
            currNode = &currNode->exs[str[i]];
        else return false;
    }
    if(currNode->end) return true;
    return false;
}

bool findPrefix(node *root, string const &pref){
    int len = pref.length();
    node *currNode = root;
    for(int i = 0; i < len; i++){
        if(currNode->exs.find(pref[i]) != currNode ->exs.end()){
            // cool
            currNode = &currNode->exs[pref[i]];
        }else return false;
    }
    return true;
}

bool findPrefixAndNotWord(node *root, string const &pref){
    int len = pref.length();
    node *currNode = root;
    for(int i = 0; i < len; i++){
        if(currNode->exs.find(pref[i]) != currNode ->exs.end()){
            // cool
            currNode = &currNode->exs[pref[i]];
        }
    }

    if(!currNode->exs.size())return true;
    else return false;

}


void clearTrie(node *root){
    root->exs.clear();
    root->cnt = 0;
    root->end = false;
}
string arr[100000];

int main(){

    int t;
    cin >> t;
    for(int f = 1; f <= t; f++){
        clearTrie(&startNode);
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            insTrie(&startNode,arr[i]);
        }
        bool isAns = true;
        for(int i = 0; i < n; i++){
            if(!findPrefixAndNotWord(&startNode,arr[i])){
                isAns = false;
                break;
            }
        }
    }

    return 0;
}