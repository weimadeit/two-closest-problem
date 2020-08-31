#include <iostream>
#include <vector>
#include "point_class.h"
#define min(a,b) ((a) < (b) ? (a) : (b))
using namespace std;
double MinDistance(vector<Point> &src_x, vector<Point> &src_y, int lc, int rc,
        int *l1, int *l2);
int main() {
    vector<Point> points;
    for (int i = 0; i < 10; ++i)
    {
        Point tmp_point;
        points.push_back(tmp_point);
    }
    vector<Point> points_x(points), points_y(points);
    sort(points_x.begin(), points_x.end(), LesserX);
    sort(points_y.begin(), points_y.end(), LesserY);
    int l1, l2;
    double min = MinDistance(points_x, points_y, 0, points_x.size()-1,
            &l1, &l2);
    cout.setf(ios_base::fixed);
    cout.precision(2);
    cout << "points are:\n";
    for (auto& entry : points_x)
        cout << entry << " ";
    cout << endl;
    cout << "minimum distance is " << min << endl;
    cout << "points label are: " << l1 << " and " << l2 << endl;
    return 0;
}
double MinDistance(vector<Point> &src_x, vector<Point> &src_y, int lc, int rc,
        int *l1, int *l2)
{
    if (lc == rc - 1)
    {
        *l1 = lc;
        *l2 = rc;
        return Dist(src_x[lc], src_x[rc]);
    }
    int mid = (lc + rc)/2;
    vector<Point> src_yl, src_yr;
    for (auto& entry : src_y)
    {
        if (entry.x <= src_x[mid].x)
            src_yl.push_back(entry);
        if (entry.x >= src_x[mid].x)
            src_yr.push_back(entry);
    }
    int ll1, ll2, rl1, rl2, cl1, cl2;
    double minL = MinDistance(src_x, src_yl, lc, mid, &ll1, &ll2);
    double minR = MinDistance(src_x, src_yr, mid, rc, &rl1, &rl2);
    double delta = min(minL, minR);
    if (delta == minL)
    {
        *l1 = ll1;
        *l2 = ll2;
    } else
    {
        *l1 = rl1;
        *l2 = rl2;
    }
    vector<Point>::iterator iter;
    for (iter = src_y.begin(); iter != src_y.end(); ++iter)
    {
        if (abs((*iter).x - src_x[mid].x) > delta)
        {
            src_y.erase(iter);
            iter--;
        }
    }
    if (src_y.size() >= 2)
        for (int i = 0; i < src_y.size(); ++i)
            for (int j = i+1; j < src_y.size(); ++j)
            {
                if (src_y[j].y - src_y[i].y > delta)
                    break;
                if (Dist(src_y[i], src_y[j]) < delta)
                {
                    delta = Dist(src_y[i], src_y[j]);
                    for (int k = 0; k < src_x.size(); ++k)
                    {
                        if (src_x[k].x == src_y[i].x && src_x[k].y == src_y[i].y)
                            cl1 = k;
                        if (src_x[k].x == src_y[j].x && src_x[k].y == src_y[j].y)
                            cl2 = k;
                        *l1 = cl1;
                        *l2 = cl2;
                    }
                }
            }
    return delta;
}