#include "rotateBST.h"
#include <iostream>
#include <string>

template<typename Key, typename Value>
class SplayTree : public rotateBST<Key, Value>
{
public:
	SplayTree();
	void insert(const std::pair<const Key, Value>& keyValuePair);
	void remove(const Key& key);
	typename SplayTree<Key, Value>::iterator find(const Key& key);
	typename SplayTree<Key, Value>::iterator findMin();
	typename SplayTree<Key, Value>::iterator findMax();
	void deleteMinLeaf();
	void deleteMaxLeaf();

protected:
	void splay(Node<Key, Value>* toSplay);
private:
	Node<Key,Value>* getLarge();
	Node<Key,Value>* LargeHelp(Node<Key, Value>* Root);
	std::string type(Node<Key, Value>* splayer);
	Node<Key, Value>* LastVisited(const Key& key, Node<Key, Value>* Root, Node<Key, Value>* Next);

};

template<typename Key, typename Value>
SplayTree<Key, Value>::SplayTree(){

}
template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::LastVisited(const Key& key, Node<Key, Value>* Root,
 Node<Key, Value>* Next){
	if(!Next){
		return Root;
	}

	if(key > Root->getKey()){
		return LastVisited(key, Next, Next->getRight());
	}
	else{
		return LastVisited(key, Next, Next->getLeft());
	}


}

template<typename Key, typename Value>
std::string SplayTree<Key, Value>::type(Node<Key, Value>* splayer){
	std::string rrzz = "rrzz";
	std::string llzz = "llzz";
	std::string rlzz = "rlzz";
	std::string lrzz = "lrzz";

	Node<Key, Value>* splayParent = splayer->getParent();
	Key key = splayer->getKey();

	if(splayParent->getLeft() && splayParent->getRight()){//parent has two children
		if(splayParent->getParent()->getLeft() && !splayParent->getParent()->getRight()){//left left
			if(key == splayParent->getLeft()->getKey()){
				return rrzz;
			}
			else{
				return lrzz;
			}
		}
		else if(splayParent->getParent()->getRight() && !splayParent->getParent()->getLeft()){
			if(key == splayParent->getRight()->getKey()){
				return llzz;
			}
			else{
				return rlzz;
			}
		}
		else{
			if(splayParent->getParent()->getRight()->getKey() == splayParent->getKey())//splayp is right child
			{
				if(key == splayParent->getRight()->getKey()){
				return llzz;
				}
			else{
				return rlzz;
				}

			}
			else 
			{
				if(key == splayParent->getRight()->getKey()){
				return rrzz;
				}
				else{
				return rlzz;
				}

			}

		}

	}

	else if(splayParent->getLeft()){ //only left
		if(splayParent->getParent()->getRight() && !splayParent->getParent()->getLeft())
		{

			return rlzz;
		}
		else if(splayParent->getParent()->getLeft() && !splayParent->getParent()->getRight())//only left
		{
			return rrzz;

		}
		else//splay parent has 2 children
		{
			if(splayParent->getKey() == splayParent->getParent()->getLeft()->getKey()){
				return rrzz;
			}
			else{
				return rlzz;
			}

		}

	} 


	else{// only right
		if(splayParent->getParent()->getRight() && !splayParent->getParent()->getLeft())
		{

			return llzz;
		}
		else if(splayParent->getParent()->getLeft() && !splayParent->getParent()->getRight())//only left
		{
			return lrzz;

		}
		else//splay parent has 2 children
		{
			if(splayParent->getKey() == splayParent->getParent()->getLeft()->getKey()){
				return lrzz;
			}
			else{
				return llzz;
			}

		}

	}

}

template<typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value>* toSplay){

	Key key = toSplay->getKey();

	if(!toSplay) return;

	if(!toSplay->getParent() || key == this->mRoot->getKey()){

	
		return;
	}

	while(toSplay->getParent()){
		

		Node<Key, Value>* splayParent = toSplay->getParent();
	
		if(!splayParent->getParent()){

			
			if(splayParent->getRight() != NULL && splayParent->getRight()->getKey() == key){

				this->leftRotate(splayParent);
				toSplay->setParent(NULL);
				
			}
			else{
				
				this->rightRotate(splayParent);
				
				toSplay->setParent(NULL);
			}
		}
		else{
			std::string instruct = type(toSplay);

			if(instruct == "llzz"){ //left left zig zig
				this->leftRotate(splayParent->getParent());
				this->leftRotate(splayParent);

			}
			else if(instruct == "rrzz"){
				this->rightRotate(splayParent->getParent());
				this->rightRotate(splayParent);
			}
			else if(instruct == "lrzz"){ //left right zig zag;

				Node<Key, Value>* z = splayParent->getParent();
				this->leftRotate(splayParent);
	
				this->rightRotate(z);
			}
			else{ // riight left zig zag
				Node<Key, Value>* z = splayParent->getParent();
				this->rightRotate(splayParent);
				this->leftRotate(z);

			}
		
		}
	}

}


template<typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair){
	BinarySearchTree<Key, Value>::insert(keyValuePair);

	splay(this->internalFind(keyValuePair.first));
}



template<typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key){
	Node<Key, Value>* toFind = this->internalFind(key);

	if(toFind){
		Node<Key, Value>* toFindParent = toFind->getParent();
	
		BinarySearchTree<Key, Value>::remove(key);

		splay(toFindParent);
	}
	else{
		splay(LastVisited(key, this->mRoot, this->mRoot));
	}
}



template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::find(const Key& key){
	Node<Key, Value>* toFind = this->internalFind(key);
	if(toFind){
		splay(toFind);
		return BinarySearchTree<Key, Value>::find(this->internalFind(key)->getKey());
	}
	else{
		splay(LastVisited(key, this->mRoot, this->mRoot));

		return this->end();
	}
}



template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin(){
	Key toLook = this->getSmallestNode()->getKey();
	
	splay(this->getSmallestNode());

	return BinarySearchTree<Key, Value>::find(toLook);

}



template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax(){
	Key toLook = getLarge()->getKey();
	splay(getLarge());

	return BinarySearchTree<Key, Value>::find(toLook);

}



template<typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeaf(){
	remove(this->getSmallestNode()->getKey());
	
}


template<typename Key, typename Value>
void SplayTree<Key, Value>::deleteMaxLeaf(){
	remove(getLarge()->getKey());

}

template<typename Key, typename Value>
Node<Key,Value>* SplayTree<Key, Value>::getLarge(){
	return LargeHelp(this->mRoot);
}

template<typename Key, typename Value>
Node<Key,Value>* SplayTree<Key, Value>::LargeHelp(Node<Key, Value>* Root){
	if(Root->getRight() != NULL){
		return LargeHelp(Root->getRight());
	}
	else{
		return Root;
	}


}
