void sub(int& a, int& b){
    a = 2;
    b = 2;
}

int main(){
    int a,b,c;
    a = 2;
    b = 3;
    c = 120;

    if (c < b){
        c = c+1;
        b = 0;
    }
    else {
        sub(a,b);
    }
    return b;
}
