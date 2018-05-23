// Example program
#include <bits/stdc++.h>
#include <ctime>
using namespace std;
struct points{
    int x, y;
} pnts[100];
const int pntCnt = 18;
double dp[pntCnt][pntCnt][1 << pntCnt + 1];
int goTo[pntCnt][pntCnt][1 << pntCnt + 1];
double getDist(points p1, points p2){
    double intermid =  (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
    return sqrt(intermid);
}
double go(int startCity, int currCity, int currState){
  if(dp[startCity][currCity][currState] != -1){
    return dp[startCity][currCity][currState];
  }
  if(currState == (1 << pntCnt) - 1){
    return getDist(pnts[currCity], pnts[startCity]);
  }
  double minAns = 1e9;
  int bstpnt = 0;
  for(int i = 0; i < pntCnt; i++){
    if( !(currState & (1 << i))){
      double ansThat = go(startCity, i, currState | (1 << i)) + getDist(pnts[currCity], pnts[i]);
      if(minAns > ansThat){
        minAns = ansThat;
        goTo[startCity][currCity][currState] = i;
      }
    }
  }
  return dp[startCity][currCity][currState] = minAns;
}

double getLength(vector<int> seq){
  double ans = 0;
  for(int i = 1; i < seq.size(); i++){
    ans += getDist(pnts[seq[i]], pnts[seq[i-1]]);
  }
  return ans;
}
int main()
{
  for(int i = 0; i < pntCnt; i++){
    for(int k = 0; k < pntCnt; k++){
      for(int j = 0; j < (1 << pntCnt); j++){
         dp[i][k][j] = -1;
         goTo[i][k][j] = 0;
      }
    }
  }
  for(int i = 0; i < pntCnt; i++){
    char trash;
    int x, y; cin >> x >> y;
    pnts[i].x = x;
    pnts[i].y = y;
  }
  double ans = 1e9;
  clock_t begin = clock();
  for(int i = 0; i < pntCnt; i++){
   ans = min(ans, go(i, i, (1 << i)));
  }
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "time : " <<  elapsed_secs << "\n";
  cout << ans << "\n";

  int currCity = -1;

  for(int i = 0; i < pntCnt; i++){
    for(int j = 0; j < pntCnt; j++){
      if(ans == dp[i][i][(1 << i)]){
        currCity = i;
        break;
      }
    }
  }
  vector<int> gen;
  int startPnt = currCity;
  int currState = (1 << startPnt);

  for(int x = 0; x < pntCnt; x++){
    int nxtPnt = goTo[startPnt][currCity][currState];
    currState |= (1 << nxtPnt);
    cout << currCity+1 << " " ; // 1-based indexing
    gen.push_back(currCity);
    currCity = nxtPnt;
  }
  cout << "\nlength is : " << getLength(gen);
  return 0;


}
