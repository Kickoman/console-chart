#include <iostream>
#include "CommonUtils.h"
#include "kfunction.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <assert.h>
#include <float.h>

using namespace std;

void getTerminalSize(int &cols, int &lines)
{
#ifdef TIOCGSIZE
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    cols = ts.ts_cols;
    lines = ts.ts_lines;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
    cols = ts.ws_col;
    lines = ts.ws_row;
#endif /* TIOCGSIZE */
}

vector<long double> calculatePoints(Function<long double>& f, long double l, long double r, int n)
{
    vector<long double> result(n);
    long double x = l, hx = (r - l) / n;

    for (int i = 0; i < n; ++i, x += hx)
        result[i] = f.run(x);

    return result;
}

int findZeroX(Function<long double>& f, long double l, long double r, int n)
{
    auto diff = DBL_MAX;
    int ans = -1;
    long double x = l, hx = (r - l) / n;

    for (int i = 0; i < n; ++i, x += hx)
    {
        if (fabs(x) < diff)
        {
            diff = fabs(x);
            ans = i;
        }
    }
    return ans;
}

void printFunction(Function<long double>& f, long double l, long double r)
{
    int cols, lines;
    getTerminalSize(cols, lines);
    vector<vector<short>> field(lines, vector<short>(cols, 0));

    vector<long double> points = calculatePoints(f, l, r, cols);

    long double miny = points[0], maxy = points[0];

    for (long double point : points)
    {
        miny = min(miny, point);
        maxy = max(maxy, point);
    }

    long double shiftUp = 0 - miny;

    for (long double & point : points)
    {
        point += shiftUp;
    }
    miny += shiftUp;
    maxy += shiftUp;

    long double hy = maxy / (lines - 1);

    assert(miny == 0);
    assert((maxy / hy) < lines);

    int axisx = int(shiftUp / hy);

    for (int i = 0; i < cols; ++i)
        field[axisx][i] = 2;

    int axisy = findZeroX(f, l, r, cols);
    if (axisy != -1)
        for (int i = 0; i < lines; ++i)
            field[i][axisy] = 2;

    for (int i = 0; i < cols; ++i)
    {
        int y = floor(points[i] / hy);
//        cerr << "[" << i << "]:\tpoints[i] = " << points[i] << "\thy = " << hy << "\ty = " << y << "\tUnround: " << points[i] / hy << endl;
        field[y][i] = 1;

    }


    for (int i = lines - 1; i >= 0; --i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (field[i][j] == 0)
                cout << " ";
            if (field[i][j] == 1)
                cout << "●";
            if (field[i][j] == 2)
                cout << "▬";
        }
        cout << endl;
    }
}

int main()
{
    Function<long double> f;
    cout << "Input the function: ";
    string raw_function;
    getline(cin, raw_function);
    f.set_function(raw_function);

    cout << "Input x range: ";
    long double l, r;
    cin >> l >> r;

    printFunction(f, l, r);
    return 0;
    cout << "Input arg: ";
    long double arg;
    cin >> arg;
    cout << "result: " << f.run(arg) << endl;
    return 0;
}
