/*
优秀的画圆法有两种？
1.中点画圆
2.正负法
*/
#ifndef DRAWCIRCLE
#define DRAWCIRCLE
#include <bits/stdc++.h>
using namespace std;

class Tool_DrawCircle
{
private:
    vector<vector<int>> draw_a_part(int R)
    {
        int theta = 5 - 4 * R;
        int end = int(R * sqrt(2));
        int curX = 0, curY = R;
        vector<vector<int>> ret;
        ret.push_back({0, R});
        while (curX < end)
        {
            if (theta >= 0)
            {
                theta += (2 * curX - 2 * curY + 5) * 4;
                curX++;
                curY--;
                ret.push_back({curX, curY});
            }
            else
            {
                theta += (2 * curX) * 4;
                curX++;
                ret.push_back({curX, curY});
            }
        }
        return ret;
    }

public:
    vector<vector<int>> draw(int x, int y, int R)
    {
        vector<vector<int>> Circle = draw_a_part(R);
        int len = Circle.size();
        for (int i = 0; i < len; i++)
        {
            Circle.push_back({Circle[i][1], Circle[i][0]});
        }
        for (int i = 0; i < 2 * len; i++)
        {
            Circle.push_back({-Circle[i][0], Circle[i][1]});
        }
        for (int i = 0; i < 4 * len; i++)
        {
            Circle.push_back({Circle[i][0], -Circle[i][1]});
        }
        return Circle;
    }
    vector<vector<int>> draw(int x, int y, int R, int width)
    {
        vector<vector<int>> Circle = draw(x, y, R);
        for (int i = 1; i < width / 2 + 1; i++)
        {
            vector<vector<int>> temp = draw(x, y, R + i);
            Circle.insert(Circle.end(), temp.begin(), temp.end());
        }
        for (int i = 1; i < (width + 1) / 2; i++)
        {
            vector<vector<int>> temp = draw(x, y, R - i);
            Circle.insert(Circle.end(), temp.begin(), temp.end());
        }
        return Circle;
    }
};

#endif