#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>

using namespace std;

typedef struct {
    int x;
    int y;
} point;
int check_line(vector<vector<char> > & area, point& pos, int s, int r, int lx, int ly) {
    int maxHeight = area[lx].size();
    if (maxHeight > (ly+s*2)) {
        maxHeight = ly+s*2;
    }
    int flag = 0;
    int counter = 0;
    for (int i=ly;i<maxHeight;i++) {
        if (area[lx][i]) {
            if (!flag) {
                counter = 1;
                flag = 1;
                pos.y = i;
            }
            else {
                counter++;
            }

        } else {
            flag = 0;
        }
    }
    if (counter >= s)
}

int check_area(vector<vector<char> > & area, point& pos, int s, int r, int lx, int ly) {

}

int step_line(vector<vector<char> > & area, point& pos, int s, int r, int lx) {
    int height = area[lx].size();
    for(int i=0; i<height;i +=(s/2)) {
        if (area[lx][i] == 0) {
            if (check_area(area, pos, s, r, lx, i))
                return 1;
        }
    }
    return 0;
}

void testcase() {
    int w;
    int h;
    cin >> w;
    cin >> h;
    vector<vector<char> > area(w, vector<char>(h, 0));

    int r,s;
    cin >> s;
    cin >> r;

    int num_trees;
    cin >> num_trees;
    for (int i=0; i<num_trees; i++) {
        int x;
        int y;
        cin >> x;
        cin >> y;
        area[x][y] = 1;
    }

    point result = {-1, -1};
    for (int i=0; i<w; i+= r) {
        if (step_line(area, result, s, r, i)) {
            cout << result.x << " " << result.y << "\n";
            return;
        }
    }
    cout << "Impossible\n";
}

int main()
{
    int testcases;
    cin >> testcases;
    for (int i=0; i<testcases; i++) {
        testcase();
    }
    return 0;
}
