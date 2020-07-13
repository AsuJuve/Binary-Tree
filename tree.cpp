#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *rig;
    Node *lef;
    Node *dad;
};

void menu();
Node *createNode(int,Node *);
void addNode(Node *&, int, Node *);
void showTree(Node *,int);
bool search(Node *&, int);
void showPreOrder(Node *&);
void showInOrder(Node *&);
void showPostOrder(Node *&);
void delet(Node *,int);
void deleteNode(Node *);
Node* minor(Node *);
void replace(Node *, Node *);
void destroy(Node *);

    Node *tree = NULL;

int main(){
    menu();
    return 0;
}

void menu(){
    system("cls");
    cout << "\t.:Menu:.\n1.Add new node\n2.Show tree\n3.Search node\n4.Show PreOrder\n5.Show InOrder\n6.Show PostOrden\n7.Delete a node\n8.Leave\n\tOption: ";
    int opt, n, cont = 0;
    cin>>opt;
    switch (opt)
    {
    case 1:
        cout<<"\n\tWrite the value of the new node: ";
        cin>>n;
        addNode(tree,n,NULL);
        break;
    case 2:
        cout << "\nActual tree: \n";
        showTree(tree,cont);
        system("pause");
        menu();
        break;
    case 3:
        cout << "\nWrite th node to search: \n";
        cin >> n;
        if (search(tree, n) == true)
        {
            cout << "\n\tThe node is in the tree" << endl;
        }else
        {
            cout << "\n\tThe node is not in the tree" << endl;
        }
        system("pause");
        menu();
        break;
    case 4:
        cout << "\nActual tree in PreOrder: \n\t";
        showPreOrder(tree);
        system("pause");
        menu();
        break;
    case 5:
        cout << "\nActual tree in InOrder: \n\t";
        showInOrder(tree);
        system("pause");
        menu();
        break;
    case 6:
        cout << "\nActual tree in PostOrder: \n\t";
        showPostOrder(tree);
        system("pause");
        menu();
        break;
    case 7:
        cout << "\nWrite the node to be deleted: \n\t";
        cin>>n;
        delet(tree,n);
        system("pause");
        menu();
        break;
    case 8:
        system("cls");
        cout << "\n\tLeaving... ";
        return;
        break;
    default:
        cout<<"\nInvalid option";
        system("pause");
        menu();
        break;
    }
}
void replace(Node *tree, Node *new_node){
    if (tree->dad)
    {
        if (tree->data == tree->dad->lef->data)
        {
            tree->dad->lef = new_node;
        }
        else if (tree->data == tree->dad->rig->data)
        {
            tree->dad->rig = new_node;
        }
        
        if (new_node)
        {
            new_node->dad = tree->dad;
        }
    }
    
}

Node* minor(Node *tree){
    if (tree==NULL)
    {
        return NULL;
    }
    if (tree->lef)
    {
        return minor(tree->lef);
    }else
    {
        return tree;
    }
}
void destroy(Node *deletedNode){
    deletedNode->lef = NULL;
    deletedNode->rig = NULL;
    delete deletedNode;
}

void deleteNode(Node *deletedNode){
    if (deletedNode->lef && deletedNode->rig)
    {
        Node *smaller = minor(deletedNode->rig);
        deletedNode->data = smaller->data;
        deleteNode(smaller);
    }
    else if (deletedNode->lef)
    {
        replace(deletedNode,deletedNode->lef);
        destroy(deletedNode);
    }
    else if (deletedNode->rig)
    {
        replace(deletedNode, deletedNode->rig);
        destroy(deletedNode);
    }
    else
    {
        replace(deletedNode,NULL);
        destroy(deletedNode);
    }
    
}

void delet(Node *tree,int n){
    if (tree == NULL)
    {
        return;
    }
    else if (n < tree->data)
    {
        delet(tree->lef,n);
    }
    else if (n < tree->data)
    {
        delet(tree->rig, n);
    }
    else
    {
        deleteNode(tree);
        cout<<"\n\tThe node has been DELETED"<<endl;
    }
    
}

void showPostOrder(Node *&tree)
{
    if (tree == NULL)
    {
        return;
    }
    else
    {
        showPreOrder(tree->lef);
        showPreOrder(tree->rig);
        cout << tree->data << " - ";
    }
}

void showInOrder(Node *&tree)
{
    if (tree == NULL)
    {
        return;
    }
    else
    {
        showPreOrder(tree->lef);
        cout << tree->data << " - ";
        showPreOrder(tree->rig);
    }
}

void showPreOrder(Node *&tree){
    if (tree == NULL)
    {
        return;
    }else
    {
        cout<<tree->data<<" - ";
        showPreOrder(tree->lef);
        showPreOrder(tree->rig);
    }
}

Node *createNode(int n,Node *dad){
    Node *new_node = new Node();
    new_node->data = n;
    new_node->lef = NULL;
    new_node->rig = NULL;
    new_node->dad = dad;
    return new_node;
}

bool search(Node *&tree, int n){
    if (tree==NULL)
    {
        return false;
    }
    if (tree->data == n)
    {
        return true;
    }
    if (n < tree->data)
    {
        search(tree->lef, n);
    }else
    {
        search(tree->rig,n);
    }
}

void addNode(Node *&tree, int n, Node *dad){
    Node *new_node = createNode(n,tree);
    if (tree != NULL)
    {
        int value = new_node->data;
        if (tree->data > value)
        {
            addNode(tree->lef,value,tree);
        }else
        {
            addNode(tree->rig, value,tree);
        }
    }else
    {
        tree = new_node;
        cout << "\tThe node with the value: " << new_node->data << " has been ADDED to the tree"<<endl;
        system("pause");
        menu();
    }
}

void showTree(Node *tree,int cont){
    if (tree == NULL)
    {
        return;
    }else
    {
        showTree(tree->rig, cont+1);
        for (int i = 0; i < cont; i++)
        {
            cout<<"     ";
        }
        cout<<tree->data<<endl;
        showTree(tree->lef,cont+1);   
    }   
}
