#include <bits/stdc++.h>

using namespace std;

///Andrew's Algorithm
///WHY ANDREW THO???

struct Point {
    long long x, y;
    
    bool operator<(Point p) {
        return x < p.x || (x == p.x && y < p.y);
    }  
    ///overloading operator just in case
};

long long ecuatie(Point C, Point A, Point B) {
    return (A.x - C.x) * (B.y - C.y) - (A.y - C.y) * (B.x - C.x);
}

///Convex Hull 
vector<Point> convex_hull(vector<Point> vec) {
    int n = vec.size(), k = 0;
 
    if (n <= 3)
        return vec;
    vector<Point> ans;
    
    ans.push_back(vec[0]);
    ans.push_back(vec[1]);
    
    for (int i = 0; i < n; i++) {
        while (ans.size() >= 2 && ecuatie(ans[ans.size() - 2], ans[ans.size() - 1], vec[i]) <= 0)
            ans.pop_back();
        ans.push_back(vec[i]);
    }
    
    while (ans.size() >= 1 && ecuatie(ans[ans.size() - 2], ans[ans.size() - 1], vec[0]) <= 0)
        ans.pop_back();
    ///last remove
            
    return ans;
}

int main() {
    int n; cin >> n;
    vector<Point> v;
    
    for(int x, y, i = 0; i < n; i++) {
        cin >> x >> y;
        v.push_back({x, y});
    }
    
    vector<Point> ans = convex_hull(v);
    
    cout << ans.size() << '\n';
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i].x << " " << ans[i].y << '\n';
    }
    
    return 0;
}
