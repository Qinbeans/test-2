#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

using std::iostream;
using std::ostream;

template <typename T>
class array{
   private:
      T* data;
      size_t size;
      void allocate(size_t inc);//<-allocate space add or insert
      void deallocate(size_t dec);//<-deallocate space pop or remove
   public:
      array();
      array(T arr[], size_t size);
      array(const array<T> &arr);
      T at(int index){return data[index];};
      size_t size(){return size;};
      friend T operator[](const array<T>& arr,int& index){return arr.data[index];};
      void insert(T,unsigned int);
};

#endif