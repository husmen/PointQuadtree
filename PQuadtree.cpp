#include <iostream>
#include <cstdlib>
#include <queue>
#define NULL 0

using namespace std;

struct Node	{
	double x;
	double y;
	Node* NW;
	Node* NE;
	Node* SE;
	Node* SW;

	//constructor
	//Node(double x, double y):  x(x),y(y),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {}
} ;
struct Node* root=NULL;

struct Node* makeNode(double x, double y)	{
	struct Node* temp = new Node;
	temp->x = x;
	temp->y = y;
	temp->NW = NULL;
	temp->NE = NULL;
	temp->SE = NULL;
	temp->SW = NULL;
	return temp;
}


class PointQuadtree	{
public:

	bool equalCoordinates(struct Node* temp, struct Node* toBeInserted)	{
		if(temp->x == toBeInserted->x && temp->y == toBeInserted->y)	{
			return true;
		}
		else	{
			return false;
		}
	}

	//return the successive quadrant where toBeInserted will be further inserted
	struct Node* getQuadrant(struct Node* temp, struct Node* toBeInserted)	{
		if(temp->x < toBeInserted->x)	{
			if(temp->y < toBeInserted->y)	{
				return temp->SW;
			}
			else	{
				return temp->NW;
			}
		}

		else if(temp->y < toBeInserted->y)	{
			return temp->SE;
		}
		else	{
			return temp->NE;
		}
	}

	bool insert(struct Node* toBeInserted)	{
			if(root == NULL)	{
				root = toBeInserted;
				return true;
			}

            struct Node *temp = root;
			while(temp != NULL && !equalCoordinates(temp, toBeInserted))	{
				cout<<temp->x;
				temp = getQuadrant(temp, toBeInserted);
				if(temp == NULL)    {
				    temp = toBeInserted;
				    return true;
				}
			}

			return false;
	}

	bool insert(double x, double y)	{
		struct Node* temp = makeNode(x,y);
		return insert(temp);
	}

	queue<struct Node*> q;
	void levelOrderTraversal(struct Node* temp) {
	    if(q.empty())
	        q.push(temp);

	    while(!q.empty())   {
	    	struct Node* popped = q.front();
	        q.pop();
	        cout << "(" << popped->x <<", " << popped->y << ") ";
	        if(popped->NW != NULL)
	            q.push(popped->NW);
	        if(popped->NE != NULL)
	            q.push(popped->NE);
	        if(popped->SE != NULL)
	        	q.push(popped->SE);
	        if(popped->SW != NULL)
	        	q.push(popped->SW);
	    }
	}

};

int main()	{
	cout<<"HI"<<endl;
	PointQuadtree pointQuadtree;
	//struct Node* root = NULL;

	pointQuadtree.insert(4,4);
	cout<<endl;
	pointQuadtree.insert(3,3);
	cout<<endl;
	pointQuadtree.insert(2,2);
	cout<<endl;
	pointQuadtree.insert(1,1);
	cout<<endl;
	pointQuadtree.insert(0,0);
	cout<<endl;
	pointQuadtree.insert(5,6);

	//traverse tree using level order traversal
	pointQuadtree.levelOrderTraversal(root);


	return 0;
}
