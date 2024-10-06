#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void genereteBillHeader(char name[30],char date[20])
{
    printf("\n\n\n");
    printf("\t    RKSS Restaurant");
    printf("\n\t   ---------------");
    printf("\nDate : %s",date);
    printf("\nInvoice To : %s\n",name);
    printf("---------------------------------------");
    printf("\nItems\t\t");
    printf("Qty\t\t");
    printf("Total\t\t\n");
    printf("---------------------------------------");
    printf("\n\n");
}

void generateBillBody(char item[30],int qty,float price)
{
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%0.2f\t\t\n",price*qty);
}

struct items{
    char item[50];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[20];
    int numOfItems;
    struct items itm[50];
};

void genereteBillFooter(float total)
{
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal+2*cgst;
    printf("\n---------------------------------------");
    printf("\nSub Total\t\t\t%0.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%0.2f","%",cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------\n");
}

int main()
{
    int opt,n;
    float total;
    float tot=0;
    char saveBill='y';
    char name[50];
    int invoicefound=0;
    struct orders ord;
    struct orders order;
    FILE *fp;
    printf("\t=============RKSS Restaurent=============");
    printf("\nPlease Select Your Prefered Option");
    printf("\n1.Generete Invoice");
    printf("\n2.SHow All Invoices");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");
    printf("\n\nYour Choise :");
    scanf("%d",&opt);
    fgetc(stdin);
    switch(opt)
    {
        case 1:
        {
            system("clear");
            printf("\nPlease Enter Name Of The Customer :\t");
            fgets(ord.customer,50,stdin);
            ord.customer[strlen(ord.customer)-1]=0;
            strcpy(ord.date,__DATE__);
            printf("\nPlease Enter The Number Of Items :\t");
            scanf("%d",&n);
            ord.numOfItems=n;
            for(int i=0;i<n;i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please Enter The Item %d:",i+1);
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                printf("Please Enter The Quantity :\t");
                scanf("%d",&ord.itm[i].qty);
                printf("Please Enter The Unit Price :\t");
                scanf("%f",&ord.itm[i].price);
                total+=ord.itm[i].qty*ord.itm[i].price;
            }
            
            genereteBillHeader(ord.customer,ord.date);
            for(int i=0;i<ord.numOfItems;i++)
            {
                generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }
            
            genereteBillFooter(total);
            
            printf("\nDo You Want To Save The Invoice :\t");
            scanf("%s",&saveBill);
            
            if(saveBill=='y')
            {
                fp=fopen("RestaurantBill.dat","a+");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if(fwrite!=0)
                {
                    printf("\nSuccessfully Saved");
                }
                else
                {
                    printf("\nError Saving");
                }
                fclose(fp);
            }
            break;
        
        }
        
        case 2:
        {
            system("clear");
            fp=fopen("RestaurantBill.dat","r");
            printf("\n  *****Your Previous Invoices*****\n");
            while(fread(&order,sizeof(struct orders),1,fp))
            {
                genereteBillHeader(order.customer,order.date);
                for(int i=0;i<order.numOfItems;i++)
                {
                    generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    total+=order.itm[i].qty*order.itm[i].price;
                }
                genereteBillFooter(tot);
            }
            fclose(fp);
            break;
        }
        
        case 3:
        {
            system("clear");
            printf("\nEnter The Name Of The Customer :\t");
            fgets(name,50,stdin);
            name[strlen(name)-1]=0;
            
            fp=fopen("RestaurantBill.dat","r");
            printf("\n  *****Invoice Of %s*****\n",name);
            while(fread(&order,sizeof(struct orders),1,fp))
            {
                tot=0;
                if(!strcmp(&order.customer,name))
                {
                    genereteBillHeader(order.customer,order.date);
                    for(int i=0;i<order.numOfItems;i++)
                    {
                        generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                        tot+=order.itm[i].qty*order.itm[i].price;
                    }
    
                    genereteBillFooter(tot);
                    invoicefound=1;
                }
                
            }
            if(!invoicefound)
            {
                printf("Sorry The Invoice for %s doesnot Found",name);
            }
            fclose(fp);
            break;
        }
        
        
        
        
    }
    
    
    
    printf("\n\n\n");
}