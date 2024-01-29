#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <algorithm>
#include <list>


using namespace std;
using namespace chrono;
random_device rd;

//-----------------------------Function to generate random integer numbers---------------------
void generateRandomNumbers(int arr[], int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(-1000000, 1000000);

    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
}

//--------------------------- Function to print the array--------------------------------------
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//---------------------------- Merge Sort for binary search ----------------------------------------
void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;


    int* leftArr = new int[n1];
    int* rightArr = new int[n2];


    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[middle + 1 + j];


    int i = 0;
    int j = 0;
    int k = left;
// Merge elements from leftArr and rightArr in sorted order
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;// Calculate the middle point
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}
//----------------------------------binary search ------------------------------------------
int binarySearch(int arr[], int left, int right, int target) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] > target)
            return binarySearch(arr, left, mid - 1, target);

        return binarySearch(arr, mid + 1, right, target);
    }

    return -1;
}
//-----------------------------------------choosing numbers for search -------------------------------
int* choosing(int arr[], int size) {
    int* result = new int[100];
    for (int i = 0; i < 100; i++) {
        uniform_int_distribution<int> dist(0, size - 1);
        int index = dist(rd);
        result[i] = arr[index];
    }

    return result;
}
//----------------------------------------linked list with merge sort ---------------------------------
struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

Node* SortedMerge(Node* a, Node* b) {
    Node* result = NULL;

    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    if (a->data <= b->data) {
        result = a;
        result->next = SortedMerge(a->next, b);
    } else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return result;
}

void FrontBackSplit(Node* source, Node** frontRef, Node** backRef) {
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;// The front half goes from 'source' to 'slow'
    *backRef = slow->next;// The back half starts from the element after 'slow'
    slow->next = NULL;//end the front half list
}

void MergeSort(Node** headRef) {
    Node* head = *headRef;
    Node* a;
    Node* b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    FrontBackSplit(head, &a, &b);

    MergeSort(&a);
    MergeSort(&b);

    *headRef = SortedMerge(a, b);
}

//-----------------------to deleting the nodes of linked list-----------------------
void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
//--------------------------- BST--------------------------------------
class BST {

    struct node {
        int data;
        node* left;
        node* right;
    };

    node* root;

    node* deleteBST(node* t) {
        if(t == NULL)
            return NULL;
        {
            deleteBST(t->left);
            deleteBST(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(int x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
            t->left = insert(x, t->left);
        else if(x > t->data)
            t->right = insert(x, t->right);
        return t;
    }

    void inOrderTraversal(node* t) {
        if(t == NULL)
            return;
        inOrderTraversal(t->left);
        cout << t->data << " ";
        inOrderTraversal(t->right);
    }

    node* find(node* t, int x) {
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            return find(t->left, x);
        else if(x > t->data)
            return find(t->right, x);
        else
            return t;
    }

    public:
    BST() {
        root = NULL;
    }

    ~BST() {
        root = deleteBST(root);
    }

    void insert(int x) {
        root = insert(x, root);
    }
    void show() {
        inOrderTraversal(root);
        cout << endl;
    }

    bool search(int x) {
        return find(root, x) != NULL;

    }
};
/// -------------------------- list in STL ------------------------

void insert(list<int>& lst, int value) {
    lst.push_back(value);
}

bool search(const list<int>& lst, int value) {
    return find(lst.begin(), lst.end(), value) != lst.end();
}

void deleteAll(list<int>& lst) {
    lst.clear();
}

void print(const list<int>& lst) {
    for (int value : lst) {
        cout << value << " ";
    }
    cout << endl;
}
///-------------------------- skip list ---------------------------

class skipNode {
public:
    int key;
    vector<skipNode*> forward;

    skipNode(int key, int level) {
        this->key = key;
        forward.resize(level + 1);
    }
};

class SkipList {
    int MAX_LEVEL;
    float P;
    int level;
    skipNode *header;

public:
    SkipList(int MAX_LEVEL, float P) {
        this->MAX_LEVEL = MAX_LEVEL;
        this->P = P;
        level = 0;
        header = new skipNode(-1, MAX_LEVEL);// Create a new header node with key -1
    }

    int randomLevel() {
        float r = (float)rand()/RAND_MAX;
        int lvl = 0;
        while (r < P && lvl < MAX_LEVEL) {
            lvl++;
            r = (float)rand()/RAND_MAX;
        }
        return lvl;
    }

    skipNode* search(int key) {
        skipNode *x = header;
        for (int i = level; i >= 0; i--) {
            while (x->forward[i] && x->forward[i]->key < key)
                x = x->forward[i];
        }
        x = x->forward[0];
        if (x && x->key == key) return x;
        return nullptr;
    }

    void insert(int key) {
        skipNode *x = header;
        vector<skipNode*> update(MAX_LEVEL + 1);
        for (int i = level; i >= 0; i--) {
            while (x->forward[i] && x->forward[i]->key < key)
                x = x->forward[i];
            update[i] = x;
        }
        x = x->forward[0];
        if (x == nullptr || x->key != key) {// If element is not present, insert it
            int rlevel = randomLevel();
            if (rlevel > level) {
                for (int i = level + 1; i < rlevel + 1; i++)
                    update[i] = header;// Update the header
                level = rlevel;// Update the level
            }
            x = new skipNode(key, rlevel);
            for (int i = 0; i <= rlevel; i++) {
                x->forward[i] = update[i]->forward[i];// Assign pointer of new node at i
                update[i]->forward[i] = x;// Insert new node in skip list
            }
        }
    }

    void display() {
        for (int i = 0; i <= level; i++) {
            skipNode *node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << node->key << " ";
                node = node->forward[i];
            }
            cout <<endl;
        }
    }

    void deleteAll() {
        skipNode *node = header->forward[0];
        while (node != nullptr) {
            skipNode *temp = node;
            node = node->forward[0];
            delete temp;
        }
        delete header;
    }
};

///-------------------------- RED BLACK TREE ----------------------
struct RBTNode {
    int data;
    RBTNode *chap, *rost, *parent;
    int color; // 1 -> Red, 0 -> Black
};


void leftRotate(RBTNode *&root, RBTNode *&pt) {
    RBTNode *pt_right = pt->rost; // Node that will be rotated to the left

    pt->rost = pt_right->chap;//The right child of pt is set to the left child of pt_right.

    if (pt->rost != nullptr)
        pt->rost->parent = pt;// Set its parent to the current node

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_right; // If the current node was the root
                        // The right node becomes the new root

    else if (pt == pt->parent->chap)// If the current node is the left child of its parent
        pt->parent->chap = pt_right;

    else// If the current node is the right child of its parent
        pt->parent->rost = pt_right;//---

    pt_right->chap = pt;// The current node becomes the left child of the right node
    pt->parent = pt_right;// The right node becomes the parent of the current node
}

// Function to perform a right rotate
void rightRotate(RBTNode *&root, RBTNode *&pt) {
    RBTNode *pt_left = pt->chap;

    pt->chap = pt_left->rost;

    if (pt->chap != nullptr)
        pt->chap->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_left;

    else if (pt == pt->parent->chap)
        pt->parent->chap = pt_left;

    else
        pt->parent->rost = pt_left;

    pt_left->rost = pt;
    pt->parent = pt_left;
}

void fixViolation(RBTNode *&root, RBTNode *&pt) {
    RBTNode *parent_pt = nullptr;
    RBTNode *grand_parent_pt = nullptr;

    while ((pt != root) && (pt->color != 0) &&
           (pt->parent != nullptr) && (pt->parent->color == 1)) {

        parent_pt = pt->parent;
        grand_parent_pt = (parent_pt != nullptr) ? parent_pt->parent : nullptr;

        if (grand_parent_pt == nullptr) {
            // If grand_parent_pt is null, break out of the loop
            break;
        }

        /* Case : A
            Parent of pt is left child of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->chap) {
            RBTNode *uncle_pt = grand_parent_pt->rost;

            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle_pt != nullptr && uncle_pt->color == 1) {
                grand_parent_pt->color = 1;
                parent_pt->color = 0;
                uncle_pt->color = 0;
                pt = grand_parent_pt;
            } else {
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (pt == parent_pt->rost) {
                    leftRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = (pt != nullptr) ? pt->parent : nullptr;
                }

                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                rightRotate(root, grand_parent_pt);
                if (parent_pt != nullptr && grand_parent_pt != nullptr) {
                    swap(parent_pt->color, grand_parent_pt->color);
                }
                pt = parent_pt;
            }
        }
        /* Case : B
           Parent of pt is right child of Grand-parent of pt */
        else {
            RBTNode *uncle_pt = grand_parent_pt->chap;

            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != nullptr) && (uncle_pt->color == 1)) {
                grand_parent_pt->color = 1;
                parent_pt->color = 0;
                uncle_pt->color = 0;
                pt = grand_parent_pt;
            } else {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->chap) {
                    rightRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = (pt != nullptr) ? pt->parent : nullptr;
                }

                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                leftRotate(root, grand_parent_pt);
                if (parent_pt != nullptr && grand_parent_pt != nullptr) {
                    swap(parent_pt->color, grand_parent_pt->color);
                }
                pt = parent_pt;
            }
        }
    }

    if (root != nullptr) {
        root->color = 0;
    }
}

RBTNode* BSTInsert(RBTNode* root, RBTNode* pt) {
    // If the tree is empty, assign a new node address to root
    if (root == nullptr)
       return pt;

    // Otherwise, recur down the tree
    if (pt->data < root->data) {
        root->chap = BSTInsert(root->chap, pt);
        root->chap->parent = root;
    } else if (pt->data > root->data) {
        root->rost = BSTInsert(root->rost, pt);
        root->rost->parent = root;
    }

    // Return the (unchanged) node pointer
    return root;
}



void insert(RBTNode *&root, int data) {
    // Allocate memory for new node
    RBTNode *pt = new RBTNode;
    pt->data = data;
    pt->chap = pt->rost = pt->parent = nullptr;
    pt->color = 1; // new node is by default red

    // If the tree is empty, the new node becomes the root
    if (root == nullptr) {
        pt->color = 0; // Set color to black for the root
        root = pt;
    } else {
        // Otherwise, do a normal BST insert
        root = BSTInsert(root, pt);

        // Fix Red-Black Tree violations
        fixViolation(root, pt);
    }
}


void inorder(RBTNode *trav) {
    if (trav == nullptr)
        return;

    inorder(trav->chap);
    cout << trav->data << "  ";
    inorder(trav->rost);
}


void deleteTree(RBTNode *&root) {
    if (root == nullptr)
        return;


    deleteTree(root->chap);
    deleteTree(root->rost);


    delete root;
    root = nullptr;
}


RBTNode* search(RBTNode *root, int data) {

    if (root == nullptr || root->data == data)
       return root;


    if (root->data < data)
       return search(root->rost, data);


    return search(root->chap, data);
}



int main() {
    srand(time(nullptr));

    int size_choose = 100;
    int size1 = 100000;
    int size2 = 1000000;
    int size3 = 10000000;
    int* arr1 = new int[size1];
    int* arr2 = new int[size2];
    int* arr3 = new int[size3];
    int* arr4 = new int [size_choose];// for search
    generateRandomNumbers(arr1, size1);
    generateRandomNumbers(arr2, size2);
    generateRandomNumbers(arr3, size3);
    generateRandomNumbers(arr4, size_choose);

    cout << "Menu:\n";
    cout << " CPU : Intel(R) Core(TM) i5-7200U CPU @ 2.50GHz   2.71 GHz\n";
    cout << " RAM : 4GB ddr4\n";
    cout << " OS : Windows 64bit\n";
    cout << " compiler : GNU GCC\n";
    cout << "1. Run arrays sorting and searching with merge sort and binary search\n";
    cout << "2. Run linked list with merge sort\n";
    cout << "3. Run only searching with BST\n";
    cout << "4. Run list data  structure in STL library\n";
    cout << "5. Run skip list with search function\n ";
    cout << "6. Run RED BLACK TREE searching algorithm\n";
    cout << "Choose an option: ";

    int choice;
    cin >> choice;
    switch (choice) {
    case 1: {


        // Measure the time to sort the generated numbers using merge sort
        auto startSorting1 = high_resolution_clock::now();
        mergeSort(arr1, 0, size1 - 1);
        auto stopSorting1 = high_resolution_clock::now();
        auto sortingDuration1 = duration_cast<milliseconds>(stopSorting1 - startSorting1);

        auto startSorting2 = high_resolution_clock::now();
        mergeSort(arr2, 0, size2 - 1);
        auto stopSorting2 = high_resolution_clock::now();
        auto sortingDuration2 = duration_cast<milliseconds>(stopSorting2 - startSorting2);

        auto startSorting3 = high_resolution_clock::now();
        mergeSort(arr3, 0, size3 - 1);
        auto stopSorting3 = high_resolution_clock::now();
        auto sortingDuration3 = duration_cast<milliseconds>(stopSorting3 - startSorting3);

        ///-------------------initializing the b search --------------------------
        auto startSB1 = high_resolution_clock::now();
        int* chosen1 = choosing(arr1, size1);
        for (int i = 0; i < 100; i++) {
            binarySearch(arr1, 0, size1 - 1, chosen1[i]);
            binarySearch(arr1, 0, size_choose - 1, arr4[i]);
        }
        auto stopSB1 = high_resolution_clock::now();
        auto SBDuration1 = duration_cast<milliseconds>(stopSB1 - startSB1);

        auto startSB2 = high_resolution_clock::now();
        int* chosen2 = choosing(arr2, size2);
        for (int i = 0; i < 100; i++) {
            binarySearch(arr2, 0, size2 - 1, chosen2[i]);
            binarySearch(arr1, 0, size_choose - 1, arr4[i]);
        }
        auto stopSB2 = high_resolution_clock::now();
        auto SBDuration2 = duration_cast<milliseconds>(stopSB2 - startSB2);

        auto startSB3 = high_resolution_clock::now();
        int* chosen3 = choosing(arr3, size3);
        for (int i = 0; i < 100; i++) {
            binarySearch(arr3, 0, size3 - 1, chosen3[i]);
            binarySearch(arr1, 0, size_choose - 1, arr4[i]);
        }
        auto stopSB3 = high_resolution_clock::now();
        auto SBDuration3 = duration_cast<milliseconds>(stopSB3 - startSB3);

        cout << "Time for sort  numbers with merge sort (size 100000): " << sortingDuration1.count() << " milliseconds" << endl;
        cout << "Time for sort  numbers with merge sort (size 1000000): " << sortingDuration2.count() << " milliseconds" << endl;
        cout << "Time for sort  numbers with merge sort (size 10000000): " << sortingDuration3.count() << " milliseconds" << endl;


        cout << "Time for  search numbers with binary search (size 100000): " << SBDuration1.count() << " milliseconds" << endl;
        cout << "Time for  search numbers with binary search (size 1000000): " << SBDuration2.count() << " milliseconds" << endl;
        cout << "Time for  search numbers with binary search (size 10000000): " << SBDuration3.count() << " milliseconds" << endl;


        //printArray(arr1,size1);



        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
        delete[] arr4;
        delete[] chosen1;
        delete[] chosen2;
        delete[] chosen3;


        break;
    }
    case 2: {


        Node* list1 = nullptr;
        Node* list2 = nullptr;
        Node* list3 = nullptr;

        for (int i = 0; i < size1; ++i) {
    Node* newNode = new Node(arr1[i]);
    newNode->next = list1;
    list1 = newNode;
}
            //printList(list1);
for (int i = 0; i < size2; ++i) {
    Node* newNode = new Node(arr2[i]);
    newNode->next = list2;
    list2 = newNode;
}

for (int i = 0; i < size3; ++i) {
    Node* newNode = new Node(arr3[i]);
    newNode->next = list3;
    list3 = newNode;
}

        auto startLinked1 = high_resolution_clock::now();
        MergeSort(&list1);
        auto stopLinked1 = high_resolution_clock::now();
        auto sortingLinked1 = duration_cast<milliseconds>(stopLinked1 - startLinked1);

        auto startLinked2 = high_resolution_clock::now();
        MergeSort(&list2);
        auto stopLinked2 = high_resolution_clock::now();
        auto sortingLinked2 = duration_cast<milliseconds>(stopLinked2 - startLinked2);

        auto startLinked3 = high_resolution_clock::now();
        MergeSort(&list3);
        auto stopLinked3 = high_resolution_clock::now();
        auto sortingLinked3 = duration_cast<milliseconds>(stopLinked3 - startLinked3);

        //printList(list1);

        deleteList(list1);
        deleteList(list2);
        deleteList(list3);


        delete[] arr1;
        delete[] arr2;
        delete[] arr3;


        cout << "Time to sort numbers on linked-list with merge sort (size 100000): " << sortingLinked1.count() << " milliseconds" << endl;
        cout << "Time to sort numbers on linked-list with merge sort (size 1000000): " << sortingLinked2.count() << " milliseconds" << endl;
        cout << "Time to sort numbers on linked-list with merge sort (size 10000000): " << sortingLinked3.count() << " milliseconds" << endl;
        break;
    }



    case 3: {


        int* chose1 = choosing(arr1, size1);
        int* chose2 = choosing(arr2, size2);
        int* chose3 = choosing(arr3, size3);


        BST root1;
        BST root2;
        BST root3;

        auto startInsertion1 = high_resolution_clock::now();
        for (int ar1=0; ar1<100000; ar1++){
        root1.insert(arr1[ar1]);
        }
        auto stopInsertion1 = high_resolution_clock::now();
        auto Insertion_time1 = duration_cast<milliseconds>(stopInsertion1 - startInsertion1);

        auto startInsertion2 = high_resolution_clock::now();
        for (int ar2=0; ar2<1000000; ar2++){
        root2.insert(arr2[ar2]);
        }
        auto stopInsertion2 = high_resolution_clock::now();
        auto Insertion_time2 = duration_cast<milliseconds>(stopInsertion2 - startInsertion2);

        auto startInsertion3 = high_resolution_clock::now();
        for (int ar3=0; ar3<10000000; ar3++){
        root3.insert(arr3[ar3]);
        }
        auto stopInsertion3 = high_resolution_clock::now();
        auto Insertion_time3 = duration_cast<milliseconds>(stopInsertion3 - startInsertion3);



        cout<<" Time to insert 100000 numbers in BST : "<<Insertion_time1.count()<<" milliseconds"<< endl;
        cout<<" Time to insert 1000000 numbers in BST : "<<Insertion_time2.count()<<" milliseconds"<< endl;
        cout<<" Time to insert 10000000 numbers in BST : "<<Insertion_time3.count()<<" milliseconds"<< endl;


        //root1.show();


       auto startSearchBST1 = high_resolution_clock::now();
       for (int chs1=0 ; chs1< 100 ; chs1++){
      /* bool found =*/ root1.search(chose1[chs1]);
                        root1.search(arr4[chs1]);
        /*if (found) {
            cout << "Element " << chose1[chs1] << " found in BST." << endl;
            } else {
            cout << "Element " << chose1[chs1] << " not found in BST." << endl;*/
    }

       auto stopSearchBST1 = high_resolution_clock::now();
       auto search_timeBST1 = duration_cast<milliseconds>(stopSearchBST1 - startSearchBST1);

       auto startSearchBST2 = high_resolution_clock::now();
       for (int chs2=0 ; chs2< 100 ; chs2++){
        root2.search(chose1[chs2]);
        root1.search(arr4[chs2]);

       }
       auto stopSearchBST2 = high_resolution_clock::now();
       auto search_timeBST2 = duration_cast<milliseconds>(stopSearchBST2 - startSearchBST2);

       auto startSearchBST3 = high_resolution_clock::now();
       for (int chs3=0 ; chs3< 100 ; chs3++){
       root3.search(chose3[chs3]);
       root1.search(arr4[chs3]);

       }
       auto stopSearchBST3 = high_resolution_clock::now();
       auto search_timeBST3 = duration_cast<milliseconds>(stopSearchBST3 - startSearchBST3);


       cout << " Time to search in BST in 100000 numbers : " << search_timeBST1.count() << " milliseconds" <<endl;
       cout << " Time to search in BST in 1000000 numbers : " << search_timeBST2.count() << " milliseconds" <<endl;
       cout << " Time to search in BST in 10000000 numbers : " << search_timeBST3.count() << " milliseconds" <<endl;

    //root1.search(99997777);
     delete[] arr1;
     delete[] arr2;
     delete[] arr3;
     delete[] arr4;

    delete[] chose1;
    delete[] chose2;
    delete[] chose3;
    break;

    }
    case 4 : {


        int* choseL1 = choosing(arr1, size1);
        int* choseL2 = choosing(arr2, size2);
        int* choseL3 = choosing(arr3, size3);

        list<int> lst1;
        list<int> lst2;
        list<int> lst3;


    auto startInsertionL1 = high_resolution_clock::now();
        for (int aL1=0; aL1<size1; aL1++){
       insert(lst1,arr1[aL1]);
        }
    auto stopInsertionL1 = high_resolution_clock::now();
    auto DurationL1 = duration_cast<milliseconds>(stopInsertionL1 - startInsertionL1);


    auto startInsertionL2 = high_resolution_clock::now();
        for (int aL2=0; aL2<size2; aL2++){
       insert(lst2,arr2[aL2]);
        }
    auto stopInsertionL2 = high_resolution_clock::now();
    auto DurationL2 = duration_cast<milliseconds>(stopInsertionL2 - startInsertionL2);



    auto startInsertionL3 = high_resolution_clock::now();
        for (int aL3=0; aL3<size3; aL3++){
       insert(lst3,arr3[aL3]);
        }
    auto stopInsertionL3 = high_resolution_clock::now();
    auto DurationL3 = duration_cast<milliseconds>(stopInsertionL3 - startInsertionL3);

        cout<<" Time to insert 100000 numbers in List1 : "<<DurationL1.count()<<" milliseconds"<< endl;
        cout<<" Time to insert 1000000 numbers in List2 : "<<DurationL2.count()<<" milliseconds"<< endl;
        cout<<" Time to insert 10000000 numbers in List3 : "<<DurationL3.count()<<" milliseconds"<< endl;

    /// initializing the search ...
    long long search_times_lst1[10] = {};
    long long search_times_lst2[10] = {};
    long long search_times_lst3[10] = {};

    auto startSearchL1 = high_resolution_clock::now();
       for (int chsL1=0 ; chsL1< size_choose ; chsL1++){
       search(lst1,choseL1[chsL1]);
       search(lst1,arr4[chsL1]);
    }
    auto stopSearchL1 = high_resolution_clock::now();
    auto search_timeL1 = duration_cast<milliseconds>(stopSearchL1 - startSearchL1);



    auto startSearchL2 = high_resolution_clock::now();
       for (int chsL2=0 ; chsL2< size_choose ; chsL2++){
       search(lst2,choseL2[chsL2]);
       search(lst2,arr4[chsL2]);
    }
    auto stopSearchL2 = high_resolution_clock::now();
    auto search_timeL2 = duration_cast<milliseconds>(stopSearchL2 - startSearchL2);



    auto startSearchL3 = high_resolution_clock::now();
       for (int chsL3=0 ; chsL3< size_choose ; chsL3++){
       search(lst3,choseL3[chsL3]);
       search(lst3,arr4[chsL3]);
    }
    auto stopSearchL3 = high_resolution_clock::now();
    auto search_timeL3 = duration_cast<milliseconds>(stopSearchL3 - startSearchL3);


        long long avg_time_Lst1 = accumulate(begin(search_times_lst1), end(search_times_lst1), 0LL) / 10;
        long long best_time_Lst1 = *min_element(begin(search_times_lst1), end(search_times_lst1));
        long long worst_time_Lst1 = *max_element(begin(search_times_lst1), end(search_times_lst1));

        long long avg_time_lst2 = accumulate(begin(search_times_lst2), end(search_times_lst2), 0LL) / 10;
        long long best_time_lst2 = *min_element(begin(search_times_lst2), end(search_times_lst2));
        long long worst_time_lst2 = *max_element(begin(search_times_lst2), end(search_times_lst2));

        long long avg_time_lst3 = accumulate(begin(search_times_lst3), end(search_times_lst3), 0LL) / 10;
        long long best_time_lst3 = *min_element(begin(search_times_lst3), end(search_times_lst3));
        long long worst_time_lst3 = *max_element(begin(search_times_lst3), end(search_times_lst3));


        cout << "Average Time for rootR1: " << avg_time_Lst1 << " ms\n";
        cout << "Best Time for rootR1: " << best_time_Lst1 << " ms\n";
        cout << "Worst Time for rootR1: " << worst_time_Lst1 << " ms\n";

        cout << "Average Time for rootR2: " << avg_time_lst2 << " ms\n";
        cout << "Best Time for rootR2: " << best_time_lst2 << " ms\n";
        cout << "Worst Time for rootR2: " << worst_time_lst2 << " ms\n";

        cout << "Average Time for rootR3: " << avg_time_lst3 << " ms\n";
        cout << "Best Time for rootR3: " << best_time_lst3 << " ms\n";
        cout << "Worst Time for rootR3: " << worst_time_lst3 << " ms\n";


        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
        delete[] arr4;

        deleteAll(lst1);
        deleteAll(lst2);
        deleteAll(lst3);

        delete[] choseL1;
        delete[] choseL2;
        delete[] choseL3;

    }
    case 5: {

     SkipList skipList1(16, 0.5);
     SkipList skipList2(19, 0.5);
     SkipList skipList3(23, 0.5);
     int* choseS1 = choosing(arr1, size1);
     int* choseS2 = choosing(arr2, size2);
     int* choseS3 = choosing(arr3, size3);

     auto startInsertionS1 = high_resolution_clock::now();
        for (int aS1=0; aS1<size1; aS1++){
        skipList1.insert(arr1[aS1]);
        }
     auto stopInsertionS1 = high_resolution_clock::now();
     auto DurationS1 = duration_cast<milliseconds>(stopInsertionS1 - startInsertionS1);


     auto startInsertionS2 = high_resolution_clock::now();
        for (int aS2=0; aS2<size2; aS2++){
        skipList2.insert(arr2[aS2]);
        }
     auto stopInsertionS2 = high_resolution_clock::now();
     auto DurationS2 = duration_cast<milliseconds>(stopInsertionS2 - startInsertionS2);


    auto startInsertionS3 = high_resolution_clock::now();
        for (int aS3=0; aS3<size3; aS3++){
        skipList3.insert(arr3[aS3]);
        }
     auto stopInsertionS3 = high_resolution_clock::now();
     auto DurationS3 = duration_cast<milliseconds>(stopInsertionS3 - startInsertionS3);


        //skipList1.display();
     cout<<" Time to insert 100000 numbers in skip list : "<<DurationS1.count()<<" milliseconds"<< endl;
     cout<<" Time to insert 1000000 numbers in skip list : "<<DurationS2.count()<<" milliseconds"<< endl;
     cout<<" Time to insert 10000000 numbers in skip list : "<<DurationS3.count()<<" milliseconds"<< endl;


       auto startSearchList1 = high_resolution_clock::now();
       for (int chL1=0 ; chL1< size_choose ; chL1++){
       skipList1.search(choseS1[chL1]);
       skipList1.search(arr4[chL1]);
    }

       auto stopSearchList1 = high_resolution_clock::now();
       auto search_timeList1 = duration_cast<milliseconds>(stopSearchList1 - startSearchList1);


       auto startSearchList2 = high_resolution_clock::now();
       for (int chL2=0 ; chL2< size_choose ; chL2++){
       skipList2.search(choseS2[chL2]);
       skipList2.search(arr4[chL2]);
    }

       auto stopSearchList2 = high_resolution_clock::now();
       auto search_timeList2 = duration_cast<milliseconds>(stopSearchList2 - startSearchList2);

       auto startSearchList3 = high_resolution_clock::now();
       for (int chL3=0 ; chL3< size_choose ; chL3++){
       skipList3.search(choseS3[chL3]);
       skipList3.search(arr4[chL3]);
    }

       auto stopSearchList3 = high_resolution_clock::now();
       auto search_timeList3 = duration_cast<milliseconds>(stopSearchList3 - startSearchList3);



        cout<<" Time to search for 100 numbers in 100000 numbers in skip list : "<<search_timeList1.count()<<" milliseconds"<< endl;
        cout<<" Time to search for 100 numbers in 1000000 numbers in skip list : "<<search_timeList2.count()<<" milliseconds"<< endl;
        cout<<" Time to search for 100 numbers in 10000000 numbers in skip list : "<<search_timeList3.count()<<" milliseconds"<< endl;



     delete[] arr1;
     delete[] arr2;
     delete[] arr3;
     delete[] arr4;
     delete[] choseS1;
     delete[] choseS2;
     delete[] choseS3;

     skipList1.deleteAll();
     skipList2.deleteAll();
     skipList3.deleteAll();

    }


    case 6: {
    RBTNode *rootR1 = nullptr;
    RBTNode *rootR2 = nullptr;
    RBTNode *rootR3 = nullptr;

    int* choseR1 = choosing(arr1, size1);
    int* choseR2 = choosing(arr2, size2);
    int* choseR3 = choosing(arr3, size3);


    auto startInsertionR1 = high_resolution_clock::now();
        for (int aR1=0; aR1<size1; aR1++){
       insert(rootR1,arr1[aR1]);
        }
    auto stopInsertionR1 = high_resolution_clock::now();
    auto DurationR1 = duration_cast<milliseconds>(stopInsertionR1 - startInsertionR1);


    auto startInsertionR2 = high_resolution_clock::now();
        for (int aR2=0; aR2<size2; aR2++){
        insert(rootR2,arr2[aR2]);
        }
    auto stopInsertionR2 = high_resolution_clock::now();
    auto DurationR2 = duration_cast<milliseconds>(stopInsertionR2 - startInsertionR2);


    auto startInsertionR3 = high_resolution_clock::now();
        for (int aR3=0; aR3<size3; aR3++){
        insert(rootR3,arr3[aR3]);
        }
    auto stopInsertionR3 = high_resolution_clock::now();
    auto DurationR3 = duration_cast<milliseconds>(stopInsertionR3 - startInsertionR3);

        cout<<" Time to insert 100000 numbers in RED BLACK TREE : "<<DurationR1.count()<<" milliseconds"<< endl;
        cout<<" Time to insert 1000000 numbers in RED BLACK TREE : "<<DurationR2.count()<<" milliseconds"<< endl;
        cout<<" Time to insert 10000000 numbers in RED BLACK TREE : "<<DurationR3.count()<<" milliseconds"<< endl;
    //inorder(rootR1);

        long long search_times_rootR1[10] = {};
        long long search_times_rootR2[10] = {};
        long long search_times_rootR3[10] = {};

       for (int i = 0; i < 10; ++i) {
       auto startSearchRBT1 = high_resolution_clock::now();
       for (int chsR1=0 ; chsR1< size_choose ; chsR1++){
       /*bool found = */search(rootR1,choseR1[chsR1]);
                        search(rootR1,arr4[chsR1]);
      /* if (found) {
            cout << "Element " << choseR1[chsR1] << " found in RBT." << endl;
            } else {
            cout << "Element " << choseR1[chsR1] << " not found in RBT." << endl;
    }*/
    }
       auto stopSearchRBT1 = high_resolution_clock::now();
       auto search_timeRBT1 = duration_cast<milliseconds>(stopSearchRBT1 - startSearchRBT1);




       auto startSearchRBT2 = high_resolution_clock::now();
       for (int chsR2=0 ; chsR2< size_choose ; chsR2++){
       search(rootR2,choseR2[chsR2]);
       search(rootR2,arr4[chsR2]);
    }

       auto stopSearchRBT2 = high_resolution_clock::now();
       auto search_timeRBT2 = duration_cast<milliseconds>(stopSearchRBT2 - startSearchRBT2);



       auto startSearchRBT3 = high_resolution_clock::now();
       for (int chsR3=0 ; chsR3< size_choose ; chsR3++){
       search(rootR3,choseR3[chsR3]);
       search(rootR3,arr4[chsR3]);
    }

       auto stopSearchRBT3 = high_resolution_clock::now();
       auto search_timeRBT3 = duration_cast<milliseconds>(stopSearchRBT3 - startSearchRBT3);
    }


        long long avg_time_rootR1 = accumulate(begin(search_times_rootR1), end(search_times_rootR1), 0LL) / 10;
        long long best_time_rootR1 = *min_element(begin(search_times_rootR1), end(search_times_rootR1));
        long long worst_time_rootR1 = *max_element(begin(search_times_rootR1), end(search_times_rootR1));

        long long avg_time_rootR2 = accumulate(begin(search_times_rootR2), end(search_times_rootR2), 0LL) / 10;
        long long best_time_rootR2 = *min_element(begin(search_times_rootR2), end(search_times_rootR2));
        long long worst_time_rootR2 = *max_element(begin(search_times_rootR2), end(search_times_rootR2));

        long long avg_time_rootR3 = accumulate(begin(search_times_rootR3), end(search_times_rootR3), 0LL) / 10;
        long long best_time_rootR3 = *min_element(begin(search_times_rootR3), end(search_times_rootR3));
        long long worst_time_rootR3 = *max_element(begin(search_times_rootR3), end(search_times_rootR3));

        //cout<<" Time to search for 100 numbers in 100000 numbers in RED BLACK TREE : "<<search_timeRBT1.count()<<" milliseconds"<< endl;
        //cout<<" Time to search for 100 numbers in 1000000 numbers in RED BLACK TREE : "<<search_timeRBT2.count()<<" milliseconds"<< endl;
        //cout<<" Time to search for 100 numbers in 10000000 numbers in RED BLACK TREE : "<<search_timeRBT3.count()<<" milliseconds"<< endl

        cout << "Average Time for rootR1: " << avg_time_rootR1 << " ms\n";
        cout << "Best Time for rootR1: " << best_time_rootR1 << " ms\n";
        cout << "Worst Time for rootR1: " << worst_time_rootR1 << " ms\n";

        cout << "Average Time for rootR2: " << avg_time_rootR2 << " ms\n";
        cout << "Best Time for rootR2: " << best_time_rootR2 << " ms\n";
        cout << "Worst Time for rootR2: " << worst_time_rootR2 << " ms\n";

        cout << "Average Time for rootR3: " << avg_time_rootR3 << " ms\n";
        cout << "Best Time for rootR3: " << best_time_rootR3 << " ms\n";
        cout << "Worst Time for rootR3: " << worst_time_rootR3 << " ms\n";




     delete[] arr1;
     delete[] arr2;
     delete[] arr3;
     delete[] arr4;

     delete[] choseR1;
     delete[] choseR2;
     delete[] choseR3;


     deleteTree(rootR1);
     deleteTree(rootR2);
     deleteTree(rootR3);

    }

    }
    return 0;

}











