#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

struct Node	{
	double x;
	double y;
	struct Node* NW;
	struct Node* NE;
	struct Node* SE;
	struct Node* SW;
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

    //insert into the final quadrant found
    struct Node* insertPointInFinalQuadrant(struct Node* temp, struct Node* toBeInserted)	{
		if(temp->x < toBeInserted->x)	{
			if(temp->y < toBeInserted->y)	{
				temp->SW = toBeInserted;
			}
			else	{
			    temp->NW = toBeInserted;
			}
		}

		else if(temp->y < toBeInserted->y)	{
		    temp->SE = toBeInserted;
		}
		else	{
		    temp->NE = toBeInserted;
		}
	}

	bool insert(struct Node* toBeInserted)	{
			if(root == NULL)	{
				root = toBeInserted;
				return true;
			}

            struct Node *temp = root;
			while(temp != NULL && !equalCoordinates(temp, toBeInserted))	{
				struct Node* quadrant = getQuadrant(temp, toBeInserted);
				if(quadrant == NULL)    {
				    insertPointInFinalQuadrant(temp, toBeInserted);
				    temp = NULL;
				    return true;
				}
				else    {
				    temp = quadrant;
				}
			}

			return false;
	}

	bool insert(double x, double y)	{
		struct Node* temp = makeNode(x,y);
		return insert(temp);
	}

    void sampleInput()   {
        insert(4,4);
    	insert(3,3);
    	insert(2,2);
    	insert(1,1);
    	insert(0,0);
    	insert(5,6);
    	insert(7,8);
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

	PointQuadtree pointQuadtree;

	pointQuadtree.sampleInput();

	//traverse tree using level order traversal
	cout << "Level Order Traversal using BFS: ";
	pointQuadtree.levelOrderTraversal(root);


	return 0;
}
