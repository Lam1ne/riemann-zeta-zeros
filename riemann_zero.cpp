#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <fstream>
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

const long double PI = 3.14159265358979323846L;

// Riemann-Siegel Z-function (with correction term)
long double Z(long double t) {
    long double a = sqrt(t / (2.0L * PI));
    int N = static_cast<int>(a);
    long double sum = 0.0L;

    #pragma omp parallel for reduction(+:sum)
    for (int n = 1; n <= N; ++n) {
        long double phi = t * log((long double)n) - t / 2.0L - PI / 8.0L;
        sum += cos(phi) / sqrt((long double)n);
    }

    // Riemann-Siegel theta
    long double theta = t * log(t / (2.0L * PI)) / 2.0L - t / 2.0L - PI / 8.0L;
    long double phiN = t * log((long double)(N + 1)) - t / 2.0L - PI / 8.0L;
    long double sign = (N % 2 == 0) ? 1.0L : -1.0L;

    // First correction term (already present)
    long double R1 = sign * cos(phiN) / (sqrt((long double)(N + 1)) * PI);

    // Second correction term (R2)
    long double R2 = -sign * sin(phiN) * (t / (2.0L * PI * (N + 1))) / (sqrt((long double)(N + 1)) * PI);

    return 2.0L * sum + R1 + R2;
}

// Bisection method to find a zero
long double find_zero(long double t1, long double t2, long double tol = 1e-14L, int max_iter = 100) {
    long double f1 = Z(t1);
    long double f2 = Z(t2);
    if (f1 * f2 > 0) {
        cerr << "No sign change in interval!" << endl;
        return NAN;
    }
    for (int i = 0; i < max_iter; ++i) {
        long double tm = 0.5L * (t1 + t2);
        long double fm = Z(tm);
        if (abs(fm) < tol) return tm;
        if (f1 * fm < 0) {
            t2 = tm;
            f2 = fm;
        } else {
            t1 = tm;
            f1 = fm;
        }
    }
    return 0.5L * (t1 + t2);
}

int main(int argc, char* argv[]) {
    // Default parameters
    long double t_start = 14.0L, t_end = 30.0L, step = 0.01L, tol = 1e-14L;
    if (argc >= 3) {
        t_start = stold(argv[1]);
        t_end = stold(argv[2]);
    }
    if (argc >= 4) step = stold(argv[3]);
    if (argc >= 5) tol = stold(argv[4]);

    cout.precision(numeric_limits<long double>::digits10 + 2);
    cout << "Scanning for non-trivial zeros of the Riemann zeta function (Riemann-Siegel formula, with correction term)..." << endl;
    cout << "Range: " << t_start << " to " << t_end << ", step: " << step << ", tolerance: " << tol << endl;

    int zero_count = 0;
    long double prev = Z(t_start);
    ofstream fout("zeros.txt");
    fout.precision(numeric_limits<long double>::digits10 + 2);
    fout << fixed; // Optional, but recommended for scientific data
    for (long double t = t_start + step; t <= t_end; t += step) {
        long double curr = Z(t);
        if (prev * curr < 0) {
            long double zero = find_zero(t - step, t, tol);
            cout << "Zero #" << ++zero_count << " at s = 0.5 + " << zero << "i" << endl;
            fout << zero << endl;
        }
        prev = curr;
    }
    fout.close();

    ofstream plotout("zeta_plot.csv");
    plotout.precision(numeric_limits<long double>::digits10 + 2);
    plotout << "t,Zt\n"; // CSV header
    for (long double t = t_start; t <= t_end; t += step) {
        long double zt = Z(t);
        plotout << t << "," << zt << "\n";
    }
    plotout.close();

    if (zero_count == 0) {
        cout << "No zeros found in the specified range." << endl;
    } else {
        cout << "Total zeros found: " << zero_count << endl;
    }
    return 0;
}