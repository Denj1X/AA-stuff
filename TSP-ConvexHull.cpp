#include <bits/stdc++.h>

using namespace std;

///Andrew's algorithm

struct Point {
    long long x, y;

    bool operator==(const Point &a) const {
        return (x == a.x && y == a.y);
    }

    ///using overloading operators
    ///for different STL methods
    Point operator=(const Point &a) {
        x = a.x;
        y = a.y;
        return *this;
    }
};

vector<Point> points, hull;

long long ecuatie(Point C, Point A, Point B) {
    return (A.x - C.x) * (B.y - C.y) - (A.y - C.y) * (B.x - C.x);
}

double distPoints(Point A, Point B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

bool compare(Point a, Point b) {
    long long o = ecuatie(points[0], a, b);

    if(o == 0)
        return distPoints(points[0], a) < distPoints(points[0], b);

    return o >= 0;
}
///comapre function for sorting points

void deleteLastLast(vector<Point> &v) {
    Point aux = v[v.size() - 1];
    v.pop_back();
    v.pop_back();
    v.push_back(aux);
}
///function for removing some points for convex hull

int main() {
    long long n, minY = INT_MAX, poz = 0;
    cin >> n;

    for(long long x, y, i = 0; i < n; i++) {
        cin >> x >> y;
        if(y < minY || (y == minY && x < points[poz].x)) {
            minY = y;
            poz = i;
        }
        points.push_back({x, y});
    }

    //bring the bootommost points first in the vector
    Point aux = points[0];
    points[0] = points[poz];
    points[poz] = aux;


    sort(points.begin() + 1, points.end(), compare);

    points.push_back(points[0]);
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for(int i = 2; i < points.size(); i++) {
        hull.push_back(points[i]);

        while(hull.size() > 2 &&
              ecuatie(hull[ hull.size() - 3 ],
                     hull[ hull.size() - 2 ],
                     hull[ hull.size() - 1 ] ) <= 0)   {
            deleteLastLast(hull);
        }
    }

    points.pop_back();

    Point minR, minI, minJ;
    double minStep3 = LONG_MAX;

    while(hull.size() <= n) {
        minStep3 = LONG_MAX;

        for(auto point : points) {
            ///the main reason for using overloading operator
            if (find(hull.begin(), hull.end(), point) == hull.end()) {
                Point r = point;
                double distMin = LONG_MAX;
                Point pi, pj;

                //finding pair(i, j) from Step 2
                for (int i = 0; i < hull.size() - 1; i++) {
                    double dist = distPoints(hull[i], r) + distPoints(r, hull[i + 1]) - distPoints(hull[i], hull[i + 1]);

                    //finding min r i j
                    if (dist < distMin) {
                        distMin = dist;
                        pi = hull[i];
                        pj = hull[i + 1];
                    }
                }

                double dist = (distPoints(pi, r) + distPoints(r, pj)) / distPoints(pi, pj);

                //finding min r* i* j*
                if (dist < minStep3) {
                    minStep3 = dist;
                    minR = r;
                    minI = pi;
                    minJ = pj;
                }
            }
        }

        hull.insert(find(hull.begin(), hull.end(), minI) + 1, minR);
    }

    for(auto p : hull) {
        cout << p.x << " " << p.y << '\n';
    }
    return 0;
}
