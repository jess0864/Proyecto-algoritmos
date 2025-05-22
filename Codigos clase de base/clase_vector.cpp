//Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>
using namespace std;

class Vector{ //Crear una clase llamada Vector
    int* v;
    int capacity;
    int size;

public:
    Vector(){ //constructor por defecto
        capacity = 10;
        size = 0;
        v = new int[capacity];
    }
    
    Vector(int c){ //constructor con parámetro
        capacity = c;
        size = 0;
        v = new int[capacity];
    }
    
    ~Vector(){ //destructor
        delete[] v;
    }
    
    int getSize(){ //función que permite retornar el tamaño del vector y es entero
        return size;
    }
    
    int getCapacity(){ //función que permite retornar la capacidad del vector y es entero
        return capacity;
    }
    
    int get(int i){
        if(i>=0 && i<size){
            return v[i];
        }else{
            return -1;
        }
    }
    
    void corrimientoDer(int i){
        //Corre todos los elementos desde la posición insert
        //una posición a la derecha
        if(size == capacity){
            resize();
        }
        for(int j=size; j>i; j--){
            v[j] = v[j-1];
        }
        size++;
    }
    
    void insert(int d, int i){
        corrimientoDer(i);
        v[i] = d;
        
    }
    
    void corrimientoIzq(int i){
        //Corre todos los elementos desd ela izquerda hacia la posición i
        for(int j=i; j<size-1; j++){
            v[j] = v[j+1];
        }
        size--;
    }
    
    void removeI(int i){
        corrimientoIzq(i);
    }
    
    int find(int d){
        int i=0;
        while(i<size && v[i]!=d){
            i++;
        }
        if(i<size){
            return i;
        }
        return -1;
    }
    
    void resize(){
        capacity *= 2;
        int* nv = new int[capacity];
        for(int i=0; i<size; i++){
            nv[i] = v[i];
        }
        delete[] v;
        v = nv;
    }
    
    void add(int d){
        if(size == capacity){
            resize();
        }
        v[size++] = d;
    }
    
    void print(){
        for(int i = 0; i<size ;i++){
            cout<<v[i]<<"\t";
        }
        cout<<endl;
    }
};

int main()
{
    srand(time(0));
    Vector v(3);
    for(int i=0; i<3; i++){
        v.add(rand()%100);
    }
    v.print();
    v.insert(44,1);
    v.print();
    return 0;
}