#include "Matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

const int MIN_NUMBER_ID = 48;
const int MAX_NUMBER_ID = 57;


namespace zich{

Matrix::Matrix(vector<double> mat, int rows, int colls){
    Matrix::rows = rows;
    Matrix::colls = colls;
    Matrix::vec = mat;
    if (this->rows*this->colls != this->vec.size())
    {
        throw invalid_argument("you can't build a matrix from this vector with these rows and colls");
    }

    if (this->colls < 1 || this->rows < 1)
    {
        throw invalid_argument("colls and rows must be positive and not 0");
    }
    

    unsigned int helper = 0;
    for (unsigned int i = 0; i < rows; i++){
        vector<double>temp;
        for (unsigned int j = 0; j < colls; j++)
        {  
            temp.push_back(mat[helper]);
            helper++;
        }
        Matrix::matrix.push_back(temp);
    }
}

int Matrix:: getRows() const{
    return this->rows;
}

int Matrix::getColls() const{
    return this->colls;
}

bool checkSameSize(const Matrix& mat1, const Matrix& mat2){
    bool ans = true;
    if (mat1.getRows() != mat2.getRows() || mat1.getColls() != mat2.getColls())
    {
        ans = false;
    }
    return ans;
}

bool isValidForMult(const Matrix& mat1, const Matrix& mat2){
    bool ans = true;
    if (mat1.getColls() != mat2.getRows())
    {
        ans = false;
    }
    return ans;
}


Matrix Matrix::operator+(const Matrix& mat){
    Matrix mat1(mat);
    if (!checkSameSize(*this, mat1))
    {
        throw invalid_argument("Matrices should be of the same size!");
    }
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->colls; j++)
        {
            mat1.matrix[i][j] = this->matrix[i][j] + mat.matrix[i][j];
        }
        
    }
    return mat1;
}


Matrix Matrix::operator-(){
    Matrix answer(*this);
    for (unsigned int i = 0; i < answer.rows; i++)
    {
        for (unsigned int j = 0; j < answer.colls; j++)
        {
            if (matrix[i][j] == 0){
                answer.matrix[i][j] = 0;
            } 
            else{
                answer.matrix[i][j] = -answer.matrix[i][j];
            }
        }
        
    }
    return answer;
}

Matrix Matrix::operator+=(const Matrix& mat){
    Matrix mat1(mat);
    if (!checkSameSize(*this, mat1)){
        throw invalid_argument("Matrices should be of the same size!");
    }
    for (unsigned int i = 0; i < this->rows; i++){
        for (unsigned int j = 0; j < this->colls; j++)
        {
            this->matrix[i][j] += mat.matrix[i][j];
        }
        
    }
    return *this;
}

Matrix Matrix::operator-=(const Matrix& mat){
    Matrix mat1(mat);
    if (!checkSameSize(*this, mat1)){
        throw invalid_argument("Matrices should be of the same size!");
    }

    for (unsigned int i = 0; i < this->rows; i++){
        for (unsigned int j = 0; j < this->colls; j++)
        {
            this->matrix[i][j] -= mat.matrix[i][j];
        }
        
    }
    
    return *this;
}

Matrix Matrix::operator*=(double number){
    for (unsigned int i = 0; i < this->rows; i++){
        for (unsigned int j = 0; j < this->colls; j++)
        {
            if (matrix[i][j] == 0)
            {
                continue;
            }
            
            this->matrix[i][j] *= number;
        }
    }  
    return *this;
}

Matrix Matrix::operator++(){
    for (unsigned int i = 0; i < this->rows; i++){
        for (unsigned int j = 0; j < this->colls; j++)
        {
            this->matrix[i][j]++;
        }
    }
    return *this;
}

Matrix Matrix::operator--(){
    for (unsigned int i = 0; i < this->rows; i++){
        for (unsigned int j = 0; j < this->colls; j++)
        {
            this->matrix[i][j]--;
        }
    }
    return *this;
}
Matrix Matrix::operator*(const Matrix& mat){
    if (!isValidForMult(*this, mat))
    {
        throw invalid_argument("The number of columns in the first matrix should be equal to the number of rows in the second!");
    }
    vector<double>helper((unsigned int)mat.colls*(unsigned int)this->rows);
    Matrix answer(helper, this->rows, mat.colls);
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < mat.colls; j++)
        {
            answer.matrix[i][j] = 0;
            for (unsigned int y = 0; y < mat.rows; y++)
            {
                answer.matrix[i][j] += matrix[i][y] * mat.matrix[y][j];
            }
        }
        
    }
    
    return answer;
}

Matrix Matrix::operator*=(const Matrix& mat){
    if (!isValidForMult(*this, mat))
    {
        throw invalid_argument("The number of columns in the first matrix should be equal to the number of rows in the second!");
    }
    vector<double>helper((unsigned int)mat.colls*(unsigned int)this->rows);
    Matrix answer(helper, this->rows, mat.colls);
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < mat.colls; j++)
        {
            answer.matrix[i][j] = 0;
            for (unsigned int y = 0; y < mat.rows; y++)
            {
                answer.matrix[i][j] += matrix[i][y] * mat.matrix[y][j];
            }
        }
        
    }
    *this = answer;
    
    return *this;
}

Matrix Matrix::operator-(const Matrix& mat){
    Matrix mat1(mat);
    if (!checkSameSize(*this, mat1))
    {
        throw invalid_argument("Matrices should be of the same size!");
    }
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->colls; j++)
        {
            if (this->matrix[i][j] - mat.matrix[i][j] == 0)
            {
                mat1.matrix[i][j] = 0;
            }
            else{
            mat1.matrix[i][j] = this->matrix[i][j] - mat.matrix[i][j];
            }
        }
        
    }
    return mat1;
}

Matrix Matrix::operator+(){
    Matrix answer(*this);
    return answer;
}

bool operator==(const Matrix& mat1, const Matrix& mat2){
    if (!checkSameSize(mat1, mat2))
    {
        throw invalid_argument("Matrices should be of the same size!");
    }
    
    for (unsigned int i = 0; i < mat1.rows; i++)
    {
        for (unsigned int j = 0; j < mat1.colls; j++)
        {
            if (mat1.matrix[i][j] != mat2.matrix[i][j])
            {
                return false;
            }
            
        }
        
    }
    return true;
}

bool Matrix::operator!=(const Matrix& mat1){
    Matrix mat(mat1);
    if (!checkSameSize(*this, mat))
    {
        throw invalid_argument("Matrices should be of the same size!");
    }
    
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->colls; j++)
        {
            if (this->matrix[i][j] != mat.matrix[i][j])
            {
                return true;
            }
            
        }
        
    }
    return false;
}

bool Matrix::operator<=(const Matrix& mat1){
    Matrix mat(mat1);
    double ans1 = 0;
    double ans2 = 0;
    if (!checkSameSize(*this, mat))
    {
        throw invalid_argument("Matrices should be of the same size!");
    }
    
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->colls; j++)
        {
            ans1 += this->matrix[i][j];
            ans2 += mat.matrix[i][j];
        }
        
    }
    return ans1 <= ans2;
}

bool Matrix::operator>=(const Matrix& mat1){
    Matrix mat(mat1);
    double ans1 = 0;
    double ans2 = 0;
    if (!checkSameSize(*this, mat))
    {
        throw invalid_argument("Matrices should be of the same size!");
    }
    
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->colls; j++)
        {
            ans1 += this->matrix[i][j];
            ans2 += mat.matrix[i][j];
        }
        
    }
    return ans1 >= ans2;
}

bool Matrix::operator<(const Matrix& mat1){
    Matrix mat(mat1);
    double ans1 = 0;
    double ans2 = 0;
    if (!checkSameSize(*this, mat))
    {
        throw invalid_argument("Matrices should be of the same size!");
    }
    
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->colls; j++)
        {
            ans1 += this->matrix[i][j];
            ans2 += mat.matrix[i][j];
        }
        
    }
    return ans1 < ans2;
}

bool Matrix::operator>(const Matrix& mat1){
    Matrix mat(mat1);
    double ans1 = 0;
    double ans2 = 0;
    if (!checkSameSize(*this, mat))
    {
        throw invalid_argument("Matrices should be of the same size!");
    }
    
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->colls; j++)
        {
            ans1 += this->matrix[i][j];
            ans2 += mat.matrix[i][j];
        }
        
    }
    return ans1 > ans2;
}

Matrix Matrix::operator++ (int i){
    Matrix mat1(*this);
       for(unsigned int i = 0; i < this->rows; i++)
       {
        for(unsigned int j = 0; j < this->colls; j++)
        {
            this->matrix[i][j]++;
        }
    }
    return mat1;
}

Matrix Matrix::operator--(int i){
   Matrix mat1(*this);
       for(unsigned int i = 0; i < this->rows; i++)
       {
        for(unsigned int j = 0; j < this->colls; j++)
        {
            this->matrix[i][j]--;
        }
    }
    return mat1;
}

ostream& operator<<(ostream& stream, const Matrix& mat){
    for (unsigned int i = 0; i < mat.rows; i++){
        stream << '[' << mat.matrix[i][0];
        for (unsigned int j = 1; j < mat.colls; j++)
        {
          stream << ' ' << mat.matrix[i][j];
        }
          stream << ']';
          if (i < mat.rows-1)
          {
            stream << endl;
          }

    }
    return stream;
}
istream& operator>>(istream& stream, Matrix& mat){
    string word;
    int colls = 1;
    int rows = 1;
    unsigned int current = 0;
    unsigned int checker = 0;
    vector<double> vec;

    getline(stream, word);
    if (word.at(0) != '[' || word.at(1) < MIN_NUMBER_ID || word.at(1) > MAX_NUMBER_ID)
    {
        throw invalid_argument("there must be '[' and then a number");
    }

    vec.push_back(word.at(1) - '0');

    for (unsigned int i = 2; word.at(i) != ']'; i++)
    {
        if (word.at(i) == ' ' || (word.at(i) > MIN_NUMBER_ID && word.at(i) < MAX_NUMBER_ID))
        {
            if (word.at(i) == ' ')
            {
                colls++;
            } 
            else {
                current = i;
                vec.push_back(word.at(i) - '0');
                continue;
            }
            
        } else {
            throw invalid_argument("only spaces and numbers are allowed inside a vector");
        }

        current = i;
    }
    
    current += 2;

    if (word.at(current) != ',' || word.at(current+1) != ' ')
    {
        throw invalid_argument("vectors must be separated with ','");
    }
    
    current += 2;

    for (unsigned int i = current; i < word.length(); i++)
    {
        if (word.at(i-1) == ']')
        {
            if (word.at(i) != ',')
            {
                throw invalid_argument("vectors must be separated with ','");
            }

            continue;
               
        }
        
        if (word.at(i-1) == ',')
        {
            if (word.at(i) != ' ')
            {
                throw invalid_argument("after ',' there must be ' '");
            }

            continue;
        }
        
            if (word.at(i) == ' ' || (word.at(i) >= MIN_NUMBER_ID && word.at(i) <= MAX_NUMBER_ID) || word.at(i) == '[' || word.at(i) == ']')
        {
            if (word.at(i) >= MIN_NUMBER_ID && word.at(i) <= MAX_NUMBER_ID)
            {
                checker++;
                vec.push_back(word.at(i) - '0');
            } 

            else if (word.at(i) == ']')
            {
                rows++;
                if (checker != colls)
                {
                    throw invalid_argument("vectors are not the same size");
                }
                checker = 0;  
            }
            
            else {
                continue;
            }
            
        } else {
            throw invalid_argument("only spaces and numbers are allowed inside a vector");
        }

        
    }
    Matrix s(vec, rows, colls);

    mat = s;
    
    return stream;
}

Matrix operator*(int number, const Matrix& mat){
    Matrix answer(mat);
    for (unsigned int i = 0; i < answer.rows; i++){
        for (unsigned int j = 0; j < answer.colls; j++)
        {
            if (answer.matrix[i][j] == 0)
            {
                continue;
            }
            
            answer.matrix[i][j] *= number;
        }
    }  
    return answer;
}

Matrix operator*(const Matrix& mat, int number){
    Matrix answer(mat);
    for (unsigned int i = 0; i < answer.rows; i++){
        for (unsigned int j = 0; j < answer.colls; j++)
        {
            if (answer.matrix[i][j] == 0)
            {
                continue;
            }
            
            answer.matrix[i][j] *= number;
        }
    }  
    return answer;
}

}