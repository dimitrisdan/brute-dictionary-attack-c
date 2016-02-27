#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *crypt(const char *key, const char *salt);

//Anadromikh sunartish gia Force Brute attack
void incforbrute(char *p, unsigned int plithos){
    if((*p)<plithos) (*p)++;
    else{
        (*p)=1;
        incforbrute(++p,plithos);
    }
}

int main(int argc, char** argv){
    
    printf("Choose:\n1.Dictionary\n2.Brute Force\n*.Quit\n");
    char ch = getchar();
    char ll=getchar(); //gia na figei to enter apo ti input...
    if(ch!='1' && ch!='2') exit(0);
    
    FILE *shadow;
    FILE *dictionary;
    time_t tstart,tend;
    char line[100];
    char *username;
    char *fullpass;
    char salt[12];
    char trypass[20];
    char *chars = "abc";
    unsigned int N = 4; //plithos grammatwn gia bruteforce
    char pin[N+1]; //deiktes ws pros pinaka chars (gia brute)
    char end[N+1];
    //Anoigma arxeiou lexikou an exei epilegei i Dictionary attack
    if(ch=='1'){
        if( (dictionary=fopen("words.english","r"))==NULL){
            printf("Dictionary not found\n");
            exit(-1);
        }
    }else if(ch=='2'){
        memset(end,'\0',N+1);
        int tm;
        for(tm=0;tm<N;tm++) end[tm] = chars[strlen(chars)-1];
    }
    memset(pin,'\0',N+1);
    memset(trypass,'\0',20);
    time(&tstart);
    while(1){
        //Dimiourgia-Paralavi kainouriou kodikou analoga me to ti exei epilexthei
        if(ch=='1'){
            memset(trypass,'\0',20);
            if(fscanf(dictionary,"%s",trypass)!=1){ 
                fclose(dictionary);
                break;
            }
        }else if(ch=='2'){
            if(strcmp(trypass,end)==0) break;
            else{
                incforbrute(pin,strlen(chars));
                int t;
                for(t=0;t<N;t++) trypass[t] = chars[pin[t]-1];
            }
        }
        
        if( (shadow=fopen("shadow","r"))==NULL){
            printf("File not found\n");
                exit(-1);
        }
        memset(line,'\0',100);
        while(fgets(line,100,shadow) !=NULL){
            memset(salt,'\0',12);
            username = strtok(line,":");
            fullpass = strtok(NULL,":");
            
            int tmp;
            for(tmp=0;tmp<11;tmp++)
                salt[tmp]=fullpass[tmp];
            if(strcmp(fullpass,crypt(trypass,salt))==0){
                printf("Username: %s Password: %s\n",username,trypass);
            }
            
            memset(username,'\0',strlen(username));
            memset(fullpass,'\0',strlen(fullpass));
        }
        fclose(shadow);
        
    }
	
	// Upologismos Xronou
    time(&tend);
    time_t duration;
    duration = tend - tstart;
    struct tm *dur;
    dur = gmtime(&duration);
    printf("\nDuration: \n");
    printf("%d sec\n", dur->tm_sec);
    printf("%d min\n", dur->tm_min);
    printf("%d hour(s)\n", dur->tm_hour);
    printf("%d day(s)\n", dur->tm_mday-1);
    //~Upologismos Xronou~
	
	return 0;
}
