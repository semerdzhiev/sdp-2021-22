#include <iostream>
#include <queue>
using namespace std;

// A 1
// C 6
struct Move {
    short x,y;
    int counter;
    Move(short x, short y, int counter = 0) {
        this->x = x;
        this->y = y;
        this->counter = counter;
    }
};

int main() {
    const short x[] = {1, 1, -1,-1, 2, 2,-2,-2};
    const short y[] = {2, -2, 2,-2, 1,-1, 1,-1};
    short prev[9][9][2]; //memset  ? [x][y][prevX] [x][y][PrevY]
    // cout<<sizeof(prev)<<endl;
    // memset (prev[0][0], -1, 9*9*2* sizeof(short)); can we actually do that?
    for (int i = 0;i< 9;i++)
        for (int t = 0;t< 9;t++) {
            prev[i][t][0] = -1;
            prev[i][t][1] = -1;
        }

    char b, e;
    int bn, en;
    cin>>b>>bn;
    cin>>e>>en;
    prev[b-'A'][bn][0] = -2;
    prev[b-'A'][bn][0] = -2;
    queue<Move> q;
    q.push(Move(b-'A', bn));
    while(q.empty() == false) {
        Move current = q.front();
        q.pop();
        if (current.x == e-'A' && current.y == en) {
            cout<<"Result is " << current.counter<<endl;
            short solX = prev[current.x][current.y][0];
            short solY = prev[current.x][current.y][1];
            short temp1, temp2;
            cout<< char(current.x+'A')<<" "<< current.y<<endl;

            while(solX != -2 ) {
                cout<< char(solX+'A') <<" "<<solY<<endl;
                temp1 = prev[solX][solY][0];
                temp2 = prev[solX][solY][1];
                solX = temp1;
                solY = temp2;
            }
            break;
        }
        for (int i = 0; i < 8; i++) {
           short currentX = current.x + x[i];
           short currentY = current.y + y[i];
           if (currentX < 0 || currentY< 0 || currentX > 8 || currentY > 8) {
               continue;
           }
           if (prev[currentX][currentY][0] != -1) {
               continue;
           }
           // 4 4
           //matrix[currentX][currentY] = true;
            prev[currentX][currentY][0] = current.x;
            prev[currentX][currentY][1] = current.y;
            q.push(Move(currentX, currentY, current.counter + 1));
        }
    }
    return 0;
}
