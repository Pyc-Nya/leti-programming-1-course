#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char oct1;
    unsigned char oct2;
    unsigned char oct3;
    unsigned char oct4;
} IPv4Address;

IPv4Address convertBtoC(IPv4Address addr);
IPv4Address convertCtoB(IPv4Address addr);
void printIPv4Address(IPv4Address addr);
void printIPv4AddressBinary(IPv4Address addr);

void clearConsole();
void pressEnterToContinue();
void clearStdin();

int main() {
    IPv4Address addrB;
    IPv4Address addrC;
    IPv4Address convertedToC;
    IPv4Address convertedToB;
    int oct1, oct2, oct3, oct4;

    clearConsole();

    printf("Enter class B (i.e. 1st number must be between 128 and 191) IP addres (example: 128.168.0.1): ");
    scanf("%d.%d.%d.%d", &oct1, &oct2, &oct3, &oct4);
    clearStdin();
    addrB.oct1 = (unsigned char)oct1;
    addrB.oct2 = (unsigned char)oct2;
    addrB.oct3 = (unsigned char)oct3;
    addrB.oct4 = (unsigned char)oct4;
    
    printf("Original Class B address: ");
    printIPv4Address(addrB);
    printIPv4AddressBinary(addrB);
    
    convertedToC = convertBtoC(addrB);
    printf("Converted to Class C: ");
    printIPv4Address(convertedToC);
    printIPv4AddressBinary(convertedToC);
    
    pressEnterToContinue();
    
    printf("Enter class C (i.e. 1st number must be between 192 and 223) IP addres (example: 192.168.0.1): ");
    scanf("%d.%d.%d.%d", &oct1, &oct2, &oct3, &oct4);
    clearStdin();
    addrC.oct1 = (unsigned char)oct1;
    addrC.oct2 = (unsigned char)oct2;
    addrC.oct3 = (unsigned char)oct3;
    addrC.oct4 = (unsigned char)oct4;

    printf("\nOriginal Class C address: ");
    printIPv4Address(addrC);
    printIPv4AddressBinary(addrC);
    
    convertedToB = convertCtoB(addrC);
    printf("Converted to Class B: ");
    printIPv4Address(convertedToB);
    printIPv4AddressBinary(convertedToB);

    pressEnterToContinue();
    
    return 0;
}

void clearConsole() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

IPv4Address convertBtoC(IPv4Address addrB) {
    IPv4Address addrC;

    /* 0x1F = 0001 1111 i.e. 31  ; we need to make 1st three bits = 0 and save other bits */
    /* 0xC0 = 1100 0000 i.e. 192 ; we need to make 1st two bits = 1 and save other bits */
    addrC.oct1 = (addrB.oct1 & 0x1F) | 0xC0;

    addrC.oct2 = addrB.oct2;
    addrC.oct3 = addrB.oct3;
    addrC.oct4 = addrB.oct4;
    
    return addrC;
}

IPv4Address convertCtoB(IPv4Address addrC) {
    IPv4Address addrB;

    /* 0x3F = 0011 1111 i.e. 63  ; we need to make 1st two bits = 0 and save other bits */
    /* 0x80 = 1000 0000 i.e. 128 ; we need to make 1st bit = 1 and save other bits */
    addrB.oct1 = (addrC.oct1 & 0x3F) | 0x80;

    addrB.oct2 = addrC.oct2;
    addrB.oct3 = addrC.oct3;
    addrB.oct4 = addrC.oct4;

    return addrB;
}

void printIPv4Address(IPv4Address addr) {
    printf("%d.%d.%d.%d\n", addr.oct1, addr.oct2, addr.oct3, addr.oct4);
}

void clearStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void pressEnterToContinue() {
    printf("\nPress ENTER to continue ");
    clearStdin();
    clearConsole();
}

void printIPv4AddressBinary(IPv4Address addr) {
    int i;

    printf("Address in binary: ");

    for (i = 7; i >= 0; i--) {
        printf("%d", (addr.oct1 >> i) & 1);
    }
    printf(".");

    for (i = 7; i >= 0; i--) {
        printf("%d", (addr.oct2 >> i) & 1);
    }
    printf(".");

    for (i = 7; i >= 0; i--) {
        printf("%d", (addr.oct3 >> i) & 1);
    }
    printf(".");

    for (i = 7; i >= 0; i--) {
        printf("%d", (addr.oct4 >> i) & 1);
    }
    printf("\n");
}
