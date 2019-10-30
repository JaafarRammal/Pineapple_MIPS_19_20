// jump 

int main(){
    int  x = 0;
    for (int i=0; i < 3; i++){
        if (x > 3){
            break;
        }
        else {
            continue;
        }
        x = x+1;
    }
    return x ;
}