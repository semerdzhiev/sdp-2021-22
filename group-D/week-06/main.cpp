#include <iostream>
#include <queue>
#define N 8
using namespace std;

struct Point {
    int x, y;
//    int steps;
//    int prevX;
//    int prevY;
    Point(int x = -1, int y = -1/* int steps = 0,int prevX = -1, int prevY = -1*/) {
        this->x = x;
        this->y = y;
//        this->steps = steps;
//        this->prevX = prevX;
//        this->prevY = prevY;
    }
};
int main() {
    // bool board[N][N] = {0}; // bool? to keep already visited places
    // in case we want to keep the previous step, much better will be to keep prev 2d array
	// with type of Point
	Point prev[N][N];
    char b, e;
    int bi, ei;
    int x[] = {1,1,-1,-1,2,2,-2,-2};
    int y[] = {2,-2,2,-2,1,-1,1,-1};
    cin>>b>>bi; // A 1 -> 0 0
    cin>>e>>ei; // B 2 -> 1 1
    queue<Point> q;
    Point begin =  Point(int(b - 'A'), bi - 1);
    q.push(begin);
    prev[begin.x][begin.y].x = -2;
    prev[begin.x][begin.y].y = -2;
    //board[begin.x][begin.y] = 1;
    while (q.empty() == false) {
        Point current = q.front();
        //cout<< "Current point" << char(current.x + 'A')<<" " << (current.y+1) <<" "<<current.steps<<endl;

        q.pop();
        if (e == (current.x + 'A') && ei == (current.y + 1)) {
            int sol = 0;
            Point solution = current;
            //cout<<solution.x<<" "<<solution.y<<"---" <<endl;
            while (solution.x != -2 && solution.y != -2) {
                cout<<char(solution.x+'A') <<" "<< (solution.y+1)<<endl;
                solution = prev[solution.x][solution.y];
                sol++;
            }
            cout<<"Required steps are "<<(sol-1)<<endl;
            break;
        }
        for (int i = 0 ;i < N ;i++) {
            Point newPoint = Point(current.x + x[i],
                                   current.y + y[i]
//                                   current.steps+1
//                                   current.x,
//                                   current.y
                                   );
           // cout<< char(newPoint.x + 'A')<<" " << (newPoint.y+1) <<" "<<newPoint.steps<<endl;
            if (newPoint.x < 0 || newPoint.x > 7
                || newPoint.y < 0 || newPoint.y > 7
                || prev[newPoint.x][newPoint.y].x != -1
                || prev[newPoint.x][newPoint.y].y != -1
                || prev[newPoint.x][newPoint.y].x == -2 // Why we need this validation
                || prev[newPoint.x][newPoint.y].y == -2 // Can we write it in much better way
               ) {
                continue;
            }
            // board[newPoint.x][newPoint.y] = 1;
            prev[newPoint.x][newPoint.y].x = current.x;
            prev[newPoint.x][newPoint.y].y = current.y;
            q.push(newPoint);
        }
    }
    return 0;
}
