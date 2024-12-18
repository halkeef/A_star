#include <iostream>
#include <vector>
#include <math.h>
#include <Windows.h>
#include "graphics.h"
using namespace std;
#define MAP_ROW 27
#define MAP_COL 23
#define STRAIGHT 10
#define SLASH 14
enum DIRECTION { D_up, D_left, D_down, D_right, D_l_up, D_l_down, D_r_up, D_r_down };

struct MyPoint {
    int p_row, p_col;
    int f, g, h;
};

struct TreeNode {
    MyPoint point;
    //vector<TreeNode*> Child;
    TreeNode* Parent;
};

TreeNode* CreatNode(int row, int col) {
    TreeNode* New_node = new TreeNode;
    *New_node = { 0 };
    New_node->point.p_row = row;
    New_node->point.p_col = col;
    return New_node;
}

int Get_H(MyPoint p, MyPoint end) {
    int H = abs(p.p_row - end.p_row) + abs(p.p_col - end.p_col);
    return H * STRAIGHT;
}

int main() {
 /*   int MAP[MAP_ROW][MAP_COL] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},*/

   int MAP[MAP_ROW][MAP_COL] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1},
  {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1},
  {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1},
  {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
  {1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    
    
    
    
    };
    
    initgraph(460, 540);
    setbkcolor(WHITE);
    cleardevice();
    

    // 绘制网格
    setlinecolor(BLACK);
    for (int i = 0; i < 460; i += 20)
    {
        line(i, 0, i, 540);
    }
    for (int j = 0; j < 540; j += 20)
    {
        line(0, j, 460, j);
    }

    // 绘制障碍物
    setfillcolor(BLACK);
    for (int row = 0; row < MAP_ROW; row++)
    {
        for (int col = 0; col < MAP_COL; col++)
        {
            if (MAP[row][col] == 1)
            {
                fillrectangle(col * 20, row * 20, (col + 1) * 20, (row + 1) * 20);
            }
        }
    }


    bool isPass[MAP_ROW][MAP_COL] = { false };
    bool isFinded = false;
    MyPoint m_begin = { 1,3 };
    MyPoint m_end = { 21,19 };
   // MyPoint m_end = { 13,17 };
    // 绘制起点（绿色）
    setfillcolor(RGB(56,146,93));
    fillrectangle(m_begin.p_col * 20, m_begin.p_row * 20, (m_begin.p_col + 1) * 20, (m_begin.p_row + 1) * 20);

    // 绘制终点（红色）
    setfillcolor(RGB(195,56,13));
    fillrectangle(m_end.p_col * 20, m_end.p_row * 20, (m_end.p_col + 1) * 20, (m_end.p_row + 1) * 20);

    Sleep(2000);

    TreeNode* Root = CreatNode(m_begin.p_row, m_begin.p_col);
    TreeNode* CurrNode = Root;
    isPass[CurrNode->point.p_row][CurrNode->point.p_col] = true;
    vector<TreeNode*>Buff;
    while (1) {
        for (int i = 0; i < 8; i++) {
            TreeNode* temp_Child = CreatNode(CurrNode->point.p_row, CurrNode->point.p_col);
            switch (i) {
            case(D_up):
                temp_Child->point.p_row--;
                temp_Child->point.g += STRAIGHT;
                break;
            case(D_left):
                temp_Child->point.p_col--;
                temp_Child->point.g += STRAIGHT;
                break;
            case(D_down):
                temp_Child->point.p_row++;
                temp_Child->point.g += STRAIGHT;
                break;
            case(D_right):
                temp_Child->point.p_col++;
                temp_Child->point.g += STRAIGHT;
                break;
            case(D_l_up):
                temp_Child->point.p_row--;
                temp_Child->point.p_col--;
                temp_Child->point.g += SLASH;
                break;
            case(D_l_down):
                temp_Child->point.p_row++;
                temp_Child->point.p_col--;
                temp_Child->point.g += SLASH;
                break;
            case(D_r_up):
                temp_Child->point.p_row--;
                temp_Child->point.p_col++;
                temp_Child->point.g += SLASH;
                break;
            case(D_r_down):
                temp_Child->point.p_row++;
                temp_Child->point.p_col++;
                temp_Child->point.g += SLASH;
                break;
            }
            if (isPass[temp_Child->point.p_row][temp_Child->point.p_col] == false
                && MAP[temp_Child->point.p_row][temp_Child->point.p_col] != 1
                && temp_Child->point.p_row < MAP_ROW && temp_Child->point.p_row >= 0
                && temp_Child->point.p_col < MAP_COL && temp_Child->point.p_col >= 0) {

                //枝桠
                setfillcolor(RGB(240,216,120));
                fillrectangle(temp_Child->point.p_col * 20, temp_Child->point.p_row * 20, (temp_Child->point.p_col + 1) * 20, (temp_Child->point.p_row + 1) * 20);
                Sleep(40);
                temp_Child->point.h = Get_H(temp_Child->point, m_end);
                temp_Child->point.f = temp_Child->point.g + temp_Child->point.h;
                temp_Child->Parent = CurrNode;
                Buff.push_back(temp_Child);
            }
            else {
                delete temp_Child;
            }

        }//end of for
        auto it = Buff.begin();
        auto minIt = Buff.begin();  //f最小
        for (it; it != Buff.end(); it++) {
            if ((*it)->point.f < (*minIt)->point.f) {
                minIt = it;
            }
        }
        CurrNode = *minIt;
        Buff.erase(minIt);
        isPass[CurrNode->point.p_row][CurrNode->point.p_col] = true;
        if (CurrNode->point.p_row == m_end.p_row && CurrNode->point.p_col == m_end.p_col) {
            isFinded = true;
            break;
        }
        if (Buff.size() == 0) {
            break;
        }
    }//end of while

    if (isFinded) {
        //cout<<"找到路径："<<endl;
        puts("找到路径：");
        vector<TreeNode*>ShowArr;
        while (CurrNode) {
            ShowArr.push_back(CurrNode);
            CurrNode = CurrNode->Parent;
        }

        //回溯
        for (auto i = ShowArr.begin(); i != ShowArr.end()-1; i++) {
            setfillcolor(RGB(6, 111, 166));
            fillrectangle((*i)->point.p_col * 20, (*i)->point.p_row * 20, ((*i)->point.p_col + 1) * 20, ((*i)->point.p_row + 1) * 20);
            Sleep(50);
        }


        auto i = ShowArr.rbegin();
        for (; i != ShowArr.rend(); i++) {
            cout << "(" << (*i)->point.p_row << "," << (*i)->point.p_col << ")->";
        }
        cout << "end" << endl;
    }
    else {
        cout << "找不到路径！" << endl;
    }
    system("pause");
    return 0;
}