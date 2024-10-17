#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <ostream>

using std::cout, std::endl;

template <typename t>
t zero(){
    return 0;
}

int twos(){
    return 2;
}

template <typename t>
class SquareMatrix{
    private:
        int* arr;//t* arr;
    public:
        int size;
        SquareMatrix(int size = 256, t (*funcptr)() = zero){
            this->size = size;
            arr = new t[size*size];
            //fill array with output of function
            for(int i=0; i<size; i++){
                for(int j=0; j<size; j++){
                    arr[size*i+j] = funcptr();
                    //cout << arr[size*i+j] << endl;
                }
            }
        }
        t& operator[](int pos){
            return arr[pos];
        }
        //multiplication operation
        friend SquareMatrix& operator*(SquareMatrix& lhs,SquareMatrix& rhs){
            if(lhs.size!=rhs.size){
                throw std::invalid_argument("Stupid didn't put in two matrixes of the same size");
            }
            SquareMatrix* output = new SquareMatrix(lhs.size);//maybe unsafe
            //SquareMatrix output(lhs.size);
            for(int i=0; i<lhs.size; i++){
                for(int j=0; j<lhs.size; j++){
                    (*output)[i*lhs.size+j] = lhs[i*lhs.size+j]*rhs[j*lhs.size+i];
                }
            }
            return *output;
        }
        //multiply by eachother
        SquareMatrix& operator*=(SquareMatrix& rhs){
            return (*this)*rhs;
        }
        friend std::ostream& operator<<(std::ostream& os, SquareMatrix& x){
            for(int i=0; i<x.size; i++){
                os<<"[ ";
                for(int j=0; j<x.size; j++){
                    os << x[x.size*i+j] << " ";
                }
                os<<"]\n";
            }
            return os;
        }


};

void test(std::string x){
    cout << x << endl;
}

int main(void){
    srand(time(NULL));
    SquareMatrix<int> one(5, rand);
    SquareMatrix<int> two(5, rand);
    cout << one << endl;
    cout << two << endl;
    clock_t t = clock();
    one= one * two;
    t = clock() - t;
    cout << one;
    cout << t << endl;
    return 0;
}
