#include <iostream>
#include <cstdlib>
#define NULL 0

using namespace std;

class Node	{
public:
	double x;
	double y;
	Node* NW;
	Node* NE;
	Node* SE;
	Node* SW;

	//constructor
	Node(double x, double y):  x(x),y(y),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {}
};


class PointQuadtree	{
public:
	bool equalCoordinates(Node* temp, Node* toBeInserted)	{
		if(temp->x == toBeInserted->x && temp->y == toBeInserted->y)	{
			return true;
		}
		else	{
			return false;
		}
	}

	//return the successive quadrant where toBeInserted will be further inserted
	Node* getQuadrant(Node* temp, Node* toBeInserted)	{
		if(temp->x < toBeInserted->x)	{
			if(temp->y < toBeInserted->y)	{
				return temp->SW;
			}
			else	{
				return temp->NW;
			}
		}

		if(temp->y < toBeInserted->y)	{
			return temp->SE;
		}
		else	{
			return temp->NE;
		}


	}

	bool insert(Node* root, Node* toBeInserted)	{
			if(root == NULL)	{
				root = toBeInserted;
				return true;
			}

			Node* temp = root;
			while(temp != NULL && !equalCoordinates(temp, toBeInserted))	{
				Node* temp_ = temp;
				Node* quadrant = getQuadrant(temp, toBeInserted);
			}
	}

	bool insert(Node* root, double x, double y)	{
		Node* temp = new Node(x,y);
		return insert(root, temp);
	}


};

int main()	{
	cout<<"HI"<<endl;
	return 0;
}
