//  Casey Hittinger
//  DSVector.hpp
//  String1
//  Custom Vector class

#ifndef DSVector_hpp
#define DSVector_hpp

#include <stdio.h>
#include <iostream>



template<class T>
class Vector{
    
public:
    
    Vector();           //initializing
    Vector(int);        //initializes the vector of so many spaces long
    Vector(const Vector<T>&);
    ~Vector();          //destructor
    
    void add(T);       //adds a value to the end
    void add(T, int);  //adds a value at a specific location in the vector
    T get(int);         //returns value at int value
    
    
    void sort(int);  //orders from desired location
    int size();         //return size of vector
    
    T& operator[](int);     //gets the value at a specific location in the vector
    
    
    Vector<T>& operator=(const Vector<T>&);       //copying
    Vector<T>& operator+=(const Vector<T>&);               //adding vector together
    bool operator==(const Vector<T>&);            //comparing
    
    
    friend std::ostream& operator<< (std::ostream&, const Vector<T>&);         //allows output
    
    
    
    void release(int);      //releases a specific value at a certain location and returns it
    
    
    void clear();       //clears the vector
    
private:
    
    void resize(int);      //changes the capacity of the vector when needed
    int vSize;
    int capacity;
    T* elements;
    
};







template<class T>
Vector<T>::Vector()
{
    capacity = 3000;
    elements = new T[capacity];
    vSize = 0;
    
}

template<class T>
Vector<T>::~Vector()
{
    delete[] elements;
    vSize = 0;
    capacity = 3000;
}

template<class T>
Vector<T>::Vector(int number)
{
    vSize = number;
    elements = new T[vSize];
    
    
    
}

template<class T>
Vector<T>::Vector(const Vector<T>& rhs)
{
    
    
    
    elements = new T[rhs.vSize];
    
    
    for(int i = 0; i < rhs.vSize;i++)
    {
        elements[i] = rhs.elements[i];
    }
    capacity = rhs.capacity;
    vSize = rhs.vSize;
}

template<class T>
void Vector<T>::resize(int num)
{
    T* pointer = new T[num + 100];
    capacity += 100;
    for(int i = 0; i < capacity; i++)
    {
        pointer[i] = elements[i];
    }
    delete[] pointer;
    elements = pointer;
    
}

template<class T>
void Vector<T>::clear()
{
    delete[] elements;
    capacity = 3000;
    vSize= 0;
    elements = new T[capacity];
    
}

template<class T>
int Vector<T>::size()
{
    return vSize;
}

template<class T>
T& Vector<T>::operator[](int location)
{
    return elements[location];
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
    while (rhs.vSize > capacity)
    {
        resize(capacity);
        
    }
    delete[] elements;
    elements = new T[rhs.vSize];
    vSize = rhs.vSize;
    capacity = rhs.capacity;
    for(int i = 0; i < rhs.vSize; i++)
    {
        elements[i] = rhs.elements[i];
    }
    return *this;
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& rhs)
{
    if (this->size() != rhs.vSize)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < this->size(); i++)
        {
            if (elements[i] != rhs.elements[i])
            {
                return false;
            }
        }
    }
    return true;
}

template<class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& rhs)
{
    T* adding = new T[vSize + rhs.vSize];
    for (int i = 0; i < vSize; i++)
    {
        adding[i] = elements[i];
    }
    int j = 0;
    for (int i = vSize, j; i < vSize + rhs.vSize; i++, j++)
    {
        adding[i] = rhs.elements[j];
    }
    
    delete[] elements;
    
    this->elements = adding;
    this->vSize += rhs.vSize;
    return *this;
    
}

template<class T>
void Vector<T>::add(T newinput)
{
    if(vSize +1 > capacity)
    {
        resize(capacity);
    }
    T* pointer = new T[capacity];
    for (int i = 0; i < vSize; i++)
    {
        pointer[i] = elements[i];
    }
    pointer[vSize] = newinput;
    
    
    delete[] elements;
    this->elements = pointer;
    this->vSize +=1;
    
    
    
}

template<class T>
void Vector<T>::add(T newinput, int location)
{
    if(vSize +1 > capacity)
    {
        resize(elements, capacity);
    }
    T* pointer = new T[capacity];
    for (int i = 0; i < location; i++)
    {
        pointer[i] = elements[i];
    }
    pointer[location] = newinput;
    
    for(int j= location +1; j < vSize; j++)
    {
        pointer[j] = elements[j-1];
    }
    delete[] elements;
    this->elements = pointer;
    this->vSize +=1;
    
    
    
}

template<class T>
void Vector<T>::release(int location)
{
    T* pointer = new T[capacity];
    for (int i = 0; i < location; i++)
    {
        pointer[i] = elements[i];
    }
    
    
    for(int j= location; j < vSize; j++)
    {
        pointer[j] = elements[j+1];
    }
    delete[] elements;
    elements = pointer;
    vSize -= 1;
    
    
}

template<class T>
T Vector<T>::get(int location)
{
    return elements[location];
}

template<class T>
void Vector<T>::sort(int begin)
{
    T* pointer = new T[capacity];
    int j = 0;
    for(int i = begin, j; i < vSize; i++, j++)
    {
        pointer[j] = elements[i];
    }
    int sub = vSize - begin;
    int k = vSize - sub;
    for (int i = 0, k; i < begin; i++, k++)
    {
        pointer[k]= elements[i];
    }
}

template<class T>
std::ostream& operator<<(std::ostream& output, const Vector<T>& rhs)
{
    for(int i = 0; i <(rhs.vSize); i++)
    {
        output << rhs.get(i) << " ";
    }
    return output;
    
}



#endif /* DSVector_hpp */
