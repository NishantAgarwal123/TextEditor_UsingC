#include<stdio.h>    
#include<stdlib.h>
#include<string.h>

struct Node
{
	char data;
	struct Node *next;
};
struct Node *TopUndo=NULL,*TopRedo=NULL;
char s[50]="\0", c;

struct Node* push(struct Node *Top, char value) //insertBegin
{
	struct Node *p;
	p=(struct Node*)malloc(sizeof(struct Node));
	p->data=value;
	p->next=Top;
	Top=p;
    return Top;
}
struct Node* pop(struct Node *Top)   //deleteBegin
{
	struct Node *p;
	if(Top==NULL) return NULL;
	p=Top;
	Top=Top->next;
	free(p);
	return Top;
}
char peek(struct Node *Top)
{
	if(Top==NULL) return '\0';
	return (Top->data);
}
void display(struct Node *Top)
{
	struct Node *ptr;
	ptr=Top;
	if(Top==NULL)
	{
		printf("Stack underflow\n");
		return ;
	}
	printf("Stack is:\n");
	while(ptr!=NULL)
	{
		printf("%c ",ptr->data);
		ptr=ptr->next;
	}
}
struct Node* destroy(struct Node *Top)
{
	while(Top!=NULL)
	{
		Top=pop(Top);
	}
	return Top;
}
void read()
{
	printf("%s\n", s);
}
void write()
{
    char temp[50];
	int i;
    printf("Type:");
    fflush(stdin);
	if(s[0]=='\0')
	{
        gets(s);
    	for(i=0;s[i]!=0;i++)
   		{
    	    TopUndo=push(TopUndo,s[i]);
    	}
	}
	else
	{
		gets(temp);
		strcat(s, temp);
        TopRedo=destroy(TopRedo);
		for(i=0;temp[i]!=0;i++)
   		{
    	    TopUndo=push(TopUndo,temp[i]);
    	}
	}
    //display(TopUndo);
    return ;
}
void undo()
{
    char x;
	x = peek(TopUndo);
	TopUndo=pop(TopUndo);
    TopRedo=push(TopRedo, x);
	s[strlen(s)-1] = '\0';
    read();
}
void redo()
{
    char x = peek(TopRedo);
	TopRedo=pop(TopRedo);
    TopUndo=push(TopUndo, x);
	strncat(s, &x, 1);
}
void save()
{
	int i=0;
    s[i]='\0';
	TopUndo=destroy(TopUndo);
	TopRedo=destroy(TopRedo);
}
void main()
{
	int i,choice;
	while(choice!=6)
	{
		printf("1.Write\n2.Read\n3.Undo\n4.Redo\n5.Save\n6.Exit\nEnter your choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:write();
			break;
			case 2:read();
			break;
			case 3:undo();
			break;
			case 4:redo();
			break;
			case 5:save();
			break;
			case 6:break;
			default:printf("Invalid Choice\n");
		}
	}
}