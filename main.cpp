#include <iostream>
#include <cmath>
using namespace std;

class Vector{
private:
    int dim;
    static int typeofArray;
    int *a;
public:
    Vector(int dimensiune=0 );
    int getDim();
    Vector(Vector& v2);
    ~Vector();
    friend std::istream& operator >> (std::istream& input, Vector& v);
    friend std::ostream& operator << (std::ostream& output, Vector& v);
    Vector& operator = (Vector& v2);
    int& operator[](int poz);
    friend class Matrice_Oarecare;
    friend class Matrice_Patratica;
    void static settypeofArray(int nr);
    int static gettypeofArray();
};

int Vector::typeofArray = -1;

Vector::Vector(int dimensiune){
    dim = dimensiune;
    a = new int[dim];
}

Vector::Vector(Vector& v2){
    dim = v2.dim;
    a = new int[dim];
    for(int i = 0; i < dim;i++){
        a[i]=v2.a[i];
    }
}

Vector::~Vector(){

    delete[]a;
    dim=0;
}

std::istream& operator >> (std::istream& input, Vector& v){

    delete[]v.a;
    if(Vector::gettypeofArray() == -1)
        input >> v.dim;
    else
        v.dim=Vector::gettypeofArray();
    v.a = new int[v.dim];
    for (int i = 0; i < v.dim; i++)
        input >> v.a[i];
    return input;
}

std::ostream& operator << (std::ostream& output, Vector& v){
    for (int i = 0; i < v.dim; i++)
        output <<v.a[i] <<" ";
    output << '\n';
    return output;
}

Vector& Vector::operator=(Vector &v2){
    if (this != &v2){
        delete[]a;
        dim=v2.dim;
        a= new int [dim];
        for (int i = 0; i < dim; i++)
            a[i]=v2.a[i];
    }
    return *this;
}

int Vector::getDim(){
    return dim;
}

int& Vector::operator[](int poz){
    if(poz < 0 || poz >= dim)
    throw "EXCEPTION: index out of boundaries";
    return a[poz];
}

void Vector::settypeofArray(int nr){
    typeofArray = nr;
}

int Vector::gettypeofArray(){
    return typeofArray;
}

class Matrice{
protected:
    Vector *v;
public:
    Matrice();
    Matrice(Matrice& m2);
    virtual ~Matrice() = 0;
    virtual int verificare_diagonala()=0;
    virtual void verificare_diag()=0;


};
Matrice::Matrice(){

}

Matrice::~Matrice(){

}
class Matrice_Oarecare: public Matrice{
private:
    int lin;
public:
    Matrice_Oarecare(int numar_linii=0);
    Matrice_Oarecare(Matrice_Oarecare& m2);
    ~Matrice_Oarecare();
    friend std::istream& operator>>(std::istream& input, Matrice_Oarecare& m );
    friend std::ostream& operator<<(std::ostream& output, Matrice_Oarecare& m );
    Vector& operator[](int poz);
    Matrice_Oarecare& operator=(Matrice_Oarecare& m2);
    int verificare_diagonala() override;
    void verificare_diag() override;
};

Matrice_Oarecare::Matrice_Oarecare(int numar_linii){
    v = new Vector[numar_linii];
    lin=numar_linii;
    Vector::settypeofArray(-1);
}

Matrice_Oarecare::Matrice_Oarecare(Matrice_Oarecare& m2){
    Vector::settypeofArray (-1);
    lin=m2.lin;
    v = new Vector[lin];
    for (int i = 0; i<lin; i++) {
        v[i] = m2.v[i];
    }
}

Matrice_Oarecare::~Matrice_Oarecare(){
    delete []v;
    lin = 0;
}
std::istream& operator>>(std::istream& input, Matrice_Oarecare& m ){
    Vector::settypeofArray(-1);
    delete [] m.v;
    input>>m.lin;
    m.v=new Vector[m.lin];
    for(int i = 0; i < m.lin;i++){
        input>>m.v[i];
    }
    return input;
}


std::ostream& operator<<(std::ostream& output, Matrice_Oarecare& m ){
    for(int i =0; i<m.lin;i++){
        output<<m[i];
    }
    return output;
}

Vector& Matrice_Oarecare:: operator[](int poz){
    return v[poz];
}

Matrice_Oarecare& Matrice_Oarecare::operator=(Matrice_Oarecare& m2){
    Vector::settypeofArray(-1);
    if(this!=&m2){
        delete [] v;
        lin=m2.lin;
        v = new Vector[lin];
        for(int i = 0; i < lin;i++){
            v[i]=m2.v[i];
        }

    }
    return *this;
}
int Matrice_Oarecare::verificare_diagonala(){
    int ok=0;
    for(int i = 0; i< lin; i++)
        for(int j = 0 ; j<i; j++)
        if ((i!=j)&&(v[i][j]!=0))
            ok++;
    return ok;

}

void Matrice_Oarecare::verificare_diag(){
    int diag;
    diag=verificare_diagonala();
    if (diag==0)
        cout<<"Matricea este m. diag";
    else
        cout<<"Matricea NU este m. diag";
}

class Matrice_Patratica: public Matrice{
private:
    int dim;
public:
    Matrice_Patratica(int numar_linii=0);
    Matrice_Patratica(Matrice_Patratica& m2);
    ~Matrice_Patratica();
    friend std::istream& operator>>(std::istream& input, Matrice_Patratica& m );
    friend std::ostream& operator<<(std::ostream& output, Matrice_Patratica& m );
    Vector& operator[](int poz);
    Matrice_Patratica& operator=(Matrice_Patratica& m2);
    int verificare_diagonala() override;
    void verificare_diag() override;
    friend int determinant(Matrice_Patratica& matrix, int n);

};

Matrice_Patratica::Matrice_Patratica(int numar_linii){
    v = new Vector[numar_linii];
    dim=numar_linii;
    Vector::settypeofArray (dim);
}

Matrice_Patratica::Matrice_Patratica(Matrice_Patratica& m2){
    Vector::settypeofArray (dim);
    dim=m2.dim;
    v = new Vector[dim];
    for (int i = 0; i<dim; i++) {
        v[i] = m2.v[i];
    }
}

Matrice_Patratica::~Matrice_Patratica(){
    delete []v;
    dim = 0;
}
std::istream& operator>>(std::istream& input, Matrice_Patratica& m ){
    delete [] m.v;
    input>>m.dim;
    Vector::settypeofArray(m.dim);
    m.v=new Vector[m.dim];
    for(int i = 0; i < m.dim;i++){
        input>>m.v[i];
    }
    return input;
}
std::ostream& operator<<(std::ostream& output, Matrice_Patratica& m ){
    for(int i =0; i<m.dim;i++){
        output<<m[i];
    }
    cout<<"Determinantul este ";
    cout<<determinant(m, m.dim);
    return output;
}

Vector& Matrice_Patratica:: operator[](int poz){
    return v[poz];
}

Matrice_Patratica& Matrice_Patratica::operator=(Matrice_Patratica& m2){
    Vector::settypeofArray(dim);
    if(this!=&m2){

        delete [] v;
        dim=m2.dim;
        v = new Vector[dim];
        for(int i = 0; i < dim;i++){

            v[i]=m2.v[i];
        }

    }
    return *this;
}

int Matrice_Patratica::verificare_diagonala(){
    int ok=0;
    for(int i = 0; i<v->dim; i++)
        for(int j = 0 ; j<i; j++)
        if ((i!=j)&&(v[i][j]!=0))
            ok++;
    return ok;

}

void Matrice_Patratica::verificare_diag(){
    int diag;
    diag=verificare_diagonala();
    if (diag==0)
        cout<<"Matricea este m. diag";
    else
        cout<<"Matricea NU este m. diag";
}

int determinant(Matrice_Patratica & matrix, int n)
{
    int det=0;
    Matrice_Patratica submatrix;
    submatrix.dim=n-1;
    if (n == 2)
      return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
   else {
      for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
               int subj = 0;
               for (int j = 0; j < n; j++) {
                  if (j == x)
                  continue;
                submatrix[subi][subj] = matrix[i][j];
                subj++;
               }
             subi++;
            }
            det = det + (pow(-1, x) * matrix[0][x] * determinant( submatrix, n - 1 ));
      }
   }
   return det;
}



int main()
{
Matrice_Oarecare m;
cin>>m;
cout<<m;

try{

        Vector a(-2);
    }
    catch(const char * err){

        cout<<err<<'\n';
    }
try{
    Vector v(3);
    v[100];
    }
    catch(const char * err){

        cout<<err<<'\n';
    }


    return 0;
}
