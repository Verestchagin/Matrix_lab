#include <initializer_list>
#include <iostream>
#include <fstream>

using namespace std;

class Matrix {

public:

    typedef int type;
    Matrix()
    {
        ptr = nullptr;
        n = 0;
        m = 0;
    }
    Matrix(std::initializer_list<int> list)
    {
        ptr = new int*[3];
        for (int i = 0; i < 3; i++)
            ptr[i] = new int[3];
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                ptr[i][j] = 0;
            }
        }
    }    
    Matrix(const Matrix& mat)
    {
        ptr = new int *[mat.n];
        for (int i = 0; i < mat.n; ++i){
            ptr[i] = new int[mat.m];
            for (int j = 0; j < mat.m; ++j){
                ptr[i][j] = mat.ptr[i][j];
            }
        }
        n = mat.n;
        m = mat.m;
    }
    auto swap_(Matrix& mat) -> void
    {
        swap(ptr, mat.ptr);
        swap(n, mat.n);
        swap(m, mat.m);
    }
    auto operator=(const Matrix& q) -> Matrix
    {
        if (ptr != nullptr){
            for (int i = 0; i < n; i++) delete[] ptr[i];
                delete [] ptr;
            return *this;
        }
        n = q.n;
        m = q.m;
        ptr = new int*[n];
        for (int i = 0; i < n; i++)
            ptr[i] = new int[m];
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                ptr[i][j] = q.ptr[i][j];
            }
        }
        return *this;
    }
    auto empty() -> bool
    {
        if (ptr == nullptr)
            return true;
        else
            return false;
    }
    auto columns() -> size_t
    {
        return m;
    }
    auto rows() -> size_t
    {
        return n;
    }
    auto operator-(const Matrix& mat) -> Matrix
    {
        if (n == mat.n && m == mat.m){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    ptr[i][j] = ptr[i][j] - mat.ptr[i][j];
                }
            }
            return *this;
        }
    } 
    auto operator+(const Matrix& mat) -> Matrix
    {
        if (n == mat.n && m == mat.m){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    ptr[i][j] = ptr[i][j] + mat.ptr[i][j];
                }
            }
            return *this;
        }
    }
    auto operator[](size_t index) -> int*
    {
        return ptr[index];
    } 
    bool operator==(const Matrix& mat)
    {
        if (n == mat.n && m == mat.m){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    if (ptr[i][j] != mat.ptr[i][j])
                        return false;
                }
            }
            return true;
        }
        return false;
    }
    friend
    auto operator<<(ostream& os, Matrix& mat) -> ostream&
    {
        int x;
        os << mat.n << " " << mat.m << endl;
        for (int i = 0; i < mat.n; i++){
            for (int j = 0; j < mat.m; j++){
                x = ptr[i][j];
                os << x;
            }
            os << endl;
        }
        return os;
    }
    friend
    auto operator>>(istream& is, Matrix& mat) -> istream&
    {
        is >> mat.n >> mat.m;
        for (int i = 0; i < mat.n; i++){
            for (int j = 0; j < mat.m; j++){
                is >> ptr[i][j];
            }
        }
        return is;
    }
    ~Matrix()
    {
        for (int i = 0; i < n; i++) delete[] ptr[i];
            delete [] ptr;
    }
private:
    int** ptr;
    size_t n;
    size_t m;
};
