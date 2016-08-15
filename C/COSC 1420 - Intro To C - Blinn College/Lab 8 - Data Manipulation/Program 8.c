/*
    Lab 8 - Opens blinn.dat and formats and saves to a file called out.txt
    
    Written by: Trevor Underwood
    Date:       April 20th 2013
    Class:      COSC 1420
*/
#include <stdio.h>

int main()
{
    FILE *in;
    FILE *fp;
    fp=fopen("E:/Lab_8/blinn.out", "w");
    if(fp == NULL)
        return 1;
    char name[8];
    int depName, quantity, inCost, outCost, nameTmp = 0, costE, marketE, costLower, totalCostE, totalMarketE, invenLower = 0;
    
    if ((in = fopen("E:/Lab_8/blinn.dat", "r")) == NULL)
    {
        printf("Can't open file blinn.dat");
        system("pause");
        return 1;
    }
    else
    {
        fprintf(fp, "\n\n\t\t\t\t    Blinn   Apparel   Store");
        fprintf(fp, "\n\n\n                                Unit Cost \t\t   Extended");
        fprintf(fp, "\n\t\tQuantity       Cost  Market\t\tCost      Market         Lower Cost\n");
        while(fscanf(in, "%d %s %d %d %d", &depName, name, &quantity, &inCost, &outCost) != EOF)
        {
            //printf("Outfile created!");
            costE = 0;
            marketE = 0;
            
            if (nameTmp != depName)
            {
                if (nameTmp > 0)
                {
                    costLower = totalCostE;
                    if (costLower > totalMarketE)
                    {
                        costLower = totalMarketE;
                        
                    }
                    invenLower += costLower;
                    fprintf(fp, "  Total \t \t \t \t \t     $%d.00  $%d.00 \t  $%d.00\n", totalCostE, totalMarketE, costLower);
                }
                switch (depName)
                {
                    case 1:
                    {
                        fprintf(fp, "Mens Dept\n");
                        break;
                    }
                    case 2:
                    {
                        fprintf(fp, "Ladies Dept\n");
                        break;
                    }
                    case 3:
                    {
                        fprintf(fp, "Girls Dept\n");
                        break;
                    }
                    case 4:
                    {
                        fprintf(fp, "Boys Dept\n");
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                nameTmp = depName;
                totalCostE = 0;
                totalMarketE = 0;
            }
            costE = quantity * inCost;
            marketE = quantity * outCost;
            totalCostE += costE;
            totalMarketE += marketE;
            fprintf(fp, "%*s \t %*d\t   %*d.00 %*d.00  \t      %*d.00   %*d.00\n", 8, name, 5, quantity, 5, inCost, 4, outCost, 5, costE, 5, marketE);
        }
        costLower = totalCostE;
        if (costLower > totalMarketE)
        {
            costLower = totalMarketE;
            fprintf(fp, "\n%d", costLower);
           
        }
        invenLower += costLower;
        fprintf(fp, "  Total \t \t \t \t \t     $%d.00  $%d.00 \t  $%d.00\n Inventory at lower cost \t\t\t\t\t\t\t $%d.00", totalCostE, totalMarketE, costLower, invenLower);
    }
    system("pause");
    return 0;
}
