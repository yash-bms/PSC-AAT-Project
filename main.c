#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_ITEMS 20
#define GST_RATE 18

void printLine() {
    printf("------------------------------------------------------------\n");
}

float calculateGST(float amount) {
    return amount * GST_RATE / 100;
}

int main() {
    int n, i;
    char item[MAX_ITEMS][50];
    int qty[MAX_ITEMS];
    float price[MAX_ITEMS], subtotal[MAX_ITEMS];
    float grossTotal = 0, discount = 0, netTotal, gst, grandTotal;
    int billNo, discountChoice;
    time_t t;

    time(&t);

    printf("Enter Bill Number: ");
    scanf("%d", &billNo);

    printf("Enter number of items (max %d): ", MAX_ITEMS);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_ITEMS) {
        printf("Invalid number of items.\n");
        return 1;
    }

    getchar(); // clear newline

    for (i = 0; i < n; i++) {
        printf("\nItem %d name: ", i + 1);
        fgets(item[i], sizeof(item[i]), stdin);
        item[i][strcspn(item[i], "\n")] = '\0';

        printf("Quantity: ");
        scanf("%d", &qty[i]);

        printf("Price per item: ");
        scanf("%f", &price[i]);

        getchar(); // clear newline

        if (qty[i] <= 0 || price[i] <= 0) {
            printf("Invalid quantity or price. Re-enter item.\n");
            i--;
            continue;
        }

        subtotal[i] = qty[i] * price[i];
        grossTotal += subtotal[i];
    }

    printf("\nApply Discount?\n");
    printf("1. Percentage\n");
    printf("2. Flat Amount\n");
    printf("3. No Discount\n");
    printf("Enter choice: ");
    scanf("%d", &discountChoice);

    if (discountChoice == 1) {
        float percent;
        printf("Enter discount percentage: ");
        scanf("%f", &percent);
        if (percent > 0)
            discount = grossTotal * percent / 100;
    }
    else if (discountChoice == 2) {
        printf("Enter flat discount amount: ");
        scanf("%f", &discount);
    }

    if (discount > grossTotal)
        discount = grossTotal;

    netTotal = grossTotal - discount;
    gst = calculateGST(netTotal);
    grandTotal = netTotal + gst;

    printLine();
    printf("\t\t\t\t\tSUPER MART BILL\n");
    printLine();
    printf("Bill No : %d\n", billNo);
    printf("Date    : %s", ctime(&t));
    printLine();
    printf("%-22s %-6s %-10s %-10s\n", "Item", "Qty", "Price", "Total");
    printLine();

    for (i = 0; i < n; i++) {
        printf("%-22s %-6d %-10.2f %-10.2f\n",
               item[i], qty[i], price[i], subtotal[i]);
    }

    printLine();
    printf("Gross Total : %.2f\n", grossTotal);
    printf("Discount    : %.2f\n", discount);
    printf("Net Total   : %.2f\n", netTotal);
    printf("GST (%d%%)   : %.2f\n", GST_RATE, gst);
    printLine();
    printf("Grand Total : %.2f\n", grandTotal);
    printLine();
    printf("\t\t\t\tThank you. Visit again.\n");
    printLine();

    return 0;
}