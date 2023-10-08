#include<fstream>
#include<graphics.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<string>
#include<stdlib.h>

using namespace std;

void search();
void search();
void homepage();
char keyword[80] = {"\0"};

class Country {
public:
    char content[240];
    char name[80];

};

int strcmpi (const char *s1, const char *s2) {
    const unsigned char *p1 = (const unsigned char *) s1;
    const unsigned char *p2 = (const unsigned char *) s2;
    unsigned char c1, c2;

    if (p1 == p2)
        return 0;

    do {
        c1 = tolower(*p1++);
        c2 = tolower(*p2++);
        if (c1 == '\0')
        break;
    } while (c1 == c2);

    return c1 - c2;
}

void border() {
    setfillstyle(3, 8);
    bar(0, 0, 180, 600);
    setfillstyle(6, 8);
    bar(820, 0, 1000, 600);
}


void input() {

    int k = 0;
    char ch;
    while(1) {

        if(kbhit) {

            ch = getch();
            if(ch == 13) {
                keyword[k] = 0;
                break;
            }
            else if(ch == 8 && k != 0) {
                k--;
                setfillstyle(1, BLACK);
                setcolor(0);
                bar(240, 340, 400, 450);
                settextstyle(7, 0, 5);
                setcolor(12);
                keyword[k] = 0;
                outtextxy(240, 340, keyword);
            } 
            else {
                settextstyle(7, 0, 5);
                setcolor(12);
                keyword[k] = ch;
                k++;
                keyword[k] = 0;

                outtextxy(240, 340, keyword);
            }
        }
    }
}

void search_homepage() {

    cleardevice();
    char seeker[7][10] = {"S", "E", "E", "K", "E", "R"};
    int colour[6] = {9, 12, 14, 9, 10, 12};

    for(int i = 0; i < 6; i++) {

        settextstyle(7, 0, 10);
        setcolor(colour[i]);
        outtextxy(190 + i * 100, 100, seeker[i]);
    }

    settextstyle(7, 0, 5);
    outtextxy(240, 300, "Search or type a URL");
    border();
}

void search() {

    search_homepage();
    input();

    cleardevice();
    border();

    Country obj;
    char word[80], tempstr[80], str[240];
    int k = 0, i = 0, j = 0, count,
    int A[20], line = 40, temp;
    fstream f;

    char countries[20][80];
    f.open("country.dat", ios::in | ios::binary);

    while(f.read((char*)&obj, sizeof(obj))) {

        count = 0;

        strcpy(str, obj.content);
        strcpy(countries[i], obj.name);
        for(j = 0; j <= strlen(str); j++) {
            if(str[j] != 0 && str[j] != 32 && str[j] != '.') {
                word[k] = str[j];
                k++;
            }
            else {
                word[k]=0;
                k=0;

                if(strcmpi(word,keyword) == 0) {
                    count++;
                }
            }
        }

        A[i] = count;

        i++;
    }
    f.close();

    for(i = 0; i < 20; i++) {
        for(j = i + 1; j < 20; j++) {
            if(A[i] < A[j]) {
                temp = A[i];
                A[i] = A[j];
                A[j] = temp;
                strcpy(tempstr, countries[i]);
                strcpy(countries[i], countries[j]);
                strcpy(countries[j], tempstr);
            }
        }
    }

    i = 0;
    settextstyle(7, 0, 5);

    char ch1[2];
    ch1[1] = 0;
    if(A[i] == 0) {
        outtextxy(180, 50, "NO RESULTS FOUND");
    }
    else {

        while(A[i] != 0) {

            ch1[0] = i + 48;

            outtextxy(250, line, countries[i]);
            outtextxy(180, line, ch1);

            //cout<<ch1<<endl;
            line += 50;
            i++;
        }
        //outtextxy(180,400,"Press CorrespondingNumber");
    }

    char choice;
    if(A[0] != 0) {
        if(kbhit) {
            choice = getch();

            int j = 0, k = 0, lineno = 10;
            char str[240] = {0};
            int n = int(choice) - 48;
            cleardevice();
            f.open("country.dat", ios::in | ios::binary);
            i = 0;
            while(f.read((char*)&obj, sizeof(obj))) {

                cleardevice();

                border();
                if(strcmpi(obj.name, countries[n]) == 0) {

                    while(obj.content[j] != 0) {
                        str[k] = obj.content[j];
                        if(k == 0 && str[k] == 32)
                        k--;
                        if(k == 24 || obj.content[j + 1] == 0) {
                            str[k + 1] = 0;
                            setcolor(15);
                            outtextxy(180, lineno, str);
                            lineno += 50;
                            k = 0;
                            j++;
                        }
                        else {
                            j++;
                            k++;
                        }

                    }
                    break;
                }

            }
            f.close();
        }
    }
}

void homepage() {
    initwindow(1000, 600, "Search Engine");
    //NAME OF THE SEARCH ENGINE
    char seeker[7][10] = {"S", "E", "E", "K", "E", "R"};
    int colour[6] = {9, 12, 14, 9, 10, 12};
    for(int i = 0; i < 6; i++) {
        settextstyle(7, 0, 10);
        setcolor(colour[i]);
        outtextxy(190 + i * 100, 100, seeker[i]);
    }
    settextstyle(7, 0, 5);

    outtextxy(390, 300, "0 Search");
    setcolor(3);
    outtextxy(390, 370, "1 Exit");

    border();
}

int main()
{
    char choice;
    int ch;
    do {
        homepage();
        if(kbhit) {
            choice = getch();
        }
        ch = int(choice) - 48;
        switch(ch) {
            case 0:     search();
                        break;
            case 1:     exit(0);
                        break;
            default:    outtextxy(340, 440, "Invalid Choice");

        }
        getch();
        cleardevice();

    } while(1);

    return 0;
}