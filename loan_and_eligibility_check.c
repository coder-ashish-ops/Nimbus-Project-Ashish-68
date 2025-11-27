/*
  loan_emi_eligibility.c
  Project: Loan Interest / EMI Calculator & Eligibility Checker
  Authors: (Ashish Kumar Rawat , Ujjaul , Sachin , Atharva)
  Description:
    - Calculate EMI for a loan given principal, annual interest rate and tenure (months/years)
    - Show Total Payment and Total Interest
    - Check eligibility using a simple rule:
       new EMI + existing EMIs <= allowed_ratio * monthly_income
      (allowed_ratio commonly 0.40 means EMI shouldn't exceed 40% of monthly income)
    - Menu-driven, simple and exam-friendly
*/

#include <stdio.h>
#include <math.h>

// Function prototypes
double calculate_emi(double principal, double annual_rate_percent, int months);
void show_emi_details(double principal, double annual_rate_percent, int months);
int check_eligibility(double monthly_income, double existing_emis, double new_emi, double allowed_ratio);

int main() {
    int choice;
    do {
        printf("\n=== Loan EMI Calculator & Eligibility Checker ===\n");
        printf("1. Calculate EMI and Interest\n");
        printf("2. Check Loan Eligibility\n");
        printf("3. Calculate EMI + Check Eligibility (Combined)\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            // Clear invalid input
            while (getchar() != '\n');
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (choice == 1) {
            double principal, annual_rate;
            int years_or_months, months;
            int mode;

            printf("\n-- EMI Calculator --\n");
            printf("Enter principal amount (e.g., 500000): ");
            scanf("%lf", &principal);
            printf("Enter annual interest rate (percent) (e.g., 7.5): ");
            scanf("%lf", &annual_rate);

            printf("Choose tenure input mode: 1 for years, 2 for months: ");
            scanf("%d", &mode);
            if (mode == 1) {
                printf("Enter tenure in years: ");
                scanf("%d", &years_or_months);
                months = years_or_months * 12;
            } else {
                printf("Enter tenure in months: ");
                scanf("%d", &months);
            }

            show_emi_details(principal, annual_rate, months);
        }
        else if (choice == 2) {
            double monthly_income, existing_emis, principal, annual_rate;
            int months, mode, years_or_months;
            double new_emi, allowed_ratio = 0.40;
            int eligible;

            printf("\n-- Eligibility Checker --\n");
            printf("Enter your monthly income (net): ");
            scanf("%lf", &monthly_income);

            printf("Enter total existing EMIs per month (if none enter 0): ");
            scanf("%lf", &existing_emis);

            printf("If you want to check eligibility for a specific loan, enter loan details.\n");
            printf("Enter principal amount (e.g., 500000): ");
            scanf("%lf", &principal);
            printf("Enter annual interest rate (percent) (e.g., 7.5): ");
            scanf("%lf", &annual_rate);

            printf("Choose tenure input mode: 1 for years, 2 for months: ");
            scanf("%d", &mode);
            if (mode == 1) {
                printf("Enter tenure in years: ");
                scanf("%d", &years_or_months);
                months = years_or_months * 12;
            } else {
                printf("Enter tenure in months: ");
                scanf("%d", &months);
            }

            new_emi = calculate_emi(principal, annual_rate, months);
            printf("\nCalculated EMI for this loan = %.2lf per month\n", new_emi);

            eligible = check_eligibility(monthly_income, existing_emis, new_emi, allowed_ratio);
            if (eligible) {
                printf("Result: Eligible (EMI within %.0f%% of income)\n", allowed_ratio*100);
            } else {
                printf("Result: Not Eligible (EMI exceeds %.0f%% of income)\n", allowed_ratio*100);
                printf("You may increase tenure or reduce loan amount to qualify.\n");
            }
        }
        else if (choice == 3) {
            double monthly_income, existing_emis, principal, annual_rate;
            int months, mode, years_or_months;
            double new_emi, allowed_ratio = 0.40;
            int eligible;

            printf("\n-- EMI + Eligibility (Combined) --\n");
            printf("Enter principal amount (e.g., 500000): ");
            scanf("%lf", &principal);
            printf("Enter annual interest rate (percent) (e.g., 7.5): ");
            scanf("%lf", &annual_rate);
            printf("Choose tenure input mode: 1 for years, 2 for months: ");
            scanf("%d", &mode);
            if (mode == 1) {
                printf("Enter tenure in years: ");
                scanf("%d", &years_or_months);
                months = years_or_months * 12;
            } else {
                printf("Enter tenure in months: ");
                scanf("%d", &months);
            }

            new_emi = calculate_emi(principal, annual_rate, months);
            printf("\nCalculated EMI = %.2lf per month\n", new_emi);
            show_emi_details(principal, annual_rate, months);

            printf("\nNow check eligibility.\n");
            printf("Enter your monthly income (net): ");
            scanf("%lf", &monthly_income);
            printf("Enter total existing EMIs per month (if none enter 0): ");
            scanf("%lf", &existing_emis);

            eligible = check_eligibility(monthly_income, existing_emis, new_emi, allowed_ratio);
            if (eligible) {
                printf("Result: Eligible (EMI within %.0f%% of income)\n", allowed_ratio*100);
            } else {
                printf("Result: Not Eligible (EMI exceeds %.0f%% of income)\n", allowed_ratio*100);
                double max_allowed = monthly_income * allowed_ratio - existing_emis;
                if (max_allowed > 0) {
                    printf("Maximum additional EMI you can afford = %.2lf per month\n", max_allowed);
                } else {
                    printf("You currently have no spare EMI capacity. Consider reducing loan or increasing tenure.\n");
                }
            }
        }
        else if (choice == 0) {
            printf("Goodbye!\n");
        }
        else {
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}

/*
  calculate_emi:
    principal        -> loan amount
    annual_rate_percent -> annual interest rate in percent (e.g., 7.5)
    months           -> loan tenure in months

  EMI formula:
    r = monthly_rate = annual_rate_percent / 12 / 100
    EMI = P * r * (1+r)^n / ((1+r)^n - 1)
*/
double calculate_emi(double principal, double annual_rate_percent, int months) {
    if (months <= 0 || principal <= 0) return 0.0;
    double r = annual_rate_percent / 12.0 / 100.0;
    if (r == 0.0) {
        // Zero interest simple division
        return principal / months;
    } else {
        double pow_val = pow(1 + r, months);
        double emi = principal * r * pow_val / (pow_val - 1);
        return emi;
    }
}

void show_emi_details(double principal, double annual_rate_percent, int months) {
    double emi = calculate_emi(principal, annual_rate_percent, months);
    double total_payment = emi * months;
    double total_interest = total_payment - principal;

    printf("\n--- EMI Details ---\n");
    printf("Loan Amount (Principal): %.2lf\n", principal);
    printf("Annual Interest Rate: %.2lf %%\n", annual_rate_percent);
    printf("Tenure: %d months (%.2lf years)\n", months, months / 12.0);
    printf("EMI (monthly): %.2lf\n", emi);
    printf("Total Payment (EMI * months): %.2lf\n", total_payment);
    printf("Total Interest Paid: %.2lf\n", total_interest);
    printf("-------------------\n");
}

/*
  check_eligibility:
    monthly_income -> net monthly income
    existing_emis  -> sum of existing EMIs per month
    new_emi        -> EMI of the new loan
    allowed_ratio  -> fraction of income allowed for EMIs (e.g., 0.40 for 40%)

  Returns 1 if eligible, 0 otherwise
*/
int check_eligibility(double monthly_income, double existing_emis, double new_emi, double allowed_ratio) {
    if (monthly_income <= 0) return 0;
    double allowed_total = monthly_income * allowed_ratio;
    double projected_total_emis = existing_emis + new_emi;
    return (projected_total_emis <= allowed_total) ? 1 : 0;
}
