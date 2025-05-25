// Program that calculates how much each person should pay when splitting a restaurant bill, including tax and tip.

#include <stdio.h>

float half(float bill, float tax, int tip){
  float tax_amount, tip_amount, total;
  // Calculate tax amount from the original bill
  tax_amount = bill * (tax / 100);
  // Calculate total after adding tax
  total = bill + tax_amount;
  // Calculate tip based on the taxed amount
  tip_amount = total * (float)tip / 100;
  // Add tip to get final total
  total += tip_amount;
   // Return half of the total amount
  return total/2;
}

int main(void)
{
    float bill_amount,tax_percent;
    int tip_percent;
    printf("Bill before tax and tip: ");
    scanf("%f", &bill_amount);
    printf("Sale Tax Percent: ");
    scanf("%f", &tax_percent);
    printf("Tip percent: ");
    scanf("%d", &tip_percent);
    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

