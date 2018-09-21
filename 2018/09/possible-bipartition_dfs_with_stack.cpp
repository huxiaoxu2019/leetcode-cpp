/**
 * https://leetcode.com/problems/possible-bipartition/description/
 *
 * dfs with stack
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <stack>

using namespace std;

class Solution {
    public:
        bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
            _g = vector< vector<int> >(N);
            // create the graph(two-demontional array)
            for (int i = 0; i < (int)dislikes.size(); ++i) {
                _g[dislikes[i][0] - 1].push_back(dislikes[i][1] - 1);
                _g[dislikes[i][1] - 1].push_back(dislikes[i][0] - 1);
            }

            // fill colors
            _colors = vector<int>(N, 0); // 0 for unknow, 1 for red, -1 for blue

            // dfs with stack
            for (int i = 0; i < N; ++i) {
                if (_colors[i] == 0 && !dfs(i, 1)) return false;
            }

            return true;
        }

    private:
        vector< vector<int> > _g;
        vector<int> _colors;
        stack<vector<int>> _sstack; // _sstack[0] for cur node, 1 for cur color
        bool dfs(int cur, int color) {
            _sstack.push(vector<int>{cur, color});
            while (_sstack.size()) {
                // get head item
                cur = _sstack.top()[0];
                color = _sstack.top()[1];

                // pop
                _sstack.pop();

                // set color
                _colors[cur] = color;

                for (int ccur : _g[cur]) {
                    if (_colors[ccur] == color) return false;
                    // push
                    if (_colors[ccur] == 0) _sstack.push(vector<int> {ccur, -color});
                }
            }
            return true;
        }
};

int main(int argc, char * argv[]) {
    bool c;
    Solution * s = new Solution();
    //[[1,2],[1,3],[2,3]]
    vector< vector<int> > l;
    vector<int> l1, l2, l3;
    l1.push_back(1);
    l1.push_back(2);
    l2.push_back(1);
    l2.push_back(3);
    l3.push_back(2);
    l3.push_back(3);
    l.push_back(l1);
    l.push_back(l2);
    l.push_back(l3);
    c = s->possibleBipartition(3, l);
    cout<<c<<endl;
}
