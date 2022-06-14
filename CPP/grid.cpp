#include "config.cpp"
#include "outputs.cpp"
#include "cell.cpp"
#pragma once

class Grid : public Outputs {

public:
    int size;
    vector<vector<Cell>> g;

    int count(int x, int y) {
        int cnt = 0;
        for (int i = x - 1; i <= x + 1; ++i) {
            for (int j = y - 1; j <= y + 1; ++j) {
                if (i < 0 || i > size - 1 || j < 0 || j > size - 1)continue;
                cnt += g[i][j].getCurState();
            }
        }
        return cnt;
    }

    Grid() {
        getSize();
        int sz;
        cin >> sz;
        size = sz;
        g.resize(sz);
        for (int i = 0; i < sz; ++i) {
            g[i].resize(sz);
        }
        system("cls");
    }

    void printGrid() {
        _setmode(_fileno(stdout), _O_U16TEXT);
  //        FILE* myFile = fopen("text.txt", "r");
        int sz = size;
        for (int i = 0; i < sz * 2 + 5; ++i) {
            wprintf(L"-");
        }
        wprintf(L"\n");
        for (int i = 0; i < sz; ++i) {
            wprintf(L"|  ");
            for (int j = 0; j < sz; ++j) {
                if (g[i][j].getCurState()) {
                    wprintf(L"o ");
                } else {
                    wprintf(L"· ");
                }
            }
            wprintf(L" |\n");
        }
        for (int i = 0; i < sz * 2 + 5; ++i) {
            wprintf(L"-");
        }
        wprintf(L"\n");
    }

    void Set() {
        askCords(size);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            g[x][y].setState(true);
        }
        system("cls");
    }

    void nextGen() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int cnt = count(i, j) - g[i][j].getCurState();
                if (g[i][j].getCurState()) {
                    g[i][j].changeNewState(cnt == 2 || cnt == 3);
                } else {
                    g[i][j].changeNewState(cnt == 3);
                }
            }
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                g[i][j].changeCurState();
            }
        }
    }

};