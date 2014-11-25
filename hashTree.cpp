//
//  hashTree.cpp
//  Lab4.Rodman.260
//
//  Created by Nathan Rodman on 5/31/14.
//  Copyright (c) 2014 nathan.rodman. All rights reserved.
//

#include "hashTree.h"
#include <fstream>

hashTree::hashTree() : root(nullptr), table(nullptr)
{
    
}

hashTree::hashTree(const char * fileName): root(nullptr), table(nullptr)
{
    initializeTable();
    ifstream inFile;
    data vendor;
    char tempName[100];
    char tempPhone[100];
    char tempProduct[100];
    char tempEvents[100];
    
    inFile.open(fileName);
    if(!inFile)
    {
        cerr << "Unable to open \"" << fileName << "\"" << endl;
        exit(2);
    }
    
    inFile.get(tempName, 100, ';');
    while(!inFile.eof())
    {
        inFile.ignore(100, ';');
        inFile.get(tempPhone, 100, ';');
        inFile.ignore(100, ';');
        inFile.get(tempProduct, 100, ';');
        inFile.ignore(100, ';');
        inFile.get(tempEvents, 100, '\n');
        inFile.ignore(100, '\n');
        
        vendor.setName(tempName);
        vendor.setPhone(tempPhone);
        vendor.setProduct(tempProduct);
        vendor.setEvents(tempEvents);
        
        add(vendor);
        
        inFile.get(tempName, 100, ';');
    }
}

int hashTree::calculateIndex(char * key) const
{
    char * c = key;
	int total = 0;
	while(*c)
	{
		total += *c;
		c++;
	}
    
	return total%capacity;

}



hashTree::~hashTree()
{
    int i;
    hashNode * curr = nullptr;
    destroyTable(root);
    for(i = 0; i < capacity; i++)
    {
        hashNode * prev;
        for(curr = table[i]; curr; curr = curr->next)
        {
            prev = curr;
            prev = nullptr;
        }
    }
    table = nullptr;
}

void hashTree::writeOut(const char * fileName)
{
    ofstream out;
    out.open(fileName);
    if(!out)
    {
        cerr << "Unable to writeout file: \"" << fileName << "\"" << endl;
        exit(2);
    }
    
    writeOut(out, root);
    out.close();
}

void hashTree::writeOut(ofstream & out, treeNode * root)
{
    if(root)
	{
		char name[100];
		char phone[100];
        char product[100];
        char events[100];
		root->item->getName (name);
		root->item->getPhone(phone);
        root->item->getProduct(product);
        root->item->getEvents(events);
        
		out << name << ';' << phone << ';' << product << ';' << events << '\n';
        
		writeOut(out, root->left);
		writeOut(out, root->right);
	}
}

void hashTree::initializeTable()
{
    table = new hashNode*[capacity];
    
	int i;
	for(i=0; i<capacity; i++)
		table[i] = NULL;
}


/* 
=============
ADD FUNCTIONS
=============
 */
 
 
void hashTree::add(const data & aData)
{
    data * ptrItem = new data;
    *ptrItem = aData;
    
    addToTable(ptrItem);
    addToTree(ptrItem);
   
}

void hashTree::addToTable(data *ptrItem)
{
    char tempProduct[100];
    char compare[100];
    ptrItem->getProduct(tempProduct);
    int index = calculateIndex(tempProduct);
    
    hashNode * newNode = new hashNode; //(*ptrItem);
    // just added
    
    newNode->item = ptrItem;
    newNode->next = NULL;
    
    
    if(table[index] == nullptr)
    {
        newNode->next = table[index];
        table[index] = newNode;
    }
    else
    {
        hashNode * curr = nullptr;
        for(curr = table[index]; curr; curr = curr->next)
        {
            curr->item->getProduct(compare);
            if (strcmp(compare, tempProduct) > 0)
            {
                newNode->next = curr->next;
                curr->next = newNode;
            }
            
        }

    }
    size++;
    
    
}

void hashTree::addToTree(data *ptrItem)
{
    insert(root, *ptrItem);
}


void hashTree::insert(treeNode*& root, data& aData)
{
    char key[100];
    char compare[100];
    
    if (root)
    {
        root->item->getName(compare);
        aData.getName(key);
    }
    
    
    
    if(!root)
	{
		root = new treeNode(&aData);
		size++;
	}
	else if(strcmp(key, compare) < 0)
	{
        insert(root->left, aData);
	}
	else
	{
		insert(root->right, aData);
	}
    
}

/*-----------------
 RETRIEVE FUNCTIONS
 ------------------*/

bool hashTree::retrieve(char * key, data & aData)
{
    return retrieve(root, key, aData);

}

bool hashTree::retrieve(treeNode * root, char * key, data& aData) const
{
    if(!root)
	{
		return false;
	}
    
	char name[100];
	root->item->getName (name);
	int temp = strcmp(name, key);
	if(temp == 0)
	{
		aData = *root->item;
		return true;
	}
	else if(temp < 0)
	{
		return retrieve(root->right, key, aData);
	}
	else
	{
		return retrieve(root->left, key, aData);
	}
}

bool hashTree::retrieve(char *productType, int & index)
{
    index = calculateIndex(productType);
    if(table[index] != nullptr)
        return true;
    else
        return false;
}
//displayProducts(int index) to show the products

/*------------------
 REMOVE FUNCTIONS
 ------------------*/

bool hashTree::remove(char * vendorName)
{
    removeFromTree(vendorName);
    removeFromTable(vendorName);
    return true;
}
//BST

void hashTree::removeFromTree(char * name)
{
    remove(root, name);
}

bool hashTree::remove(treeNode*& root, char * key)
{
    if(!root)
		return false;
	char name[100];
	root->item->getName (name);
	int temp = strcmp(name, key);
	if(temp == 0)
	{
		deleteNode(root);
		return true;
	}
	else if (temp < 0)
		return remove(root->right, key);
	else
		return remove(root->left, key);
}

void hashTree::deleteNode(treeNode *& target)
{
    treeNode * temp;
    
	//a leaf
	if(!target->left && !target->right)
	{
		delete target;
		target = NULL;
	}
	//no left child
	else if(!target->left)
	{
		temp = target;
		target = target->right;
		temp->right = NULL;
		delete temp;
	}
	//no right child
	else if(!target->right)
	{
		temp = target;
		target = target->left;
		temp->left = NULL;
		delete temp;
	}
	
	else
	{
        treeNode * prev = NULL;
		treeNode * curr = target->right;
		while(curr->left)
		{
			prev = curr;
			curr = curr->left;
		}
        
		
		target->item = curr->item;
        
		if(!prev)
			target->right = curr->right;
		else
			prev->left = curr->right;
        
		curr->right = NULL;
		delete curr;
	}
	size--;
}

//Table

bool hashTree::removeFromTable(char * name)
{
    int index = calculateIndex(name);
    
	
	hashNode * curr = table[index];
	hashNode * prev = NULL;
	char ch[100];
	while (curr)
	{
		curr->item->getName(name);
		if(strcmp(name, ch) == 0)
		{
			//find match and remove the node
			if(!prev)
				table[index] = curr->next;
			else
				prev->next = curr->next;
            
			curr->next = NULL;
			delete curr;
			return true;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return false;

}


/*----------------
 DISPLAY FUNCTIONS
 -----------------*/

void hashTree::displayByName()
{
    display(root);
}

void hashTree::display(treeNode * root) const
{
    if(root)
	{
		display(root->left);
		root->item->print();
		display(root->right);
	}
}

void hashTree::displayByType()
{
    for (int i=0; i < capacity; i++)
    {
        if(table[i])
        {
            char aProduct[100];
            table[i]->item->getProduct(aProduct);
            cout << "\t " << aProduct << endl;
            hashNode * curr;
            for(curr = table[i]; curr; curr = curr->next)
                curr->item->print();
        }
    }
}

void hashTree::displayProducts(int index)
{
    hashNode * curr = nullptr;
    
    for(curr = table[index]; curr; curr = curr->next)
        curr->item->print();
}

void hashTree::destroyTable(treeNode *&root)
{
        if(root)
        {
            destroyTable(root->left);
            destroyTable(root->right);
            delete root;
            root = NULL;
        }
}



