/*利用中点划线算法*/

#ifndef DRAWLINE
#define DRAWLINE

#include <bits/stdc++.h>
using namespace std;

class Tool_DrawLine
{
public:
    vector<vector<int>> draw(int x1, int y1, int x2, int y2, int width = 1)
    {
        //预处理x1,x2,y1,y2的顺序
        if ((abs(x1 - x2) >= abs(y1 - y2) && x2 <= x1) || (abs(x1 - x2) < abs(y1 - y2) && y2 <= y1))
        {
            swap(x1, x2);
            swap(y1, y2);
        }

        if (abs(x1 - x2) >= abs(y1 - y2))
        {
            if (y1 >= y2)
            {
                int a = y1 - y2, b = -(x1 - x2), c = x1 * y2 - y1 * x2;
                int d1 = 2 * a, d2 = 2 * a - 2 * b, theta = 2 * a - b;
                int curX = x1, curY = y1;
                vector<vector<int>> ret;
                ret.push_back({x1, y1});
                while (curX < x2)
                {
                    if (theta < 0)
                    {
                        curX++;
                        theta += d1;
                        for (int i = 0; i < (width + 1) / 2; i++)
                            ret.push_back({curX, curY + i});
                        for (int i = 1; i < width / 2 + 1; i++)
                            ret.push_back({curX, curY - i});
                    }
                    else
                    {
                        curX++;
                        curY--;
                        theta += d2;
                        for (int i = 0; i < (width + 1) / 2; i++)
                            ret.push_back({curX, curY - i});
                        for (int i = 1; i < width / 2 + 1; i++)
                            ret.push_back({curX, curY + i});
                    }
                }
                return ret;
            }
            else
            {
                int a = y1 - y2, b = -(x1 - x2), c = x1 * y2 - y1 * x2;
                int d1 = 2 * a, d2 = 2 * a + 2 * b, theta = 2 * a + b;
                int curX = x1, curY = y1;
                vector<vector<int>> ret;
                ret.push_back({x1, y1});
                while (curX < x2)
                {
                    if (theta > 0)
                    {
                        curX++;
                        theta += d1;
                        for (int i = 0; i < (width + 1) / 2; i++)
                            ret.push_back({curX, curY - i});
                        for (int i = 1; i < width / 2 + 1; i++)
                            ret.push_back({curX, curY + i});
                    }
                    else
                    {
                        curX++;
                        curY++;
                        theta += d2;
                        for (int i = 0; i < (width + 1) / 2; i++)
                            ret.push_back({curX, curY + i});
                        for (int i = 1; i < width / 2 + 1; i++)
                            ret.push_back({curX, curY - i});
                    }
                }
                return ret;
            }
        }
        else
        {
            if (x1 >= x2)
            {
                int a = y1 - y2, b = -(x1 - x2), c = x1 * y2 - y1 * x2;
                int d1 = 2 * b, d2 = -2 * a + 2 * b, theta = -a + 2 * b;
                int curX = x1, curY = y1;
                vector<vector<int>> ret;
                ret.push_back({x1, y1});
                while (curY < y2)
                {
                    if (theta > 0)
                    {
                        curY++;
                        theta += d1;
                        for (int i = 0; i < (width + 1) / 2; i++)
                            ret.push_back({curX + i, curY});
                        for (int i = 1; i < width / 2 + 1; i++)
                            ret.push_back({curX - i, curY});
                    }
                    else
                    {
                        curX--;
                        curY++;
                        theta += d2;
                        for (int i = 0; i < (width + 1) / 2; i++)
                            ret.push_back({curX - i, curY});
                        for (int i = 1; i < width / 2 + 1; i++)
                            ret.push_back({curX + i, curY});
                    }
                }
                return ret;
            }
            else
            {
                int a = y1 - y2, b = -(x1 - x2), c = x1 * y2 - y1 * x2;
                int d1 = 2 * b, d2 = 2 * a + 2 * b, theta = a + 2 * b;
                int curX = x1, curY = y1;
                vector<vector<int>> ret;
                ret.push_back({x1, y1});
                while (curY < y2)
                {
                    if (theta < 0)
                    {
                        curY++;
                        theta += d1;
                        for (int i = 0; i < (width + 1) / 2; i++)
                            ret.push_back({curX - i, curY});
                        for (int i = 1; i < width / 2 + 1; i++)
                            ret.push_back({curX + i, curY});
                    }
                    else
                    {
                        curX++;
                        curY++;
                        theta += d2;
                        for (int i = 0; i < (width + 1) / 2; i++)
                            ret.push_back({curX + i, curY});
                        for (int i = 1; i < width / 2 + 1; i++)
                            ret.push_back({curX - i, curY});
                    }
                }
                return ret;
            }
        }
    }
};
#endif