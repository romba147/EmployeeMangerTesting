//
// Created by Eyal on 22/04/2022.
//
#ifndef HW1_WET_AVLTREE_H
#define HW1_WET_AVLTREE_H
#include <cmath>
#include <exception>



/** need to complete:
 * inorder - V
 * reverse inorder - V
 * smart inorder (by min to max values) -
 * Build empty tree with n nodes -
 * add exceptions for new - bad alloc
 * add status for functions
 */

/*int max (int x , int y) {
    if (x>y) {
        return x;
    }
    return y;
}*/



template <class T>
struct node {
    node *left;
    node *right;
    T *data;
    int height;

    explicit node(T* data) : data (data)
    {
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

template <class T>
class AVLtree {
public:
    node<T> * root;
    int size;

    AVLtree() {
        this->root = nullptr;
        size=0;
    }
    ~AVLtree(){
        this->deleteAllNodes(root);
    }
    int calHeight (node<T>* p) const{
        if (!(p->left) && !(p->right)){
            return 0;
        }
        else if (!(p->left))
        {
            return p->right->height + 1;
        }
        else if (!(p->right))
        {
            return p->left->height + 1;
        }
        if (p->left->height > p->right->height)
        {
            return p->left->height +1;
        }
        return p->right->height +1;
    }

    void updateHeight (node<T>* top)
    {
        top->right->height = calHeight(top->right);
        top->left->height = calHeight(top->left);
        top->height= calHeight(top);
    }

    int calBF (node<T>* p) const{
        if (p->right && p->left){
            return p->left->height - p->right->height;
        }
        else if (p->left && !(p->right)){
            return (p->left->height)+1;
        }
        else if (!(p->left) && p->right){
            return -1-(p->right->height);
        }
        return 0;
    }

    node<T>* ll_rotation (node<T>* p){
        node<T>* top =p->left;
        p->left= top->right;
        top->right= p;
        if(p==root)
        {
            root=top;
        }
        updateHeight(top);

        return top;
    }

    node<T>* rr_rotation (node<T>* p){
        node<T>* top = p->right;
        p->right = top->left;
        top->left = p;
        if(p==root)
        {
            root=top;
        }
        updateHeight (top);

        return top;
    }

    node<T>* rl_rotation (node<T>* p){
        node<T>* top1 = p->right;
        node<T>* top2 = p->right->left;
        p->right = top2->left;
        top1->left = top2->right;
        top2->left = p;
        top2->right = top1;
        if(p==root)
        {
            root=top2;
        }
        updateHeight(top2);

        return top2;
    }

    node<T>* lr_rotation (node<T>* p){
        node<T>* top1 = p->left;
        node<T>* top2 = p->left->right;
        p->left = top2->right;
        top1->right = top2->left;
        top2->right = p;
        top2->left = top1;
        if(p==root)
        {
            root=top2;
        }
        updateHeight(top2);
        return top2;
    }

    node<T>* insert (T* data)
    {
        return insertAux(root,data);
    }

    node<T>* insertAux (node<T>* r,T* data)
    {
        if (!r){
            auto* newNode = new node<T>(data);
            if (!newNode)
            {
                return nullptr;
            }
            if (root == nullptr)
            {
                root = newNode;
            }
            r = newNode;
            size++;
            return r;
        }
        else{
            if (*(data) < *(r->data))
                r->left = insertAux(r->left,data);
            else
                r->right = insertAux(r->right,data);
        }

        r->height = calHeight(r);

        if (calBF(r)==2 && calBF(r->left)==1){
            r = ll_rotation(r);
        }
        else if (calBF(r)==-2 && calBF(r->right)==-1){
            r = rr_rotation(r);
        }
        else if (calBF(r)==-2 && calBF(r->right)==1){
            r = rl_rotation(r);
        }
        else if (calBF(r)==2 && calBF(r->left)==-1){
            r = lr_rotation(r);
        }

        return r;
    }

    node<T>* smallest (node<T>* r) {
        if (r == nullptr)
        {
            return nullptr;
        }
        while (r->left){
            r = r->left;
        }
        return r;
    }
    node<T>* biggest (node<T>* r) {
        if (r == nullptr)
        {
            return nullptr;
        }
        while (r->right){
            r = r->right;
        }
        return r;
    }

    node<T>* deleteNode (node<T>* r , T* data) {
        ///added this condition. if there are problems with delete - check here
        if (r == nullptr)
        {
            return nullptr;
        }
        if (!(r->left) && !(r->right)){
            if (r == this->root){
                this->root = nullptr;
            }
            delete r;
            size--;
            return nullptr;
        }

        node<T>* s;
        node<T>* b;

        if (*(r->data) < *(data)){
            r->right = deleteNode(r->right,data);
        }
        else if (*(r->data) > *(data)){
            r->left = deleteNode(r->left,data);
        }
        else
        {
            if (r->left)
            {
                s = biggest(r->left);
                r->data = s->data;
                r->left = deleteNode(r->left,s->data);
            }
            else
            {
                b = smallest(r->right);
                r->data = b->data;
                r->right = deleteNode(r->right,b->data);
            }
        }
        r->height = calHeight(r);

        if (calBF(r)==2 && calBF(r->left)==1){
            r = ll_rotation(r);
        }
        else if (calBF(r)==-2 && calBF(r->right)==-1){
            r = rr_rotation(r);
        }
        else if (calBF(r)==-2 && calBF(r->right)==1){
            r = rl_rotation(r);
        }
        else if (calBF(r)==2 && calBF(r->left)==-1){
            r = lr_rotation(r);
        }
        else if (calBF(r)==2 && calBF(r->left)==0){
            r = ll_rotation(r);
        }
        else if (calBF(r)==-2 && calBF(r->right)==0){
            r = ll_rotation(r);
        }

        return r;
    }

    node<T>* findNode (node<T>* r , T* data) const
    {
        if (r == nullptr)
        {
            return nullptr;
        }

        if (*(data) == *(r->data))
        {
            return r;
        }

        else if (*(data) < *(r->data))
        {
            return findNode(r->left,data);
        }
        else if ((*(data) > *(r->data)))
        {
            return  findNode(r->right,data);
        }
        return nullptr;
    }

    //inorder - calling the function creates an array using malloc
    //if no need to limit array size - insert tree size as max
    T** inorderArray (int max ) const
    {
        int counter=0;
        T** arr = (T**)malloc(max*sizeof(T*));
        inorderArrayAux(root, arr, &counter, max);
        return arr;
    }

    void inorderArrayAux (node<T>* r, T* arr[], int* counter , int max) const
    {
        if (!r)
        {
            return;
        }
        inorderArrayAux (r->left, arr , counter,max);
        if (*counter < max) {
            arr[*counter] = r->data;
            *counter = *counter + 1;
            inorderArrayAux(r->right, arr, counter, max);
        }
    }

    T** reverseInorderArray (int max) const
    {
        int counter=0;
        T** arr = (T**)malloc(max*sizeof(T*));
        reverseInorderArrayAux(root, arr, &counter, max);
        return arr;
    }

    void reverseInorderArrayAux (node<T>* r, T* arr[], int* counter , int max) const
    {
        if (!r)
        {
            return;
        }
        reverseInorderArrayAux (r->right, arr , counter,max);
        if (*counter < max) {
            arr[*counter] = r->data;
            *counter = *counter + 1;
            reverseInorderArrayAux(r->left, arr, counter, max);
        }

    }

    T** smartInorderArray (T* min , T* max , int* numMatching) const
    {
        int counter=0;
        T** arr = (T**)malloc(size*sizeof(T*));
        smartInorderArrayAux(root, arr, &counter,  min , max);
        *numMatching = counter;
        T** arr2 = (T**)malloc((counter)*sizeof(T*));
        while (counter > 0){
            arr2[counter-1] = arr [counter-1];
            counter --;
        }
        free (arr);
        return arr2;
    }

    void smartInorderArrayAux (node<T>* r, T* arr[], int* counter , T* min , T* max) const {
        if (!r) {
            return;
        }
        if (*(r->data) > *(min) || *(r->data) == *(min)) {
            smartInorderArrayAux(r->left, arr, counter, min, max);
        }
        if ((*(r->data) < *(max) ||*(r->data) == *(max) ) && (*(r->data) > *(min) || *(r->data) == *(min))) {
            arr[*counter] = r->data;
            *counter = *counter + 1;
        }

        if (*(r->data) < *(max) ||*(r->data) == *(max)) {
            smartInorderArrayAux(r->right, arr, counter, min, max);
        }
    }

    void deleteLeafsFromRight (int numToDelete)
    {
        root = deleteLeafsFromRightAux(root, &numToDelete);
    }

    node<T>* deleteLeafsFromRightAux (node<T>* r, int* numToDelete)
    {
        if (!r)
        {
            return nullptr;
        }
        r->right = deleteLeafsFromRightAux (r->right, numToDelete);
        if (*numToDelete!=0 && (!(r->left) && !(r->right)))
        {
            r = deleteNode(r, nullptr);
            (*numToDelete)--;
            return nullptr;
        }
        if(*numToDelete==0)
        {
            return r;
        }
        r->left = deleteLeafsFromRightAux(r->left, numToDelete);
        return r;
    }

    void fillEmptyTreeFromSortedArray (T** arr)
    {
        int counter=0;
        fillEmptyTreeFromSortedArrayAux(root, arr, &counter);
    }

    void fillEmptyTreeFromSortedArrayAux (node<T>* r, T* arr[], int* counter)
    {
        if (!r)
        {
            return;
        }
        fillEmptyTreeFromSortedArrayAux (r->left, arr , counter);
        if (*counter < size) {
            r->data = arr[*counter];
            *counter = *counter + 1;
            fillEmptyTreeFromSortedArrayAux(r->right, arr, counter);
        }
    }

    node<T>* deleteAllNodes(node<T>* r) {
        if(r== nullptr)
        {
            return nullptr;
        }
        node<T> *base = r;
        r = deleteAllNodesAux(base, r);
        deleteNode(r, nullptr);
        return nullptr;
    }

    node<T>* deleteAllNodesAux(node<T>* base, node<T>* r)
    {
        if (r== nullptr)
        {
            return nullptr;
        }                       //added condition
        if ((!(r->left) && !(r->right))) //changed condition
        {
            r = deleteNode(r, nullptr);
            return nullptr;
        }
        r->left = deleteAllNodesAux(base, r->left);
        r->right = deleteAllNodesAux(base, r->right);
        if ((!(r->left) && !(r->right)) || r!=base)
        {
            r = deleteNode(r, nullptr);
            return nullptr;
        }
    }

    node<T>* deleteTreeWithData(node<T>* r) {
        if(r == nullptr)
        {
            return nullptr;
        }
        node<T> *base = r;
        r = deleteTreeWithDataAux(base, r);
        deleteLeafWithData(r);
        return nullptr;
    }

    node<T>* deleteTreeWithDataAux(node<T>* base, node<T>* r)
    {
        if (r== nullptr)
        {
            return nullptr;
        }
        if ((!(r->left) && !(r->right)) && r!=base)
        {
            r = deleteLeafWithData(r);
            return nullptr;
        }
        r->left = deleteTreeWithDataAux(base, r->left);
        r->right = deleteTreeWithDataAux(base, r->right);
        if ((!(r->left) && !(r->right)) && r!=base)
        {
            r = deleteLeafWithData(r);
            return nullptr;
        }
    }

    node<T>* deleteLeafWithData (node<T>* r)
    {
        if (r->data!= nullptr)
        {
            delete r->data;
        }
        delete r;
        size--;
        return nullptr;
    }
};

template<class T>
node<T>* createEmptyCompleteTreeAux (node<T>* r, int completeH)
{
    if(completeH==-1)
    {
        return nullptr;
    }
    r = new node<T>(nullptr);
    r->height=completeH;
    r->left = createEmptyCompleteTreeAux(r->left, completeH-1);
    r->right = createEmptyCompleteTreeAux(r->right, completeH-1);
    return r;
}


template<class T>
///gets pointer to tree - with no nodes
void createEmptyCompleteTree (AVLtree<T>* completeTree ,int completeH)
{
    completeTree->root = createEmptyCompleteTreeAux(completeTree->root, completeH);
    completeTree->size = exp2(completeH+1)-1;
}

template<class T>
///needs to get ptr to tree - with no nodes
void createEmptyNearlyCompleteTree (AVLtree<T>* emptyTree, int finalSize)
{
    int newH= ceil(log2(finalSize+1))-1;
    createEmptyCompleteTree<T>(emptyTree,newH);
    emptyTree->deleteLeafsFromRight(emptyTree->size - finalSize);
    emptyTree->size=finalSize;
}

template<class T>
void mergeArrays (T** arr1, T** arr2, T** destArr , int t1size, int t2size)
{
    T** p1=arr1;
    T** p2=arr2;
    T** pDest=destArr;
    int t1 = t1size;
    int t2 = t2size;
    while (t1 > 0 && t2 > 0)
    {
        if (*(*p1)<*(*p2) || *(*p1)==*(*p2))
        {
            *pDest=*p1;
            p1++;
            t1 -- ;
        }
        else
        {
            *pDest=*p2;
            p2++;
            t2 --;
        }
        pDest++;
    }
    while (t1 > 0)
    {
        *pDest=*p1;
        p1++;
        pDest++;
        t1--;

    }
    while (t2>0)
    {
        *pDest=*p2;
        p2++;
        pDest++;
        t2 -- ;
    }
}

template<class T>
void uniteTrees (AVLtree<T>* t1 , AVLtree<T>* t2, AVLtree<T>* destTree)
{
    T** arr1 = t1->inorderArray(t1->size);
    T** arr2 = t2->inorderArray(t2->size);
    T** uniteArr = (T**)malloc((t1->size + t2->size)*sizeof(T*));
    mergeArrays(arr1, arr2, uniteArr, t1->size,t2->size);
    createEmptyNearlyCompleteTree<T>(destTree,t1->size+t2->size);
    destTree->fillEmptyTreeFromSortedArray(uniteArr);
    free(arr1);
    free(arr2);
    free(uniteArr);
}


#endif //HW1_WET_AVLTREE_H
