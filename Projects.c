#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct TreeNode
{
    int id;
    char name[20];
    char illness[20];
    struct TreeNode *left;
    struct TreeNode *right;
    
}TreeNode;
typedef struct Node
{
    TreeNode * patient;
    struct Node * next;
} Node;

typedef struct Queue
{
  Node *front;
  Node *rear;

} Queue;
TreeNode * Insert_tree(TreeNode *root,TreeNode *add)
{
    if(!root)
        return add;
    else if( root->id >add->id)
       root->left=Insert_tree(root->left,add);
    else
        root->right=Insert_tree(root->right,add);

    return root;
}
TreeNode * finder(TreeNode *root,int id)
{
    if (!root || root->id==id)
        return root;
    else if (root->id>id)
        return finder(root->left,id);

    return finder(root->right,id);
}
Node *Create_Node(int id,char *name,char*illness)
{
  Node *new1=  (Node*)malloc(sizeof(Node));
  new1->patient=(TreeNode*)malloc(sizeof(TreeNode));
  new1->patient->id=id;
  new1->next=NULL;
  strcpy(new1->patient->illness,illness);
  strcpy(new1->patient->name,name);
  new1->patient->left=NULL;
  new1->patient->right=NULL;
  return new1;
}
void Enqueue(Queue *queue,Node * new1)
{
    if(!queue->front)
    {
        queue->front=new1;
        queue->rear=new1;

    }
    else
    {
        queue->rear->next=new1;
        queue->rear=new1;
    }

}
int isEmpty(Queue *queue)
{
    return queue->front==NULL;
}
TreeNode* Deque(Queue * queue)
{
    if(isEmpty(queue))
    {
        printf("Queue is empty and cannot be popped from it");
        return NULL;
    }
    else
    {
        if(queue->front==queue->rear)
        {
            TreeNode * temp=queue->front->patient;
            free(queue->front);
            queue->front=NULL;
            queue->rear=NULL;
            return temp;
            
        }
        else
        {
            TreeNode * temp=queue->front->patient;
            Node * ptr=queue->front;
            queue->front=queue->front->next;
            free(ptr);
            return temp;

        }
    }
}
int Front(Queue * queue)
{
    if(isEmpty(queue))
        return -1;
    return queue->front->patient->id;
}
TreeNode * MinNode(TreeNode *root)
{
    while(root && root->left)
        root=root->left;
    return root;
}
void Display_details(Queue *q)
{
 Node * n=q->front;
 if(!n)
    printf("No details to display\n");
else 
{
    printf("Patient_id\tpatient_name\tpatient_illness\n");
    while(n)
    {
        printf("%d\t%s\t%s\n",n->patient->id,n->patient->name,n->patient->illness);
        n=n->next;
    }
}




}
TreeNode * Delete_from_bst(TreeNode *root,int id)
{  if(!root)
        return root;

   if(root->id>id)
        root->left=Delete_from_bst(root,id);
   
   else if(root->id<id)
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
    root->id=Min->id;
    strcpy(root->illness,Min->illness);
    strcpy(root->name,Min->name);
    root->right=Delete_from_bst(root->right,Min->id);
    
    


   }
   return root;
}
void Insert(Queue * queue,TreeNode ** root,int id,char *name,char *illness)
{
   Node *new1=Create_Node(id,name,illness);

   *root=Insert_tree(*root,new1->patient);
   Enqueue(queue,new1);


}
void delete_node(Queue* queue,TreeNode **root)
{   int id=Front(queue);
    if(id!=-1)
    {
        TreeNode * temp=    Deque(queue);
       
        
            printf("Patient's %d of name %s is suffering from %s",temp->id,temp->name,temp->illness);
            TreeNode * temp1=*root;
        temp1=Delete_from_bst(temp1,id);
       
        *root=temp1;
        
        

        

        
        
        
        
           
    }
    else
        printf("Queue is Empty");
    
    
    
   

}
Queue * Create_Queue()
{
  Queue *Q=(Queue*)malloc(sizeof(Queue));
  Q->front=NULL;
  Q->rear=NULL;
}
int main()
{

    TreeNode *root=NULL;
    Queue *queue=Create_Queue();
    int choice;
    char name[20];
    char illness[20];
    int id;
    TreeNode * temp;
    int flag=1;
    while(flag)
    {
        printf("\nHospital Management System\n");
        printf("1. Add Patient\n");
        printf("2. Display Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient in order\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
                printf("Enter patient ID: ");
                scanf("%d", &id);
                if(!finder(root,id))
                {
                    printf("Enter patient name: ");
                    scanf("%s", name);
                    printf("Enter patient illness: ");
                    scanf("%s", illness);
                    Insert(queue,&root,id,name,illness);
                }
                else
                    printf("User id already exists");

        
            break;
        case 2:
          
           Display_details(queue);
           break;
        case 3:
           printf("Enter the id of the patient: ");
           scanf("%d",&id);
           TreeNode *find=finder(root,id);
           if(find)
                 printf("Patient's %d of name %s is suffering from %s",find->id,find->name,find->illness);
           else
                printf("No patient with corresponding id :",id);

            break;
        case 4:
           delete_node(queue,&root);
            // if (temp)
            // printf("Patient's %d of name %s is suffering from %s",temp->id,temp->name,temp->illness);
            


            break;

        case 5:
            printf("bye See u Next Time");
            flag=0;
            break;
            

        default:
            printf("Invalid Number Could you please enter a valid number");
            break;
        }
    }
}