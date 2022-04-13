#include <string>
#include <vector>

namespace zich{
class Matrix{
private:
    int rows;
    int colls;
    std::vector<double> vec;
    std::vector<std::vector<double>> matrix;
public:
    Matrix(std::vector<double> mat, int rows, int colls);
    int getRows() const;
    int getColls() const;
    friend std::ostream& operator<<(std::ostream& stream, const Matrix& mat);
    friend std::istream& operator>>(std::istream& stream, Matrix& mat);
    Matrix operator+(const Matrix& mat);
    Matrix operator-();
    Matrix operator+=(const Matrix& mat);
    Matrix operator-=(const Matrix& mat);
    Matrix operator*=(double number);
    Matrix operator*=(const Matrix& mat);
    Matrix operator++();
    Matrix operator--();
    Matrix operator+();
    Matrix operator*(const Matrix& mat);
    Matrix operator- (const Matrix& mat);
    Matrix operator++(int i);
    Matrix operator--(int i);
    friend Matrix operator*(int number, const Matrix& mat);
    friend Matrix operator*(const Matrix& mat, int number);
    friend bool operator==(const Matrix& mat1, const Matrix& mat2);
    bool operator!=(const Matrix& mat1);
    bool operator<=(const Matrix& mat1);
    bool operator>=(const Matrix& mat1);
    bool operator<(const Matrix& mat1);
    bool operator>(const Matrix& mat1);
};
}