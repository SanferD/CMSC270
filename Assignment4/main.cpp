#include <fstream>

#define SKIP(ch) (ch==' ' || ch=='\n' || ch=='\t')
#define DELIM(ch) (ch=='{'||ch=='}'||ch==' '||ch=='\n'||ch==';')

void format(std::ifstream&, std::ofstream&, int ind = 0);
char *indent(int);

int main()
{
    std::ifstream src("C:/Programs/CMSC270/Assignment4/code.c");
    std::ofstream dest("C:/Programs/CMSC270/Assignment4/formatted.c");

    format(src,dest);

    return 0;
}

void format(std::ifstream& src, std::ofstream& dest, int ind)
{
    while(src.peek() != EOF)
    {
        char ch = src.get();

        if(DELIM(ch)) for(;SKIP(src.peek());src.get());
        switch(ch)
        {
        case ' ':
            if(src.peek() != '{') dest << ch;
            break;
        case '{':
            dest << ' ' << ch << '\n' << indent(ind+1);
            format(src,dest,ind+1);
            dest << indent(ind) << '}' << '\n';
            if(DELIM(ch)) for(;SKIP(src.peek());src.get());
            if(src.peek() != '}') dest << indent(ind);
            break;
        case '}':
            return;
        case ';':
            dest << ch << "\n";
            if(src.peek() != '}') dest << indent(ind);
            break;
        case '\n':
            if(src.peek() != '{') dest << '\n';
            break;
        default:
            dest << ch;
            break;
        }
    }
}

char *indent(int num)
{
    char *tabs = (char*) calloc(num+1, sizeof(char));
    for(int i=0;i!=num;tabs[i++]='\t');
    return tabs;
}
