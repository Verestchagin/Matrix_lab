#include <initializer_list>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;#include <initializer_list>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

template <typename type, size_t n, size_t m>
class Matrix {
public:
    Matrix();
    Matrix(initializer_list<type> list);
    Matrix(const Matrix&);
    auto swap_(Matrix&) -> void;
    auto operator=(const Matrix& q) -> Matrix&;
    auto empty() -> bool;
    auto columns() -> size_t;
    auto rows() -> size_t;
    auto operator-(const Matrix&) -> Matrix;
    auto operator+(const Matrix&) -> Matrix;
    auto operator[](size_t index) -> type*;
    bool operator==(const Matrix&);
    template <typename T2, size_t n2, size_t m2>
    friend ostream& operator<<(ostream&, const Matrix<T2, n2, m2>&);
    template <typename T3, size_t n3, size_t m3>
    friend istream& operator>>(istream&, Matrix<T3, n3, m3>&);
    ~Matrix();
private:
    type** ptr;
};

template <typename type, size_t n, size_t m>
Matrix<type, n, m>::Matrix() : ptr(nullptr) {
}

template <typename type, size_t n, size_t m>
Matrix<type, n, m>::Matrix(initializer_list<type> list) {
    ptr = new type*[n];
    auto p = list.begin();
    for (int i = 0; i < n; i++)
        ptr[i] = new type[m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++, p++)
            ptr[i][j] = *p;
    }
}

template <typename type, size_t n, size_t m>
Matrix<type, n, m>::Matrix(const Matrix& mat) {
    ptr = new type *[n];
    for (int i = 0; i < n; i++){
        ptr[i] = new type[m];
        for (int j = 0; j < m; j++)
            ptr[i][j] = mat.ptr[i][j];
    }
}

template <typename type, size_t n, size_t m>
auto Matrix<type, n, m>::empty() -> bool {
    if (ptr == nullptr)
        return true;
    else
        return false;
}

template <typename type, size_t n, size_t m>
auto Matrix<type, n, m>::columns() -> size_t {
    return m;
}

template <typename type, size_t n, size_t m>
auto Matrix<type, n, m>::rows() -> size_t {
    return n;
}

template <typename type, size_t n, size_t m>
auto Matrix<type, n, m>::operator[](size_t index) -> type* {
    return ptr[index];
}

template <typename type, size_t n, size_t m>
auto Matrix<type, n, m>::operator-(const Matrix& mat) -> Matrix {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            ptr[i][j] = ptr[i][j] - mat.ptr[i][j];
    }
    return *this;
}

template <typename type, size_t n, size_t m>
auto Matrix<type, n, m>::operator+(const Matrix& mat) -> Matrix {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            ptr[i][j] = ptr[i][j] + mat.ptr[i][j];
    }
    return *this;
}

template <typename type, size_t n, size_t m>
bool Matrix<type, n, m>::operator==(const Matrix& mat) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (ptr[i][j] != mat.ptr[i][j])
                return false;
        }
    }
    return true;
}

template <typename type, size_t n, size_t m>
ostream& operator<<(ostream& os, const Matrix<type, n, m>& mat) {
    os << n << " " << m << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            os << mat.ptr[i][j]<<"  ";
        os << endl;
    }
    return os;
}

template <typename type, size_t n, size_t m>
istream& operator>>(istream& is, Matrix<type, n, m>& mat) {
    if(is) {
        mat.ptr = new type*[n];
        for(int i = 0; i < n; i++)
            mat.ptr[i] = new type[m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                is >> mat.ptr[i][j];
        }
    }
    return is;
}

template <typename type, size_t n, size_t m>
auto Matrix<type, n, m>::swap_(Matrix& mat) -> void {
    swap(ptr, mat.ptr);
}

template <typename type, size_t n, size_t m>
auto Matrix<type, n, m>::operator=(const Matrix& mat) -> Matrix& {
    if (ptr != nullptr) {
        for (int i = 0; i < n; i++)
            delete[] ptr[i];
        delete [] ptr;
        return *this;
    }
    ptr = new type*[n];
    for (int i = 0; i < n; i++)
        ptr[i] = new type[m];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            ptr[i][j] = mat.ptr[i][j];
    }
    return *this;
}

template <typename type, size_t n, size_t m>
Matrix<type, n, m>::~Matrix() {
    for (int i = 0; i < n; i++)
        delete[] ptr[i];
    delete [] ptr;
}

class Matrix_t{
private:
    int** ptr;
    size_t n;
    size_t m;

public:
    Matrix_t()
    {
        ptr = nullptr;
        n = 0;
        m = 0;
    }
    Matrix_t(std::initializer_list<int> list)
    {
        n=3;
        m=3;

        ptr = new int*[3];
        for (int i = 0; i < 3; i++)
            ptr[i] = new int[3];
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                ptr[i][j] = 0+rand()%10;
            }
        }
    }

    Matrix_t(const Matrix_t& mat)
    {
        n = mat.n;
        m = mat.m;
        ptr = new int *[mat.n];
        for (int i = 0; i < mat.n; i++){
            ptr[i] = new int[mat.m];
        }

        for(int i=0; i < mat.n; i++){
            for (int j = 0; j < mat.m; j++){
                ptr[i][j] = mat.ptr[i][j];
            }
        }
    }


    auto swap_(Matrix_t& mat) -> void
    {
        swap(ptr, mat.ptr);
        swap(n, mat.n);
        swap(m, mat.m);
    }
    auto operator=(const Matrix_t& q) -> Matrix_t
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

    auto operator-(const Matrix_t& mat) -> Matrix_t&
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

    auto operator+(const Matrix_t& mat) -> Matrix_t&
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
    bool operator==(const Matrix_t& mat)
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
    auto operator<<(ostream& os, Matrix_t& mat) -> ostream&
    {
        os << mat.n << " " << mat.m << endl;
        for (int i = 0; i < mat.n; i++){
            for (int j = 0; j < mat.m; j++){
                os << mat.ptr[i][j]<<"  ";
            }
            os << endl;
        }
        return os;
    }
    friend
    auto operator>>(istream& is, Matrix_t& mat) -> istream&
    {
      if(is){

        is >> mat.n >> mat.m;
        mat.ptr=new int*[mat.n];
        for(int i=0; i < mat.n; i++)
            mat.ptr[i]=new int[mat.m];
        for (int i = 0; i < mat.n; i++){
            for (int j = 0; j < mat.m; j++){
                is >> mat.ptr[i][j];
            }
        }
        return is;
      }

    }
    ~Matrix_t()
    {
        for (int i = 0; i < n; i++) delete[] ptr[i];
            delete [] ptr;
    }
};
