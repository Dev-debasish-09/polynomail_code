#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

class Polynomial {
private:
    vector<int> vec1;
    vector<int> vec2;
    int deg1;
    int deg2;

public:
    // Constructor
    Polynomial(int d1, int d2, vector<int> v1, vector<int> v2) {
        deg1 = d1;
        deg2 = d2;
        vec1 = v1;
        vec2 = v2;
    }

    // Destructor
    ~Polynomial() {
        cout<<"code end"<<endl;
    };


    // Output of the polynomial
    void printpoly(vector<int> &x, int y) {
        if (y == 0) {
            cout << "It is a constant polynomial and the term is:" << endl;
            cout << x[0];
        } else {
            for (int i = y; i >= 0; i--) {
                cout << x[i] << "x^" << i;
                if (i != 0) {
                    cout << " + ";
                }
            }
        }
        cout << endl;
    }

    // Sum of two polynomials
    void sum_of_poly(vector<int> &x, vector<int> &y) {
        int m = x.size();
        int n = y.size();
        int deg = max(m, n);
        vector<int> result(deg, 0);
        for (int i = 0; i < m; i++) {
            result[i] = result[i] + x[i];
        }
        for (int i = 0; i < n; i++) {
            result[i] = result[i] + y[i];
        }
        printpoly(result, deg - 1);
    }

    // Difference of two polynomials
    void diff_of_poly(vector<int> &x, vector<int> &y) {
        int m = x.size();
        int n = y.size();
        int deg = max(m, n);
        vector<int> result(deg, 0);
        for (int i = 0; i < m; i++) {
            result[i] = result[i] + x[i];
        }
        for (int i = 0; i < n; i++) {
            result[i] = result[i] - y[i];
        }
        printpoly(result, deg - 1);
    }

    // Product of two polynomials
    vector<int> prod_of_poly(vector<int> &x, vector<int> &y) {
        int m = x.size();
        int n = y.size();
        int deg = m + n - 1;
        vector<int> result(deg, 0);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result[i + j] += x[i] * y[j];
            }
        }
        return result;
    }

    // Division of two polynomials
    void div_of_poly(vector<int> &x, vector<int> &y) {
        vector<int> u, v;
        int m = x.size() - 1;
        int n = y.size() - 1;
        int deg = m - n + 1;

        u.resize(deg, 0);
        v = x;

        for (int i = m; i >= n; i--) {
            if (v[i] != 0) {
                int coef = v[i] / y[n];
                u[i - n] = coef;

                for (int j = 0; j <= n; j++) {
                    v[i - j] -= coef * y[n - j];
                }
            }
        }
        printpoly(u, deg - 1);
        printpoly(v, m - 1);
    }

    // Check root of the polynomial
    int check_root(vector<int> &x, int y) {
        int res = 0;
        int pow = 1;
        for (int coef : x) {
            res += coef * pow;
            pow *= y;
        }
        return res;
    }

    // Polynomial expansion
    vector<int> expand_root(int a, int n) {
        vector<int> poly = {-a, 1}; 
        vector<int> result = {1}; 

        for (int i = 0; i < n; i++) {
            result = prod_of_poly(result, poly); // Multiply result by (x - a)
        }
        return result;
    }

    void output_check_root(vector<int> &x, int y, int z) {
        int val = check_root(x, y);
        if (val == 0) {
            cout << y << " is a root of the polynomial." << endl;
            vector<int> root_exp;
            root_exp = expand_root(y, z);
            div_of_poly(x, root_exp);
        } else {
            cout << y << " is not a root of the polynomial" << endl;
        }
    }
};

int main() {
    int deg1;
    cout << "Enter the degree of the polynomial :" << endl;
    cin >> deg1;
    vector<int> vec;
    int no;
    cout << "Enter the coef of the polynomial from the constant to higher degree" << endl;
    for (int i = 0; i < deg1 + 1; i++) {
        cin >> no;
        vec.push_back(no);
    }
    int deg2;
    cout << "Enter the degree of the second polynomial :" << endl;
    cin >> deg2;
    vector<int> vec1;
    int ino;
    cout << "Enter the coef of second as per the order of first polynomial" << endl;
    for (int i = 0; i < deg2 + 1; i++) {
        cin >> ino;
        vec1.push_back(ino);
    }

    Polynomial poly(deg1, deg2, vec, vec1);

    poly.printpoly(vec, deg1);
    poly.printpoly(vec1, deg2);
    cout << "Sum of poly" << endl;
    poly.sum_of_poly(vec, vec1);
    cout << "Subs of poly" << endl;
    poly.diff_of_poly(vec, vec1);
    cout << "Prod of poly" << endl;
    vector<int> v = poly.prod_of_poly(vec, vec1);
    int l = v.size();
    poly.printpoly(v, l - 1);
    cout << "Div of poly" << endl;
    poly.div_of_poly(vec, vec1);
    cout << "Enter the expected root of the polynomial" << endl;
    int root;
    cin >> root;
    cout << "Enter m if the root is correct then operation is p(x)/(x - r)^m " << endl;
    int m;
    cin >> m;
    poly.output_check_root(vec, root, m);

    return 0;
}
