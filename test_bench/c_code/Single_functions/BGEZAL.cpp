// BGEZAL

void linking_function(int& input){
    input = 2;
}
int main(){
    int  x = 5;
    if (x >0){
        linking_function(x);
    }
    return x ;
}