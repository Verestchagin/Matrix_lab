#include <initializer_list>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

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
