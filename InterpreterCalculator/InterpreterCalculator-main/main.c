#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef union
{
    float fData;
    char  cData;
} Item;

typedef struct
{
    Item items[100];
    int top;
} Stack;

Stack * initialize()
{
    Stack *s = malloc(sizeof(Stack));
    s->top = 0;
    return s;
}

int isEmpty(Stack *s)
{
    if(s->top == 0)
        return 1;
    else
        return 0;
}

Item top(Stack *s)
{
    return s->items[s->top -1];;
}

Item pop(Stack *s)
{
    s->top --;
    return s->items[s->top];
}

void push(Stack *s, Item val)
{
    s->items[s->top] = val;
    s->top ++;
}

int priority(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 0;
    case '*':
    case '/':
    case '%':
        return 1;
    case '^':
        return 2;
    case '(':
        return 3;
    }
}

int isnumber2(char str[])
{
    int i,flag;
    for(i=0; i<strlen(str); i++)
    {
        flag=0;
        if(isdigit(str[i]) || str[i]=='.')
            flag = 1;
        if(flag==0)
            return 0;
    }
    return 1;
}

int isnumber (char str[])
{

    int i;
    for(i=0; i<strlen(str); i++)
    {
        {
            if(isdigit(str[i]))
                return 1;
        }
    }
    return 0;
}

int isOperator(char *y)
{
    if(y[0]=='+')
        return 1;
    else if(y[0]=='-')
        return 2;
    else if(y[0]=='^')
        return 3;
    else if(y[0]=='*')
        return 4;
    else if(y[0]=='/')
        return 5;
    else if(y[0]=='%')
        return 6;
    else if(y[0]=='(')
        return 7;
    else if(y[0]==')')
        return 8;
    else
        return 0;
}

int isOperator2(char y)
{
    if(y=='+'|| y=='-'|| y=='*'||y=='/'|| y=='%'|| y=='^' || y=='('|| y==')')
        return 1;
    else
        return 0;
}

void infixToPostfix(char* infix, char* postfix)
{
    int i,count=0;
    Stack *s = initialize();
    Item x;
    char a[2];
    char *token=strtok(infix," ");
    while(token!=NULL)
    {
        if(isnumber(token))
        {
            strcat(postfix,token);
            strcat(postfix," ");
        }
        else
        {
            if (isOperator(token))
            {
                x.cData=token[0];
                if(isEmpty(s))
                    push(s,x);
                else if(top(s).cData == '(' && token[0]!=')')
                    push(s,x);
                else if(token[0] == ')')
                {
                    while(!isEmpty(s) && top(s).cData!='(')
                    {
                        a[0]=pop(s).cData;
                        a[1]='\0';
                        strcat(postfix,a);
                        strcat(postfix," ");
                    }
                    pop(s);
                }
                else
                {
                    while(!isEmpty(s) && top(s).cData!='(' && priority(top(s).cData)>=priority(token[0]))
                    {
                        a[0]=pop(s).cData;
                        a[1]='\0';
                        strcat(postfix,a);
                        strcat(postfix," ");
                    }
                    push(s,x);
                }
            }
            else
            {
                printf("Wrong symbols !");
                exit(0);
            }
        }
        token=strtok(NULL," ");
    }
    while(!isEmpty(s))
    {
        a[0]=pop(s).cData;
        a[1]='\0';
        strcat(postfix,a);
        strcat(postfix," ");
    }
}

float evaluate(char c,float op1,float op2)
{
    if(c=='+')
        return op1+op2;
    if(c=='-')
        return op1-op2;
    if(c=='*')
        return op1*op2;
    if(c=='/')
        return op1/op2;
    if(c=='^')
        return pow(op1,op2);
}

float evaluatePostfix(char* postfix)
{
    Stack *s=initialize();
    Item x;
    char a[2];
    float op1,op2,num;
    char *token=strtok(postfix," ");
    while(token != NULL)
    {
        if(isnumber(token))
        {
            x.fData=atof(token);
            push(s,x);
        }
        else
        {
            op2 = pop(s).fData;
            op1 = pop(s).fData;
            num = evaluate(token[0],op1,op2);
            x.fData=num;
            push(s,x);
        }
        token=strtok(NULL," ");
    }
    num = pop(s).fData;
    return num;
}

typedef struct
{
    char *key;
    float value;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(char *key,float value)
{
    Node* n = malloc(sizeof(Node));
    n->key = malloc(30);
    strcpy(n->key,key);
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node* search(Node* root,char *key)
{
    if(root == NULL)
        return 0;
    else if (strcasecmp(key,root->key) == 0)
        return root;
    else if(strcasecmp(key,root->key) < 0)
        return search(root->left,key);
    else
        return search(root->right,key);
}

Node* put(Node* node, char *key,float value)
{
    if(search(node,key)!=0)
    {
        search(node,key)->value = value;
    }
    else
    {
        if(node == NULL)
            return newNode(key,value);
        if(strcasecmp(key,node->key) < 0)
            node->left = put(node->left,key,value);
        else if(strcasecmp(key,node->key) > 0)
            node->right = put(node->right,key,value);
        return node;
    }
}



int isKey (char str[])
{
    int i,flag;
    for(i=0; i<strlen(str); i++)
    {
        flag=0;

        if(isalpha(str[i]))
            flag = 1;
        if(flag==0)
            return 0;
    }
    return 1;
}

float replace(Node *root,char *infix)
{
    char infixFinal[250] = "";
    char postfixFinal[250] = "";
    float value;
    char temp[15] = "";

    char *token = strtok(infix," ");
    while(token!=NULL)
    {
        if(isnumber2(token))
            strcat(infixFinal,token);
        else if(isOperator(token) && strlen(token)==1)
            strcat(infixFinal,token);
        else if(isKey(token))
        {
            value = search(root,token)->value;
            gcvt(value,10,temp);
            strcat(infixFinal,temp);
        }

        else if(token[0]=='-' && strlen(token)>1)
        {

            int i;
            char temp2[50]="";
            for(i=1; i<strlen(token); i++)
            {
                temp2[i-1]=token[i];
            }

            if(isnumber2(temp2))
            {
                strcat(infixFinal,"-");
                strcat(infixFinal,temp2);
            }
            else if(isKey(temp2))
            {
                value = search(root,temp2)->value;
                gcvt(value,10,temp);
                strcat(infixFinal,"-");
                strcat(infixFinal,temp);
            }

        }
        else
        {
            printf("Error 1");
            exit(0);
        }
        strcat(infixFinal," ");

        token = strtok(NULL," ");

    }

    infixToPostfix(infixFinal,postfixFinal);
    return evaluatePostfix(postfixFinal);

}

void validate(char *infix2)
{
    char infix[250];
    strcpy(infix,infix2);
    int flag = 0;
    int i;
    int open=0;
    int closed=0;
    int flagB=0;
    int flag22=0;

    if(isOperator2(infix[0]) && infix[0]!='(' && infix[0]!='-')
    {
        printf("Invalid Expression");
        exit(0);
    }

    for(i=0; i<strlen(infix); i++)
    {
        if(infix[i]=='(')
        {
            open++;
            flagB++;
        }
        if(infix[i]==')')
        {
            closed++;
            flagB--;
        }
        if(flagB<0)
        {
            printf("Invalid Expression");
            exit(0);
        }

    }
    printf("%d %d %d \n",open,closed,flagB);
    if(open != closed || flagB!=0)
    {
        printf("Invalid Expression");
        exit(0);
    }

    char *token = strtok(infix," ");



    while(token!=NULL)
    {
        printf("%s\n",token);
        if((isKey(token) || (token[0]=='-' && isalpha(token[1]))) && flag22==0)
        {
            flag = 0;
            flag22=1;
        }
        else if((isnumber2(token) || (token[0]=='-' && isdigit(token[1]))) && flag22==0)
        {
            flag = 0;
            flag22=1;
        }
        else if(isOperator(token))
        {
            flag22=0;
            if(token[0]=='+' && (flag==8 || flag==0))
                flag = 1;
            else if(token[0]=='-' && (flag==8 || flag==0))
                flag = 2;
            else if(token[0]=='^' && (flag==8 || flag==0))
                flag = 3;
            else if(token[0]=='*' && (flag==8 || flag==0))
                flag = 4;
            else if(token[0]=='/' && (flag==8 || flag==0))
                flag = 5;
            else if(token[0]=='%' && (flag==8 || flag==0))
                flag = 6;
            else if(token[0]=='(' && flag!=0)
                flag = 7;
            else if(token[0]==')' && flag==0)
                flag = 8;
            else
            {
                printf("Invalid Expression");
                exit(0);
            }
        }
        else
        {
            printf("Invalid Expression");
            exit(0);
        }
        token=strtok(NULL," ");
    }
    if(flag!=0 && flag!=8)
    {
        printf("Invalid Expression");
        exit(0);
    }

}

void replaceWithoutSpaces(char *infix)
{
    int i,j;
    char spaces[250]="";
    char temp[50]="";
    int flag = 0;
    int flagNegative = 0;
    for(i=0; i<strlen(infix); i++)
    {

        if(isdigit(infix[i]))
        {
            flagNegative=1;
            for(j=i; j<strlen(infix); j++)
            {

                if(isdigit(infix[j]) || infix[j]=='.')
                {
                    flag = 0;
                    temp[0]=infix[j];
                    strcat(spaces,temp);
                }
                else
                    break;

            }
            strcat(spaces," ");
            i = j-1;
        }
        else if(isalpha(infix[i]))
        {
            flagNegative=1;
            for(j=i; j<strlen(infix); j++)
            {
                if(isalpha(infix[j]))
                {
                    flag = 0;
                    temp[0]=infix[j];
                    strcat(spaces,temp);
                }
                else
                    break;
            }
            strcat(spaces," ");
            i = j-1;
        }
        else if(isOperator2(infix[i]) && flagNegative==0)
        {
            flagNegative=1;
            temp[0]=infix[i];
            strcat(spaces,temp);
        }
        else if(isOperator2(infix[i]))
        {
            flagNegative=1;
            temp[0]=infix[i];
            strcat(spaces,temp);
            if(flag==0 || infix[i]!='-')
            {
                strcat(spaces," ");
                flag=1;
            }
        }
//        printf("%s\n",spaces);
    }
    strcpy(infix,spaces);

}


Node* ReadFromFile(Node *root)
{

    FILE *f1;
    f1=fopen("src.txt","r");
    if(f1==NULL)
    {
        printf("Error Reading File");
        exit(0);
    }
    char key[30] = "";
    char temp[30] = "";
    char infix[250] = "";
    int count;
    int flag;
    float value;


    while(!feof(f1))
    {
        char infix2[250] = "";
        fscanf(f1,"%s ",key);
        fscanf(f1,"%s ",temp);
        fscanf(f1,"%[^\n]\n",infix);


        if(isKey(key) && temp[0]=='=' && strlen(temp)==1)
        {
            count = 0;
            flag = 0;

            replaceWithoutSpaces(infix);
//            printf("?????\n");
            char *token = strtok(infix," ");

            if(isnumber2(token))
            {
                value = atof(token);
                flag = 1;
            }

            while(token!=NULL)
            {
                strcat(infix2,token);
                strcat(infix2," ");
                count++;
                token = strtok(NULL," ");
            }

            if(count==1)
            {
                if(flag==1)
                    root = put(root,key,value);
                else if(isKey(infix))
                {
                    if(search(root,infix)!=0)
                        root = put(root,key,search(root,infix)->value);
                    else
                    {
                        printf("KEY NOT FOUND");
                        exit(0);
                    }
                }
                else
                {
                    printf("ERROR IN NUMBER");
                    exit(0);
                }
            }
            else
            {
                printf("%s\n",infix2);
                value = replace(root,infix2);
                root = put(root,key,value);
            }
        }
        else
        {
            printf("Error in Statement\n");
            return NULL;
        }
    }
    fclose(f1);
    return root;


}

void InOrdertraverse(Node *root)
{
    if (root!=NULL)
    {
        InOrdertraverse(root->left);
        printf("%s = %.2f\n",root->key,root->value);
        InOrdertraverse(root->right);
    }
}

int main()
{
    Node *BST = NULL;
    BST = ReadFromFile(BST);
    InOrdertraverse(BST);

    return 0;
}
