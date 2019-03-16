<<<<<<< HEAD
=======
/* Your code here! */
>>>>>>> e45f4609d67f5e5a359b6af369fa94b7cea20e74
#ifndef _DSETS_H_
#define _DSETS_H_

#include <vector>

using std::vector;

<<<<<<< HEAD
class DisjointSets 
{
    public: 
=======
class DisjointSets
{
    public:
>>>>>>> e45f4609d67f5e5a359b6af369fa94b7cea20e74
        /**
          * Creates num unconnected root nodes at the end of the vector.
          * @param num is the number of nodes to add.
          */
        void addelements(int num);

        /**
          * This function should compress paths and works as described in lecture.
<<<<<<< HEAD
          * @param elem the element you are trying to find. 
          * @return the index of the root of the up-tree in which the parameter element resides.
          */ 
        int find(int elem);

        /**
          * This function should be implemented as union-by-size. 
          * That is, when you setunion two disjoint sets, 
          * the smaller (in terms of number of nodes) should point at the larger. 
          * This function works as described in lecture, 
          * except that you should not assume that the arguments 
          * to setunion are roots of existing uptrees.
          * 
          * Your setunion function SHOULD find the roots of its arguments before combining the trees. 
          * If the two sets are the same size, 
          * make the tree containing the second argument point to the tree containing the first. 
          * (Note that normally we could break this tie arbitrarily, 
          * but in this case we want to control things for grading.)
          * @param a Index of the first element to union
          * @param b Index of the second element to union
          */  
=======
          * @param elem the element you are trying to find.
          * @return the index of the root of the up-tree in which the parameter element resides.
          */
        int find(int elem);

        /**
          * This function should be implemented as union-by-size.
          * That is, when you setunion two disjoint sets,
          * the smaller (in terms of number of nodes) should point at the larger.
          * This function works as described in lecture,
          * except that you should not assume that the arguments
          * to setunion are roots of existing uptrees.
          *
          * Your setunion function SHOULD find the roots of its arguments before combining the trees.
          * If the two sets are the same size,
          * make the tree containing the second argument point to the tree containing the first.
          * (Note that normally we could break this tie arbitrarily,
          * but in this case we want to control things for grading.)
          * @param a Index of the first element to union
          * @param b Index of the second element to union
          */
>>>>>>> e45f4609d67f5e5a359b6af369fa94b7cea20e74
        void setunion(int a, int b);

        /**
          * This function should return the size of the uptree containing the element.
<<<<<<< HEAD
          * @param the element you are looking for. 
          * @return the size of the uptree containing the element.  
          */
        int size(int elem);
    
    private:

        vector<int> dsets; 
=======
          * @param the element you are looking for.
          * @return the size of the uptree containing the element.
          */
        int size(int elem);

    private:

        vector<int> dsets;
>>>>>>> e45f4609d67f5e5a359b6af369fa94b7cea20e74
        /**
         * Helper function for find.
         * @param elem the element searched for
         * @return the root index
<<<<<<< HEAD
         */  
=======
         */
>>>>>>> e45f4609d67f5e5a359b6af369fa94b7cea20e74
        int _find(int elem);

        /**
         * Compress path helper function.
         * @param elem the element to start compression from
         * @param root the value that is being reassigned
<<<<<<< HEAD
         */ 
=======
         */
>>>>>>> e45f4609d67f5e5a359b6af369fa94b7cea20e74
        void compress(int elem, int root);

        /**
         * Helper function for size.
         * @param elem the element to start from.
         * @return the size
<<<<<<< HEAD
         */ 
        int _size(int elem);
};

#endif
=======
         */
        int _size(int elem);
};

#endif
>>>>>>> e45f4609d67f5e5a359b6af369fa94b7cea20e74
