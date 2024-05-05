#include <iostream>

using namespace std;

bool sert = false;

//y 2 3 12 15 6 6 36 4 2 20 4 8 40
bool isEnd(double* z_c, int n)
{
    double e = 1e-10;
    bool end = false;

    for (int i = 0; i < n; i++)
    {
        if (sert)
        {
            if (z_c[i] < 0 && abs(z_c[i]) > e) end = true;
        }
        else
        {
            if (z_c[i] > 0) end = true;
        }
    }
    return end;
}

int main()
{
    int n, m;

    cout << "Maksimallasdirmadir mi? (y/n): ";
    string b;
    cin >> b;

    if (b == "y" || b == "Y")
    {
        sert = true;
    }

    cout << "Deyisken sayi: ";
    cin >> n;

    cout << "Sertlerin sayi: ";
    cin >> m;

    double* s = new double[m];
    double* x = new double[n];
    double* c = new double[m];
    double** a = new double* [m];

    for (int i = 0; i < m; i++)
    {
        a[i] = new double[n + m + 1];
    }

    cout << "Meqsed funksiyasinin emsallarini daxil et:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    cout << "Sertler matrisini daxil et:\n";

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            if (j == n)
            {
                cin >> a[i][n + m];
            }
            else
            {
                cin >> a[i][j];
            }
        }

        for (int j = n; j < n + m; j++)
        {
            if (j - n == i) a[i][j] = 1;
            else a[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++)
    {
        s[i] = 0;
        c[i] = 0;
    }
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << x[i] << "\t";
    }
    for (int i = 0; i < n; i++)
    {
        cout << s[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n + m + 1; j++)
        {
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }

    double* z = new double[n + m + 1];
    double* z_c = new double[n + m];

    for (int i = 0; i < m + n + 1; i++)
    {
        z[i] = 0;
        for (int j = 0; j < m; j++)
        {
            z[i] += c[j] * a[j][i];
        }
        //cout << z[i] << "\t";

        if (i < n)
        {
            z_c[i] = z[i] - x[i];
        }
        else
        {
            if (i < n + m)
            {
                z_c[i] = z[i] - s[i - n];
            }
        }
    }
    //cout << endl;

    for (int i = 0; i < n + m; i++)
    {
        cout << z_c[i] << "\t";
    }
    cout << endl;

    while (isEnd(z_c, m + n))
    {
        double max = !sert ? -DBL_MAX : z_c[0];
        int index_j = 0;
        for (int i = 0; i < n + m; i++)
        {
            if (sert)
            {
                if(z_c[i] < 0)
                if (max > z_c[i])
                {
                    max = z_c[i];
                    index_j = i;
                }
            }
            else
            {
                if(z_c[i] >0)
                if (max < z_c[i])
                {
                    max = z_c[i];
                    index_j = i;
                }
            }
        }

        int index_i = 0;
        double min = a[0][index_j] > 0 ? a[0][n + m] / a[0][index_j] : DBL_MAX;
        for (int i = 0; i < m; i++)
        {
            if(a[i][n + m] / a[i][index_j] > 0)
            if (a[i][n + m] / a[i][index_j] < min)
            {
                index_i = i;
                min = a[i][n + m] / a[i][index_j];
            }
        }

        c[index_i] = x[index_j];

        cout << "c : ";
        for (int i = 0; i < m; i++)
        {
            cout << c[i] << " ";
        }
        cout << endl << endl;
        //1

        double h = a[index_i][index_j];
        for (int i = 0; i < n + m + 1; i++)
        {
            a[index_i][i] /= h;
        }

        //0

        for (int i = 0; i < m; i++)
        {
            if (i != index_i)
            {
                double k = a[i][index_j];

                for (int j = 0; j < n + m + 1; j++)
                {
                    a[i][j] -= k * a[index_i][j];
                }
            }
        }

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n + m + 1; j++)
            {
                cout << a[i][j] << "\t";
            }
            cout << endl;
        }

        cout << "z:\t";
        for (int i = 0; i < m + n + 1; i++)
        {
            z[i] = 0;
            for (int j = 0; j < m; j++)
            {
                z[i] += c[j] * a[j][i];
            }
            cout << z[i] << "\t";
        }
        cout << endl;

        cout << "z - c:\t";
        for (int i = 0; i < m + n; i++)
        {
            if (i < n)
            {
                z_c[i] = -(x[i] - z[i]);
            }
            else
            {
                if (i < n + m)
                {
                    z_c[i] = -(s[i - n] - z[i]);
                }
            }
            cout << z_c[i] << "\t";
        }
        cout << endl;
    }
    cout << "\nOptimal qiymet: " << z[n + m];
}