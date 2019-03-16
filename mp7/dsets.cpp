/* Your code here! */
<<<<<<< HEAD
=======
/* Your code here! */
>>>>>>> e45f4609d67f5e5a359b6af369fa94b7cea20e74
#include <vector>
#include <iostream>
#include "dsets.h"

using namespace std;

void DisjointSets::addelements(int num) {
    for(int i = 0; i < num; i++) {
        dsets.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    int root = _find(elem);
    compress(elem, root);
    return root;
}

int DisjointSets::_find(int elem) {
    if(dsets[elem] < 0) {
        return elem;
    } else {
        return _find(dsets[elem]);
    }
}

void DisjointSets::compress(int elem, int root) {
    if(dsets[elem] == root || elem == root) {
        return;
    } else {
<<<<<<< HEAD
        int next = dsets[elem]; 
=======
        int next = dsets[elem];
>>>>>>> e45f4609d67f5e5a359b6af369fa94b7cea20e74
        dsets[elem] = root;
        compress(next, root);
    }
}


void DisjointSets::setunion(int a, int b) {
    if(_find(a) == _find(b)) { return; }

    int newSize = -1 * _size(a) - _size(b);

    if(_size(a) > _size(b)) {
        dsets[_find(b)] = _find(a);
        dsets[_find(a)] = newSize;
    } else {
        dsets[_find(a)] = _find(b);
        dsets[_find(b)] = newSize;
<<<<<<< HEAD
    } 
=======
    }
>>>>>>> e45f4609d67f5e5a359b6af369fa94b7cea20e74
}

int DisjointSets::size(int elem) {
    return _size(elem);
}

int DisjointSets::_size(int elem) {
    if(dsets[elem] < 0) {
        return -1 * dsets[elem];
    } else {
        return _size(dsets[elem]);
    }
}
<<<<<<< HEAD

=======
>>>>>>> e45f4609d67f5e5a359b6af369fa94b7cea20e74
