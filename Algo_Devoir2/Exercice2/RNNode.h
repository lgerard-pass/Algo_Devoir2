#pragma once
template <class T>
class TwoThreeFourNode;
template<typename T>
class RNNode
{
private:
	T data;
	bool red;
	RNNode<T>* leftchild;
	RNNode<T>* rightchild;
public:
	RNNode() {
		this->red = false;
		this->leftchild = NULL;
		this->rightchild = NULL;
	}
	RNNode(T data, bool isRed, RNNode<T>* leftchild = NULL, RNNode<T>* rightchild = NULL) {
		this->data = data;
		this->red = isRed;
		this->leftchild = leftchild;
		this->rightchild = rightchild;
	}
	virtual ~RNNode() {};
	bool isRed() {
		return this->red;
	}
	bool isBlack() {
		return !this->red;
	}
	bool isLeaf() {
		return (this->leftchild == NULL && this->rightchild == NULL);
	}
	T getData() {
		return this->data;
	}
	void setLeftChild(RNNode<T>* node) {
		this->leftchild = node;
	}
	void setRightChild(RNNode<T>* node) {
		this->right = node;
	}
	RNNode<T>* getLeftChild() {
		return this->leftchild;
	}
	RNNode<T>* getRightChild() {
		return this->rightchild;
	}
	TwoThreeFourNode<T>* getEquivalentTwoThreeFourNode() {
		TwoThreeFourNode<T>* newNode;
		if (this->isLeaf()) {
			newNode = new TwoThreeFourNode<T>();
			newNode->pushKey(this->data);
			return newNode;
		}
		else if (this->rightchild == NULL || this->leftchild == NULL) {
			return NULL;
		}
		else if (this->leftchild->isBlack() && this->rightchild->isBlack()) {
			newNode = new TwoThreeFourNode<T>();
			TwoThreeFourNode<T>* newLeftNode = this->leftchild->getEquivalentTwoThreeFourNode();
			TwoThreeFourNode<T>* newRightNode = this->rightchild->getEquivalentTwoThreeFourNode();
			newNode->pushKey(this->data);
			newNode->addChild(newLeftNode);
			newNode->addChild(newRightNode);
			return newNode;

		}
		else if (this->leftchild->isRed() && this->rightchild->isRed()) {
			newNode = new TwoThreeFourNode<T>();
			TwoThreeFourNode<T>* newFirstNode = this->leftchild->leftchild->getEquivalentTwoThreeFourNode();
			TwoThreeFourNode<T>* newSecondNode = this->leftchild->rightchild->getEquivalentTwoThreeFourNode();
			TwoThreeFourNode<T>* newThirdNode = this->rightchild->leftchild->getEquivalentTwoThreeFourNode();
			TwoThreeFourNode<T>* newFourthNode = this->rightchild->rightchild->getEquivalentTwoThreeFourNode();
			newNode->pushKey(this->data);
			newNode->pushKey(this->leftchild->data);
			newNode->pushKey(this->rightchild->data);
			newNode->addChild(newFirstNode);
			newNode->addChild(newSecondNode);
			newNode->addChild(newThirdNode);
			newNode->addChild(newFourthNode);
			return newNode;
		}
		else if (this->leftchild->isRed() && this->rightchild->isBlack()) {
			newNode = new TwoThreeFourNode<T>();
			TwoThreeFourNode<T>* newFirstNode = this->leftchild->leftchild->getEquivalentTwoThreeFourNode();
			TwoThreeFourNode<T>* newSecondNode = this->leftchild->rightchild->getEquivalentTwoThreeFourNode();
			TwoThreeFourNode<T>* newThirdNode = this->rightchild->getEquivalentTwoThreeFourNode();
			if (newThirdNode == NULL) {
				newThirdNode = new TwoThreeFourNode<T>();
				if (this->rightchild->leftchild == NULL) {
					newThirdNode->pushKey(this->rightchild->data);
					newThirdNode->pushKey(this->rightchild->leftchild->data);
				}
				else if (this->rightchild->rightchild == NULL) {
					newThirdNode->pushKey(this->rightchild->leftchild->data);
					newThirdNode->pushKey(this->rightchild->data);
				}
			}
			newNode->pushKey(this->leftchild->getData());
			newNode->pushKey(this->data);
			newNode->addChild(newFirstNode);
			newNode->addChild(newSecondNode);
			newNode->addChild(newThirdNode);
			return newNode;
		}
		else if (this->leftchild->isBlack() && this->rightchild->isRed()) {
			newNode = new TwoThreeFourNode<T>();
			TwoThreeFourNode<T>* newFirstNode = this->leftchild->getEquivalentTwoThreeFourNode();
			TwoThreeFourNode<T>* newSecondNode = this->rightchild->leftchild->getEquivalentTwoThreeFourNode();
			TwoThreeFourNode<T>* newThirdNode = this->rightchild->rightchild->getEquivalentTwoThreeFourNode();
			if (newFirstNode == NULL) {
				newFirstNode = new TwoThreeFourNode<T>();
				if (this->leftchild->leftchild == NULL) {
					newThirdNode->pushKey(this->rightchild->data);
					newThirdNode->pushKey(this->rightchild->leftchild->data);
				}
				else if (this->leftchild->rightchild == NULL) {
					newThirdNode->pushKey(this->rightchild->leftchild->data);
					newThirdNode->pushKey(this->rightchild->data);
				}
			}
			newNode->pushKey(this->data);
			newNode->pushKey(this->rightchild->data);
			newNode->addChild(newFirstNode);
			newNode->addChild(newSecondNode);
			newNode->addChild(newThirdNode);
			return newNode;
		}
	}
	template <typename U> friend std::ostream& operator<<(std::ostream& stream, const RNNode<U> node) {
		if (node.leftchild != NULL) {
			stream << *node.leftchild;
		}
		stream << node.data;
		if (node.rightchild != NULL) {
			stream << *node.rightchild;
		}
		return stream;
	}
};

