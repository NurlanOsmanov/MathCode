#include <iostream>
using namespace std;

#define N 10
#define M 5

double J(double u[N+1][M], double* f, double tau, double k0, double h)
{
	double H = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 1; j < M - 1; j++)
		{
			u[i + 1][j] = u[i][j] + (tau * k0) / (h * h) * (u[i][j - 1] - 2 * u[i][j] + u[i][j + 1]);
		}
	}
	for (int i = 0; i <= N; i++)
	{
		H += (u[i][1] - f[i]) * (u[i][1] - f[i]);
	}

	return H;
}

int main()
{
	double e1, e2;
	double u[N + 1][M];
	double a, b, h, tau, T, k0, k, ksi;
	k0 = 1;
	T = 0.1;
	a = 0;
	b = 1;
	h = (b - a) / M;
	tau = T / N;

	//5-ci sert qiymetleri:
	double q[N + 1] = { 0.198669, 0.195699 ,0.192773 ,0.152062 ,0.121417 ,0.0947762 ,0.0741491 ,0.0578571 ,0.0451612, 0.03524, 0.0274998 };

	//qradient addimi
	ksi = 0.1;
	//Dayanma serti
	e1 = 0.0001;
	//Toreme epslonu
	e2 = 0.0001;

	//baslangic sert
	for (int i = 0; i < M; i++)
	{
		double x = a + h * i;
		u[0][i] = sin(x);
	}

	//serhed sertleri
	for (int i = 0; i <= N; i++)
	{
		u[i][0] = 0;
		u[i][M - 1] = 0;
	}
	while (true)
	{
		//En kicik kvadratlar ile J tapilir

		double J_0 = J(u, q, tau, k0, h);

		//Qradiyent, yeni toreme hesablanir

		double grad_J = (J(u, q, tau, k0 + e2, h) - J_0) / e2;

		//qradient usulu tedbiq edilir.

		k = k0 - ksi * grad_J;


		//Dayandirma serti
		if (abs(grad_J) < e1 || abs(k - k0) < e1) break;
		k0 = k;
	}
	cout << "k = " << k << endl;

	cout << "\nNetice:" << endl;
	//Neticenin ekrana cixarilmasi
	//yeni k ucun sebeke qurulur
	for (int i = 0; i < N; i++)
	{
		for (int j = 1; j < M - 1; j++)
		{
			u[i + 1][j] = u[i][j] + (tau * k) / (h * h) * (u[i][j - 1] - 2 * u[i][j] + u[i][j + 1]);
		}
	}

	for (int i = 0; i <= N; i++)
	{
		cout << "t = " << i * tau << ":   \t";
		for (int j = 0; j < M; j++)
		{
			cout << u[i][j] << "   \t";
		}
		cout << endl << endl;
	}
	cout << "\nDeqiq qiymet:\n";
	//ilk misal ucun 1.5 goturmusduk.
	for (int i = 0; i < N; i++)
	{
		for (int j = 1; j < M - 1; j++)
		{
			u[i + 1][j] = u[i][j] + (tau * 1.5) / (h * h) * (u[i][j - 1] - 2 * u[i][j] + u[i][j + 1]);
		}
	}

	for (int i = 0; i <= N; i++)
	{
		cout << "t = " << i * tau << ":   \t";
		for (int j = 0; j < M; j++)
		{
			cout << u[i][j] << "  \t";
		}
		cout << endl << endl;
	}
}
