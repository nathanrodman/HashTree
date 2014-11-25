//
//  hashTree.h
//  Lab4.Rodman.260
//
//  Created by Nathan Rodman on 5/31/14.
//  Copyright (c) 2014 nathan.rodman. All rights reserved.
//

#ifndef Lab4_Rodman_260_hashTree_h
#define Lab4_Rodman_260_hashTree_h

#include "data.h"

struct treeNode
{
	data * item;
	treeNode *left, *right;
    treeNode(data * aData)
    {
        item = aData;
        left = nullptr;
        right = nullptr;
    }
   
};

struct hashNode
{
	data * item;
	hashNode * next;
/*    hashNode(const data& aData)
    {
        *item = aData;
        next = nullptr;
    }
 */
};

class hashTree
{
public:
    hashTree();
    hashTree(const char * fileName);
    hashTree(const hashTree & aHashTree);
    ~hashTree();
    
    const hashTree& operator=(hashTree & aCollection);
    
    void add(const data & aData);
    bool retrieve(char * key, data & aData);
    bool retrieve(char * productType, int & index);
    bool remove(char * vendorName);
    void displayByType();
    void displayByName();
    void displayProducts(int index);
    void writeOut(const char * fileName);
    
private:
    treeNode * root;	//the bst
	hashNode ** table;	//the hash table
	void addToTree(data * ptrItem);
	void addToTable(data * ptrItem);
	void removeFromTree(char * name);
	bool removeFromTable(char * name);
    
    int calculateIndex(char * key) const;
    int capacity = 11;
    int size;
    
    void initializeTable();
    
    //Recursive functions for BST
    
    void insert(treeNode*& root, data& aData);
	bool retrieve(treeNode * root, char * key, data& aData) const;
	bool remove(treeNode*& root, char * key);
	void deleteNode(treeNode *& target);
	void display(treeNode * root) const;
	void destroyTable(treeNode*& root);
	void copyTable(treeNode*& newRoot, treeNode * root);
    void writeOut(ofstream & out, treeNode * root);
    
    
};

#endif
