#include<stdio.h>
#include<stdlib.h>
#include<string.h>//strcmp等を使うため
#include<time.h>//現在時刻を得るため
#include<stdbool.h>//boolを使うため
#define MAX 100//配列、ポインターの大きさ用
#define ERR -5//打ち間違い用
int alphaout(char *input, int number);//数字だけにする関数
int miss();//打ちミスを処理する関数
char select(char *intonly);//選択肢を確認する関数
int timeanddate(int enter);//計算結果を出す関数
int calc(int *bunkai, int ans);//実際の計算を行う関数
//月の計算を行う関数
int monthcheck(int *bunkai, const int *sixty, const int *month);
int main(){
    char *input;//入力
    input = (char *)malloc(sizeof(char)*MAX);//メモリ確保
    printf("どのプログラムを選択しますか\n");
    printf("選択肢  1:現在時刻より後 2:入力した値より後\n");
    printf("数字をを入力してください(半角数字以外は消えます)\n>");
    alphaout(input, 0);
    free(input);//メモリ解放
    return 0;
}
//アルファベットを除く
int alphaout(char *input, int number){
  char intonly[MAX] = {0};
  int num = 0;
  fgets(input,MAX,stdin);//inputの入力
  int line = strlen(input);//inputが何文字かを知る
  if(line == 1){//実際の文字列より1大きくなる
    miss();
    return ERR;//ERRによってプログラムを終了させる
  }
  for(int i=0; i < line-1; i++){
    for(int j=0; j <=9 ; j++){
      if( (int)*(input+i) == (48+j) ){
      intonly[num]= *(input+i);
      num++;//48は0の文字コード57は9の文字コード
      }
  }
  }
  if(intonly[0] == '\0'){
    miss();//intonlyに何も入っていないなら終了
    return ERR;
  } 
  //number=0はmain関数のみ使う
  if(number == 0){
    char ans[MAX] = {0};
    printf("入力内容は以上でよろしいですか？\n");
    printf("  yes / no \n>");
    fgets(ans,MAX,stdin);
    //文字列比較にはstrcmpでないといけない
    //strcasecmpは大文字小文字の区別をしない
    if(strcasecmp(ans, "yes\n") == 0){
      select(intonly);
    }
    else if(strcasecmp(ans, "no\n") == 0){
      miss();
      return 0;
    } 
    else{
      printf("yes / no以外が打たれたので終了します");
      return 0;
    }
  }else if(number == 1){
    int ans = atoi(intonly);//文字列なので
    return ans;
  }
  return 0;
}

int miss(){
  printf("もう一度打ち直してください");
  return 0;
}
//どのプログラムか決める
char select(char *intonly){
  int ans = 0;
  if(*intonly == '1'){
      ans = timeanddate(1);
  }else if(*intonly == '2'){
      ans = timeanddate(2);
  }else{
      printf("エラー。選択肢にありません");
      return 0;
  }
  if(ans == ERR) return 0;
  return 0;
}

int timeanddate(int enter){
  printf("どの計算をしますか\n");
  printf("選択肢   1:分刻み 2:時間刻み \n\t 3:日付刻み  4:月刻み\n\t 5:年刻み\n>");
  char *input;
  input = (char *)malloc(sizeof(char)*MAX);
  int ans = alphaout(input, 1);//返答
  free(input);
  if(ans > 5){
    miss();//6以上の選択肢はないので
    return 0;
  }
  if(ans == ERR) return ERR;
  time_t timer = time(NULL);
  struct tm *ltime;
  ltime = localtime(&timer);
  char year[MAX],timestr[MAX], week[MAX];
  strftime(year, MAX, "%Y",ltime);//年
  strftime(timestr, MAX, "%m%d%H%M",ltime);//月日時間分
  strftime(week, MAX, "%w",ltime);//曜日を文字型の数字で出す
  int yearint = atoi(year);//yearは文字列なのでatoi
  char c[5][5];
  int bunkai[10] = {0};
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 1; j++){
      //月日時間分で分けられた配列
      c[i][j] = timestr[j+2*i];
      c[i][j+1] = timestr[j+1+2*i];
    }
    bunkai[4-i] = atoi(c[i]);//int型に変換
  }
  bunkai[5] = yearint;//年をbunkai[5]に代入
  int iweek = atoi(week);//iweekに曜日を数字で表したものを代入
  char *today[7] = { "日", "月", "火", "水", "木", "金", "土" };
  //fgetsには\nが入るので。scanfだとバグが起こった
  char *today1[7] ={ "日\n", "月^n", "火\n", "水\n", "木\n", "金\n", "土\n"};
  if(enter == 1){
  printf("現在時刻%d年%02d月%02d日%02d時%02d分 %s曜日\n"
  ,bunkai[5],bunkai[4],bunkai[3],bunkai[2],bunkai[1],*(today+iweek));
  }
  else if(enter == 2){//selectで2を入れるとこっち
    input = (char *)malloc(sizeof(char)*MAX);
    printf("何年何月何日何時何分<-左から何に数字を入れるように\n");
    printf("入力してください\n");
    for(int i = 5; i >= 1; i--){
      printf(">");
      bunkai[i] = alphaout(input, 1);
      if(bunkai[i] == ERR) return 0;
    }
    free(input);
    char output[MAX];
    printf("何曜日?(正確に漢字を入れないと今日の曜日になります)\n>");
    fgets(output,MAX,stdin);
    for(int i = 0; i <= 6; ++i) if(strcmp(output,today1[i]) == 0) iweek = i;
      printf("元とする時刻%d年%02d月%02d日%02d時%02d分 %s曜日\n"
    ,bunkai[5],bunkai[4],bunkai[3],bunkai[2],bunkai[1],*(today+iweek));
  }
  int count[6] = {0,bunkai[1],bunkai[2],bunkai[3],bunkai[4],bunkai[5]};
  int check = 0;
  check = calc(bunkai, ans);//これが実際の計算
  if(check == ERR) return ERR;
  int total[6] = {0};
  for(int i = 3; i <= 5; i++) total[i] = bunkai[i] - count[i];
  int total1[3] = {0};//月の数を入れる変数
  const int month[5] = {2,4,6,9,11};
  int min = count[4], max = bunkai[4]; 
  int differ = bunkai[5] - count[5];//年同士の計算
  if(bunkai[5] != count[5]) total[5]--;//下のfor文で1年分は計算できるので
  if(bunkai[5] > count[5]) max += 12;
  for(int i = min; i < max; i++){
    bool flag = true;
    int k = i;
    if(max > 12 && i > 12) k -= 12;
    for(int j = 0; j < 5; j++){
      if(month[j] == k){//2,4,6,9,11月なのか？
        flag = false;
        break;
    }
    }
    if(flag){//31日
      total1[0]++;
    }else if(k != 2){//30日以下
      total1[1]++;
    }else{//2月
      total1[2]++;
    }
  }
  if(bunkai[5] % 4 != 0){
    total[4] = total1[0]*31 + total1[1]*30 + total1[2]*28;
  }else{
    int leap = differ / 4;//閏年用
    total[4] = total1[0]*31 + total1[1]*30 + total1[2]*28 + leap;
  }
  int sdays = (total[5]*365 + total[4] + total[3] + iweek) % 7;
  printf("求めた時刻%d年%02d月%02d日%02d時%02d分 %s曜日\n"
  ,bunkai[5],bunkai[4],bunkai[3],bunkai[2],bunkai[1],*(today+sdays));
  return 0;
}

int calc(int *bunkai, int ans){
  //[0]念の為 [1]分 [2]時 [3]日(1) 
  //[4]日(2) [5]日(3) [6]月 [7]閏年
  const int sixty[20] = {60,60,24,32,31,29,12,30};
  const int month[5] = {2,4,6,9,11};//30日じゃない月
  char *input;
  input = (char *)malloc(sizeof(char)*MAX);
  if(ans == 5) printf("何年後?\n>");
  if(ans == 4) printf("何月後?\n>");
  if(ans == 3) printf("何日後?\n>");
  if(ans == 2) printf("何時間後?\n>");
  if(ans == 1) printf("何分後?\n>");
  int tmp = alphaout(input, 1);
  if(tmp == ERR) return ERR;
  free(input);
  //年は単純に足せばよいのでif文はない
  *(bunkai+ans) += tmp;//足し算
  if(ans == 4){
    while(*(bunkai+ans) > sixty[ans+2]){
      *(bunkai+ans) -= 12;
      *(bunkai+5) += 1;
    }
    }
  if(ans == 3) monthcheck(bunkai, sixty ,month);
  if(ans <= 2){
  while(*(bunkai+ans) >= sixty[ans]){
    *(bunkai+ans) -= sixty[ans];
    *(bunkai+ans+1) += 1;
  }
  }
  if(ans >= 2) calc(bunkai, ans-1);//ansが1のときは再帰しない
//足し方の順番的におかしい数字になることがあるので
  for(int i = 1; i < 10; i++){
    if(i <= 2){
    while(*(bunkai+i) >= sixty[i]){
      *(bunkai+i) -= sixty[i];
      *(bunkai+i+1) += 1;
    }
    }else if(3 <= i  && i <= 5){
      monthcheck(bunkai, sixty, month);
      i = 5;
    }else if(i == 6){
      while(*(bunkai+4) > sixty[i]){
      *(bunkai+4) -= sixty[i];
      *(bunkai+5) += 1;
      }
    }
  }
  return 0;
}

int monthcheck(int *bunkai, const int *sixty, const int *month){
  while(*(bunkai+3) >= *(sixty+3)){  
    //月が12より大きいなら(無いと全部31日になる)
    //月は前の計算で12以下なので13の時に使われる
    if(*(bunkai+4) > *(sixty+6)){
       *(bunkai+4) -= *(sixty+6); 
       *(bunkai+5) += 1;
    }
    bool flag = true;
    for(int i = 0; i < 5; i++){
      if(*(bunkai+4) == *(month+i)){
        flag = false;//2,4,6,9,11月のときと場合分け
        break;//つけないと11月の時以外反応しなくなる
      }
    }
    if(flag){//31日
        *(bunkai+3) = *(bunkai+3) + 1 - *(sixty+3);
        *(bunkai+4) += 1;
    }else{//30日
      if(*(bunkai+4) != 2){
        *(bunkai+3) = *(bunkai+3) + 1 - *(sixty+4);
        *(bunkai+4) += 1;
      }else{//２月
        if(*(bunkai+5) % 4 != 0){
        *(bunkai+3) = *(bunkai+3) + 1 - *(sixty+5);
        *(bunkai+4) += 1;
        }else{//閏年なら2月を29日として計算する
        *(bunkai+3) = *(bunkai+3) + 1 - *(sixty+7);
        *(bunkai+4) += 1;
        }
      }
    }
    }
  return 0;
}
