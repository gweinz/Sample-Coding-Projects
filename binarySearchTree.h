#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <algorithm>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node 
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<const Key, Value>& getItem() const;
	std::pair<const Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);
	void setHeight(int height);

protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
	int mHeight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) 
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
	, mHeight(1)
{ 

} 

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node() 
{ 

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const 
{ 
	return mItem; 
}

/**
* A non-const getter for the item. 
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() 
{ 
	return mItem; 
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const 
{ 
	return mItem.first; 
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const 
{ 
	return mItem.second; 
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const 
{ 
	return mParent; 
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const 
{ 
	return mLeft; 
}

/**
* An implementation of the virtual function for retreiving the right child. 
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const 
{ 
	return mRight; 
}

/**
* A const getter for the height.
*/
template<typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) 
{ 
	mParent = parent; 
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) 
{ 
	mLeft = left; 
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) 
{ 
	mRight = right; 
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) 
{ 
	mItem.second = value; 
}

/**
* A setter for the height of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setHeight(int height) 
{ 
	mHeight = height;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree 
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
		int height(); //TODO 
		bool isBalanced(); //TODO 
		virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
		virtual void remove(const Key& key); //TODO
		void clear(); //TODO
		void print() const;

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator 
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<const Key, Value>& operator*();
				std::pair<const Key, Value>* operator->();

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;
		};

	public:
		iterator begin();
		iterator end();
		iterator find(const Key& key) const;
		

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode(); //TODO
		void printRoot (Node<Key, Value>* root) const;
	private:
		Node<Key, Value>* getSmallestHelper(Node<Key, Value>* Start);
		Node<Key, Value>* internalHelper(Node<Key, Value>* Start,const Key& key) const;
		void insertHelp(const std::pair<const Key, Value>& keyValuePair, Node<Key, Value>* Start, Node<Key, Value>* Root);
		void ClearHelp(Node<Key, Value>* Start);
		void removeHelper(Node<Key, Value>* toRemove);
		bool BalanceHelper(Node<Key, Value>* Root, int &height);
		int heightHelp(Node<Key, Value>* Root);
		Node<Key, Value>* getLargestHelper(Node<Key, Value>* Start);
		void updateHeight(Node<Key, Value>* toUpdate);
		
	protected:
		Node<Key, Value>* mRoot;
};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{ 

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{ 

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() 
{ 
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() 
{ 
	return &(mCurrent->getItem()); 
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{ 
	mRoot = NULL;
	// TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() 
{ 	
	clear();
	mRoot = NULL;
	// TODO
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{ 
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const 
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::heightHelp(Node<Key, Value>* Root){
	if(Root == NULL){
		return 0;
	}
	else{
		return 1 + std::max(heightHelp(Root->getLeft()), heightHelp(Root->getRight()));
	}
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{

	if(mRoot == NULL) return 0;

	if(!mRoot->getRight() && !mRoot->getLeft()) return 1;

	if(!mRoot->getRight()){
		return mRoot->getLeft()->getHeight() + 1;
	}
	if (!mRoot->getLeft())
	{
		return mRoot->getRight()->getHeight() + 1;
	}

	int left = mRoot->getLeft()->getHeight();
	int right = mRoot->getRight()->getHeight();

	if(left >= right){
		return(left + 1);
	}

	else{
		return(right + 1);
	}

}


/**
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::BalanceHelper(Node<Key, Value>* Root, int &height){
	int left_height = 0;
	int right_height = 0;

	bool leftworks = false;
	bool rightworks = false;

	if(Root == NULL){
		height = 0;
		return true;

	}

	leftworks = BalanceHelper(Root->getLeft(), left_height);
	rightworks = BalanceHelper(Root->getRight(), right_height);

	height = std::max(left_height, right_height);
	height += 1;

	if(abs(left_height - right_height) > 1) return false;

	else if(leftworks && rightworks) return true;

	else return false;



}
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	if(mRoot == NULL){

		return true;
	}

	else{

		int height = 0;

		return BalanceHelper(mRoot, height);
	}
	// TODO
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when 
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::updateHeight(Node<Key, Value>* toUpdate){
	if(toUpdate == NULL){
		return;
	}
	else if(toUpdate->getRight() != NULL && toUpdate->getLeft() != NULL){

		int newHeight = std::max(toUpdate->getLeft()->getHeight(), toUpdate->getRight()->getHeight()) + 1;
		
		toUpdate->setHeight(newHeight);
		updateHeight(toUpdate->getParent());
	}
	else if(toUpdate->getRight() == NULL && toUpdate->getLeft() != NULL){
		toUpdate->setHeight(toUpdate->getLeft()->getHeight() + 1);
		updateHeight(toUpdate->getParent());
	}
	else if(toUpdate->getLeft() == NULL && toUpdate->getRight() != NULL){
		toUpdate->setHeight(toUpdate->getRight()->getHeight() + 1);
		updateHeight(toUpdate->getParent());
	}
	else{
		
		toUpdate->setHeight(1);
		updateHeight(toUpdate->getParent());
	}
}

template<typename Key, typename Value>
void  BinarySearchTree<Key, Value>::insertHelp(const std::pair<const Key, Value>& keyValuePair,
 Node<Key, Value>* Start, Node<Key, Value>* Root){
	if(Start == NULL){
		Start = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, Root);
		if(Root->getKey() > keyValuePair.first){
			Root->setLeft(Start);
		}
		else{
			Root->setRight(Start);
		}
		updateHeight(Root);
		return;
	}
	else if(keyValuePair.first > Start->getKey()){
		insertHelp(keyValuePair, Start->getRight(), Start);
	}
	else{
		insertHelp(keyValuePair, Start->getLeft(), Start);
	}

}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	if(mRoot == NULL){
		mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		return;
	}
	else if(internalFind(keyValuePair.first) != NULL){
		return;
	}
	else{
		insertHelp(keyValuePair, mRoot, mRoot);
	}
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	Node<Key, Value>* toRemove = internalFind(key);

	if(toRemove == NULL){
		return;
	}
	else{
		removeHelper(toRemove);
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeHelper(Node<Key, Value>* toRemove){
	//IF REMOVE NODE IS ROOT... HANDLE 4 EXTRA CASEs
	if(toRemove->getKey() == mRoot->getKey()){
		//if no children
		if(!toRemove->getRight() && !toRemove->getLeft()){
			
			delete toRemove;
			mRoot = NULL;
			return;
		}
		//if only left child
		else if(toRemove->getLeft() && !toRemove->getRight()){
			toRemove->getLeft()->setParent(NULL);
			mRoot = toRemove->getLeft();
			toRemove->setLeft(NULL);
		
			updateHeight(mRoot);
			delete toRemove;
		}
		//if only right child
		else if(toRemove->getRight() && !toRemove->getLeft()){
			toRemove->getRight()->setParent(NULL);
			mRoot = toRemove->getRight();
			toRemove->setRight(NULL);

			updateHeight(mRoot);
			delete toRemove;
		}
		//two children
		else{
			Node<Key, Value>* toPromote = getLargestHelper(toRemove->getLeft());
			
 			//toPromote is a leaf node aka no left or right
			if(toPromote->getHeight() == 1){
				if(toPromote->getKey() == toRemove->getLeft()->getKey())
				{
					mRoot = toPromote;
					toRemove->getRight()->setParent(toPromote);
					toPromote->setRight(toRemove->getRight());
					toPromote->setLeft(NULL);
					toPromote->setParent(NULL);
		
					delete toRemove;
					updateHeight(toPromote);
					return;
				}//if its a right leaf node, can't be anything to its right or left
				else{
					Node<Key, Value>* toPromoteParent = toPromote->getParent();
					mRoot = toPromote;
					toPromote->getParent()->setRight(NULL);
					toPromote->setParent(NULL);
					toPromote->setLeft(toRemove->getLeft());
					toPromote->getLeft()->setParent(toPromote);
					toPromote->setRight(toRemove->getRight());
					toPromote->getRight()->setParent(toPromote);
			
					delete toRemove;
					updateHeight(toPromoteParent);
					return;
				}
			}
			else{
				if(toPromote->getKey() == toRemove->getLeft()->getKey()){
					mRoot = toPromote;
					toRemove->getRight()->setParent(toPromote);
					toPromote->setRight(toRemove->getRight());
					toPromote->setLeft(toRemove->getLeft()->getLeft());
					toPromote->getLeft()->setParent(toPromote);
					toPromote->setParent(NULL);
		
					delete toRemove;
					updateHeight(toPromote);
					return;
				}
				else{
					
					mRoot = toPromote;
					Node<Key, Value>* toPromoteParent = toPromote->getParent();
					toRemove->getRight()->setParent(toPromote);
					toPromote->setRight(toRemove->getRight());
					toPromote->getParent()->setRight(toPromote->getLeft());
					toPromote->setLeft(toRemove->getLeft());
					toPromote->getLeft()->setParent(toPromote);
					
					toPromote->setParent(NULL);
			
					updateHeight(toPromoteParent);
					delete toRemove;
					return;
				}
			}
		}
	}
	//leaf child
	else if(!toRemove->getRight() && !toRemove->getLeft()){
		Node<Key, Value>* Parental = toRemove->getParent();
		if(Parental->getKey() > toRemove->getKey()){
			Parental->setLeft(NULL);
		}
		else{
			Parental->setRight(NULL);
		}
		updateHeight(Parental);
		
		delete toRemove;
		updateHeight(Parental);
		return;
	}
	//only left
	else if(toRemove->getLeft() && !toRemove->getRight()){

		if(toRemove->getParent()->getKey() > toRemove->getKey()){
			toRemove->getLeft()->setParent(toRemove->getParent());
			toRemove->getParent()->setLeft(toRemove->getLeft());
		}
		else{
			toRemove->getLeft()->setParent(toRemove->getParent());
			toRemove->getParent()->setRight(toRemove->getLeft());
		}

		updateHeight(toRemove->getParent());
		delete toRemove;
	

	}
	//only right
	else if(toRemove->getRight() && !toRemove->getLeft()){

		if(toRemove->getParent()->getKey() > toRemove->getKey()){
			toRemove->getRight()->setParent(toRemove->getParent());
			toRemove->getParent()->setLeft(toRemove->getRight());
		}
		else{
			toRemove->getRight()->setParent(toRemove->getParent());
			toRemove->getParent()->setRight(toRemove->getRight());
		}

		updateHeight(toRemove->getParent());
		delete toRemove;
		

	}
	//both :(
	else{
		Node<Key, Value>* toPromote = getLargestHelper(toRemove->getLeft());

		//toPromote is a leaf node aka no left or right
		if(toPromote->getHeight() == 1){
			if(toPromote->getKey() == toRemove->getLeft()->getKey())
			{
				if(toRemove->getParent()->getKey() > toRemove->getKey()){
					toRemove->getParent()->setLeft(toPromote);
				}
				else{
					toRemove->getParent()->setRight(toPromote);
				}
				toPromote->setParent(toRemove->getParent());
				toRemove->getRight()->setParent(toPromote);
				toPromote->setRight(toRemove->getRight());
				toPromote->setLeft(NULL);
				
				delete toRemove;
				updateHeight(toPromote);
				return;
			}//if its a right leaf node, can't be anything to its right or left
			else{
				Node<Key, Value>* toPromoteParent = toPromote->getParent();	
				toPromote->getParent()->setRight(NULL);
				if(toRemove->getParent()->getKey() > toRemove->getKey()){
					toRemove->getParent()->setLeft(toPromote);
				}
				else{
					toRemove->getParent()->setRight(toPromote);
				}

				toPromote->setParent(toRemove->getParent());
				toPromote->setLeft(toRemove->getLeft());
				toPromote->getLeft()->setParent(toPromote);
				toPromote->setRight(toRemove->getRight());
				toPromote->getRight()->setParent(toPromote);
			
				delete toRemove;
				updateHeight(toPromoteParent);
				return;
			}
		}
		else{
			if(toPromote->getKey() == toRemove->getLeft()->getKey()){
				if(toRemove->getParent()->getKey() > toRemove->getKey()){
					toRemove->getParent()->setLeft(toPromote);
				}
				else{
					toRemove->getParent()->setRight(toPromote);
				}

				toRemove->getRight()->setParent(toPromote);
				toPromote->setRight(toRemove->getRight());
				toPromote->setLeft(toRemove->getLeft()->getLeft());
				toPromote->getLeft()->setParent(toPromote);
				toPromote->setParent(toRemove->getParent());
			
				delete toRemove;
				updateHeight(toPromote);
				return;
			}
			else{
				toPromote->getParent()->setRight(toPromote->getLeft());
				if(toRemove->getParent()->getKey() > toRemove->getKey()){
					toRemove->getParent()->setLeft(toPromote);
				}
				else{
					toRemove->getParent()->setRight(toPromote);
				}

				Node<Key, Value>* toPromoteParent = toPromote->getParent();
				toRemove->getRight()->setParent(toPromote);
				toPromote->setRight(toRemove->getRight());
				toPromote->setLeft(toRemove->getLeft());
				toPromote->getLeft()->setParent(toPromote);
		
				toPromote->setParent(toRemove->getParent());
			
				updateHeight(toPromoteParent);
				delete toRemove;
				return;
			}
		}
	}
}


/**
* A method to remove all contents of the tree and reset the values in the tree 
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::ClearHelp(Node<Key, Value>* Start){
	if(Start != NULL){
		ClearHelp(Start->getLeft());
		ClearHelp(Start->getRight());
		delete Start;
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// TODO
	ClearHelp(mRoot);
	mRoot = NULL;

}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getLargestHelper(Node<Key, Value>* Start){
	if(Start->getRight() != NULL){
		return getLargestHelper(Start->getRight());
	}
	else{
		return Start;
	}

}
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestHelper(Node<Key, Value>* Start){
	if(Start->getLeft() != NULL){
		return getSmallestHelper(Start->getLeft());
	}
	else{
		return Start;
	}

}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode()
{
	Node<Key, Value>* toReturn;
	if(mRoot == NULL){
		toReturn = NULL;
	}
	else{
		toReturn = getSmallestHelper(mRoot);
	}
	return toReturn;
}

/**
* Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalHelper(Node<Key, Value>* Start,const Key& key) const{
	if(Start == NULL){
		return NULL;
	}
	else if(Start->getKey() == key){
		return Start;
	}
	else if(Start->getKey() > key){
		return internalHelper(Start->getLeft(), key);
	}
	else{
		return internalHelper(Start->getRight(), key);
	}
}
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const 
{
	return internalHelper(mRoot, key);

}

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
