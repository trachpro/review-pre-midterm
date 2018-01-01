#include<stdio.h>
#include<string.h>

char *trim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

    if( str + len - 1 != endp )
            *(endp + 1) = '\0';
    else if( frontp != str &&  endp == frontp )
            *str = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) { *endp++ = *frontp++; }
            *endp = '\0';
    }


    return str;
}

int split(char a[][100], char *s, char c) {

    int n = strlen(s);

    int i = 0;
    int t = 0;
    int st = 0;
    while(t!=n) {
        // printf("%c--\n",s[i])
        if(s[t] == c) {
            
            if(a[i][0]) i++;
            t++;
            st = 0;
            continue;
        }

        a[i][st] = s[t];
        st++;
        t++;
    }

    return i+1;
}

int main() {

    char a[100][100];
    char s[100] = "A11111    A2-5  A4-9    100";

    int n = split(a, s, ' ');

    for(int i = 0; i< n; i++) {

        printf("%s\n",trim(a[i]));
    }

    sscanf(sizeof('a') + a[0],"%d",&n);
    printf("--%d\n",n);
}