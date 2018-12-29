#include "bst.h"
#include <set>


template<typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value>
{

protected: 
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);

public:
	bool sameKeys(const rotateBST& t2) const;
	void transform(rotateBST& t2) const;
	Node<Key, Value>* rootNode();

private:
	void inOrderTraversal(std::set<Value> &toReturn, Node<Key, Value>* Item) const;
	

};

template<typename Key, typename Value>
Node<Key, Value>* rotateBST<Key, Value>::rootNode(){
	return this->mRoot;
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::inOrderTraversal(std::set<Value> &toReturn,
 Node<Key, Value>* Item) const{
	if(Item == NULL){
		return;
	}
	inOrderTraversal(toReturn, Item->getLeft());
	toReturn.insert(Item->getValue());
	inOrderTraversal(toReturn, Item->getRight());
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r){

	Node<Key, Value>* x = r->getRight();
	if(!r->getRight()) return;
	if(!r->getParent()) {
		this->mRoot = x;
		this->mRoot->setParent(NULL);
		
	
	}

	else if(r->getParent()->getKey() > x->getKey()){

		r->getParent()->setLeft(x);
		x->setParent(r->getParent());
		
	}
	else{
		r->getParent()->setRight(x);
		x->setParent(r->getParent());
	}
	
	if(x->getLeft()){
		
		Node<Key, Value>* TreeToMove = x->getLeft();
		r->setRight(TreeToMove);
		TreeToMove->setParent(r);
	}
	else{
		r->setRight(NULL);
	}
	r->setParent(x);
	x->setLeft(r);

}

template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r){

	if(!r->getLeft()) return;
	Node<Key, Value>* x = r->getLeft();

	if(!r->getParent()){
		this->mRoot = x;
		x->setParent(NULL);
	}
	else if(r->getParent()->getKey() > x->getKey()){

		r->getParent()->setLeft(x);
		x->setParent(r->getParent());
	}
	else{
		r->getParent()->setRight(x);
		x->setParent(r->getParent());
	}

	if(x->getRight()){
		Node<Key, Value>* TreeToMove = x->getRight();
		r->setLeft(TreeToMove);
		TreeToMove->setParent(r);
	}
	else{
		r->setLeft(NULL);
	}
	r->setParent(x);
	x->setRight(r);


}

template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const{
	std::set<Value> thisSet;
	inOrderTraversal(thisSet, this->mRoot);
	std::set<Value> t2_Set;
	inOrderTraversal(t2_Set, t2.mRoot);

	return (thisSet == t2_Set);

}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const{
	Node<Key, Value>* NodeToRotate = t2.mRoot;
	while(NodeToRotate){

		while(NodeToRotate->getLeft()){

			t2.rightRotate(NodeToRotate);
		}
		NodeToRotate = NodeToRotate->getParent();
	}

	Node<Key, Value>* NodeToLeft = t2.mRoot;

	
	while(NodeToLeft->getKey() != this->mRoot->getKey()){

		t2.leftRotate(NodeToLeft);
		NodeToLeft = t2.mRoot;
	}

	Node<Key, Value>* LastRotates = t2.mRoot->getLeft();
	while(LastRotates->getKey() != this->mRoot->getLeft()->getKey()){
		t2.rightRotate(LastRotates);
		LastRotates = LastRotates->getParent();
	}
	LastRotates = t2.mRoot->getRight();
	while(LastRotates->getKey() != this->mRoot->getRight()->getKey()){
		t2.leftRotate(LastRotates);
		LastRotates = LastRotates->getParent();
	}


}