#include "array.h"

template <typename T>
array<T>::array(){
   size = 0;
   data=nullptr;
}

template <typename T>
array<T>::array(T arr[], size_t size){
   //
}

template <typename T>
array<T>::array(const array<T> &arr){
   data=(T*)malloc(arr.size);
   for(int i = 0; i < arr.size; i++){
      data[i]=arr[i];
   }
}

template <typename T>
void array<T>::insert(T obj, unsigned int index){
   int diff = size - index;
   temp = (T*)malloc(diff);
   for(int i = 0; i < diff; i++){
      temp[i] = data[index+i];
   }
   allocate(1);
   data[index] = obj;
   for(int i = 1; i <= diff; i++){
      data[index+i] = temp[i-1];
   }
}

template <typename T>
void array<T>::allocate(size_t inc){
   size += inc;
   temp = (T*)malloc(size);
   for(int i = 0; i < size-inc; i++){
      temp[i] = data[i];
   }
   free(data);
   data = temp;
   temp = nullptr;
}