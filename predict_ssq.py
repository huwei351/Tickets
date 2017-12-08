#-*- coding: UTF-8 -*-

import string
import mysql.connector
from bs4 import BeautifulSoup
import requests
import re
import sys
reload(sys)
sys.setdefaultencoding('utf8')

ELEMENT_GOLD = 'gold'
ELEMENT_WOOD = 'wood'
ELEMENT_WATER = 'water'
ELEMENT_FIRE = 'fire'
ELEMENT_EARTH = 'earth'

MYSQL_HOSTS = '127.0.0.1'
MYSQL_USER = 'root'
MYSQL_PASSWORD = 'huwei351'
MYSQL_PORT = '3306'
MYSQL_DB = 'ssq'

cnx = mysql.connector.connect(user = MYSQL_USER,password= MYSQL_PASSWORD,host =MYSQL_HOSTS,database=MYSQL_DB)
cur = cnx.cursor(buffered=True)

list1_num = {}
list1_elem = {}
list2_num = {}
list2_elem = {}
list3_num = {}
list3_elem = {}
list4_num = {}
list4_elem = {}
list5_num = {}
list5_elem = {}
list6_num = {}
list6_elem = {}
listx_num = {}
listx_elem = {}

def update_database(qid):
    res = -2
    url='http://kaijiang.zhcw.com/zhcw/html/ssq/list.html'
    html = requests.get(url) 
    content=BeautifulSoup(html.text, 'lxml')
    rows = content.findAll('tr')
    for row in rows:
        if re.search("em class", str(row)):
            columns = row.findAll('td')
            rid = re.findall(r'(\d+)', str(columns[1]))[0]
            date = str(columns[0])[19:29]
            balls = re.findall(r'(\d+)', str(columns[2]))
            rb1 = balls[1]
            rb2 = balls[2]
            rb3 = balls[3]
            rb4 = balls[4]
            rb5 = balls[5]
            rb6 = balls[6]
            bb = balls[7]
            dict = {'rid':rid, 'date':date, 'rb1':rb1, 'rb2':rb2, 'rb3':rb3, 'rb4':rb4, 'rb5':rb5, 'rb6':rb6, 'bb':bb}
            if (rid > bytes(qid)):
                print("rid=" + rid + ", date=" + date + ", rb1=" + rb1 + ", rb2=" + rb2 + ", rb3=" + rb3 + ", rb4=" + rb4 + ", rb5=" + rb5 + ", rb6=" + rb6 + ", bb=" + bb)
                save_result_into_database(dict)
                res = 0
    return res

def save_result_into_database(dict):
    date = dict['date']
    ret = select_title(date)
    if ret[0] ==1:
        print('result already exsisted')
    else:
        rid = dict['rid']
        rb1 = dict['rb1']
        rb2 = dict['rb2']
        rb3 = dict['rb3']
        rb4 = dict['rb4']
        rb5 = dict['rb5']
        rb6 = dict['rb6']
        bb = dict['bb']
        insert_ssq_result(rid,date,rb1,rb2,rb3,rb4,rb5,rb6,bb)
        print('starting save results')

def insert_ssq_result(rid,date,rb1,rb2,rb3,rb4,rb5,rb6,bb):
    sql = 'INSERT INTO ssq_result (`rid`,`date`,`rb1`,`rb2`,`rb3`,`rb4`,`rb5`,`rb6`,`bb`) VALUES (%(rid)s,%(date)s,%(rb1)s,%(rb2)s,%(rb3)s,%(rb4)s,%(rb5)s,%(rb6)s,%(bb)s)'
    value = {
        'rid':rid,
        'date':date,
        'rb1':rb1,
        'rb2':rb2,
        'rb3':rb3,
        'rb4':rb4,
        'rb5':rb5,
        'rb6':rb6,
        'bb':bb,
    }
    cur.execute(sql,value)
    cnx.commit()

def select_title(date):#这个是利用标题去重的，虽然按照区域划分应该不会重复，只是预防万一
    sql= 'SELECT EXISTS (SELECT 1 FROM ssq_result WHERE date = %(date)s)'
    value = {
        'date':date
    }
    cur.execute(sql,value)
    return  cur.fetchall()[0]

def select_result(rid):
    sql= 'SELECT * FROM ssq_result WHERE rid = %(rid)s'
    value = {
        'rid':rid
    }
    cur.execute(sql,value)
    return  cur.fetchone()

def select_local_latest_result():
    sql= 'SELECT * FROM ssq_result ORDER BY date DESC'
    cur.execute(sql)
    return  cur.fetchall()[0]

def select_redball_list(field,  rid):
    #select rid,rb1 from ssq_result where rid <= 2017001 order by date asc;
    sql= 'SELECT rid,' + field + ' FROM ssq_result WHERE rid <= %(rid)s ORDER BY date ASC'
    value = {
        'rid':rid
    }
    cur.execute(sql, value)
    return  cur.fetchall()

def get_win_level(presult, aresult):
    red = 0
    blue = 0
    level = 0
    if (presult[6] == aresult[6]):
        blue = 1
    for i in range(6):
        for j in range(6):
            if(presult[j] == aresult[i]):
                red += 1
                break
    if (blue == 1):
        if red == 6:
            level = 1
        elif red == 5:
            level = 3
        elif red == 4:
            level = 4
        elif red == 3:
            level = 5
        else:
            level = 6
    else:
        if red == 6:
            level = 2
        elif red == 5:
            level = 4
        elif red == 4:
            level = 5
    return level

def get_num_wuxing(num):
    if (num == 9 or num == 10 or num == 21 or num == 22 or num == 33):
        return ELEMENT_GOLD
    elif (num == 3 or num == 4 or num == 15 or num == 16 or num == 27 or num == 28):
        return ELEMENT_WOOD
    elif (num == 1 or num == 12 or num == 13 or num == 24 or num == 25):
        return ELEMENT_WATER
    elif (num == 6 or num == 7 or num == 18 or num == 19 or num == 30 or num == 31):
        return ELEMENT_FIRE
    elif (num == 2 or num == 5 or num == 8 or num == 11 or num == 14 or num == 17 or num == 20 or num == 23 or num == 26 or num == 29 or num == 32):
        return ELEMENT_EARTH
    else:
        return 'Invalid Number'

def predict_field(field, rid):
    global list1_num
    global list1_elem 
    global list2_num 
    global list2_elem 
    global list3_num 
    global list3_elem 
    global list4_num 
    global list4_elem 
    global list5_num 
    global list5_elem 
    global list6_num 
    global list6_elem
    global listx_num
    global listx_elem
    dict_num = {}
    dict_elem = {}
    r1_list_origin = select_redball_list(field, rid)
    r1_list = [line[1] for line in r1_list_origin]
    r1_list_len = len(r1_list)
    for j in range(r1_list_len-1):
        if (r1_list[j] == r1_list[r1_list_len-1]):
            dict_num.setdefault(r1_list[j+1], 0)
            dict_num[r1_list[j+1]] += 1
        if (get_num_wuxing(r1_list[j]) == get_num_wuxing(r1_list[r1_list_len-1])):
            dict_elem.setdefault(get_num_wuxing(r1_list[j+1]), 0)
            dict_elem[get_num_wuxing(r1_list[j+1])] += 1
    list1_num = dict_num.copy()
    list1_elem = dict_elem.copy()
    dict_num.clear()
    dict_elem.clear()
    print '连续1期相同：'
    print sorted(list1_num.items(), key=lambda x:x[1], reverse=True)
    print sorted(list1_elem.items(), key=lambda x:x[1], reverse=True)
    for j in range(r1_list_len-2):
        if (r1_list[j] == r1_list[r1_list_len-2] and r1_list[j+1] == r1_list[r1_list_len-1]):
            dict_num.setdefault(r1_list[j+2], 0)
            dict_num[r1_list[j+2]] += 1
        if (get_num_wuxing(r1_list[j]) == get_num_wuxing(r1_list[r1_list_len-2]) and get_num_wuxing(r1_list[j+1]) == get_num_wuxing(r1_list[r1_list_len-1])):
            dict_elem.setdefault(get_num_wuxing(r1_list[j+2]), 0)
            dict_elem[get_num_wuxing(r1_list[j+2])] += 1
    list2_num = dict_num.copy()
    list2_elem = dict_elem.copy()
    dict_num.clear()
    dict_elem.clear()
    print '连续2期相同：'
    print sorted(list2_num.items(), key=lambda x:x[1], reverse=True)
    print sorted(list2_elem.items(), key=lambda x:x[1], reverse=True)
    for j in range(r1_list_len-3):
        if (r1_list[j] == r1_list[r1_list_len-3] and r1_list[j+1] == r1_list[r1_list_len-2] and r1_list[j+2] == r1_list[r1_list_len-1]):
            dict_num.setdefault(r1_list[j+3], 0)
            dict_num[r1_list[j+3]] += 1
        if (get_num_wuxing(r1_list[j]) == get_num_wuxing(r1_list[r1_list_len-3]) and get_num_wuxing(r1_list[j+1]) == get_num_wuxing(r1_list[r1_list_len-2]) and \
            get_num_wuxing(r1_list[j+2]) == get_num_wuxing(r1_list[r1_list_len-1])):
            dict_elem.setdefault(get_num_wuxing(r1_list[j+3]), 0)
            dict_elem[get_num_wuxing(r1_list[j+3])] += 1
    list3_num = dict_num.copy()
    list3_elem = dict_elem.copy()
    dict_num.clear()
    dict_elem.clear()
    print '连续3期相同：'
    print sorted(list3_num.items(), key=lambda x:x[1], reverse=True)
    print sorted(list3_elem.items(), key=lambda x:x[1], reverse=True)
    for j in range(r1_list_len-4):
        if (r1_list[j] == r1_list[r1_list_len-4] and r1_list[j+1] == r1_list[r1_list_len-3] and r1_list[j+2] == r1_list[r1_list_len-2] and r1_list[j+3] == r1_list[r1_list_len-1]):
            dict_num.setdefault(r1_list[j+4], 0)
            dict_num[r1_list[j+4]] += 1
        if (get_num_wuxing(r1_list[j]) == get_num_wuxing(r1_list[r1_list_len-4]) and get_num_wuxing(r1_list[j+1]) == get_num_wuxing(r1_list[r1_list_len-3]) and \
            get_num_wuxing(r1_list[j+2]) == get_num_wuxing(r1_list[r1_list_len-2]) and get_num_wuxing(r1_list[j+3]) == get_num_wuxing(r1_list[r1_list_len-1])):
            dict_elem.setdefault(get_num_wuxing(r1_list[j+4]), 0)
            dict_elem[get_num_wuxing(r1_list[j+4])] += 1
    list4_num = dict_num.copy()
    list4_elem = dict_elem.copy()
    dict_num.clear()
    dict_elem.clear()
    print '连续4期相同：'
    print sorted(list4_num.items(), key=lambda x:x[1], reverse=True)
    print sorted(list4_elem.items(), key=lambda x:x[1], reverse=True)
    for j in range(r1_list_len-5):
        if (r1_list[j] == r1_list[r1_list_len-5] and r1_list[j+1] == r1_list[r1_list_len-4] and r1_list[j+2] == r1_list[r1_list_len-3] and r1_list[j+3] == r1_list[r1_list_len-2] and r1_list[j+4] == r1_list[r1_list_len-1]):
            dict_num.setdefault(r1_list[j+5], 0)
            dict_num[r1_list[j+5]] += 1
        if (get_num_wuxing(r1_list[j]) == get_num_wuxing(r1_list[r1_list_len-5]) and get_num_wuxing(r1_list[j+1]) == get_num_wuxing(r1_list[r1_list_len-4]) and \
            get_num_wuxing(r1_list[j+2]) == get_num_wuxing(r1_list[r1_list_len-3]) and get_num_wuxing(r1_list[j+3]) == get_num_wuxing(r1_list[r1_list_len-2]) and \
            get_num_wuxing(r1_list[j+4]) == get_num_wuxing(r1_list[r1_list_len-1])):
            dict_elem.setdefault(get_num_wuxing(r1_list[j+5]), 0)
            dict_elem[get_num_wuxing(r1_list[j+5])] += 1
    list5_num = dict_num.copy()
    list5_elem = dict_elem.copy()
    dict_num.clear()
    dict_elem.clear()
    print '连续5期相同：'
    print sorted(list5_num.items(), key=lambda x:x[1], reverse=True)
    print sorted(list5_elem.items(), key=lambda x:x[1], reverse=True)
    for j in range(r1_list_len-6):
        if (r1_list[j] == r1_list[r1_list_len-6] and r1_list[j+1] == r1_list[r1_list_len-5] and r1_list[j+2] == r1_list[r1_list_len-4] and \
            r1_list[j+3] == r1_list[r1_list_len-3] and r1_list[j+4] == r1_list[r1_list_len-2] and r1_list[j+5] == r1_list[r1_list_len-1]):
            dict_num.setdefault(r1_list[j+6], 0)
            dict_num[r1_list[j+6]] += 1
        if (get_num_wuxing(r1_list[j]) == get_num_wuxing(r1_list[r1_list_len-6]) and get_num_wuxing(r1_list[j+1]) == get_num_wuxing(r1_list[r1_list_len-5]) and \
            get_num_wuxing(r1_list[j+2]) == get_num_wuxing(r1_list[r1_list_len-4]) and get_num_wuxing(r1_list[j+3]) == get_num_wuxing(r1_list[r1_list_len-3]) and \
            get_num_wuxing(r1_list[j+4]) == get_num_wuxing(r1_list[r1_list_len-2]) and get_num_wuxing(r1_list[j+5]) == get_num_wuxing(r1_list[r1_list_len-1])):
            dict_elem.setdefault(get_num_wuxing(r1_list[j+6]), 0)
            dict_elem[get_num_wuxing(r1_list[j+6])] += 1
    list6_num = dict_num.copy()
    list6_elem = dict_elem.copy()
    dict_num.clear()
    dict_elem.clear()
    print '连续6期相同：'
    print sorted(list6_num.items(), key=lambda x:x[1], reverse=True)
    print sorted(list6_elem.items(), key=lambda x:x[1], reverse=True)
    for num in list1_num.keys():
        count = 0
        for j in range(len(r1_list), 0, -1):
            if (r1_list[j-1] == num):
                break;
            else:
                count += 1
        dict_num[num] = count
    for elem in list1_elem.keys():
        count = 0
        for j in range(len(r1_list), 0, -1):
            if (get_num_wuxing(r1_list[j-1]) == elem):
                break;
            else:
                count += 1
        dict_elem[elem] = count
    listx_num = dict_num.copy()
    listx_elem = dict_elem.copy()
    dict_num.clear()
    dict_elem.clear()
    print '数字/五行遗漏期数：'
    print listx_num.items()
    print sorted(listx_elem.items(), key=lambda x:x[1], reverse=True)

def predict_result(qid):
    aresult = list(select_result(qid)[3:])
    print("第" + bytes(qid) + "开奖结果为：")
    print(aresult)
    print("第" + bytes(qid+1) + "期红1预测为：")
    predict_field('rb1', qid)
    print("第" + bytes(qid+1) + "期红2预测为：")
    predict_field('rb2', qid)
    print("第" + bytes(qid+1) + "期红3预测为：")
    predict_field('rb3', qid)
    print("第" + bytes(qid+1) + "期红4预测为：")
    predict_field('rb4', qid)
    print("第" + bytes(qid+1) + "期红5预测为：")
    predict_field('rb5', qid)
    print("第" + bytes(qid+1) + "期红6预测为：")
    predict_field('rb6', qid)
    print("第" + bytes(qid+1) + "期蓝预测为：")
    predict_field('bb', qid)

def clear_list_num_elem():
    global list1_num
    global list1_elem 
    global list2_num 
    global list2_elem 
    global list3_num 
    global list3_elem 
    global list4_num 
    global list4_elem 
    global list5_num 
    global list5_elem 
    global list6_num 
    global list6_elem
    global listx_num
    global listx_elem
    list1_num.clear()
    list1_elem.clear()
    list2_num.clear()
    list2_elem.clear()
    list3_num.clear()
    list3_elem.clear()
    list4_num.clear()
    list4_elem.clear()
    list5_num.clear()
    list5_elem.clear()
    list6_num.clear()
    list6_elem.clear()
    listx_num.clear()
    listx_elem.clear()

def predict_result2(qid):
    global list1_num
    global list1_elem 
    global list2_num 
    global list2_elem 
    global list3_num 
    global list3_elem 
    global list4_num 
    global list4_elem 
    global list5_num 
    global list5_elem 
    global list6_num 
    global list6_elem
    aresult = list(select_result(qid)[3:])
    print("第" + bytes(qid) + "开奖结果为：")
    print(aresult)
    tlist = []
    result_list = []
    for i in range(1, 8):
        tup = ()
        if (i < 7):
            field = 'rb' + bytes(i)
            field_name = '红' + bytes(i)
        else:
            field = 'bb'
            field_name = '蓝'
        print ('******************** ' + field_name + '预测为：********************')
        predict_field(field, qid)
        if (len(list6_elem) > 0):
            if (len(list6_num) > 0):
                for elem in list6_elem.keys():
                    for num in list6_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            if(len(list5_num) > 0):
                for elem in list6_elem.keys():
                    for num in list5_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()                    
                    continue
            if(len(list4_num) > 0):
                for elem in list6_elem.keys():
                    for num in list4_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()                   
                    continue
            if(len(list3_num) > 0):
                for elem in list6_elem.keys():
                    for num in list3_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            if(len(list2_num) > 0):
                for elem in list6_elem.keys():
                    for num in list2_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            for elem in list6_elem.keys():
                for num in list1_num.keys():
                    if (get_num_wuxing(num) == elem):
                        tup += (num,)
            tlist += [tup]
            clear_list_num_elem()
            continue;
        elif (len(list5_elem) > 0):
            if(len(list5_num) > 0):
                for elem in list5_elem.keys():
                    for num in list5_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            if(len(list4_num) > 0):
                for elem in list5_elem.keys():
                    for num in list4_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            if(len(list3_num) > 0):
                for elem in list5_elem.keys():
                    for num in list3_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            if(len(list2_num) > 0):
                for elem in list5_elem.keys():
                    for num in list2_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            for elem in list5_elem.keys():
                for num in list1_num.keys():
                    if (get_num_wuxing(num) == elem):
                        tup += (num,)
            tlist += [tup]
            clear_list_num_elem()
            continue
        elif (len(list4_elem) > 0):
            if(len(list4_num) > 0):
                for elem in list4_elem.keys():
                    for num in list4_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            if(len(list3_num) > 0):
                for elem in list4_elem.keys():
                    for num in list3_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            if(len(list2_num) > 0):
                for elem in list4_elem.keys():
                    for num in list2_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            for elem in list4_elem.keys():
                for num in list1_num.keys():
                    if (get_num_wuxing(num) == elem):
                        tup += (num,)
            tlist += [tup]
            clear_list_num_elem()
            continue
        elif (len(list3_elem) > 0):
            if(len(list3_num) > 0):
                for elem in list3_elem.keys():
                    for num in list3_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            if(len(list2_num) > 0):
                for elem in list3_elem.keys():
                    for num in list2_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            for elem in list3_elem.keys():
                for num in list1_num.keys():
                    if (get_num_wuxing(num) == elem):
                        tup += (num,)
            tlist += [tup]
            clear_list_num_elem()
            continue
        elif (len(list2_elem) > 0):
            if(len(list2_num) > 0):
                for elem in list2_elem.keys():
                    for num in list2_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                if (len(tup) > 0):
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            for elem in list2_elem.keys():
                for num in list1_num.keys():
                    if (get_num_wuxing(num) == elem):
                        tup += (num,)
            tlist += [tup]
            clear_list_num_elem()
            continue
        elif (len(list1_elem) > 0):
                for elem in list1_elem.keys():
                    for num in list1_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                tlist += [tup]
                clear_list_num_elem()
                continue
        else:
            print 'No same number and elememt'
    print("第" + bytes(qid+1) + "预测为：")
    print tlist
    if (len(tlist) == 7):
        for r1 in tlist[0]:
            for r2 in tlist[1]:
                for r3 in tlist[2]:
                    for r4 in tlist[3]:
                        for r5 in tlist[4]:
                            for r6 in tlist[5]:
                                for bb in tlist[6]:
                                    if (r1 < r2 and r2 < r3 and r3 < r4 and r4 < r5 and r5 < r6):
                                        result_list += [(r1, r2, r3, r4, r5, r6, bb)]
    for i in range(len(result_list)):
        print "[" + bytes(i+1) + "]:", result_list[i]

def calc_predict_result_accuracy(qid):
    global list1_num
    global list1_elem 
    global list2_num 
    global list2_elem 
    global list3_num 
    global list3_elem 
    global list4_num 
    global list4_elem 
    global list5_num 
    global list5_elem 
    global list6_num 
    global list6_elem
    total_incom = 0
    total_cost = 0
    total_gain = 0
    total_level_one = 0
    total_level_two = 0
    total_level_three = 0
    total_level_four = 0
    total_level_five = 0
    total_level_six = 0
    latest_rid = select_local_latest_result()[1]
    for q in range(qid, latest_rid):
        aresult = list(select_result(q)[3:])
        print("第" + bytes(q) + "开奖结果为：")
        print(aresult)
        tlist = []
        result_list = []
        for i in range(1, 8):
            tup = ()
            if (i < 7):
                field = 'rb' + bytes(i)
                field_name = '红' + bytes(i)
            else:
                field = 'bb'
                field_name = '蓝'
            print (field_name + '预测为：')
            predict_field(field, q)
            if (len(list6_elem) > 0):
                if (len(list6_num) > 0):
                    for elem in list6_elem.keys():
                        for num in list6_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                if(len(list5_num) > 0):
                    for elem in list6_elem.keys():
                        for num in list5_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()                    
                        continue
                if(len(list4_num) > 0):
                    for elem in list6_elem.keys():
                        for num in list4_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()                   
                        continue
                if(len(list3_num) > 0):
                    for elem in list6_elem.keys():
                        for num in list3_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                if(len(list2_num) > 0):
                    for elem in list6_elem.keys():
                        for num in list2_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                for elem in list6_elem.keys():
                    for num in list1_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                tlist += [tup]
                clear_list_num_elem()
                continue;
            elif (len(list5_elem) > 0):
                if(len(list5_num) > 0):
                    for elem in list5_elem.keys():
                        for num in list5_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                if(len(list4_num) > 0):
                    for elem in list5_elem.keys():
                        for num in list4_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                if(len(list3_num) > 0):
                    for elem in list5_elem.keys():
                        for num in list3_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                if(len(list2_num) > 0):
                    for elem in list5_elem.keys():
                        for num in list2_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                for elem in list5_elem.keys():
                    for num in list1_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                tlist += [tup]
                clear_list_num_elem()
                continue
            elif (len(list4_elem) > 0):
                if(len(list4_num) > 0):
                    for elem in list4_elem.keys():
                        for num in list4_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                if(len(list3_num) > 0):
                    for elem in list4_elem.keys():
                        for num in list3_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                if(len(list2_num) > 0):
                    for elem in list4_elem.keys():
                        for num in list2_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                for elem in list4_elem.keys():
                    for num in list1_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                tlist += [tup]
                clear_list_num_elem()
                continue
            elif (len(list3_elem) > 0):
                if(len(list3_num) > 0):
                    for elem in list3_elem.keys():
                        for num in list3_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                if(len(list2_num) > 0):
                    for elem in list3_elem.keys():
                        for num in list2_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                for elem in list3_elem.keys():
                    for num in list1_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                tlist += [tup]
                clear_list_num_elem()
                continue
            elif (len(list2_elem) > 0):
                if(len(list2_num) > 0):
                    for elem in list2_elem.keys():
                        for num in list2_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    if (len(tup) > 0):
                        tlist += [tup]
                        clear_list_num_elem()
                        continue
                for elem in list2_elem.keys():
                    for num in list1_num.keys():
                        if (get_num_wuxing(num) == elem):
                            tup += (num,)
                tlist += [tup]
                clear_list_num_elem()
                continue
            elif (len(list1_elem) > 0):
                    for elem in list1_elem.keys():
                        for num in list1_num.keys():
                            if (get_num_wuxing(num) == elem):
                                tup += (num,)
                    tlist += [tup]
                    clear_list_num_elem()
                    continue
            else:
                print 'No same number and elememt'
        print tlist
        if (len(tlist) == 7):
            for r1 in tlist[0]:
                for r2 in tlist[1]:
                    for r3 in tlist[2]:
                        for r4 in tlist[3]:
                            for r5 in tlist[4]:
                                for r6 in tlist[5]:
                                    for bb in tlist[6]:
                                        if (r1 < r2 and r2 < r3 and r3 < r4 and r4 < r5 and r5 < r6):
                                            result_list += [(r1, r2, r3, r4, r5, r6, bb)]
        print 'predict result list, length = ' + bytes(len(result_list))
        print result_list
        actual_result = list(select_result(q+1)[3:])
        print("第" + bytes(q+1) + "开奖结果为：")
        print actual_result
        level_one = 0
        level_two = 0
        level_three = 0
        level_four = 0
        level_five = 0
        level_six = 0
        for li in result_list:
            print li
            level = get_win_level(list(li), actual_result)
            if (level == 1):
                level_one += 1
            elif (level == 2):
                level_two += 1 
            elif (level == 3):
                level_three += 1
            elif (level == 4):
                level_four += 1
            elif (level == 5):
                level_five += 1
            elif (level == 6):
                level_six += 1
        print("一等奖" + bytes(level_one) + "注")
        print("二等奖" + bytes(level_two) + "注")
        print("三等奖" + bytes(level_three) + "注")
        print("四等奖" + bytes(level_four) + "注")
        print("五等奖" + bytes(level_five) + "注")
        print("六等奖" + bytes(level_six) + "注")
        income = level_one*5000000*0.8 + level_two*250000*0.8 + level_three*3000 + level_four*200 + level_five*10 + level_six*5
        cost = len(result_list)*2
        gain = income-len(result_list)*2
        print("总共投注" + bytes(len(result_list)) + "注, 共花费" + bytes(cost) + "元")
        print("中奖总金额" + bytes(income) + "元， 净利润" + bytes(gain) + "元")
        total_level_one += level_one 
        total_level_two += level_two
        total_level_three += level_three
        total_level_four += level_four
        total_level_five += level_five
        total_level_six += level_six
        total_incom += income
        total_cost += cost
        total_gain += gain
    print("[汇总] : 总共" + "一等奖" + bytes(total_level_one) + "注, " + "二等奖" + bytes(total_level_two) + "注, " + "三等奖" + bytes(total_level_three) + "注, "\
        + "四等奖" + bytes(total_level_four) + "注, " + "五等奖" + bytes(total_level_five) + "注, " + "六等奖" + bytes(total_level_six) + "注")
    print('[汇总] : 总共花费' + bytes(total_cost) + '元, 总中奖总金额' + bytes(total_incom) + '元， 净利润' + bytes(total_gain) + '元')

def calc_predict_result_accuracy2(qid):
    global list1_num
    global list1_elem 
    global list2_num 
    global list2_elem 
    global list3_num 
    global list3_elem 
    global list4_num 
    global list4_elem 
    global list5_num 
    global list5_elem 
    global list6_num 
    global list6_elem
    total_count_list = []
    total_incom = 0
    total_cost = 0
    total_gain = 0
    total_level_one = 0
    total_level_two = 0
    total_level_three = 0
    total_level_four = 0
    total_level_five = 0
    total_level_six = 0
    latest_rid = select_local_latest_result()[1]
    for q in range(qid, latest_rid):
        aresult = list(select_result(q)[3:])
        print("第" + bytes(q) + "开奖结果为：")
        print(aresult)
        tlist = []
        result_list = []
        for i in range(1, 8):
            tup = ()
            if (i < 7):
                field = 'rb' + bytes(i)
                field_name = '红' + bytes(i)
            else:
                field = 'bb'
                field_name = '蓝'
            print (field_name + '预测为：')
            predict_field(field, q)
            list1_elem_items = sorted(list1_elem.items(), key=lambda x:x[1], reverse=True)
            list2_elem_items = sorted(list2_elem.items(), key=lambda x:x[1], reverse=True)
            list3_elem_items = sorted(list3_elem.items(), key=lambda x:x[1], reverse=True)
            list4_elem_items = sorted(list4_elem.items(), key=lambda x:x[1], reverse=True)
            list5_elem_items = sorted(list5_elem.items(), key=lambda x:x[1], reverse=True)
            list6_elem_items = sorted(list6_elem.items(), key=lambda x:x[1], reverse=True)
            print "list1_elem_items:", list1_elem_items
            print "list2_elem_items:", list2_elem_items
            print "list3_elem_items:", list3_elem_items
            print "list4_elem_items:", list4_elem_items
            print "list5_elem_items:", list5_elem_items
            print "list6_elem_items:", list6_elem_items
#            if (len(list6_elem_items) > 0):
#                tup = (list6_elem_items[0][0],)
#                tlist += [tup]
#                continue
#            elif (len(list5_elem_items) > 0):
#                tup = (list5_elem_items[0][0],)
#                tlist += [tup]
#                continue
#            elif (len(list4_elem_items) > 0):
#                tup = (list4_elem_items[0][0],)
#                tlist += [tup]
#                continue
#            elif (len(list3_elem_items) > 0):
#                tup = (list3_elem_items[0][0],)
#                tlist += [tup]
#                continue
#            elif (len(list2_elem_items) > 0):
#                tup = (list2_elem_items[0][0],)
#                tlist += [tup]
#                continue
#            else:
            tup = (list1_elem_items[0][0],list1_elem_items[1][0],list1_elem_items[2][0])
            tlist += [tup]
#            continue
        print tlist
        actual_result = list(select_result(q+1)[3:])
        #print("第" + bytes(q+1) + "开奖结果为：")
        #print actual_result
        count = 0
        for i in range(6):
            if (tlist[i][0] == get_num_wuxing(actual_result[i]) or tlist[i][1] == get_num_wuxing(actual_result[i]) or tlist[i][2] == get_num_wuxing(actual_result[i])):
                count += 1
        total_count_list += [count]
    print('[汇总] : 总共参与' + bytes(latest_rid-qid) + '期, 6球五行全中' + bytes(total_count_list.count(6)) + '期, 占比' + bytes(float(total_count_list.count(6))/(latest_rid-qid)*100) + '%'\
        + ', 5球五行全中' + bytes(total_count_list.count(5)) + '期, 占比' + bytes(float(total_count_list.count(5))/(latest_rid-qid)*100) + '%'\
        + ', 4球五行全中' + bytes(total_count_list.count(4)) + '期, 占比' + bytes(float(total_count_list.count(4))/(latest_rid-qid)*100) + '%'\
        + ', 3球五行全中' + bytes(total_count_list.count(3)) + '期, 占比' + bytes(float(total_count_list.count(3))/(latest_rid-qid)*100) + '%'\
        + ', 2球五行全中' + bytes(total_count_list.count(2)) + '期, 占比' + bytes(float(total_count_list.count(2))/(latest_rid-qid)*100) + '%'\
        + ', 1球五行全中' + bytes(total_count_list.count(1)) + '期, 占比' + bytes(float(total_count_list.count(1))/(latest_rid-qid)*100) + '%'\
        + ', 0球五行全中' + bytes(total_count_list.count(0)) + '期, 占比' + bytes(float(total_count_list.count(0))/(latest_rid-qid)*100) + '%')
    print total_count_list.index(6)

def calc_predict_result_accuracy3(qid):
    global list1_num
    global list1_elem 
    global list2_num 
    global list2_elem 
    global list3_num 
    global list3_elem 
    global list4_num 
    global list4_elem 
    global list5_num 
    global list5_elem 
    global list6_num 
    global list6_elem
    total_count = 0
    latest_rid = select_local_latest_result()[1]
    for q in range(qid, latest_rid):
        aresult = list(select_result(q)[3:])
        print("第" + bytes(q) + "开奖结果为：")
        print(aresult)
        tlist = []
        result_list = []
        tup = ()
        field = 'rb2'
        field_name = '红2'
        #field = 'bb'
        #field_name = '蓝'
        print (field_name + '预测为：')
        predict_field(field, q)
        list1_elem_items = sorted(list1_elem.items(), key=lambda x:x[1], reverse=True)
        list2_elem_items = sorted(list2_elem.items(), key=lambda x:x[1], reverse=True)
        list3_elem_items = sorted(list3_elem.items(), key=lambda x:x[1], reverse=True)
        list4_elem_items = sorted(list4_elem.items(), key=lambda x:x[1], reverse=True)
        list5_elem_items = sorted(list5_elem.items(), key=lambda x:x[1], reverse=True)
        list6_elem_items = sorted(list6_elem.items(), key=lambda x:x[1], reverse=True)
        print "list1_elem_items:", list1_elem_items
        print "list2_elem_items:", list2_elem_items
        print "list3_elem_items:", list3_elem_items
        print "list4_elem_items:", list4_elem_items
        print "list5_elem_items:", list5_elem_items
        print "list6_elem_items:", list6_elem_items
        if (len(list6_elem_items) > 0):
            tup = (list6_elem_items[0][0],)
        elif (len(list5_elem_items) > 0):
            tup = (list5_elem_items[0][0],)
        elif (len(list4_elem_items) > 0):
            tup = (list4_elem_items[0][0],)
        elif (len(list3_elem_items) > 0):
            tup = (list3_elem_items[0][0],)
        elif (len(list2_elem_items) > 0):
            tup = (list2_elem_items[0][0],)
        else:
            tup = (list1_elem_items[0][0],)
        actual_result = list(select_result(q+1)[3:])
        if (tup[0] == get_num_wuxing(actual_result[0])):
            total_count += 1
    print('[汇总] : 总共参与' + bytes(latest_rid-qid) + '期, 五行中' + bytes(total_count) + '期, 占比' + bytes(float(total_count)/(latest_rid-qid)*100) + '%')

def calc_predict_result_accuracy4(qid):
    total_incom = 0
    total_cost = 0
    total_gain = 0
    total_level_one = 0
    total_level_two = 0
    total_level_three = 0
    total_level_four = 0
    total_level_five = 0
    total_level_six = 0
    latest_rid = select_local_latest_result()[1]
    for q in range(qid, latest_rid):
        print("第" + bytes(q) + "期统计及预测为：")
        ball_list = []
        for i in range(1, 8):
            if (i < 7):
                field = 'rb' + bytes(i)
                field_name = '红' + bytes(i)
            else:
                field = 'bb'
                field_name = '蓝'
            print (field_name + '统计为：')
            num_list = select_redball_list(field, qid)
            num_list = [line[1] for line in num_list]
            elem_list = [get_num_wuxing(num) for num in num_list]
            temp = []
            temp_new = []
            num_count_list = []
            num_top_count = 0
            elem_top_count = 0
            for i in range(min(num_list), max(num_list)+1): 
                num_count_list += [(i, num_list.count(i))]
            print 'num_count_list:', num_count_list
            sorted_num_count_list = sorted(num_count_list, key=lambda x:x[1], reverse=True)
            print 'sorted_num_count_list', sorted_num_count_list
            for i in range(len(sorted_num_count_list)):
                num_top_count += sorted_num_count_list[i][1]
                temp += [sorted_num_count_list[i][0]]
                if (float(num_top_count)/len(num_list) >= 0.9):
                    print 'Top ' + bytes(i+1) + ' numbers count probility >= 90%'
                    break
            elem_count_list = [(ELEMENT_GOLD, elem_list.count(ELEMENT_GOLD)),(ELEMENT_WOOD, elem_list.count(ELEMENT_WOOD)),(ELEMENT_WATER, elem_list.count(ELEMENT_WATER)),\
            (ELEMENT_FIRE, elem_list.count(ELEMENT_FIRE)),(ELEMENT_EARTH, elem_list.count(ELEMENT_EARTH))]
            elem_count_list = sorted(elem_count_list, key=lambda x:x[1], reverse=True)
            print 'elem_count_list:', elem_count_list
            for i in range(3):
                elem_top_count += elem_count_list[i][1]
            print 'Top 3 elememts count probility = ' + bytes(float(elem_top_count)/len(elem_list)*100) + '%'
            print 'temp before del:', temp
            for i in range(len(temp)):
                if (get_num_wuxing(temp[i]) == elem_count_list[0][0] or get_num_wuxing(temp[i]) == elem_count_list[1][0] or get_num_wuxing(temp[i]) == elem_count_list[2][0]):
                    temp_new += [temp[i]]
            print 'temp after del:', temp_new
            ball_list += [temp_new]
        print 'ball_list:', ball_list
        result_list = []
        if (len(ball_list) == 7):
            for r1 in ball_list[0]:
                for r2 in ball_list[1]:
                    for r3 in ball_list[2]:
                        for r4 in ball_list[3]:
                            for r5 in ball_list[4]:
                                for r6 in ball_list[5]:
                                    for bb in ball_list[6]:
                                        if (r1 < r2 and r2 < r3 and r3 < r4 and r4 < r5 and r5 < r6):
                                            result_list += [(r1, r2, r3, r4, r5, r6, bb)]
        print 'predict result list, length = ' + bytes(len(result_list))
        #print result_list
        actual_result = list(select_result(q+1)[3:])
        print("第" + bytes(q+1) + "开奖结果为：")
        print actual_result
        level_one = 0
        level_two = 0
        level_three = 0
        level_four = 0
        level_five = 0
        level_six = 0
        for li in result_list:
            #print li
            level = get_win_level(list(li), actual_result)
            if (level == 1):
                level_one += 1
            elif (level == 2):
                level_two += 1 
            elif (level == 3):
                level_three += 1
            elif (level == 4):
                level_four += 1
            elif (level == 5):
                level_five += 1
            elif (level == 6):
                level_six += 1
        print("一等奖" + bytes(level_one) + "注")
        print("二等奖" + bytes(level_two) + "注")
        print("三等奖" + bytes(level_three) + "注")
        print("四等奖" + bytes(level_four) + "注")
        print("五等奖" + bytes(level_five) + "注")
        print("六等奖" + bytes(level_six) + "注")
        income = level_one*5000000*0.8 + level_two*250000*0.8 + level_three*3000 + level_four*200 + level_five*10 + level_six*5
        cost = len(result_list)*2
        gain = income-len(result_list)*2
        print("总共投注" + bytes(len(result_list)) + "注, 共花费" + bytes(cost) + "元")
        print("中奖总金额" + bytes(income) + "元， 净利润" + bytes(gain) + "元")
        total_level_one += level_one 
        total_level_two += level_two
        total_level_three += level_three
        total_level_four += level_four
        total_level_five += level_five
        total_level_six += level_six
        total_incom += income
        total_cost += cost
        total_gain += gain
    print("[汇总] : 总共" + "一等奖" + bytes(total_level_one) + "注, " + "二等奖" + bytes(total_level_two) + "注, " + "三等奖" + bytes(total_level_three) + "注, "\
        + "四等奖" + bytes(total_level_four) + "注, " + "五等奖" + bytes(total_level_five) + "注, " + "六等奖" + bytes(total_level_six) + "注")
    print('[汇总] : 总共花费' + bytes(total_cost) + '元, 总中奖总金额' + bytes(total_incom) + '元， 净利润' + bytes(total_gain) + '元')

def calc_predict_result_accuracy5(qid):
    global list1_num
    global list1_elem 
    global list2_num 
    global list2_elem 
    global list3_num 
    global list3_elem 
    global list4_num 
    global list4_elem 
    global list5_num 
    global list5_elem 
    global list6_num 
    global list6_elem
    global listx_num
    global listx_elem
    total_count_list = []
    total_incom = 0
    total_cost = 0
    total_gain = 0
    total_level_one = 0
    total_level_two = 0
    total_level_three = 0
    total_level_four = 0
    total_level_five = 0
    total_level_six = 0
    latest_rid = select_local_latest_result()[1]
    for q in range(qid, latest_rid):
        aresult = list(select_result(q)[3:])
        print("第" + bytes(q) + "开奖结果为：")
        print(aresult)
        tlist = []
        result_list = []
        for i in range(7, 8):
            tup = ()
            if (i < 7):
                field = 'rb' + bytes(i)
                field_name = '红' + bytes(i)
            else:
                field = 'bb'
                field_name = '蓝'
            print (field_name + '预测为：')
            predict_field(field, q)
            list1_elem_items = sorted(list1_elem.items(), key=lambda x:x[1], reverse=True)
            list2_elem_items = sorted(list2_elem.items(), key=lambda x:x[1], reverse=True)
            list3_elem_items = sorted(list3_elem.items(), key=lambda x:x[1], reverse=True)
            list4_elem_items = sorted(list4_elem.items(), key=lambda x:x[1], reverse=True)
            list5_elem_items = sorted(list5_elem.items(), key=lambda x:x[1], reverse=True)
            list6_elem_items = sorted(list6_elem.items(), key=lambda x:x[1], reverse=True)
            listx_elem_items = sorted(listx_elem.items(), key=lambda x:x[1], reverse=True)
            print "list1_elem_items:", list1_elem_items
            print "list2_elem_items:", list2_elem_items
            print "list3_elem_items:", list3_elem_items
            print "list4_elem_items:", list4_elem_items
            print "list5_elem_items:", list5_elem_items
            print "list6_elem_items:", list6_elem_items
            print "listx_elem_items:", listx_elem_items
            tup = (list1_elem_items[1][0],)
            tlist += [tup]
        print tlist
        actual_result = list(select_result(q+1)[3:])
        #print("第" + bytes(q+1) + "开奖结果为：")
        #print actual_result
        count = 0
        for i in range(1):
            if (tlist[i][0] == get_num_wuxing(actual_result[i])):
                count += 1
        total_count_list += [count]
    print('[汇总] : 总共参与' + bytes(latest_rid-qid) + '期, 6球五行全中' + bytes(total_count_list.count(6)) + '期, 占比' + bytes(float(total_count_list.count(6))/(latest_rid-qid)*100) + '%'\
        + ', 5球五行全中' + bytes(total_count_list.count(5)) + '期, 占比' + bytes(float(total_count_list.count(5))/(latest_rid-qid)*100) + '%'\
        + ', 4球五行全中' + bytes(total_count_list.count(4)) + '期, 占比' + bytes(float(total_count_list.count(4))/(latest_rid-qid)*100) + '%'\
        + ', 3球五行全中' + bytes(total_count_list.count(3)) + '期, 占比' + bytes(float(total_count_list.count(3))/(latest_rid-qid)*100) + '%'\
        + ', 2球五行全中' + bytes(total_count_list.count(2)) + '期, 占比' + bytes(float(total_count_list.count(2))/(latest_rid-qid)*100) + '%'\
        + ', 1球五行全中' + bytes(total_count_list.count(1)) + '期, 占比' + bytes(float(total_count_list.count(1))/(latest_rid-qid)*100) + '%'\
        + ', 0球五行全中' + bytes(total_count_list.count(0)) + '期, 占比' + bytes(float(total_count_list.count(0))/(latest_rid-qid)*100) + '%')

def calculate_income(qid,full):
    aresult = list(select_result(qid)[3:])
    print("第" + bytes(qid) + "开奖结果为：")
    print(aresult)
    if full:
        filename = "./ssq_results/" + bytes(qid) + "-predict-full.txt"
    else:
        filename = "./ssq_results/" + bytes(qid) + "-predict.txt"
    print("filename = " + filename)
    file = open(filename, 'r')
    linesList = file.readlines()
    linesList = [line.strip().split(',') for line in linesList]
    file.close()
    level_one = []
    level_two = []
    level_three = []
    level_four = []
    level_five = []
    level_six = []
    for i in range(len(linesList)):
        temp = linesList[i][5].strip().split('+')
        linesList[i][5] = temp[0]
        linesList[i] += [temp[1]]
        presult = [string.atoi(line) for line in linesList[i]]
        level = get_win_level(presult, aresult)
        if (level == 1):
            level_one += [i + 1]
        elif (level == 2):
            level_two += [i + 1] 
        elif (level == 3):
            level_three += [i + 1]
        elif (level == 4):
            level_four += [i + 1]
        elif (level == 5):
            level_five += [i + 1]
        elif (level == 6):
            level_six += [i + 1]
    print("一等奖" + bytes(len(level_one)) + "注")
    print(level_one)
    print("二等奖" + bytes(len(level_two)) + "注")
    print(level_two)
    print("三等奖" + bytes(len(level_three)) + "注")
    print(level_three)
    print("四等奖" + bytes(len(level_four)) + "注")
    print(level_four)
    print("五等奖" + bytes(len(level_five)) + "注")
    print(level_five)
    print("六等奖" + bytes(len(level_six)) + "注")
    print(level_six)
    income = (len(level_one)*5000000 + len(level_two)*250000)*0.8 + len(level_three)*3000 + len(level_four)*200 + len(level_five)*10 + len(level_six)*5
    print("总共投注" + bytes(len(linesList)) + "注, 共花费" + bytes(len(linesList)*2) + "元")
    print("中奖总金额" + bytes(income) + "元， 净利润" + bytes(income-len(linesList)*2) + "元")
    return 0

latest_rid = select_local_latest_result()[1]
update_database(latest_rid)
latest_rid = select_local_latest_result()[1]
#calculate_income(latest_rid, 1)
#predict_result(latest_rid)
predict_result2(latest_rid)
#calc_predict_result_accuracy(2017100)
#calc_predict_result_accuracy2(2017001)
#calc_predict_result_accuracy3(2017001)
#calc_predict_result_accuracy4(2017001)
#calc_predict_result_accuracy5(2017001)