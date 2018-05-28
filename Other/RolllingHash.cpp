#include <iostream>
#include <set>

using namespace std;
typedef long long ll;
long long mod = 1e9+7;
long long prime = 33;
int n,m;
set<ll> strs;

ll calc(string str){
    long long h=0;
    long long lastPow = 1;
    for(int i = 0; i < str.length(); i++){
        h+=(lastPow * (str[i]+1-'a'));
        h%=mod;
        lastPow*=prime;
        lastPow%=mod;
    }
    return h;
}

bool search(string s, int checkId){
    ll searchVal = (calc(s) - (pow*(st[i]+1-'a'))%mod + (pow*(checkId))%mod + mod)%mod;
    if(strs.find(searchVal) != strs.end()){
	return true;
    } 
    return false;

}
int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        string str;
        cin >> str;
        strs.insert(calc(str));
    }
  

    return 0;
}