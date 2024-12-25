#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<math.h>
#define MAX 100
#define SELECT 9//選択肢の数
char* input(char* string, char* charonly);
int inputnumber(char* number);
char* shuffle(char* string, int length);
char* reverse(char* string, int length);
char* vowelout(char* string, int length, int inout);
char* alphachange(char* string, int length);
char* alphamove(char* string, int length, int plusminus);
char* sort(char* string, int length, int maxmin);
int main(){
  int length = 0;
  char* string, *charonly;
  string = (char*)malloc(sizeof(char) * MAX);
  charonly = (char*)malloc(sizeof(char) * MAX);
  input(string, charonly);
  string = charonly;
  while(string[length] != '\0') length++;//長さを求める
  printf("[0]終了[1]場所シャッフル[2]リバース[3]母音抜き[4]子音抜き\n");
  printf("[5]アルファベットの大文字小文字変換\n");
  printf("[6]選択された数字分アルファベットを後にずらす\n");
  printf("[7]選択された数字分アルファベットを前にずらす\n");
  printf("[8]昇順(A->Z)[9]降順(Z->A)\n");
  printf("選択肢の数字を入力してください\n>");
  char number[MAX];
  while(true){
  int num = inputnumber(number);//数字を入力
  if(num == 0) break;
  if(num == 1) shuffle(string, length);
  if(num == 2) reverse(string, length);
  if(num == 3) string = vowelout(string, length, 0);
  if(num == 4) string = vowelout(string, length, 1);
  if(num == 5) alphachange(string, length);
  if(num == 6) alphamove(string, length, 0);
  if(num == 7) alphamove(string, length, 1);
  if(num == 8) sort(string, length, 0);
  if(num == 9) sort(string, length, 1);
  printf("途中結果[%s]\n次の動作の数字を選んでください\n>", string);
  }

  free(string);
  printf("最終結果[%s]\n", string);
  return 0;
}

char* input(char *string, char *charonly){
  printf("文字列を入力してください(アルファベット以外は削除されます)>");
  fgets(string, MAX, stdin);
  int k = 0;
  for(int i = 0; i < MAX; i++){
    if(string[i] >= 'a' && string[i] <= 'z'){
      charonly[k] = string[i];
      k++;
    }else if(string[i] >= 'A' && string[i] <= 'Z'){
      charonly[k] = string[i];
      k++;
    }else{
      continue;
    }
  }
  return 0;
}

int inputnumber(char *number){
  int num = 0;
  while(true){
  char number[MAX];
  fgets(number, MAX, stdin);//一文字に入力だとバグ発生
  num = atoi(number);
  if( number[0] - '0' != 0 && num == 0){
    printf("エラー。もう一度入力してください\n>");
  }else{
    bool flag = false;
    for(int i = 0; i <= SELECT; i++){
        if(num == i) flag = true; 
    }
    if(flag) break;
    else printf("エラー。その数字はありません\n>");
  }

  }
  return num;
}
char* shuffle(char *string, int length){
  srand(time(NULL));
for(int i = 0; i < length; i++){
    int random = rand() % length;
    char tmp = string[i];
    string[i] = string[random];
    string[random] = tmp;
  }
  return 0;
}

char* reverse(char *string, int length){
  for(int i = 0; i < length/2; i++){
    char tmp = string[i];
    string[i] = string[length-1-i];
    string[length-1-i] = tmp;
  }
  return 0;
}

char *vowelout(char *string, int length, int inout){
  char vowel[] = {'a','i','u','e','o','A','I','U','E','O'};
  char* ans;
  int k = 0;
  ans = (char*)malloc(sizeof(char) * MAX);

  for(int i = 0; i < length; i++){
    bool flag = false;
    for(int j = 0; j < 10; j++){
      if(inout == 0){
        if(string[i] == vowel[j]){
          string[i] = ' ';
          continue;//次の文字に移る
        }
        }else if(inout == 1){
          if(string[i] == vowel[j]){
            flag = true;
            if(flag) break;
        }
        }
  }
  if(!flag && inout == 1){
    string[i] = ' ';
  }
  }
  for(int i = 0; i < length; i++){
    if(string[i] != ' '){
      ans[k] = string[i];
      k++;
    }
  }
  return ans;
}

char* alphachange(char* string, int length){
  for(int i = 0; i < length; i++){
    if(string[i] >= 'a' && string[i] <= 'z'){
      string[i] = string[i] - 32;//大文字に変換
    }else if(string[i] >= 'A' && string[i] <= 'Z'){
      string[i] = string[i] + 32;//小文字に変換
    }
  }
  return string;
}

char* alphamove(char* string, int length, int plusminus){
  int tmp = 0;
  while(true){
    char movenum[MAX];
    int move[MAX] = {0}, movelength = 0;
    bool flag = false;

    printf("何文字ずらしますか\n>");
    fgets(movenum, MAX, stdin);
    while(movenum[movelength] != '\n') movelength++;
    movenum[movelength] = '\0';

    for(int i = 0; i < movelength; i++){
      move[i] = atoi(&movenum[i]);
    }

    for(int i = 0; i < movelength; i++){
    if(movenum[i] - '0' != 0 && move[i] == 0){
        printf("エラー。もう一度入力してください\n");
        break;
      }else{
        flag = true;
        tmp = move[0];//数字の場合先頭アドレスでいいらしい
    }
  }
  if(flag) break;
  }

  int movetotal = tmp;
  while(movetotal >= 26) movetotal -= 26;
  tmp = movetotal;
  if(plusminus == 1) movetotal = 0 - movetotal;//マイナスのほうが分かりやすい

  if (movetotal == 0) return string;//何もしない

  for(int i = 0; i < length; i++){
    if(string[i] >= 'a' && string[i] <= 'z'){
      if(string[i] == 'z' && movetotal > 0){//zを超える場合
        string[i] = 'a' + movetotal - 1;
      }else if(string[i] == 'a' && movetotal < 0){//aを下回る場合
        string[i] = 'z' + movetotal + 1;
      }

        else{
        if(string[i] + movetotal > 'z'){//zを超える場合
          string[i] = string[i] + movetotal - 26;
        }else if(string[i] + movetotal < 'a'){//aを下回る場合
          string[i] = string[i] + movetotal + 26;
        }
        else{
          string[i] = string[i] + movetotal;
        }
        }

    }else if(string[i] >= 'A' && string[i] <= 'Z'){
      if(string[i] == 'Z' && movetotal > 0){//+
        string[i] = 'A' + movetotal - 1;
      }else if(string[i] == 'A' && movetotal < 0){//-
        string[i] = 'Z' + movetotal + 1;
      }
      else{
        if(string[i] + movetotal > 'Z'){//zを超える場合
          string[i] = string[i] + movetotal - 26;
        }else if(string[i] + movetotal < 'A'){//aを下回る場合
          string[i] = string[i] + movetotal + 26;
        }
        else{
          string[i] = string[i] + movetotal;
        }
      }
    }
  }
  printf("アルファベットを");
  if(plusminus == 0) printf("後");
  else printf("前");
  printf("に%d文字ずらしました\n", tmp);
  return string;
}

char* sort(char* string, int length, int maxmin){
  char max, min;
  if(maxmin == 0){//昇順
    for(int i = 0; i < length; i++){
      min = i;
      for(int j = i+1; j < length; j++){
        if(string[j] < string[min]){
          min = j;
        }
      }

      if(min != i){
      char tmp = string[i];
      string[i] = string[min];
      string[min] = tmp;
    }

    }
  }else if(maxmin == 1){//降順
    for(int i = 0; i < length; i++){
      max = i;
      for(int j = i+1; j < length; j++){
        if(string[j] > string[max]){
          max = j;
        }
      }
      if(max != i) {
        char tmp = string[i];
        string[i] = string[max];
        string[max] = tmp;
      }
    }
  }
  return 0;
}
