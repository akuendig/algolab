#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>
#include <climits>
using namespace std;

typedef struct {
    int x;
    int y;
} point;

point speed[] = {
    {-1,-1},
    {-1,0},
    {-1,1},
    {0,-1},
    {0,0},
    {0,1},
    {1,-1},
    {1,0},
    {1,1}
};

typedef struct {
    int x; // Current position
    int y;
    int sx;// Current speed
    int sy;
    int hops;
} hproperties;

hproperties make_hproperties(int x, int y, int sx, int sy, int hops) {
    hproperties h = {x, y, sx, sy, hops};
//    h.x = x;
//    h.y = y;
//    h.sx = sx;
//    h.sy = sy;
//    h.hops = hops;
    return h;
}

int map_speed(int x, int y) {
    return (x+3)*7+y+3;
}

int map_speed(point p) {
    return map_speed(p.x, p.y);
}

void testcase() {

    int X;
    int Y;
    cin >> X;
    cin >> Y;
    vector<vector<int> > db(X, vector<int>(Y, 0));
    vector<vector<vector<int> > > level(X, vector<vector<int> >(Y, vector<int>(49, -1)));
//    cout << level[0][2][4] << "\n";
    queue<hproperties> hqueue;

    point startpoint;
    point endpoint;
    // Start and End
    cin >> startpoint.x;
    cin >> startpoint.y;
    cin >> endpoint.x;
    cin >> endpoint.y;

    // Insert obstacles
    int numObstacles;
    cin >> numObstacles;
    for (int k=0; k<numObstacles; k++) {
        int x1, y1, x2, y2;
        cin >> x1;
        cin >> y1;
        cin >> x2;
        cin >> y2;

        for (int i=x1; i<=x2; i++) {
            for (int j=y1; j<=y2; j++) {
                db[i][j] = 1;
            }
        }
    }

    // Insert start point
    //db[startpoint.x][startpoint.y] = 0;
    if (db[endpoint.x][endpoint.y] > 0) {
        cout << "No solution.\n";
        return;
    }

    int posx = startpoint.x;
    int posy = startpoint.y;
    int numhops = 0;
    hqueue.push(make_hproperties(posx, posy, 0, 0, numhops));
    level[startpoint.x][startpoint.y][map_speed(0, 0)] = 0;
    while ( !(posx == endpoint.x && posy == endpoint.y) && !hqueue.empty()) {
        hproperties item = hqueue.front();
        hqueue.pop();
        numhops = item.hops + 1;
        assert(numhops >= 0);

        for (unsigned int k=0; k < 9; k++) {
            //cout << k << "\n";
            int speedx = item.sx + speed[k].x;
            int speedy = item.sy + speed[k].y;

            assert(speed[k].x >= -1 && speed[k].x <= 1 );
            assert(speed[k].y >= -1 && speed[k].y <= 1 );

            if (speedx > 3 || speedy > 3 || speedx < -3 || speedy < -3)
                continue;

            posx = item.x + speedx;
            posy = item.y + speedy;
            if (posx >= X || posy >= Y || posx < 0 || posy < 0)
                continue;
            if (db[posx][posy] > 0) // Obstacles
                continue;

            int speedhash = map_speed(speedx, speedy);

            if (level[posx][posy][speedhash] > -1)
                continue;

            level[posx][posy][speedhash] = numhops;

            if (posx == endpoint.x && posy == endpoint.y) {
                cout << "Optimal solution takes " << numhops << " hops.\n";
                return;
            }

            //db[cx][cy] = thops;
            hqueue.push(make_hproperties(posx, posy, speedx, speedy, numhops));
        }
    }
    if (posx == endpoint.x && posy == endpoint.y)
        cout << "Optimal solution takes " << numhops << " hops.\n";
    else
        cout << "No solution.\n";
}

int main() {
    int testcases;
    cin >> testcases;
    for (int i=0; i<testcases;i++) {
        testcase();
    }
}
