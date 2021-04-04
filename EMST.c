//Lab 5

// Kruskal's MST using union-find trees
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numVertices,numEdges;
int *parent, numTrees;
double *weight; 

//creating struct for edges
struct edge 
{
  int tail,head; 
  double weight;
};
typedef struct edge edgeType;
edgeType *edgeTab;

//creating struct for input
struct input
{
    int tail, head; 
}; 
typedef struct input inputType; 
inputType *inputTab; 


// Findint the root of tree containing x
int find(int x)
{
    int i,j,root;

    // Find the root
    for (i=x; parent[i]!=i; i=parent[i]);
    root=i;

    //make all of the nodes on the path
    for (i=x; parent[i]!=i; j=parent[i],parent[i]=root,i=j);

    return root;
}

void unionFunc(int i,int j)
{
    if (weight[i]>weight[j])
    {
        parent[j]=i;
        weight[i]+=weight[j];
    }
    else
    {
        parent[i]=j;
        weight[j]+=weight[i];
    }
    numTrees--;
}

//manipulated to be  able to handle doubles
int weightAscending(const void* xin, const void* yin)
{
    edgeType *x,*y;

    x=(edgeType*) xin;
    y=(edgeType*) yin;
    
    if(x->weight > y->weight)
    {
        return 1;
    }
    else if(x->weight < y->weight)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int i; 
    double MSTweight=0;
    int root1,root2;

    //taking in iunput of number of vertices
    scanf("%d",&numVertices);
    //holding in the number of edges with provided formula
    numEdges = (numVertices * (numVertices-1)/2); 

    //initializing dynamic arrays
    inputTab=(inputType*) malloc(numEdges*sizeof(inputType)); //added initialization of input table
    edgeTab=(edgeType*) malloc(numEdges*sizeof(edgeType));
    parent=(int*) malloc(numVertices*sizeof(int));
    weight=(double*) malloc(numVertices*sizeof(double));

    if (!edgeTab || !parent || !weight)
    {
        printf("error 2\n");
        exit(0);
    }

    //for loop that scans in the input tail and the input head
    for(i = 0; i < (numVertices*2); i++)
    {
        scanf("%d %d", &inputTab[i].tail, &inputTab[i].head); 
    }

    //initializing variables
    int count = 1; 
    int position = 0; 
    double weightTemp; 
    int j; 

    //echo print
    for(i = 0; i < numVertices; i++)
    {
        printf("%d %d %d\n", i, inputTab[i].tail, inputTab[i].head); 
    }

    //filling up the edge table

    //outer loop will check the tails
    for(i = 0; i < numVertices; i++)
    {
        //inner loop will check the heads
        for(j = count; j < numVertices; j++)
        {
            //storing tail 
            edgeTab[position].tail = i; 
            
            //storing head
            edgeTab[position].head = j; 

            //weight, calculated by using the distance formula
            weightTemp = sqrt(pow((inputTab[j].tail-inputTab[i].tail),2)+pow((inputTab[j].head-inputTab[i].head),2));

            //storing weight 
            edgeTab[position].weight = weightTemp; 

            position++; 
        }
        count++; 
    }

    //forloop used to set parents and weight
    for (i=0;i<numVertices;i++)
    {
        parent[i]=i;
        weight[i]=1;
    }

    numTrees=numVertices;
    qsort(edgeTab,numEdges,sizeof(edgeType),weightAscending);

    //resetting count variable
    count = 0; 

    //For loop utilized to print out if the root was included
    for (i=0;i<numEdges;i++)
    {
        //checks if it will exit out of for loop
        if(count == numVertices-1)
        {
            break;
        }

        root1=find(edgeTab[i].tail);
        root2=find(edgeTab[i].head);
        if (root1==root2)
            printf("%d %d \t %.3lf discarded\n",edgeTab[i].tail,edgeTab[i].head,
            edgeTab[i].weight);
        else
        {
            printf("%d %d \t %.3lf included\n",edgeTab[i].tail,edgeTab[i].head,
            edgeTab[i].weight);
            MSTweight+=edgeTab[i].weight;
            unionFunc(root1,root2);
            count++; 
        }
    }

    //checking if MST does not exist
    if (numTrees!=1)
    {
        printf("MST does not exist\n");
    }

    printf("Sum of weights of spanning edges \t %.3lf\n",MSTweight);
    
    //Free memory
    free(edgeTab);
    free(inputTab); 
    free(parent);
    free(weight);
}
