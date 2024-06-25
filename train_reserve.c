#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct TreeNode
{
    int pid;
    char name[20];
    struct TreeNode *left;
    struct TreeNode *right;
    
}TreeNode;

TreeNode * Insert_tree(TreeNode *root,TreeNode *add)
{
    if(!root)
        return add;
    else if( root->pid >add->pid)
       root->left=Insert_tree(root->left,add);
    else
        root->right=Insert_tree(root->right,add);

    return root;
}
TreeNode * finder(TreeNode *root,int id)
{
    if (!root || root->pid==id)
        return root;
    else if (root->pid>id)
        return finder(root->left,id);

    return finder(root->right,id);
}
TreeNode * MinNode(TreeNode *root)
{
    while(root && root->left)
        root=root->left;
    return root;
}
TreeNode * Delete_from_bst(TreeNode *root,int id)
{  if(!root)
        return root;

   if(root->pid>id)
        root->left=Delete_from_bst(root,id);
   
   else if(root->pid<id)
        root->right=Delete_from_bst(root,id);
   
   else
   {
     //printf("Patient's %d of name %s is suffering from %s",root->id,root->name,root->illness);
    if(root->left==NULL)
        {
            TreeNode * temp=root->right;
            free(root);
            
            return temp;
        }
    if(root->right==NULL)
        {
            TreeNode * temp=root->left;
            free(root);
            return temp;
        }
    TreeNode * Min=MinNode(root->right);
    root->pid=Min->pid;
    
    strcpy(root->name,Min->name);
    root->right=Delete_from_bst(root->right,Min->pid);
    
    


   }
   return root;
}
typedef struct Node
{
 struct Train *train;
 struct Node *next;

}Node;

typedef struct Hashmap
{
 struct Node * head;
}Hashmap;

typedef struct Train
{
    
    char name[20];
    int capacity;
    int currently_booked;
    TreeNode *root;

}Train;

// void Display_node(Node * head)
// {
   
// }
void Display(Hashmap * hashmap,int n)
{
    
    
    printf("Train_name\tTrain Capacity\tTrain Booked\n");
    for (int i=0;i<n;i++)
    {    Node *start=hashmap[i].head;
    while (start)
    {
     printf("%s\t%d\t%d\n",start->train->name,start->train->capacity,start->train->currently_booked);
     start=start->next;
    }
    }

}

TreeNode * CreateTreeNode(int pid,char *name)
{
    TreeNode * new1=(TreeNode*)malloc(sizeof(TreeNode));
    new1->pid=pid;
    strcpy(new1->name,name);
    new1->left=NULL;
    new1->right=NULL;
    return new1;
}




int Hash_function(char *string,int Total_trains)
{
    unsigned long int value = 0;
    unsigned int i = 0;
    

    // Convert string to an integer
   while(string[i]!='\0')
   {
        value = value * 37 + string[i];
        i+=1;
    }

    value = value % Total_trains;
    return value;
}


Train * NewTrain(char *train_name,int capacity)
{
    Train * new1=(Train*)malloc(sizeof(Train));
    strcpy(new1->name,train_name);
    new1->capacity=capacity;
    new1->currently_booked=0;
    new1->root=NULL;
    return new1;
}
Node * NewNode(char *train_name,int capacity)
{
    Node*new1=(Node*)malloc(sizeof(Node));
    new1->next=NULL;
    new1->train=NewTrain(train_name,capacity);
    return new1;
}
Hashmap * CreateNew(int Total_Trains)
{
    Hashmap * hashmap= (Hashmap*)malloc(sizeof(Hashmap)*Total_Trains);
    for(int i=0;i<Total_Trains;i++)
        hashmap[i].head=NULL;

    return hashmap;
}
Train * Find(Hashmap* hashmap,int index,char*train_name)
{
    Node *start=hashmap[index].head;
    while(start)
    {
      if(strcmp(start->train->name,train_name)==0)
        return start->train;
      start=start->next;
    
    }
    return NULL;
}
void Insert_train_name(Hashmap * hashmap,char *train_name,int capacity,int Total_trains)
{
   int index=Hash_function(train_name,Total_trains);
   printf("%d",index);
   Node* Start=hashmap[index].head;
   if(!Start)
        hashmap[index].head=NewNode(train_name,capacity);
   
   else
   {
    while(Start->next)
        Start=Start->next;
    
    Start->next=NewNode(train_name,capacity);
   }

}
int Get_availspace_train(Hashmap* hashmap,int index,char*train_name)
{
    Node *start=hashmap[index].head;
    while(start)
    {
      if(strcmp(start->train->name,train_name)==0)
        return start->train->capacity-start->train->currently_booked;
    start=start->next;
    }
    return 0;
    
}

int isSpaceAvailable(Hashmap *hashmap,char *train_name,int Total_trains)
{
    int index=Hash_function(train_name,Total_trains);
     return Get_availspace_train(hashmap,index,train_name);
}
void Cancel_ticket(Hashmap*hashmap,char *train_name,int pid,int Total_trains)
{
    int index=Hash_function(train_name,Total_trains);
    Train * train =Find(hashmap,index,train_name);
    if (finder(train->root,pid))
    {
        train->root=Delete_from_bst(train->root,pid);
        train->currently_booked-=1;
        printf("Currently booked reduced by 1");
    }
}
void BookSeats(Hashmap *hashmap,char *train_name,int Total_trains,int passenger_id,char *pname)
{
     int index=Hash_function(train_name,Total_trains);
     Train * train=Find(hashmap,index,train_name);
     TreeNode *New1=CreateTreeNode(passenger_id,pname);
     train->root=Insert_tree(train->root,New1);
     train->currently_booked+=1;



}


int main()
{ 
    int n;
    printf("Enter the Total Number of Trains");
    scanf("%d",&n);
    Hashmap * hashmap=CreateNew(n);
    char name[20];
    int capacity;
    int seats;
    int passenger_id;
    char pname[20];
    for(int i=0;i<n;i++)
    {
        printf("Enter the %d th Train name :",i+1);
        scanf("%s",name);
        printf("Enter the %d th  Train Capacity :",i+1);
        scanf("%d",&capacity);
        Insert_train_name(hashmap,name,capacity,n);
    }
        int flag=1;
        int inputs;
        int ID=1;
        while(flag)
        {
            printf("Enter 1 to book an ticket\n");
            printf("Enter 2 to cancel the ticket\n");
            printf("Enter 3 to display The trains\n");

            scanf("%d",&inputs);
            switch (inputs)
            {
            case 1:
                printf("Enter the Train_name :");
                scanf("%s",&name);
               
                if(isSpaceAvailable(hashmap,name,n)>0)
                {  
                      printf("enter the Passenger id:");
                      scanf("%d",&passenger_id);
                      printf("enter the passenger name");
                      scanf("%s",pname);
                      BookSeats(hashmap,name,n,passenger_id,pname);
                      printf("Inserted succesfully");

                }
                else
                    printf("No tickets available");
            break;
            case 2:
              printf("Enter the Train_name :");
                scanf("%s",&name);
              printf("enter the Passenger id:");
                scanf("%d",&passenger_id);
              Cancel_ticket(hashmap,name,passenger_id,n);
              break;
            case 3:
                Display(hashmap,n);
                break;        
            
            default:
                break;
            }
        }

    return 0;
    }

    
