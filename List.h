//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_LIST_H
#define WET1_LIST_H

template<class T>
class List {
private:
    int key;
    T data;
    List<T>* previous;
    List<T>* next;
};


#endif //WET1_LIST_H
