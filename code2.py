from bs4 import BeautifulSoup
import requests
import re
import datetime
import locale

def get_time(flag1):
    locale.setlocale(locale.LC_ALL, 'ja_JP.UTF-8')
    dt = datetime.datetime.today()
    flag = 0
    flag2 = False
    try:
        flag = int(flag1)
    except ValueError as e:
        print(f"{e}")
        exit(1)
        
    if flag == 0: return dt, flag2
    
    fb = [" ","前","後"]
    how_many = ["年","ヶ月","日","時間"]
    example = ["2年","3ヶ月","10日","15時間"]
    time_input = []
    for i in range(len(how_many)):
        tmp = input(f"何{how_many[i]}{fb[flag]}(例: {example[i]}{fb[flag]}(数字のみでも可))>")
        if how_many[i] + fb[flag] in tmp:
            tmp = tmp.split(f"{how_many[i] + fb[flag]}")#数字部分を切り抜く
            time_input.append(int(tmp[0]))
        else:
            try:
                time_input.append(int(tmp))#数字のみの場合
            except ValueError as e:
                print(f"{e}")
                exit(1)
    
    dt_list = []#現在時刻y,m,dの文字列
    dt_list_int = []#int y,m
    ans = []
    if flag == 1:
        dt_m = dt - datetime.timedelta(days=int(time_input[2]),hours=int(time_input[3]))
    elif flag == 2:
        dt_m = dt + datetime.timedelta(days=int(time_input[2]),hours=int(time_input[3]))
    else:
        print("エラー")
        exit(1)
        
    dt_list = str(dt_m.date()).split('-')#年から日まで
    dt_list_int = [int(dt_list[i]) for i in range(0,len(dt_list)-1)]
    
    for i in reversed(range(len(dt_list_int))):
        if flag == 1:
            tmp = dt_list_int[i] - time_input[i]
            while i == len(dt_list_int) - 1 and tmp < 1:
                tmp += 12
                dt_list_int[i-1] -= 1
        elif flag == 2:
            tmp = dt_list_int[i] + time_input[i]
            while i == len(dt_list_int) - 1 and tmp > 12:
                tmp -= 12
                dt_list_int[i-1] += 1
        else:
            print("エラー")
            exit(1)
        ans.append(tmp)
    if ans[1] < 0:#年がマイナスになったとき
        ans[1] = abs(ans[1])
        flag2 = True
    if ans[1] >= 10000:#4桁までしか入らない
        print("一万の位を切り捨てます")
        while ans[1] >= 10000:
            ans[1] -= 10000
    dt_ans = dt_m.replace(year=ans[1], month=ans[0])
    return dt_ans, flag2

def get_wikipedia_events(month, day):
    url = "https://ja.wikipedia.org/w/api.php"

    params = {#リストの中に辞書を入れる
        "action": "parse",
        "page": "日本の記念日一覧",
        "format": "json",
        "prop": "text"
    }

    try:
        response = requests.get(url, params=params)#リクエストを送る
        response.raise_for_status()#エラーがあれば例外を発生させる

        data = response.json()
        html_content = data["parse"]["text"]["*"]

        # BeautifulSoupでHTML解析
        soup = BeautifulSoup(html_content, "html.parser")#html_contentを解析する
        # 月の見出しを探す
        events_section = soup.find("h2", id=f"{month}月")
        if events_section:
            # 見出しの次の<ul>タグを取得
            events_list = events_section.find_next("ul")
            if events_list:
                # リスト内のテキストを抽出
                if day < 10: target_date = f"0{day}日"#日付が1桁の場合は0を付ける
                else: target_date = f"{day}日"
                events = [li.get_text() for li in events_list.find_all("li")
                        if li.get_text().split()[0] == target_date
                        ]
                return events
            else:
                return ["月のリストが見つかりませんでした。"]
        else:
            return ["月のセクションが見つかりませんでした。"]
    except Exception as e:
        return [f"エラーが発生しました: {e}"]

if __name__ == "__main__":
    print("現在か過去か未来か決めてください")
    flag1 = input("[0]現在[1]過去[2]未来>")
    dt_ans, flag2= get_time(flag1)
    bc = ""
    if flag2:
        bc = "紀元前"
    dt_ans_md = []
    dt_ans_md = str(dt_ans.date()).split('-')
    month = int(dt_ans_md[1])
    day = int(dt_ans_md[2])
    events = get_wikipedia_events(month, day)
    for event in events:
        holiday = []
        holiday = event.split(' ')
        print(dt_ans.strftime(f"{bc}%Y年%m月%d日%H時%M分%a曜日"),f"- {holiday[2]}")
      
